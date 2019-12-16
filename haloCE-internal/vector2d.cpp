#include "pch.h"
#include "vector2d.h"
#include <math.h>

vec2_t::vec2_t() {
	x = y = 0;
}

vec2_t::vec2_t(float fx, float fy) {
	x = fx;
	y = fy;
}

vec2_t::~vec2_t(void) { };

float vec2_t::length() {
	return sqrt((x * x) + (y * y)); //probably faster way to do this with assembly :P
}

float vec2_t::distance(vec2_t vec) {
	float dx = vec.x - x;
	float dy = vec.y - y;

	return sqrt(dx * dx + dy * dy);
}

std::string vec2_t::toString() {
	return "[ " + std::to_string(x) + " " + std::to_string(y) + " ]";
}
