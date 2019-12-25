#include "pch.h"
#include "constants.h"

namespace addr {
	uint32_t* RUNTIME_DATA_BEGIN = reinterpret_cast<uint32_t*>(0x40000000);
	uint32_t* VIEW_ANGLES = reinterpret_cast<uint32_t*>(0x402AD4B8);
	uint32_t* VIEW_MATRIX = reinterpret_cast<uint32_t*>(0x40001F70); //wrong address :(
	uint32_t* CAMERA_POS = reinterpret_cast<uint32_t*>(0x006AC6D0);
	uint32_t* CAMERA_LOOK_VECTOR = reinterpret_cast<uint32_t*>(0x006AC72C); //0x20
}