#pragma once

#include "engine.h"

namespace globals {
	extern std::unique_ptr<halo_engine> engine;

	void init();
}

namespace menu {
	extern bool aim_enabled;
}