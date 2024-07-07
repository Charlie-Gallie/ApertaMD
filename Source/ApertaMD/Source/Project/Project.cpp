#include "Project.hpp"

#include "DataInterface.hpp"

#include <iostream> // debug

AMD_NAMESPACE_BEGIN

Status Project::LoadProject(const std::filesystem::path& projectPath)
{
	DataInterface& dataInterface = DataInterface::GetInstance();

	// Attempt to load project file
	Status loadProjectStatus = dataInterface.LoadData(projectPath);

	AMD_ASSERT(loadProjectStatus == Status::SUCCESS, "Failed to load project: \"%s\"", projectPath.string().c_str())
	{
		return Status::FAIL;
	}

	Status populateEnvironmentFields = PopulateEnvironmentFields();
	AMD_ASSERT(populateEnvironmentFields == Status::SUCCESS, "Failed to populate environment fields")
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

Status Project::PopulateEnvironmentFields()
{
	DataInterface& dataInterface = DataInterface::GetInstance();
	Status getValueStatus;

	// Get project name
	getValueStatus = dataInterface.GetValue(environment.name, Accessor::PROJECT_ENVIRONMENT, Accessor::NAME);
	AMD_ASSERT(getValueStatus == Status::SUCCESS, "Failed to get project name")
	{
		return Status::FAIL;
	}

	// Get project major version
	getValueStatus = dataInterface.GetValue(environment.versionMajor, Accessor::PROJECT_ENVIRONMENT, Accessor::APERTAMD_VERSION_MAJOR);
	AMD_ASSERT(getValueStatus == Status::SUCCESS, "Failed to get project major version")
	{
		return Status::FAIL;
	}

	// Get project minor version
	getValueStatus = dataInterface.GetValue(environment.versionMinor, Accessor::PROJECT_ENVIRONMENT, Accessor::APERTAMD_VERSION_MINOR);
	AMD_ASSERT(getValueStatus == Status::SUCCESS, "Failed to get project minor version")
	{
		return Status::FAIL;
	}

	// Get project patch version
	getValueStatus = dataInterface.GetValue(environment.versionPatch, Accessor::PROJECT_ENVIRONMENT, Accessor::APERTAMD_VERSION_PATCH);
	AMD_ASSERT(getValueStatus == Status::SUCCESS, "Failed to get project patch version")
	{
		return Status::FAIL;
	}

	return Status::SUCCESS;
}

std::string Project::Environment::GetName()
{
	return name;
}

U32 Project::Environment::GetVersionMajor()
{
	return versionMajor;
}

U32 Project::Environment::GetVersionMinor()
{
	return versionMinor;
}

U32 Project::Environment::GetVersionPatch()
{
	return versionPatch;
}

AMD_NAMESPACE_END