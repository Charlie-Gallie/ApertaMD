#include "Project.hpp"

AMD_NAMESPACE_BEGIN

Status Project::LoadProject(const std::filesystem::path& projectPath)
{
	AMD_ASSERT(std::filesystem::exists(projectPath), "Attemped to load project which does not exist: \"%s\"", projectPath.string().c_str())
	{
		return Status::FAIL;
	}

	// Attempt to open the project file
	projectFileHandle.open(projectPath, std::fstream::in | std::fstream::out);

	AMD_ASSERT(projectFileHandle.is_open(), "Failed to open project: \"%s\"", projectPath.string().c_str())
	{
		return Status::FAIL;
	}

	// If opening the file was successful, parse JSON into the project data
	auto parseStatus = projectFileData.parse(
		projectFileHandle,
		nullptr, // Callback to handle unexpected values
		false // Disallow exceptions
	);

	// Ensure the file was properly parsed
	AMD_ASSERT(parseStatus != nlohmann::json::value_t::discarded, "Failed to parse project file: \"%s\"", projectPath.string().c_str())
	{
		return Status::FAIL;
	}

	return Status::SUCCESS;
}

AMD_NAMESPACE_END