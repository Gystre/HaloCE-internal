#include "pch.h"
#include <algorithm>
#include "aimbot.h"
#include "constants.h"
#include "vector2d.h"
#include "variables.h"
#include "matrix.h"
#include "math.h"

aimbot botaim;

int cross_distance = -15000;

GameObject* getClosestToCrosshair(engine_snapshot snapshot) {
	GameObject* closest = nullptr;

	vec2_t crosshair = vec2_t(globals::engine->get_width()/2, globals::engine->get_height()/2);
	float dist = FLT_MAX;

	float display_w = globals::engine->get_width();
	float display_h = globals::engine->get_height();
	float horizontalFovRadians = **reinterpret_cast<float**>(addr::PTR_TO_CAMERA_HORIZONTAL_FIELD_OF_VIEW_IN_RADIANS);
	float verticalFov = horizontalFovRadians * display_h / display_w;
	verticalFov = std::clamp(verticalFov - .03f, 0.1f, glm::pi<float>()); // Have to offset by this to get correct ratio for 16:9, need to look into this further
	glm::mat4 projection_matrix = glm::perspectiveFov(verticalFov, display_w, display_h, 0.5f, 15.0f);

	glm::vec3 pos = *reinterpret_cast<glm::vec3*>(addr::CAMERA_POS);
	glm::vec3 dir = *reinterpret_cast<glm::vec3*>(addr::CAMERA_LOOK_VECTOR);
	glm::vec3 lookAt = pos + dir;
	glm::mat4 view_matrix = glm::lookAt(pos, lookAt, glm::vec3(0, 0, 1));

	glm::mat4 view_projection_matrix = projection_matrix * view_matrix;

	for (GameObject* entity : snapshot.gameObjects) {
		if (entity && entity->tag_id != tags::PLAYER && entity->health > 0) {
			vec2_t headPos; //passed by reference so will always be initialized

			//calculate cross distance
			if (settings::aim_fov_enabled && cross_distance < math::get_w2s_distance(globals::engine->get_width(), globals::engine->get_height(), entity->position, settings::aim_fov_size)) {
				cross_distance = math::get_w2s_distance(globals::engine->get_width(), globals::engine->get_height(), entity->position, settings::aim_fov_size);

				if (cross_distance <= settings::aim_fov_size * settings::aim_fov_size && math::openGLworldToScreen(view_projection_matrix, entity->position, globals::engine->get_width(), globals::engine->get_height(), headPos)) {
					float newDist = crosshair.distance(headPos);
					if (newDist < dist) {
						closest = entity;
						dist = newDist;
					}
				}
			} else if (math::openGLworldToScreen(view_projection_matrix, entity->position, globals::engine->get_width(), globals::engine->get_height(), headPos)) {
				float newDist = crosshair.distance(headPos);
				if (newDist < dist) {
					closest = entity;
					dist = newDist;
				}
			}
		}
	}

	return closest;
}

GameObject* getClosest(engine_snapshot snapshot) {
	GameObject* local_player = snapshot.get_player();
	GameObject* closest = nullptr;

	float dist = FLT_MAX;

	for (GameObject* entity : snapshot.gameObjects) {
		if (entity && entity->tag_id != tags::PLAYER && entity->health > 0) {
			float newDist = sqrt((entity->position.x - local_player->position.x) * (entity->position.x - local_player->position.x) +
								 (entity->position.y - local_player->position.y) * (entity->position.y - local_player->position.y) +
								 (entity->position.z - local_player->position.z) * (entity->position.z - local_player->position.z));

			if (newDist < dist) {
				closest = entity;
				dist = newDist;
			}
		}
	}

	return closest;
}

static bool is_down = false;
static bool is_clicked = false;
static bool is_aiming = false;

void aimbot::update(engine_snapshot snapshot) {
	if (settings::aim_style == HOLD && GetAsyncKeyState(VK_RBUTTON)) {
		GameObject* local_player = snapshot.get_player();
		GameObject* entity = settings::aim_selection_style == CROSSHAIR ? getClosestToCrosshair(snapshot) : getClosest(snapshot);

		if (entity == nullptr || local_player == nullptr) return;

		float dx = entity->position.x - local_player->position.x;
		float dy = entity->position.y - local_player->position.y;
		double angleYaw = atan2(dy, dx);

		double distance = sqrt(dx * dx + dy * dy);
		float dz = entity->position.z - local_player->position.z;
		double anglePitch = atan2(dz, distance);

		vec3_t ang = vec3_t(angleYaw, anglePitch, 0);
		set_view_angles(ang);
	} else if (settings::aim_style == TAP) {
		if (GetAsyncKeyState(VK_LMENU))
		{
			is_clicked = false;
			is_down = true;
		}
		else if (!GetAsyncKeyState(VK_LMENU) && is_down)
		{
			is_clicked = true;
			is_down = false;
		}
		else
		{
			is_clicked = false;
			is_down = false;
		}

		if (is_clicked)
		{
			is_aiming = !is_aiming;
		}

		if (is_aiming) {
			GameObject* local_player = snapshot.get_player();
			GameObject* entity = settings::aim_selection_style == CROSSHAIR ? getClosestToCrosshair(snapshot) : getClosest(snapshot);

			if (entity == nullptr || local_player == nullptr) return;

			float dx = entity->position.x - local_player->position.x;
			float dy = entity->position.y - local_player->position.y;
			double angleYaw = atan2(dy, dx);

			double distance = sqrt(dx * dx + dy * dy);
			float dz = entity->position.z - local_player->position.z;
			double anglePitch = atan2(dz, distance);

			vec3_t ang = vec3_t(angleYaw, anglePitch, 0);
			set_view_angles(ang);
		}
	}
}