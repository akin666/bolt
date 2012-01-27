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

Work *Handler::handle( std::string alias , std::string path , std::string type )
{
	return NULL;
}

}
} /* namespace bolt */
