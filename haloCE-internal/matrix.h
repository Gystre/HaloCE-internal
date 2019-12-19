#pragma once

#include "vector3d.h"
#include "vector2d.h"

//TODO: write a tostring for this

class mat4_t {
public:
	mat4_t();
	mat4_t(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
	~mat4_t();


	//Memory layout of data will affect order of matrix. 
	//DirectX: Usualy Row-Major
	//OpenGL: Usualy Column-Major

	//    X,   Y,   Z,   W
	float m11, m12, m13, m14; //00, 01, 02, 03
	float m21, m22, m23, m24; //04, 05, 06, 07
	float m31, m32, m33, m34; //08, 09, 10, 11
	float m41, m42, m43, m44; //12, 13, 14, 15'

	bool worldToScreen(vec3_t worldPos, int width, int height, vec2_t& out_pos);
};