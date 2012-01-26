/*
 * texthandler.hpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#ifndef TEXTHANDLER_HPP_
#define TEXTHANDLER_HPP_

#include <resource/handler.hpp>

namespace bolt
{
namespace resource
{

class TextHandler : public Handler
{
public:
	TextHandler();
	virtual ~TextHandler();

	virtual bool canHandle( const std::string& extension );
	virtual Work *handle( const std::string& alias , const std::string path );
};

}
} /* namespace bolt */
#endif /* TEXTHANDLER_HPP_ */
