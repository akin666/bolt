/*
 * graphicsexception.hpp
 *
 *  Created on: 31.1.2012
 *      Author: akin
 */

#ifndef GRAPHICSEXCEPTION_HPP_
#define GRAPHICSEXCEPTION_HPP_

#include <stdexcept>

namespace bolt
{

class GraphicsException : public std::runtime_error
{
public:
	GraphicsException( std::string msg );
	virtual ~GraphicsException() throw();
};

} /* namespace bolt */
#endif /* GRAPHICSEXCEPTION_HPP_ */
