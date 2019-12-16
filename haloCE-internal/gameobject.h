#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "vector3d.h"
#include "constants.h"

class GameObject{
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
	uint32_t padding3[3];
	glm::quat rotationQuaternion;
	uint32_t padding3_2[7];
	vec3_t position_ineffective; //not sure what this for???
	uint32_t padding4[13];
	float health;
	float shield;
};

//class GameObject {
//public:
//	DWORD mapId; // 0x0000
//	long unk[3]; // 0x0004
//	char unkBits : 2; // 0x0010
//	bool ignoreGravity : 1;
//	char unk1 : 4;
//	bool immovable : 1;
//	char unkBits1[3];
//	unsigned long timer; // 0x0014
//	char empty[0x44]; // 0x0018
//	vec3_t position; // 0x005c
//	vec3_t velocity; // 0x0068
//	vec3_t rotation; // 0x0074 (not sure why this is used, doesn't yaw do orientation?)
//	vec3_t axial; // 0x0080 (yaw, pitch, roll)
//	vec3_t unkVector; // 0x008C (not sure, i let server deal with it)
//	char unkChunk[0x28]; // 0x0098
//	unsigned long ownerPlayer; // 0x00c0 (index of owner (if has one))
//	unsigned long ownerObject; // 0x00c4 (object id of owner, if projectile is player id)
//	char unkChunk1[0x18]; // 0x00c8
//	float health; // 0x00e0
//	float shield; // 0x00e4
//	char unkChunk2[0x2c]; // 0x00e8
//	unsigned long veh_weaponId; // 0x0114
//	unsigned long player_curWeapon; // 0x0118
//	unsigned long vehicleId; // 0x011C
//	BYTE bGunner; // 0x0120
//	short unkShort; // 0x0121
//	BYTE bFlashlight; // 0x0123
//	long unkLong; // 0x0124
//	float shield1; // 0x0128 (same as other shield)
//	float flashlightCharge; // 0x012C (1.0 when on)
//	long unkLong1; // 0x0130
//	float flashlightCharge1; // 0x0134
//	long unkChunk3[0x2f]; // 0x0138
//};

void set_view_angles(vec3_t& angle);
vec3_t get_view_angles();