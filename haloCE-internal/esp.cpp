#include "pch.h"
#include "esp.h"
#include "variables.h"
#include "matrix.h"
#include "constants.h"
#include "drawing.h"

esp pse;

void esp::update(engine_snapshot snapshot) {
	mat4_t view_matrix = *reinterpret_cast<mat4_t*>(addr::VIEW_MATRIX);
	for (int i = 0; i < snapshot.gameObjects.size(); i++) {
		GameObject* entity = snapshot.gameObjects[i];
		vec2_t screen_pos;
		if (entity && entity->tag_id != tags::PLAYER && entity->health > 0 && view_matrix.worldToScreen(entity->position, globals::engine->window_client_rect.right, globals::engine->window_client_rect.bottom, screen_pos)) {
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
			float center = globals::engine->window_client_rect.right / -2;
			drawing::drawBorderBox(screen_pos.x + center, screen_pos.y, globals::engine->window_client_rect.right, head - 2, 2);
		}
	}
}