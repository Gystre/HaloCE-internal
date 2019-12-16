#include "pch.h"
#include "gameobject.h"

void set_view_angles(vec3_t& angle) {
	*reinterpret_cast<vec3_t*>(addr::VIEW_ANGLES) = angle;
}

vec3_t get_view_angles() {
	return *reinterpret_cast<vec3_t*>(addr::VIEW_ANGLES);
}