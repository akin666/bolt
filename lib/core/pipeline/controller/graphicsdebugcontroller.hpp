/*
 * GraphicsDebugController.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef GRAPHICSDEBUGCONTROLLER_HPP_
#define GRAPHICSDEBUGCONTROLLER_HPP_

#include <pipeline/controller.hpp>
#include <graphics/bufferobject.hpp>
#include <glm/glm>
#include <set>
#include <common>

namespace bolt
{
class GraphicsDebugController: public bolt::Controller
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
	GraphicsDebugController( std::string name , bolt::StringSet& dependencies );
	virtual ~GraphicsDebugController();

	virtual void initialize() throw (std::exception);

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ControllerNode& node );
};
}

#endif /* GraphicsDebugController */
