#pragma once
#ifndef AMD_WINDOW_WINDOW
#define AMD_WINDOW_WINDOW

#include <string>

#include <GLFW/glfw3.h>

#include "ErrorHandling/ErrorHandling.hpp"
#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

class Window
{
public:
	static inline Window& GetInstance()
	{
		static Window instance;
		return instance;
	}

	static void GLFWErrorCallback(int, const char*);

	Status Initialize();
	Status PreRenderUpdate();
	Status PostRenderUpdate();

	bool inline IsAlive()
	{
		return !(glfwWindowShouldClose(glfwWindow));
	}

private:
	GLFWwindow* glfwWindow = nullptr;

	struct 
	{
		std::string title = "ApertaMD";
		U32 width = 1920;
		U32 height = 1080;
	} configuration;

	Window() = default;
};

AMD_NAMESPACE_END

#endif // ifndef AMD_WINDOW_WINDOW