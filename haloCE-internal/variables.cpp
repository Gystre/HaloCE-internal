#include "pch.h"
#include "variables.h"

namespace globals {
	std::unique_ptr<halo_engine> engine;

	void init() {
		engine = std::make_unique<halo_engine>();
	}
}

namespace menu {
	bool aim_enabled = false;
}