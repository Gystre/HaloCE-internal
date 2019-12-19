#include "pch.h"

#include "hook.h"
#include "constants.h"
#include "variables.h"
#include "aimbot.h"
#include "esp.h"
#include "drawing.h"

static bool is_down = false;
static bool is_clicked = false;

void loop() {
	engine_snapshot snapshot = {};
	globals::engine->get_snapshot(snapshot);
	snapshot.filter_enemies(); //dont aim at friends lol

	//drawing::drawLine(0, 0, 500, 500, COLORREF(RGB(255,0,0)));

	if (GetAsyncKeyState(VK_F1)) {
		for (GameObject* entity : snapshot.gameObjects) {
			entity->position = snapshot.get_player()->position;
		}
	}

	//if (GetAsyncKeyState(VK_LMENU))
	//{
	//	is_clicked = false;
	//	is_down = true;
	//}
	//else if (!GetAsyncKeyState(VK_LMENU) && is_down)
	//{
	//	is_clicked = true;
	//	is_down = false;
	//}
	//else
	//{
	//	is_clicked = false;
	//	is_down = false;
	//}

	//if (is_clicked)
	//{
	//	menu::aim_enabled = !menu::aim_enabled;
	//}

	pse.update(snapshot);
	botaim.update(snapshot);
}

