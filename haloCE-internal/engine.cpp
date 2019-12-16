#include "pch.h"
#include "engine.h"

using namespace addr;

int8_t MAGIC_DATAPOOLHEADER[] = {/* 0x00, 0x08, 0x0C, 0x00, 0x01, 0x00, 0x00, 0x00,*/ 0x40, 0x74, 0x40, 0x64 };

//relative to window, not desktop
RECT halo_engine::window_client_rect() {
	if (haloHWND) {
		RECT outRect;
		if (GetClientRect(haloHWND, &outRect)) {
			return outRect;
		}
	}
	return RECT();
}

halo_engine::halo_engine()
{
	// Scan memory for object pools
	uint32_t data_pool_size = 0x1B40000;

	for (uint32_t i = 0; i < data_pool_size / 4; i++) {
		if (memcmp(&MAGIC_DATAPOOLHEADER, &(RUNTIME_DATA_BEGIN[i]), sizeof(MAGIC_DATAPOOLHEADER)) == 0) {
			DataPool* pool = (DataPool*)(&RUNTIME_DATA_BEGIN[i] - 10);
			dataPools.push_back(pool);

			if (std::string(pool->Name) == "object") {
				objectDataPool = pool;
			}
		}
	}
	haloHWND = FindWindowA(FALSE, "Halo");
}

void halo_engine::get_snapshot(engine_snapshot& snapshot)
{
	if (objectDataPool != nullptr)
	{
		int count = objectDataPool->ObjectCount;
		for (int i = 0; i < count; i++) {
			uint32_t* basePtr = (uint32_t*)&objectDataPool->ObjectPointers[i];

			if ((int)*basePtr == 0) {
				continue;
			}
			if ((int)*basePtr < 0x40000000 || (int)*basePtr > 0x41B40000) {
				continue;
			}

			GameObject* object = (GameObject*)(*basePtr - 24); // Backtrack 24 bytes from the pointed to location
			snapshot.gameObjects.push_back(object);
		}
	}
}

//guess this is write process memory
void halo_engine::patch_memory(LPVOID dest_address, uint8_t* src_address, size_t patch_size)
{
	unsigned long old_protection, unused;
	//give that address read and write permissions and store the old permissions at oldProtection
	VirtualProtect(dest_address, patch_size, PAGE_EXECUTE_READWRITE, &old_protection);

	//write the memory into the program and overwrite previous value
	std::copy_n(src_address, patch_size, static_cast<uint8_t*>(dest_address));

	//reset the permissions of the address back to oldProtection after writting memory
	VirtualProtect(dest_address, patch_size, old_protection, &unused);
}