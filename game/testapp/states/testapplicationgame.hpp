/*
 * testapplicationgame.hpp
 *
 *  Created on: 29.1.2012
 *      Author: akin
 */

#ifndef TESTAPPLICATIONGAME_HPP_
#define TESTAPPLICATIONGAME_HPP_

#include <pipeline/controller.hpp>
#include <input/mouse.hpp>
#include <tque>

namespace bolt
{
class ShaderProgram;
}

class TestApplicationGame: public bolt::Controller, public bolt::Mouse
{
public:
	const static std::string KEY;
protected:
	bool initialized;
	bolt::StringSet dependecies;
	bolt::ShaderProgram *shaderProgram;

	bolt::Entity box;
	bolt::Entity box2;
	bolt::Entity camera;

	int times;

	bool left;
	bool right;

	class MouseEvent {
	public:
		enum MType {
			WHEEL,
			BUTTON,
			MOVE
		};
		MType type;
		float x,y;
		float wheel;
		float state;
		bolt::Button button;

		MouseEvent():x(0),y(0),wheel(0),state(0),button(bolt::ADDON_LAST){}
	};

	bolt::TQue<MouseEvent*> mouse;
	bolt::TQue<MouseEvent*> freeMouse;

public:
	TestApplicationGame();
	virtual ~TestApplicationGame();

	virtual void initialize() throw (std::exception);
	virtual void start( bolt::ControllerNode& node );

	// Mouse
	virtual void handleMouseMove( float x , float y );
	virtual void handleMouseButton( bolt::Button button , float state );
	virtual void handleMouseWheel( float val );
};

#endif /* TESTAPPLICATIONGAME_HPP_ */
