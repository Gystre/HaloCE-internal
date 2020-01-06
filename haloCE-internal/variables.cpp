#include "pch.h"
#include "variables.h"
#include "drawing.h"

namespace globals {
	std::unique_ptr<halo_engine> engine;

	void init() {
		engine = std::make_unique<halo_engine>();
	}

	void shutdown() {
		engine.release();
		//might want to move this somewhere else
		drawing::shutdown();
	}
}

namespace settings {
	bool aim_enabled = false;
	int aim_style = 0;
	int aim_selection_style = 0;
	bool aim_fov_enabled = false;
	float aim_fov_size = 50;

	bool esp_enabled = false;
	bool tracers_enabled = false;
	float esp_color[4] = { 1, 0, 0, 0 };

	bool speed = true;
	float how_fast = 0.5;

	bool lock_health = false;
	bool lock_shield = false;
	bool lock_frag_grenades = false;
	bool lock_plasma_grenades = false;
}