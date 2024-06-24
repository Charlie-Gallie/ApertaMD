#include "Project.hpp"

#include <iostream> // debug

AMD_NAMESPACE_BEGIN

Status Project::LoadProject(const std::filesystem::path& projectPath)
{
	std::string projectPathAsString = projectPath.string();

	AMD_ASSERT(std::filesystem::exists(projectPath), "Attemped to load project which does not exist: \"%s\"", projectPathAsString.c_str())
	{
		return Status::FAIL;
	}

	// Attempt to open the project file
	projectFileHandle.open(projectPath, std::fstream::in | std::fstream::out);

	AMD_ASSERT(projectFileHandle.is_open(), "Failed to open project: \"%s\"", projectPathAsString.c_str())
	{
		return Status::FAIL;
	}

	// If opening the file was successful, parse JSON into the project data
	projectFileData = nlohmann::json::parse(
		projectFileHandle,
		nullptr, // Callback to handle unexpected values
		false // Disallow exceptions
	);

	// Ensure the file was properly parsed
	AMD_ASSERT(projectFileData.is_discarded() == false, "Failed to parse project file: \"%s\". This probably means the project file contains malformed JSON.", projectPathAsString.c_str())
	{
		return Status::FAIL;
	}

	// Parse the project data into the project configuration structure
	Status parseConfigurationStatus = ParseConfiguration();

	AMD_ASSERT(parseConfigurationStatus == Status::SUCCESS, "Failed to parse project configuration: \"%s\"", projectPathAsString.c_str())
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

Status Project::DoBasicKeysExist(bool& keysExist)
{
	keysExist = true;

	// Check the section "project_configuration" exists
	keysExist &= projectFileData.contains("project_configuration");

	// Check if all the required keys under "project_configuration" exists
	const char* projectConfigurationKeys[] = {
		"name",
		"entry_templates"
	};

	for (const char* keyName : projectConfigurationKeys)
	{
		keysExist &= projectFileData["project_configuration"].contains(keyName);

		// TODO: Quit early if any return false
	}

	return Status::SUCCESS;
}

Status Project::ParseConfiguration()
{
	// Get whether the basic required keys exist
	bool doBasicKeysExist = false;
	AMD_ASSERT(DoBasicKeysExist(doBasicKeysExist) == Status::SUCCESS, "Failed to check if basic keys exist while parsing configuration")
	{
		return Status::FAIL;
	}

	// Error if keys don't exist
	AMD_ASSERT(doBasicKeysExist == true, "The project file is invalid: The required basic keys to parse the project do not exist")
	{
		return Status::FAIL;
	}

	auto entryTemplatesData = projectFileData["project_configuration"]["entry_templates"];

	for (auto& entryTemplateData : entryTemplatesData)
	{
		Configuration::EntryTemplate entryTemplate;
		entryTemplate.name = entryTemplateData["name"].get<std::string>();

		for (auto& fieldTemplate : entryTemplateData["fields"])
		{
			entryTemplate.fields.push_back({
				.name = fieldTemplate["name"].get<std::string>(),
				.type = fieldTemplate["data_type"].get<std::string>()
			});
		}

		configuration.AddTemplate(entryTemplate.name, entryTemplate.fields);
	}

	return Status::SUCCESS;
}

AMD_NAMESPACE_END