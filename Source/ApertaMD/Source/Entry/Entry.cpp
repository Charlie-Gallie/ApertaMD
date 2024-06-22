#include <iostream>

#include "Window/Window.hpp"
#include "UI/UI.hpp"

#include "imgui.h"

int main()
{
	AMD::Window& window = AMD::Window::GetInstance();
	AMD::UI& ui = AMD::UI::GetInstance();

	window.Initialize();
	ui.Initialize();

	while (window.IsAlive())
	{
		window.PreRenderUpdate();

		ui.Update();

		window.PostRenderUpdate();
	}

	return 0;
}