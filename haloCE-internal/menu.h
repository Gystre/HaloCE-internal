#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class menu {
public:
	void init();
	void shutdown();
	void tick();
	GLFWwindow* get_window();
};

extern menu hack_menu;