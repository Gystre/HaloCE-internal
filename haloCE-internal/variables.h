#pragma once

#include "engine.h"

namespace globals {
	extern std::unique_ptr<halo_engine> engine;

	void init();
	void shutdown();
}

namespace settings {
	extern bool menu_open;
	extern bool aim_enabled;
}