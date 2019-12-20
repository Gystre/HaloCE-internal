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
		vec3_t view_angles = get_view_angles();
		if (entity && entity->tag_id != tags::PLAYER && entity->health > 0 && view_matrix.worldToScreen(entity->position, globals::engine->get_width(), globals::engine->get_height(), screen_pos)) {
			drawing::drawBorderBox(0, 0, 300, 400, 2);
		}
	}
}