#pragma once

#include "gameobject.h"
#include "engine.h"

class aimbot {
public:
	void update(engine_snapshot snapshot);
};

extern aimbot botaim;