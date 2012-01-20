/*
 * fencecomponent.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef FENCECOMPONENT_HPP_
#define FENCECOMPONENT_HPP_

#include "../component.hpp"

namespace bolt
{
class FenceComponent: public bolt::Component
{
public:
	const static std::string INPUT;
	const static std::string SIMULATION;
	const static std::string LOGIC;
	const static std::string RENDER;
	const static std::string POSTPROCESS;
protected:
	bolt::StringSet& dependencies;
public:
	FenceComponent( std::string fencename , bolt::StringSet& dependencies );
	virtual ~FenceComponent();

	virtual bool initialize();

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ComponentNode& node );
};
}

#endif /* FENCECOMPONENT_HPP_ */
