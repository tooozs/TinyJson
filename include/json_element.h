#pragma once
#include <string>

using string_t = std::string;

class Element {
public:
	virtual ~Element() {}

	virtual bool is_value() const noexcept { return false; }
	virtual bool is_object() const noexcept { return false; }
	virtual bool is_array() const noexcept { return false; }

};