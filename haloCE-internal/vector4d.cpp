#include "pch.h"
#include "vector4d.h"

vec4_t::vec4_t(void) {
	x = y = z = w = 0.0f;
}

vec4_t::vec4_t(float fx, float fy, float fz, float fw) {
	x = fx;
	y = fy;
	z = fz;
	w = fw;
}

vec4_t::~vec4_t(void) { };