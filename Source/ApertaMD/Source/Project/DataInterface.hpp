#pragma once
#ifndef AMD_PROJECT_DATAINTERFACE
#define AMD_PROJECT_DATAINTERFACE

#include <filesystem>
#include <fstream>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "ErrorHandling/ErrorHandling.hpp"
#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

/**
* This is used for the class member DataInterface::accessorMap
* This is used to access project data regions agnostic to their string or binary name
*/
enum class Accessor
{
	APERTAMD_VERSION_MAJOR,
	APERTAMD_VERSION_MINOR,
	APERTAMD_VERSION_PATCH,
	PROJECT_ENVIRONMENT,
	PROJECT_DEFINITION,
	FIELDS,
	NAME,
	DATA_TYPE,
	ENTRY_TEMPLATES,
	ENTRY_TEMPLATE
};

class DataInterface
{
public:
	static inline DataInterface& GetInstance()
	{
		static DataInterface instance;
		return instance;
	}

	/**
	* This will load a project by a given path. Internally, this will make the JSON data structure for it.
	* Returns Status::SUCCESS if the project loaded successfully, otherwise Status::FAIL
	*/
	Status LoadProject(const std::filesystem::path&);

	/**
	* Returns true is there is currently an open project, otherwise false
	*/
	bool IsDataLoaded();

private:
	DataInterface() = default;

	bool isDataLoaded = false;
	std::fstream projectFileHandle;
	nlohmann::json projectJSON;

	/**
	* This is used to separate the string literal of the project file entries to the code implementation
	* This allows auto-completion, being strongly typed, and easy refactoring if necessary
	*/
	static inline std::unordered_map<Accessor, std::string> accessorMap =
	{
		{ Accessor::APERTAMD_VERSION_MAJOR, "apertamd_version_major" },
		{ Accessor::APERTAMD_VERSION_MINOR, "apertamd_version_minor" },
		{ Accessor::APERTAMD_VERSION_PATCH, "apertamd_version_patch" },
		{ Accessor::PROJECT_ENVIRONMENT, "project_environment" },
		{ Accessor::PROJECT_DEFINITION, "project_definition" },
		{ Accessor::FIELDS, "fields" },
		{ Accessor::NAME, "name" },
		{ Accessor::DATA_TYPE, "data_type" },
		{ Accessor::ENTRY_TEMPLATES, "entry_templates" },
		{ Accessor::ENTRY_TEMPLATE, "entry_template" }
	};
};

AMD_NAMESPACE_END

#endif // ifndef AMD_PROJECT_DATAINTERFACE