#include "pch.h"
#include "math.h"

namespace math {
	bool openGLworldToScreen(glm::mat4 view, vec3_t pos, int windowWidth, int windowHeight, vec2_t& screen) {
		vec4_t clipCoords;
		clipCoords.x = pos.x * view[0].x + pos.y * view[1].x + pos.z * view[2].x + view[3].x;
		clipCoords.y = pos.x * view[0].y + pos.y * view[1].y + pos.z * view[2].y + view[3].y;
		clipCoords.z = pos.x * view[0].z + pos.y * view[1].z + pos.z * view[2].z + view[3].z;
		clipCoords.w = pos.x * view[0].w + pos.y * view[1].w + pos.z * view[2].w + view[3].w;

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

	float get_w2s_distance(RECT window_rect, vec2_t screen_enemy_pos, float radius) {
		float x = screen_enemy_pos.x - (window_rect.right - window_rect.left) / 2;
		float y = screen_enemy_pos.y - (window_rect.bottom - window_rect.top) / 2;
		return radius * radius - (x * x + y * y);
	}
}