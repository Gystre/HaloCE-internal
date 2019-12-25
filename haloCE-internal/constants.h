#pragma once
#include "pch.h"

namespace addr {
	extern uint32_t* RUNTIME_DATA_BEGIN;
	extern uint32_t* VIEW_ANGLES;
	extern uint32_t* VIEW_MATRIX;
	extern uint32_t* CAMERA_POS;
	extern uint32_t* CAMERA_LOOK_VECTOR;
}

struct ObjectPoolObject
{
	uint32_t ObjectAddress;
	uint32_t unk1;
	uint32_t unk2;
};

struct DataPool {
	char Name[32];
	uint32_t unk1; // 000C0800
	uint32_t unk2; // 00000001
	uint32_t DataHeader; // 0x64407440 @t@d
	int16_t UnkCounter1;
	int16_t ObjectCount;
	int16_t UnkCounter3;
	int16_t UnkCounter4; // Total objects ever?
	uint32_t DataBeginAddress;
	uint32_t unk3;
	uint32_t unk4;

	ObjectPoolObject ObjectPointers[8192];
};

enum tags : short {
	STATIC_PROP = 580,
	TERMINAL = 616,
	BULKHEAD = 628,
	TREE1 = 632,
	ANIMATED_LIGHT = 680,
	DEBRIS = 720,
	DOOR1 = 732,
	TREE2 = 736,
	PROJECTILE = 764,
	AMMO_HEALTH_CONSUMABLE = 800,
	DOOR2 = 940,
	NEEDLER = 732,
	SHOTGUN = 1088,
	MA5B = 1204,
	PLASMA_PISTOL = 1320,
	POA_TERMINAL = 1356,
	PLASMA_RIFLE_OR_ROCKETS = 1436,
	POA_BRIDGE_CHAIR = 1612,
	GUILTY_SPARK = 1616,
	PISTOL = 1668,
	UNKNOWN = 1728,
	BANSHEE = 1960,
	GHOST = 2076,
	WRAITH = 2424,
	PELICAN = 2888,
	POPCORN = 2892,
	GRUNT = 3356, //e
	MAYBE_WARTHOG = 3584,
	PLAYER = 3588,
	MARINE = 3704,
	INFECTION_FORM = 3936, //e
	ELITE = 4400,  //e 
	JACKAL = 4516, //e
	HUNTER = 4864, //e
	CPT_KEYES = 5328,
	FLOOD_HUMAN = 5792, //e
	FLOOD_ELITE = 6024 //e
};