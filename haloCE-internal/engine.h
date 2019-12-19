#pragma once

#include <dwmapi.h>
#include <string>
#include <vector>
#include "constants.h"
#include "gameobject.h"
#include <atomic>

struct engine_snapshot {
	std::vector<GameObject*> gameObjects;

	void filter_enemies() {
		for (int i = gameObjects.size()-1; i >= 0; i--) {
			GameObject* entity = gameObjects[i];
			if (entity->tag_id != tags::PLAYER && entity->tag_id != tags::ELITE && entity->tag_id != tags::GRUNT && entity->tag_id != tags::JACKAL && entity->tag_id != tags::INFECTION_FORM && entity->tag_id != tags::HUNTER && entity->tag_id != tags::FLOOD_HUMAN && entity->tag_id != tags::FLOOD_ELITE){
				gameObjects.erase(gameObjects.begin()+i, gameObjects.begin()+i+1);
			}
		}
	}

	GameObject* get_player() {
		for (auto& v : gameObjects) {
			if (v->tag_id == tags::PLAYER) {
				return v;
			}
		}
		return nullptr;
	}
};

class halo_engine
{
private:
	HWND haloHWND = NULL;
	std::vector<DataPool*> dataPools;
	DataPool* objectDataPool = nullptr;
	int32_t enableFastForward{ 0 };
	int32_t fastForwardTick{ 0 };

public:
	halo_engine();

	RECT window_client_rect();

	void get_snapshot(engine_snapshot& snapshot);
	HWND get_wnd_handle();
	void patch_memory(LPVOID dest_address, uint8_t* src_address, size_t patch_size);

	static halo_engine& get() {
		static halo_engine instance;
		return instance;
	}
};

