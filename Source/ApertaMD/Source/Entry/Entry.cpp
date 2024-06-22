#include <iostream>

#include "Window/Window.hpp"
#include "UI/UI.hpp"
#include "Project/Project.hpp"

#include "imgui.h"

int main()
{
	AMD::Window& window = AMD::Window::GetInstance();
	AMD::UI& ui = AMD::UI::GetInstance();

	window.Initialize();
	ui.Initialize();
	AMD::Project& project = AMD::Project::GetInstance();

	project.LoadProject("test_project.json");

	while (window.IsAlive())
	{
		window.PreRenderUpdate();

		ui.Update();

		window.PostRenderUpdate();
	}

	return 0;
}