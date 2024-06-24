#pragma once
#ifndef AMD_PROJECT_DATAINTERFACE
#define AMD_PROJECT_DATAINTERFACE

#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

#include "ErrorHandling/ErrorHandling.hpp"
#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

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
	bool IsProjectOpen();

private:
	DataInterface() = default;

	bool isProjectOpen = false;
	std::fstream projectFileHandle;
	nlohmann::json projectJSON;
};

AMD_NAMESPACE_END

#endif // ifndef AMD_PROJECT_DATAINTERFACE