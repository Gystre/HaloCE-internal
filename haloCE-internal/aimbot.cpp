#include "pch.h"
#include "aimbot.h"
#include "constants.h"
#include "vector2d.h"
#include "variables.h"
#include "matrix.h"
#include "math.h"

#define M_PI 3.141592653589793238462643383279502f

aimbot botaim;

GameObject* getClosestToCrosshair(engine_snapshot snapshot) {
	GameObject* closest = nullptr;

	vec2_t crosshair = vec2_t(globals::engine->get_width()/2, globals::engine->get_height()/2);
	float dist = FLT_MAX;

	glm::vec3 pos = *reinterpret_cast<glm::vec3*>(addr::CAMERA_POS);
	glm::vec3 dir = *reinterpret_cast<glm::vec3*>(addr::CAMERA_LOOK_VECTOR);
	glm::vec3 lookAt = pos + dir;

	glm::mat4 view_matrix = glm::lookAt(pos, lookAt, glm::vec3(0, 0, 1));

	for (GameObject* entity : snapshot.gameObjects) {
		if (entity && entity->tag_id != tags::PLAYER && entity->health > 0) {
			vec2_t headPos; //passed by reference so will always be initialized
			if (math::openGLworldToScreen(view_matrix, entity->position, globals::engine->get_width(), globals::engine->get_height(), headPos)) {
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

void aimbot::update(engine_snapshot snapshot) {
	//if (menu::aim_enabled) {
	if(GetAsyncKeyState(VK_LMENU)) {
		GameObject* local_player = snapshot.get_player();
		GameObject* entity = getClosestToCrosshair(snapshot);

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