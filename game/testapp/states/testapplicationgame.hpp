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
#include <input/osinput.hpp>
#include <tque>

namespace bolt
{
class ShaderProgram;
}

class TestApplicationGame: public bolt::Controller, public bolt::Mouse , public bolt::OSInput
{
public:
	const static std::string KEY;
protected:
	bool initialized;
	bolt::StringSet dependecies;
	bolt::ShaderProgram *shaderProgram;

	bolt::Entity box;
	bolt::Entity box2;
	bolt::Entity land;
	bolt::Entity camera;

	int times;

	bool left;
	bool right;
	bool mid;

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

		MouseEvent():x(0),y(0),wheel(0),state(0),button(bolt::NONE){}
	};

	bolt::TQue<MouseEvent*> mouse;
	bolt::TQue<MouseEvent*> freeMouse;

public:
	TestApplicationGame();
	virtual ~TestApplicationGame();

	virtual void initialize();
	virtual void start( bolt::ControllerNode& node );

	// Mouse
	virtual void handleMouseMove( float x , float y );
	virtual void handleMouseButton( bolt::Button button , float state );
	virtual void handleMouseWheel( float val );

	// OSInput
	virtual bool handleClose();
};

#endif /* TESTAPPLICATIONGAME_HPP_ */
