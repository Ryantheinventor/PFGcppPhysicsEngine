#pragma once
#include <type_traits>
template<typename Enum>
Enum operator |(Enum lhs, Enum rhs) 
{
	static_assert(std::is_enum<Enum>::value,
		"tempalate parameter is not an enum type");

	using underlying = typename std::underlying_type<Enum>::type;

	return static_cast<Enum>(
		static_cast<underlying>(lhs) | 
		static_cast<underlying>(rhs)
		);
}