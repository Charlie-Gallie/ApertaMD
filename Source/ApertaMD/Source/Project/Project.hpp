#pragma once
#ifndef AMD_PROJECT_PROJECT
#define AMD_PROJECT_PROJECT

#include <filesystem>

#include "Configuration.hpp"
#include "ErrorHandling/ErrorHandling.hpp"
#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

class Project
{
public:
	class Environment
	{
		friend class Project;
	public:
		std::string GetName();
		U32 GetVersionMajor();
		U32 GetVersionMinor();
		U32 GetVersionPatch();

	private:
		Environment() = default;

		std::string name = "";
		U32 versionMajor = 0;
		U32 versionMinor = 0;
		U32 versionPatch = 0;
	};

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

	Status PopulateEnvironmentFields();

	Environment environment;
	bool isProjectOpen = false;
};

AMD_NAMESPACE_END

#endif // ifndef AMD_PROJECT_PROJECT