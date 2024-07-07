#include <iostream>

#include "Window/Window.hpp"
#include "UI/UI.hpp"
#include "Project/Project.hpp"
#include "Project/DataInterface.hpp"

#include "imgui.h"

using namespace AMD;

int main()
{
	Window& window = Window::GetInstance();
	UI& ui = UI::GetInstance();

	window.Initialize();
	ui.Initialize();
	Project& project = Project::GetInstance();

	project.LoadProject("test_project.json");

	DataInterface& dataInterface = DataInterface::GetInstance();

	std::string projectName;
	dataInterface.GetValue(projectName, Accessor::PROJECT_ENVIRONMENT, Accessor::NAME);

	std::cout << projectName << std::endl;

	while (window.IsAlive())
	{
		window.PreRenderUpdate();

		ui.Update();

		window.PostRenderUpdate();
	}

	return 0;
}