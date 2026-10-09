#pragma once
#include <variant>
#include <stdexcept>
#include "json_element.h"

using value_t = std::variant <
	std::nullptr_t,
	bool,
	int,
	double,
	string_t>;

class Value : public Element {
private:
	value_t m_value;
	//定义类型判断模板函数
	template <typename T>
	bool is_t() const noexcept {
		return std::holds_alternative<T>(m_value);
	}
	//定义类型获取模板函数
	template <typename T>
	T as_t() const {
		return std::get<T>(m_value);
	}

public:
	//初始化构造函数
	Value() : m_value(nullptr) {}
	Value(bool p_value) : m_value(p_value) {}
	Value(int p_value) : m_value(p_value) {}
	Value(double p_value) : m_value(p_value) {}
	Value(const string_t& p_value) : m_value(p_value) {}
	Value(const char* p_value) : Value((string_t)p_value) {} //委托构造

	//-----实现基类-----
	bool is_value() const noexcept override { return true; }
	Value* as_value() override { return this; }
	Element* copy() const noexcept override { return new Value(*this); } //待优化：1、智能指针；2、在内存耗尽时无法进行new，但因noexcept不会抛出错误
	//类型判断
	bool is_null() const noexcept { return is_t<std::nullptr_t>(); }
	bool is_bool() const noexcept { return is_t<bool>(); }
	bool is_int() const noexcept { return is_t<int>(); }
	bool is_double() const noexcept { return is_t<double>(); }
	bool is_string() const noexcept { return is_t<string_t>(); }
	bool is_number() const noexcept { return is_int() || is_double(); } //通用数字判断
	//类型获取
	bool as_bool() const {
		if (is_bool())
			return as_t<bool>();
		throw TypeException("Value is not a boolean");
	}
	bool as_int() const {
		if (is_int())
			return as_t<int>();
		throw TypeException("Value is not an integer");
	}
	double as_double() const {
		if (is_double())
			return as_t<double>();
		throw TypeException("Value is not a double");
	}
	string_t as_string() const {
		if (is_string())
			return as_t<string_t>();
		throw TypeException("Value is not a string");
	}
	//序列化
	std::string serialize() const noexcept override {
		if (is_bool())
			return as_bool() ? "true" : "false";
		else if(is_int())
			return std::to_string(as_int());
		else if (is_double())
			return std::to_string(as_double());
		else if (is_string())
			return "\"" + as_string() + "\"";
		else
			return "null";
	}
};