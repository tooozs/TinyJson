#include <stdexcept>

//异常类
class TypeException : public std::runtime_error {
public:
	explicit TypeException(const std::string& msg) : std::runtime_error(msg) {}
};
