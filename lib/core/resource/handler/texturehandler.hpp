/*
 * texturehandler.hpp
 *
 *  Created on: 27.1.2015
 *      Author: akin
 */

#ifndef TEXTUREHANDLER_HPP_
#define TEXTUREHANDLER_HPP_

#include "handler.hpp"

namespace bolt
{
namespace resource
{

class TextureHandler : public Handler
{
public:
	TextureHandler();
	virtual ~TextureHandler();

	virtual bool canHandle( const std::string& extension );
	virtual Work *handle( std::string alias , std::string path , std::string type );
};

}
} /* namespace bolt */
#endif /* TextureHandler */
