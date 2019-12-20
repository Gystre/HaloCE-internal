#pragma once

#include "engine.h"

namespace globals {
	extern std::unique_ptr<halo_engine> engine;

	void init();
	void shutdown();
}

namespace menu {
	extern bool aim_enabled;
}