#include "pch.h"
#include "vector3d.h"


vec3_t::vec3_t(void) {
	x = y = z = 0.0f;
}

vec3_t::vec3_t(float fx, float fy, float fz) {
	x = fx;
	y = fy;
	z = fz;
}

vec3_t::~vec3_t(void) { };

void vec3_t::clamp() {
	x = x > 1.492 ? 1.492 : x;
	y = y > 1.492 ? 1.492 : y;
}

void vec3_t::normalize(void) {
	auto vec_normalize = [&](vec3_t& v) {
		auto l = v.length();

		if (l != 0.0f) {
			v.x /= l;
			v.y /= l;
			v.z /= l;
		}
		else {
			v.x = v.y = 0.0f; v.z = 1.0f;
		}

		return l;
	};

	vec_normalize(*this);
}

float vec3_t::normalize_in_place() {
	float radius = sqrt(x * x + y * y + z * z);

	// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.f / (radius + FLT_EPSILON);

	x *= iradius;
	y *= iradius;
	z *= iradius;

	return radius;
}

float vec3_t::length(void) {
	float root = 0.0f, sqsr = this->length_sqr();

	__asm        sqrtss xmm0, sqsr
	__asm        movss root, xmm0

	return root;
}

float vec3_t::length_sqr(void) {
	auto sqr = [](float n) {
		return static_cast<float>(n * n);
	};

	return (sqr(x) + sqr(y) + sqr(z));
}

float vec3_t::dot(const vec3_t other) {
	return (x * other.x + y * other.y + z * other.z);
}

std::string vec3_t::toString() {
	return "[ " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + " ]";
}