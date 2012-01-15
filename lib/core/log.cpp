/*
 * applicationlog.cpp
 *
 *  Created on: 8.1.2012
 *      Author: akin
 */

#include "log.hpp"
#include <iostream>

namespace bolt
{
Log::Log()
{
}

Log::~Log()
{
}

std::ostream& Log::error()
{
	return std::cerr;
}

std::ostream& Log::warning()
{
	return std::cout;
}

std::ostream& Log::log()
{
	return std::cout;
}

std::ostream& Log::out()
{
	return std::cout;
}
}
