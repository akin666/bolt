/*
 * handler.hpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#ifndef HANDLER_HPP_
#define HANDLER_HPP_

#include <string>
#include <work>

namespace bolt
{
namespace resource
{

class Handler
{
public:
	Handler();
	virtual ~Handler();

	virtual bool canHandle( const std::string& extension );
	virtual Work *handle( std::string alias , std::string path , std::string type );
};

}
} /* namespace bolt */
#endif /* HANDLER_HPP_ */
