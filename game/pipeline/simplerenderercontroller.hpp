/*
 * SimpleRendererController.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef SIMPLETENDERERCONTROLLER_HPP_
#define SIMPLETENDERERCONTROLLER_HPP_

#include <component/controller.hpp>
#include <graphics/bufferobject.hpp>
#include <glm/glm>

class SimpleRendererController: public bolt::Controller
{
public:
	const static std::string KEY;
protected:
	bool initialized;
	bolt::StringSet dependecies;

	bolt::BufferObject vertexBuffer;
	bolt::BufferObject textureBuffer;
	bolt::BufferObject indexBuffer;

	glm::mat4 model;
	glm::mat4 lense;
public:
	SimpleRendererController();
	virtual ~SimpleRendererController();

	virtual void initialize() throw (std::exception);

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ControllerNode& node );
};

#endif /* SIMPLETENDERERCOMPONENT_HPP_ */
