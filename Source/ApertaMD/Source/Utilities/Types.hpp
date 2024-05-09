#pragma once
#ifndef AMD_UTILITIES_TYPES
#define AMD_UTILITIES_TYPES

#include <cstdint>

#include "Utilities/Macros.hpp"

AMD_NAMESPACE_BEGIN

using I8 = std::int8_t;
using I16 = std::int16_t;
using I32 = std::int32_t;
using I64 = std::int64_t;

using U8 = std::uint8_t;
using U16 = std::uint16_t;
using U32 = std::uint32_t;
using U64 = std::uint64_t;

using Char8 = char;
using UChar8 = unsigned char;
using Char16 = char16_t;
using Char32 = char32_t;

using Byte = unsigned char;

using Size = decltype(sizeof(0));

template<Size>
struct WordSize;

template<>
struct WordSize<4>
{
	using Type = U32;
};

template<>
struct WordSize<8>
{
	using Type = U64;
};

using Word = WordSize<sizeof(void*)>::Type;

AMD_NAMESPACE_END

#endif // ifndef AMD_UTILITIES_TYPES