#include "pch.h"
#include "esp.h"
#include "variables.h"
#include "matrix.h"
#include "constants.h"
#include "drawing.h"
#include "vector4d.h"
#include "math.h"

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

void esp::update(engine_snapshot snapshot) {
	glm::vec3 pos = *reinterpret_cast<glm::vec3*>(addr::CAMERA_POS);
	glm::vec3 dir = *reinterpret_cast<glm::vec3*>(addr::CAMERA_LOOK_VECTOR);
	glm::vec3 lookAt = pos + dir;

	glm::mat4 view_matrix = glm::lookAt(pos, lookAt, glm::vec3(0, 0, 1));

	for (int i = 0; i < snapshot.gameObjects.size(); i++) {
		GameObject* entity = snapshot.gameObjects[i];
		vec2_t screen_pos;
		vec3_t view_angles = get_view_angles();
		if (entity && entity->tag_id != tags::PLAYER && entity->health > 0 && math::openGLworldToScreen(view_matrix, entity->position, globals::engine->get_width(), globals::engine->get_height(), screen_pos)) {
			drawing::drawString(screen_pos.x, screen_pos.y, COLORREF(RGB(255, 0, 0)), tag_to_name(entity->tag_id).c_str());
		}
	}
}