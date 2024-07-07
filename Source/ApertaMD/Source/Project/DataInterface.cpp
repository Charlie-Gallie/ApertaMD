#include "DataInterface.hpp"

AMD_NAMESPACE_BEGIN

bool DataInterface::IsDataLoaded()
{
	return isDataLoaded;
}

Status DataInterface::LoadData(const std::filesystem::path& projectPath)
{
	// Attempt to open the file
	dataFileHandle.open(projectPath, std::fstream::in | std::fstream::out);

	// Ensure the file has successfully opened
	AMD_ASSERT(dataFileHandle.is_open() == true, "Failed to open project file: \"%s\"", projectPath.string().c_str())
	{
		return Status::FAIL;
	}

	// Attempt to parse the JSON project file
	dataJSON = dataJSON.parse(
		dataFileHandle,
		nullptr, // Parser callback - "a parser callback function of type parser_callback_t which is used to
		         // control the deserialization by filtering unwanted values (optional)" - nlohmann json API
		false // Disallow exceptions
	);

	// Throw if JSON parsing failed
	AMD_ASSERT(dataJSON.is_discarded() == false, "Failed to parse project file - The contents are likely malformed")
	{
		return Status::FAIL;
	}

	// Specify that the project is loaded
	isDataLoaded = true;

	return Status::SUCCESS;
}

AMD_NAMESPACE_END