/*
 * shaderhandler.hpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#ifndef SHADERHANDLER_HPP_
#define SHADERHANDLER_HPP_

#include <resource/handler.hpp>

namespace bolt
{
namespace resource
{

class ShaderHandler : public Handler
{
public:
	ShaderHandler();
	virtual ~ShaderHandler();

	virtual bool canHandle( const std::string& extension );
	virtual Work *handle( const std::string& alias , const std::string path );
};


class ShaderWork : public Work
{
protected:
	std::string alias;
	std::string path;
public:
	ShaderWork( const std::string& alias , const std::string path );
	virtual ~ShaderWork();

	virtual bool begin();
	virtual void run();
	virtual void end();
};

}
} /* namespace bolt */
#endif /* SHADERHANDLER_HPP_ */

