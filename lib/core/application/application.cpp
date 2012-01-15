/*
 * application.cpp
 *
 *  Created on: 8.1.2012
 *      Author: akin
 */

#include "application.hpp"
#include <log>

namespace bolt
{

Application::Application()
{
}

Application::~Application()
{
}

void Application::run()
{
	LOG_OUT << "Hi!\nTo use properly this system, you need to override Application and set Main ApplicationPolicy to use your Application.\nMore on this, read Main class." << std::endl;
}

} /* namespace bolt */
