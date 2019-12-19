#pragma once

class vec4_t {
public:
	vec4_t();
	vec4_t(float, float, float, float);
	~vec4_t();

	float x, y, z, w;
};