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

	// This takes a project file and populates all of the members of this class to match the project
	Status LoadProject(const std::filesystem::path&);

private:
	Project() = default;

	nlohmann::json projectFileData;
	std::fstream projectFileHandle;
	Configuration configuration;
};

AMD_NAMESPACE_END

#endif // ifndef AMD_PROJECT_PROJECT