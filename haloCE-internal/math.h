#pragma once
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include <glm/gtc/matrix_transform.hpp>


namespace math {
	//maybe move this function to matrix class???
	//column major
	bool openGLworldToScreen(glm::mat4 view, vec3_t pos, int windowWidth, int windowHeight, vec2_t& screen);
}