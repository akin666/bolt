
#ifndef EXCEPTIONHANDLER_HPP_
#define EXCEPTIONHANDLER_HPP_

#include <exception>

namespace bolt
{

class ExceptionHandler
{
public:
	ExceptionHandler();
	virtual ~ExceptionHandler();

	virtual void handleException( const std::exception& exeption );
};

} /* namespace bolt */
#endif
