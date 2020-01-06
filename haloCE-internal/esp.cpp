#include "pch.h"
#include "esp.h"
#include "variables.h"
#include "matrix.h"
#include "constants.h"
#include "drawing.h"
#include "vector4d.h"
#include "math.h"
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

esp pse;

std::string tag_to_name(short tag) {
	switch (tag) {
		case tags::ELITE:
			return "Elite";
		case tags::GRUNT:
			return "Grunt";
		case tags::JACKAL:
			return "Jackal";
		case tags::HUNTER:
			return "Hunter";
		case tags::FLOOD_ELITE:
			return "Flood Elite";
		case tags::FLOOD_HUMAN:
			return "Flood Human";
		case tags::INFECTION_FORM:
			return "Infection Form";
		default:
			return "Unknown";
	}
}

void esp::createTexture(IDirect3DDevice9* pDevice, LPCVOID color, UINT colorSize, LPDIRECT3DTEXTURE9* texture) {
	D3DXCreateTextureFromFileInMemory(pDevice, color, colorSize, texture);
}

void esp::doChams(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE primType, INT baseVertexIndex, UINT minVertexIndex, UINT numVertices, UINT startIndex, UINT primCount) {
	if (GRUNT) {
		pDevice->SetRenderState(D3DRS_ZENABLE, false);
		pDevice->SetTexture(0, texRed);
		pDevice->DrawIndexedPrimitive(primType, baseVertexIndex, minVertexIndex, numVertices, startIndex, primCount);
		pDevice->SetRenderState(D3DRS_ZENABLE, true);
	}
}

void esp::update(engine_snapshot snapshot, GameObject* local_player) {
	float display_w = globals::engine->get_width(); //alot faster to define local variable at top than reference globals namespace lots of times
	float display_h = globals::engine->get_height();
	float horizontalFovRadians = **reinterpret_cast<float**>(addr::PTR_TO_CAMERA_HORIZONTAL_FIELD_OF_VIEW_IN_RADIANS);
	float verticalFov = horizontalFovRadians * display_h / display_w;
	verticalFov = std::clamp(verticalFov - .03f, 0.1f, glm::pi<float>()); // Have to offset by this to get correct ratio for 16:9, need to look into this further
	glm::mat4 projection_matrix = glm::perspectiveFov(verticalFov, display_w, display_h, 0.5f, 15.0f);

	glm::vec3 pos = *reinterpret_cast<glm::vec3*>(addr::CAMERA_POS);
	glm::vec3 dir = *reinterpret_cast<glm::vec3*>(addr::CAMERA_LOOK_VECTOR);
	glm::vec3 lookAt = pos + dir;
	glm::mat4 view_matrix = glm::lookAt(pos, lookAt, glm::vec3(0, 0, 1));

	//thanks halo tas <3
	glm::mat4 view_projection_matrix = projection_matrix * view_matrix;

	float r = settings::esp_color[0];

	for (int i = 0; i < snapshot.gameObjects.size(); i++) {
		GameObject* entity = snapshot.gameObjects[i];
		vec2_t screen_pos;
		float dist = sqrt((entity->position.x - local_player->position.x) * (entity->position.x - local_player->position.x) +
						(entity->position.y - local_player->position.y) * (entity->position.y - local_player->position.y) +
						(entity->position.z - local_player->position.z) * (entity->position.z - local_player->position.z));

		if (entity && entity->tag_id != tags::PLAYER && entity->health > 0 && math::openGLworldToScreen(view_projection_matrix, entity->position, globals::engine->get_width(), globals::engine->get_height(), screen_pos)) {
			drawing::drawString(screen_pos.x, screen_pos.y, D3DCOLOR_ARGB(255, 255, 0, 0), tag_to_name(entity->tag_id).c_str());
			drawing::drawString(screen_pos.x, screen_pos.y + 11, D3DCOLOR_ARGB(255, 255, 0, 0), ("Health: " + std::to_string(entity->health * 100) + "%%").c_str());
			drawing::drawString(screen_pos.x, screen_pos.y + 22, D3DCOLOR_ARGB(255, 255, 0, 0), (std::to_string(dist) + " units").c_str());

			if (settings::tracers_enabled) {
				drawing::drawLine(D3DXVECTOR2(display_w/2, display_h/2), D3DXVECTOR2(screen_pos.x, screen_pos.y), 2, D3DCOLOR_ARGB(255, 255, 0, 0));
			}
		}
	}
}