/*
 * GraphicsBackgroundController.hpp
 *
 *  Created on: 1.2.2012
 *      Author: akin
 */

#ifndef GRAPHICSBACKGROUNDCONTROLLER_HPP_
#define GRAPHICSBACKGROUNDCONTROLLER_HPP_

#include <component/controller.hpp>
#include <graphics/bufferobject.hpp>
#include <system/clock.hpp>

namespace bolt
{
class ShaderProgram;
class Uniform;
class GraphicsBackgroundController : public bolt::Controller
{
public:
	const static std::string KEY;
protected:
	bolt::StringSet dependencies;

	ShaderProgram *program;

	Clock myTime;

	Uniform *resolution;
	Uniform *time;

	BufferObject vertexBuffer;
	BufferObject indexBuffer;
public:
	GraphicsBackgroundController( std::string name , bolt::StringSet& dependencies );
	virtual ~GraphicsBackgroundController();

	void setShaderProgram( ShaderProgram *app );

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void initialize() throw (std::exception);
	virtual void start( bolt::ControllerNode& node );
};

} /* namespace bolt */
#endif /* GRAPHICSBACKGROUNDCONTROLLER_HPP_ */
