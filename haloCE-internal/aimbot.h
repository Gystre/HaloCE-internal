#pragma once

#include "engine.h"

//not sure if these belong in enum or defines :P
#define HOLD 0
#define TAP 1
#define TEST 2

#define CROSSHAIR 0
#define DISTANCE 1

class aimbot {
public:
	void update(engine_snapshot snapshot);
};

extern aimbot botaim;