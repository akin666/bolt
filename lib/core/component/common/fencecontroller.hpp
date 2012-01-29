/*
 * FenceController.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef FENCECONTROLLER_HPP_
#define FENCECONTROLLER_HPP_

#include <component/controller.hpp>
#include <common>

namespace bolt
{
class FenceController: public bolt::Controller
{
public:
	const static std::string INPUT;
	const static std::string SIMULATION;
	const static std::string LOGIC;
	const static std::string RENDER;
	const static std::string POSTPROCESS;
protected:
	bolt::StringSet dependencies;
public:
	FenceController( std::string fencename , bolt::StringSet& dependencies );
	virtual ~FenceController();

	virtual void initialize() throw (std::exception);

	virtual void getDependencies( bolt::StringSet& dep );

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	virtual void start( bolt::ControllerNode& node );
};
}

#endif /* FENCECONTROLLER_HPP_ */
