#pragma once
#ifndef AMD_PROJECT_PROJECT
#define AMD_PROJECT_PROJECT

#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

#include "Configuration.hpp"
#include "ErrorHandling/ErrorHandling.hpp"
#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

class Project
{
public:
	static inline Project& GetInstance()
	{
		static Project instance;
		return instance;
	}

	/**
	* This takes a project file and populates all of the members of this class to match the project
	*/
	Status LoadProject(const std::filesystem::path&);

	/**
	* Returns true if there is currently a loaded project, otherwise false
	*/
	bool IsProjectOpen();

private:
	Project() = default;

	bool isProjectOpen = false;
	nlohmann::json projectFileData;
	std::fstream projectFileHandle;
	Configuration configuration;

	/**
	* Assigns the boolean reference to true if the required keys exist to load a project, otherwise assigns false
	* This does not completely validate the project data
	* Returns Status::SUCCESS always
	* In the instance the call fails, the boolean reference is left in an undefined state
	* 
	* In the future, this function should be somehow replaced with a system which has a realization of all keys which should exist
	* E.g., an enumeration to associate with the keys, something like ProjectConfiguration.GetValue(ProjectConfigKeys<Keys::PROJECT_NAME>());
	* The example is long but it's just to convey the point
	*/
	Status DoBasicKeysExist(bool&);

	/**
	* This function takes the project file data and parses it into the project configuration
	* Returns Status::FAIL if there is a failure parsing, otherwise Status::SUCCESS
	*/
	Status ParseConfiguration();
};

AMD_NAMESPACE_END

#endif // ifndef AMD_PROJECT_PROJECT