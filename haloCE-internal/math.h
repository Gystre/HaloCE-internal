#pragma once
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include <glm/gtc/matrix_transform.hpp>

#define M_PI 3.141592653589793238462643383279502f

namespace math {
	//maybe move this function to matrix class???
	//column major
	bool openGLworldToScreen(glm::mat4 view, vec3_t pos, int windowWidth, int windowHeight, vec2_t& screen);
	float get_w2s_distance(float width, float height, vec3_t enemy, float radius);
}