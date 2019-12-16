#include "pch.h"
#include "matrix.h"

bool matrix4x4::worldToScreen(vec3_t worldPos, int width, int height, vec2_t& screenPos) {
	//multiply vector against matrix
	float screenX = (m11 * worldPos.x) + (m21 * worldPos.y) + (m31 * worldPos.z) + m41;
	float screenY = (m12 * worldPos.x) + (m22 * worldPos.y) + (m32 * worldPos.z) + m42;
	float screenW = (m14 * worldPos.x) + (m24 * worldPos.y) + (m34 * worldPos.z) + m44;

	//camera position (eye level/middle of screen)
	float camX = width / 2;
	float camY = height / 2;

	//convert to homogeneous position
	float x = camX + (camX * screenX / screenW);
	float y = camY - (camY * screenY / screenW);
	screenPos = vec2_t(x, y);

	//check if object is behind camera / off screen (not visible)
	//w = z where z is relative to the camera 
	return (screenW > 0.001f);
}