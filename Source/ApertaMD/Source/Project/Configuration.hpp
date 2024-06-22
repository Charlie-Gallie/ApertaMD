#pragma once
#ifndef AMD_PROJECT_CONFIGURATION
#define AMD_PROJECT_CONFIGURATION

#include <any>
#include <string>
#include <vector>

#include "ErrorHandling/ErrorHandling.hpp"
#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

class Configuration
{
public:
	Configuration() = default;

	struct EntryField
	{
		std::string name;
		std::string type;
		std::any value;
	};

	struct EntryTemplate
	{
		std::string name;
		std::vector<EntryField> fields;
	};

	/**
	* Adds a template to the internal configuration list of entry templates
	* Retusn Status::FAIL if a template with the name already exists, otherwise Status::SUCCESS
	* 
	* TODO: This is dumb, why don't you just pass in the full struct rather than the name seperate
	*/
	Status AddTemplate(const std::string&, const std::vector<EntryField>&);

	/**
	* Assigns the value of the EntryTemplate& type to the value of the entry template with a given name
	* Returns Status::FAIL if a template with the given name doesn't exist, otherwise Status::SUCCESS
	* Upon failure, the returning value of the entry template is undefined
	*/
	Status GetTemplateByName(const std::string&, EntryTemplate&);

	/**
	* Returns true if an entry template with the name already exists within the internal list, otherwise false
	*/
	bool DoesTemplateNameExist(const std::string&);

private:
	std::vector<EntryTemplate> templates;
};

AMD_NAMESPACE_END

#endif // ifndef AMD_PROJECT_CONFIGURATION