#pragma once
#include <exception>
#define DERIVE_FROM_STD_EXCEPTION(name)														\
class name : public std::exception															\
{																							\
public:																						\
	explicit name(const std::string& message = std::string()) : msg_(message) {}			\
	virtual ~name() throw() {}																\
	virtual const char* what() const throw() { return msg_.c_str(); }						\
protected:																					\
	std::string msg_;																		\
}																							//end of macro
