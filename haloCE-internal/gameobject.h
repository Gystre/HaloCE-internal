#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "vector3d.h"
#include "constants.h"

class GameObject {
public:
	uint32_t header_head; // "daeh"
	uint32_t tag_id;
	uint32_t ptr_a;
	uint32_t ptr_next_object;
	uint32_t ptr_previous_object;
	uint32_t header_tail; // "liat"
	uint32_t padding1[6];
	uint32_t counter;
	uint32_t padding2[16];
	vec3_t position;
	vec3_t velocity; // 0x0068
	glm::quat rotationQuaternion;
	uint32_t padding3_2[7];
	vec3_t position_ineffective; //not sure what this for???
	uint32_t padding4[13];
	float health; //0xF8
	float shield; //0xFC
	char pad_0x0100[0x236]; //0x0100
	BYTE frag_grenades; //0x0336 
	BYTE plasma_grenades; //0x0337 
};

void set_view_angles(vec3_t& angle);
vec3_t get_view_angles();