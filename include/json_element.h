#pragma once
#include <string>

using string_t = std::string;

class Element {
public:
	virtual ~Element() {}
	//类型识别
	virtual bool is_value() const noexcept { return false; }
	virtual bool is_object() const noexcept { return false; }
	virtual bool is_array() const noexcept { return false; }
	//类型转换
	virtual Value* as_value() { throw TypeException("Invalid base type!"); }
	virtual Object* as_object() { throw TypeException("Invalid base type!"); }
	virtual Array* as_array() { throw TypeException("Invalid base type!"); }
	//通用操作
	virtual Element* copy() const = 0;
	virtual std::string serialize() const noexcept { return ""; }
	virtual void clear();
	//比较操作
	virtual bool operator==(const Element& other) const noexcept { return false; }
	virtual bool operator!=(const Element& other) const noexcept { return true; }
};