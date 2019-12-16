#include "pch.h"

#include "hook.h"
#include "constants.h"
#include "variables.h"
#include "aimbot.h"

static bool is_down = false;
static bool is_clicked = false;

void loop() {
	engine_snapshot snapshot = {};
	globals::engine->get_snapshot(snapshot);
	snapshot.filter_enemies(); //dont aim at friends lol

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
		menu::aim_enabled = !menu::aim_enabled;
	}

	botaim.update(snapshot);
}