#include "pch.h"
#include "variables.h"
#include "drawing.h"

namespace globals {
	std::unique_ptr<halo_engine> engine;

	void init() {
		engine = std::make_unique<halo_engine>();
		drawing::init();
	}

	void shutdown() {
		drawing::shutdown();
	}
}

namespace menu {
	bool aim_enabled = false;
}