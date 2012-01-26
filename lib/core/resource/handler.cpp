/*
 * handler.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "handler.hpp"
#include <iostream>

namespace bolt
{
namespace resource
{

Handler::Handler()
{
}

Handler::~Handler()
{
}

bool Handler::canHandle( const std::string& extension )
{
	return false;
}

Work *Handler::handle( const std::string& alias , const std::string path )
{
	return NULL;
}

}
} /* namespace bolt */
