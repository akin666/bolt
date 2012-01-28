
#include "exceptionhandler.hpp"
#include <log>

namespace bolt
{

ExceptionHandler::ExceptionHandler()
{
}

ExceptionHandler::~ExceptionHandler()
{
}

void ExceptionHandler::handleException( const std::exception& exeption )
{
	// The default behavior is GOOD to have.
	// This means, you do not need to write the exception handling right away.
	// But also, important note is, that it actually reports something, somewhere.
	LOG_ERROR << "Received unhandled exception!! " << exeption.what() << std::endl;
}

} /* namespace bolt */
