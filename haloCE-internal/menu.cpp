#include "pch.h"
#include "menu.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx9.h"
#include "variables.h"

WNDPROC oWndProc;
ImVec2 border_size = ImVec2(540, 500);

LRESULT APIENTRY ImGuiWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		ImGui::GetIO().MouseDown[0] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		ImGui::GetIO().MouseDown[0] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		ImGui::GetIO().MouseDown[1] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		ImGui::GetIO().MouseDown[1] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONDOWN:
		ImGui::GetIO().MouseDown[2] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONUP:
		ImGui::GetIO().MouseDown[2] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEWHEEL:
		ImGui::GetIO().MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		ImGui::GetIO().MousePos.x = (signed short)(lParam); ImGui::GetIO().MousePos.y = (signed short)(lParam >> 16); return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

void menu::init(HWND window, IDirect3DDevice9* pDevice) {
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplDX9_Init(window, pDevice);
	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)ImGuiWndProc);
}

void menu::shutdown() {
	//clean up input hook
	SetWindowLongPtr(globals::engine->get_wnd_handle(), GWLP_WNDPROC, (LONG_PTR)oWndProc);
}

void menu::checkInputs() {
	static bool is_down = false;
	static bool is_clicked = false;
	if (GetAsyncKeyState(VK_INSERT))
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!GetAsyncKeyState(VK_INSERT) && is_down)
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
		settings::menu_open = !settings::menu_open;
	}
}

void drawMainTab() {
	ImGui::BeginChild("main", border_size, true);
	{
		ImGui::Text("Welcome to Kyle's halo combat evolved hacks. Enjoy your stay!");

		//LPDIRECT3DTEXTURE9* texture = NULL;
		//D3DXCreateTextureFromFileInMemory(interfaces::directx, "/assets/supersaist.png", 135883, texture);
		//ImGui::Image(texture, ImVec2(256, 256), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
	}
	ImGui::EndChild();
}

void drawFunTab() {
	ImGui::BeginChild("fun", border_size, true);
	{

	}
	ImGui::EndChild();
}

void drawMiscTab() {
	ImGui::BeginChild("misc", border_size, true);
	{

	}
	ImGui::EndChild();
}

void menu::tick() {
	checkInputs();

	ImGui_ImplDX9_NewFrame();

	ImGui::GetIO().MouseDrawCursor = settings::menu_open;

	if (settings::menu_open) {
		ImVec2 mainWindowPos;
		//ImGui::PushFont(tabs);
		ImGui::SetNextWindowSize(ImVec2(650, 680));
		ImGui::Begin("Halo Internal by Kyle", &settings::menu_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		{
			static char buttons[][16] = { "main", "fun", "misc" };

			static int iTab = 0;
			for (int i = 0; i < 3; i++)
			{
				if (i > 0) ImGui::SameLine(0.0f, -0.3f);

				if (ImGui::Button(buttons[i], ImVec2(160, 30)))
					iTab = i;
			}
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			switch (iTab) {
			case 0: drawMainTab(); break;
			case 1: drawFunTab(); break;
			case 2: drawMiscTab(); break;
			}

			ImGui::End();
		}
		//ImGui::PopFont();
	}

	ImGui::Render();
}