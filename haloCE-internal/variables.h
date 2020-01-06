#pragma once

#include "engine.h"

namespace globals {
	extern std::unique_ptr<halo_engine> engine;

	void init();
	void shutdown();
}

namespace settings {
	extern bool aim_enabled;
	extern int aim_style;
	extern int aim_selection_style;
	extern bool aim_fov_enabled;
	extern float aim_fov_size;

	extern bool esp_enabled;
	extern bool tracers_enabled;
	extern float esp_color[4];

	extern bool speed;
	extern float how_fast;

	extern bool lock_health;
	extern bool lock_shield;
	extern bool lock_frag_grenades;
	extern bool lock_plasma_grenades;
}