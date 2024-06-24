#include "Project.hpp"

#include "DataInterface.hpp"

AMD_NAMESPACE_BEGIN

Status Project::LoadProject(const std::filesystem::path& projectPath)
{
	DataInterface& dataInterface = DataInterface::GetInstance();

	// Attempt to load project file
	Status loadProjectStatus = dataInterface.LoadProject(projectPath);

	AMD_ASSERT(loadProjectStatus == Status::SUCCESS, "Failed to load project: \"%s\"", projectPath.string().c_str())
	{
		return Status::FAIL;
	}



	// Specify that the project is now open
	isProjectOpen = true;

	return Status::SUCCESS;
}

bool Project::IsProjectOpen()
{
	return isProjectOpen;
}

AMD_NAMESPACE_END