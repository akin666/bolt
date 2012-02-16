/*
 * graphicslandcontroller.hpp
 *
 *  Created on: 17.2.2012
 *      Author: akin
 */

#ifndef GRAPHICSLANDCONTROLLER_HPP_
#define GRAPHICSLANDCONTROLLER_HPP_

#include <pipeline/controller.hpp>
#include <graphics/bufferobject.hpp>

namespace bolt
{
class ShaderProgram;
class Uniform;

class GraphicsLandController: public bolt::Controller
{
public:
	const static std::string KEY;
protected:
	bool initialized;
	bolt::StringSet dependencies;

	bolt::BufferObject vertexBuffer;
	bolt::BufferObject indexBuffer;

	typedef std::set< bolt::uint > EntitySet;

	EntitySet entities;
public:
	GraphicsLandController( std::string name , bolt::StringSet& dependencies );
	virtual ~GraphicsLandController();

	virtual void initialize();

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void start( bolt::ControllerNode& node );
};

} /* namespace bolt */
#endif /* GRAPHICSLANDCONTROLLER_HPP_ */
