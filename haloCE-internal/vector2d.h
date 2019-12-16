#pragma once

#include <string>

class vec2_t {
public:
	vec2_t();
	vec2_t(float, float);
	~vec2_t();

	float x, y;

	vec2_t& operator+=(const vec2_t& v) {
		x += v.x; y += v.y; return *this;
	}
	vec2_t& operator-=(const vec2_t& v) {
		x -= v.x; y -= v.y; return *this;
	}
	vec2_t& operator*=(float v) {
		x *= v; y *= v; return *this;
	}
	//vec2_t operator+(const vec2_t& v) {
	//	return vec2_t{ x + v.x, y + v.y };
	//}
	//vec2_t operator-(const vec2_t& v) {
	//	return vec2_t{ x - v.x, y - v.y };
	//}
	//vec2_t operator*(float v) const {
	//	return vec2_t{ x * v, y * v };
	//}
	vec2_t& operator/(float v) {
		x /= v; y /= v; return *this;
	}

	float& operator[](int i) {
		return ((float*)this)[i];
	}
	float operator[](int i) const {
		return ((float*)this)[i];
	}

	float length();
	float distance(vec2_t);
	std::string toString();
};