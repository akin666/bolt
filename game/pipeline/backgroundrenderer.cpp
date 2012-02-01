/*
 * backgroundrenderer.cpp
 *
 *  Created on: 1.2.2012
 *      Author: akin
 */

#include "backgroundrenderer.hpp"
#include <singleton>
#include <component/common/positionproperty.hpp>
#include <component/common/fencecontroller.hpp>
#include <opengl>
#include <graphics/shader/shaderprogram.hpp>

namespace bolt
{
const std::string BackgroundRenderer::KEY("backgroundrenderer");

BackgroundRenderer::BackgroundRenderer()
: bolt::Controller( KEY , false ),
  program( NULL )
{
}

BackgroundRenderer::~BackgroundRenderer()
{
}

void BackgroundRenderer::setShaderProgram( ShaderProgram *app )
{
	program = app;
}

void BackgroundRenderer::getDependencies(bolt::StringSet & dep)
{
	dep.clear();
}

void BackgroundRenderer::initialize() throw (std::exception)
{
}

void BackgroundRenderer::start( bolt::ControllerNode& node )
{
	if( program != NULL )
	{
		// Render a QUAD using shader program..
	}
}

} /* namespace bolt */
