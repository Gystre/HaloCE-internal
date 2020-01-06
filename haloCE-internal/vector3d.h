#pragma once
#include <string>
#include <limits>

#define CHECK_VALID( _v ) 0

class vec3_t {
public:
	vec3_t();
	vec3_t(float, float, float);
	~vec3_t();

	float x, y, z;

	vec3_t& operator+=(const vec3_t& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}
	vec3_t& operator-=(const vec3_t& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}
	vec3_t& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}
	vec3_t operator+(const vec3_t& v) {
		return vec3_t{ x + v.x, y + v.y, z + v.z };
	}
	vec3_t operator-(const vec3_t& v) {
		return vec3_t{ x - v.x, y - v.y, z - v.z };
	}
	vec3_t operator*(const vec3_t& v) {
		return vec3_t{ x * v.x, y * v.y, z * v.z };
	}
	vec3_t operator*(float v) const {
		return vec3_t{ x * v, y * v, z * v };
	}
	vec3_t& operator/(float v) {
		x /= v; y /= v; z /= v; return *this;
	}

	float& operator[](int i) {
		return ((float*)this)[i];
	}
	float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline void init(float ix, float iy, float iz)
	{
		x = ix; y = iy; z = iz;
		CHECK_VALID(*this);
	}

	void clamp();
	void normalize();
	float normalize_in_place();
	float length();
	float length_sqr();
	float dot(const vec3_t other);
	std::string toString();
};