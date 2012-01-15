/*
 * application.hpp
 *
 *  Created on: 8.1.2012
 *      Author: akin
 *
 *      Current Application is saved in Singleton class.
 *      Singleton<Application>::get()
 *      Singleton<Application>::set( Application* )
 */

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include "applicationstate.hpp"

#include <log.hpp>
#include <event/eventhandler.hpp>
#include <exception/exceptionhandler.hpp>
#include <event/eventhandler.hpp>
#include <exception/exceptionhandler.hpp>
#include <input/keyboardinputhandler.hpp>
#include <input/mouseinputhandler.hpp>
#include <input/joystickinputhandler.hpp>

namespace bolt
{

class Application
	: public EventHandler ,
	  public Log ,
	  public ExceptionHandler,
	  public ApplicationState ,
	  public KeyboardInputHandler ,
	  public MouseInputHandler ,
	  public JoystickInputHandler
{
public:
	Application();
	virtual ~Application();

	virtual void run();
};

} /* namespace bolt */
#endif /* APPLICATION_HPP_ */
