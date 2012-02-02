/*
 * backgroundrenderer.hpp
 *
 *  Created on: 1.2.2012
 *      Author: akin
 */

#ifndef BACKGROUNDRENDERER_HPP_
#define BACKGROUNDRENDERER_HPP_

#include <component/controller.hpp>
#include <graphics/bufferobject.hpp>
#include <system/clock.hpp>

namespace bolt
{
class ShaderProgram;
class Uniform;
class BackgroundRenderer : public bolt::Controller
{
public:
	const static std::string KEY;
protected:
	ShaderProgram *program;

	Clock myTime;

	Uniform *resolution;
	Uniform *time;

	BufferObject vertexBuffer;
	BufferObject indexBuffer;
public:
	BackgroundRenderer();
	virtual ~BackgroundRenderer();

	void setShaderProgram( ShaderProgram *app );

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void initialize() throw (std::exception);
	virtual void start( bolt::ControllerNode& node );
};

} /* namespace bolt */
#endif /* BACKGROUNDRENDERER_HPP_ */
