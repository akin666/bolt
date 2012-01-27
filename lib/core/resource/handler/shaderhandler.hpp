/*
 * shaderhandler.hpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#ifndef SHADERHANDLER_HPP_
#define SHADERHANDLER_HPP_

#include "handler.hpp"

namespace bolt
{
namespace resource
{

class ShaderHandler : public Handler
{
public:
	static const std::string fragmentExtension;
	static const std::string vertexExtension;
	static const std::string geometryExtension;
	static const std::string controlExtension;
	static const std::string evaluationExtension;
public:
	ShaderHandler();
	virtual ~ShaderHandler();

	virtual bool canHandle( const std::string& extension );
	virtual Work *handle( std::string alias , std::string path , std::string type );
};

}
} /* namespace bolt */
#endif /* SHADERHANDLER_HPP_ */

