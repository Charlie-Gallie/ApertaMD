#include <iostream>

#include "Window/Window.hpp"
#include "UI/UI.hpp"
#include "Project/Project.hpp"
#include "Project/DataInterface.hpp"

#include "imgui.h"

using namespace AMD;

int main()
{
	Project& project = Project::GetInstance();
	DataInterface& dataInterface = DataInterface::GetInstance();
	Window& window = Window::GetInstance();
	UI& ui = UI::GetInstance();

	window.Initialize();
	ui.Initialize();
	project.LoadProject("test_project.json");

	while (window.IsAlive())
	{
		window.PreRenderUpdate();

		ui.Update();

		window.PostRenderUpdate();
	}

	return 0;
}