#include "pch.h"
#include "matrix.h"
#include "vector4d.h"

mat4_t::mat4_t() {
	m11 = m12 = m13 = m14 = m21 = m22 = m23 = m24 = m31 = m32 = m33 = m34 = m41 = m42 = m43 = m44 = 0;
}

mat4_t::mat4_t(float x1, float x2, float x3, float x4, 
	float y1, float y2, float y3, float y4, 
	float z1, float z2, float z3, float z4, 
	float w1, float w2, float w3, float w4) {

	m11 = x1; m12 = x2; m13 = x3; m14 = x4;
	m21 = y1; m22 = y2; m23 = y3; m24 = y4;
	m31 = z1; m32 = z2; m33 = z3; m34 = z4;
	m41 = w1; m42 = w2; m43 = w3; m44 = w4;
}

mat4_t::~mat4_t() { }

//w2s specifically for directx
bool mat4_t::worldToScreen(vec3_t pos, int windowWidth, int windowHeight, vec2_t& screen) {
    vec4_t clipCoords;
    clipCoords.x = pos.x * m11 + pos.y * m12 + pos.z * m13 + m14;
    clipCoords.y = pos.x * m21 + pos.y * m22 + pos.z * m23 + m24;
    clipCoords.z = pos.x * m31 + pos.y * m33 + pos.z * m33 + m34;
    clipCoords.w = pos.x * m41 + pos.y * m44 + pos.z * m43 + m44;

    if (clipCoords.w < 0.1f)
        return false;


    vec3_t NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
    screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

    return true;
}

std::string mat4_t::toString() {
	return "[ " + std::to_string(m11) + " " + std::to_string(m12) + " " + std::to_string(m13) + " " + std::to_string(m14) + " ]\n" +
		"[ " + std::to_string(m21) + " " + std::to_string(m22) + " " + std::to_string(m23) + " " + std::to_string(m24) + " ]\n" +
		"[ " + std::to_string(m31) + " " + std::to_string(m32) + " " + std::to_string(m33) + " " + std::to_string(m34) + " ]\n" +
		"[ " + std::to_string(m41) + " " + std::to_string(m42) + " " + std::to_string(m43) + " " + std::to_string(m44) + " ]";
}