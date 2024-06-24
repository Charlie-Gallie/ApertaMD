#include "DataInterface.hpp"

AMD_NAMESPACE_BEGIN

bool DataInterface::IsProjectOpen()
{
	return isProjectOpen;
}

Status DataInterface::LoadProject(const std::filesystem::path& projectPath)
{
	// Attempt to open the file
	projectFileHandle.open(projectPath, std::fstream::in | std::fstream::out);

	// Ensure the file has successfully opened
	AMD_ASSERT(projectFileHandle.is_open() == true, "Failed to open project file: \"%s\"", projectPath.string().c_str())
	{
		return Status::FAIL;
	}

	// Attempt to parse the JSON project file
	projectJSON = projectJSON.parse(
		projectFileHandle,
		nullptr, // Parser callback - "a parser callback function of type parser_callback_t which is used to
		         // control the deserialization by filtering unwanted values (optional)" - nlohmann json API
		false // Disallow exceptions
	);

	// Throw if JSON parsing failed
	AMD_ASSERT(projectJSON.is_discarded() == false, "Failed to parse project file - The contents are likely malformed")
	{
		return Status::FAIL;
	}

	// Specify that the project is loaded
	isProjectOpen = true;

	return Status::SUCCESS;
}

AMD_NAMESPACE_END