#pragma once

#include "Utilities/Macros.hpp"
#include "UI/Layer.hpp"

#include "imgui.h"

AMD_NAMESPACE_BEGIN

class TestLayer : public Layer
{
public:
	TestLayer() = default;

	Status OnUpdate() override
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Create"))
				{
				}

				if (ImGui::MenuItem("Open", "Ctrl+O"))
				{
				}

				ImGui::BeginDisabled(true);
				if (ImGui::MenuItem("Save", "Ctrl+S"))
				{
				}
				ImGui::EndDisabled();

				if (ImGui::MenuItem("Save as.."))
				{
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		return Status::SUCCESS;
	}

private:

};

AMD_NAMESPACE_END