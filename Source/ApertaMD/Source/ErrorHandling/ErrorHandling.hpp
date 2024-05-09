#pragma once
#ifndef AMD_ERRORHANDLING_ERRORHANDLING
#define AMD_ERRORHANDLING_ERRORHANDLING

#include "Utilities/Macros.hpp"
#include "Utilities/Types.hpp"

AMD_NAMESPACE_BEGIN

enum class Status : Word
{
	SUCCESS = static_cast<Word>(true),
	FAIL = static_cast<Word>(false)
};

#define AMD_ERROR(message, ...) \
	std::printf(message "\n", __VA_ARGS__)

#define AMD_ASSERT(condition, message, ...) \
	if (static_cast<bool>(condition) == false && ((AMD_ERROR(message, __VA_ARGS__)), true))

AMD_NAMESPACE_END

#endif // ifndef AMD_ERRORHANDLING_ERRORHANDLING