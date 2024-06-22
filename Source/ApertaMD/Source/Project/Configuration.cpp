#include "Configuration.hpp"

AMD_NAMESPACE_BEGIN

Status Configuration::AddTemplate(const std::string& name, const std::vector<EntryField>& fields)
{
	AMD_ASSERT(DoesTemplateNameExist(name) == false, "Attmpted to add a template with an existing name: \"%s\"", name.c_str())
	{
		return Status::FAIL;
	}

	templates.push_back({
		.name = name,
		.fields = fields
	});

	return Status::SUCCESS;
}

Status Configuration::GetTemplateByName(const std::string& name, EntryTemplate& returningEntryTemplate)
{
	for (const EntryTemplate& entryTemplate : templates)
	{
		if (entryTemplate.name == name)
		{
			returningEntryTemplate = entryTemplate;
			return Status::SUCCESS;
		}
	}

	// This will only be reached if no template with the given name was found
	AMD_ERROR("Attempted to get a template by a name which doesn't exist: \"%s\"", name.c_str());

	return Status::FAIL;
}

bool Configuration::DoesTemplateNameExist(const std::string& name)
{
	for (const EntryTemplate& entryTemplate : templates)
	{
		if (entryTemplate.name == name)
		{
			return true;
		}
	}

	return false;
}

AMD_NAMESPACE_END