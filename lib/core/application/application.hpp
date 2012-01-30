/*
 * application.hpp
 *
 *  Created on: 8.1.2012
 *      Author: akin
 *
 *      Current Application is saved in Singleton class.
 *      getSingleton<Application>()
 *      setSingleton<Application>( Application* )
 */

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include "applicationstate.hpp"

#include <log.hpp>
#include <event/eventhandler.hpp>
#include <exception/exceptionhandler.hpp>
#include <event/eventhandler.hpp>
#include <exception/exceptionhandler.hpp>

namespace bolt
{

class Application
	: public EventHandler ,
	  public ExceptionHandler,
	  public ApplicationState
{
public:
	Application();
	virtual ~Application();

	// The whole thing is running, when entering run -> video & audio exists etc.
	virtual void run();
};

} /* namespace bolt */
#endif /* APPLICATION_HPP_ */
