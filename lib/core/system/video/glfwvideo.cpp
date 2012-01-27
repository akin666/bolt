/*
 * glfwvideo.cpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#include "glfwvideo.hpp"
#include <log>
#include <opengl>

// if components are not initialized/set, SET EM!
#include <singleton>
#include <component/input/touchcontroller.hpp>
#include <component/input/keyboardcontroller.hpp>
#include <component/input/mousecontroller.hpp>
#include <component/input/joystickcontroller.hpp>

namespace bolt
{

// GLFW INPUT HANDLING
namespace GLFWInputHandling
{
	TouchController *touch = NULL;
	KeyboardController *keyboard = NULL;
	MouseController *mouse = NULL;
	JoystickController *joystick = NULL;

	int mouseX = 0;
	int mouseY = 0;
	int mouseWheel = 0;

	void setup()
	{
		// Setup components, IF needed.
		touch = getSingleton<TouchController>();
		keyboard = getSingleton<KeyboardController>();
		mouse = getSingleton<MouseController>();
		joystick = getSingleton<JoystickController>();

		// Setup input components
		if( touch == NULL )
		{
			touch = new TouchController();
			setSingleton<TouchController>(touch);
		}
		if( keyboard == NULL )
		{
			keyboard = new KeyboardController();
			setSingleton<KeyboardController>(keyboard);
		}
		if( mouse == NULL )
		{
			mouse = new MouseController();
			setSingleton<MouseController>(mouse);
		}
		if( joystick == NULL )
		{
			joystick = new JoystickController();
			setSingleton<JoystickController>(joystick);
		}

		glfwGetMousePos( &mouseX , &mouseY );
		mouseWheel = glfwGetMouseWheel();
	}

	void keyboardCharCallback(int key, int action)
	{
		keyboard->handleKeyboardCharacter( (unsigned int)key , (action == GLFW_PRESS ? 1.0f : 0.0f ) );
	}

	void keyboardCallback(int key, int action)
	{
		keyboard->handleKeyboard( (unsigned int)key , (action == GLFW_PRESS ? 1.0f : 0.0f ) );
	}

	void mouseWheelCallback(int wheel)
	{
		mouse->handleMouseWheel( wheel - mouseWheel );
	}

	void mouseButtonCallback(int button, int action)
	{
		Button resolver;
		switch( button )
		{
			case GLFW_MOUSE_BUTTON_LEFT :
				resolver = LEFT;
				break;
			case GLFW_MOUSE_BUTTON_RIGHT :
				resolver = RIGHT;
				break;
			case GLFW_MOUSE_BUTTON_MIDDLE :
				resolver = MIDDLE;
				break;
			case GLFW_MOUSE_BUTTON_4 :
				resolver = ADDON_1;
				break;
			case GLFW_MOUSE_BUTTON_5 :
				resolver = ADDON_2;
				break;
			case GLFW_MOUSE_BUTTON_6 :
				resolver = ADDON_3;
				break;
			case GLFW_MOUSE_BUTTON_7 :
				resolver = ADDON_4;
				break;
			case GLFW_MOUSE_BUTTON_8 :
				resolver = ADDON_5;
				break;
			default:
				resolver = ADDON_6;
				break;
		}

		mouse->handleMouseButton( resolver , (action == GLFW_PRESS ? 1.0f : 0.0f ) );
	}

	void mouseMoveCallback(int x, int y)
	{
		mouse->handleMouseMove( x - mouseX , y - mouseY );

		mouseX = x;
		mouseY = y;
	}
}
// GLFW INPUT HANDLING

GLFWVideo::GLFWVideo()
: dpi(96),
  windowed(true),
  cursorVisible( true ),
  major(3),
  minor(1),
  title("GLFWBolt")
{
}

GLFWVideo::~GLFWVideo()
{
}

float GLFWVideo::getDPI()
{
	return dpi;
}

bool GLFWVideo::isWindowed()
{
	return windowed;
}

void GLFWVideo::setDPI(float val)
{
	dpi = val;
}

void GLFWVideo::setWindowed(bool val)
{
	windowed = val;
}

void GLFWVideo::setMajorVersion(int v)
{
	major = v;
}

void GLFWVideo::setMinorVersion(int v)
{
	minor = v;
}

bool GLFWVideo::isCursorVisible()
{
	return cursorVisible;
}

void GLFWVideo::setCursorVisible( bool val )
{
	cursorVisible = val;
	if( cursorVisible )
	{
		glfwEnable( GLFW_MOUSE_CURSOR );
	}
	else
	{
		glfwDisable( GLFW_MOUSE_CURSOR );
	}
}

bool GLFWVideo::initialize()
{
	if (glfwInit() != GL_TRUE)
	{
		LOG_ERROR << "glfwInit failed!" << std::endl;
		return false;
	}

	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR , major );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR , minor );

	// Initialize render target..
	rendertarget.initialize();

	// Enable gl1+ functionality!.
	if( !GL_INITIALIZATION )
	{
		LOG_ERROR << "Failed to initialize GL Extended." << std::endl;
		return false;
	}

	// GL Data List logging.
	LOG_OUT << "Video renderer Data: " << std::endl;
	LOG_OUT << " Vendor:" << glGetString(GL_VENDOR) << std::endl;
	LOG_OUT << " Renderer:" << glGetString(GL_RENDERER) << std::endl;
	LOG_OUT << " Version:" << glGetString(GL_VERSION) << std::endl;

	LOG_OUT << " Extensions:" << std::endl;
	GLint n, i;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	for (i = 0; i < n; i++)
	{
		LOG_OUT << "  - " << glGetStringi(GL_EXTENSIONS, i) << std::endl;
	}
	LOG_OUT << "." << std::endl;

	// Disable/Enable mouse cursor
	setCursorVisible( cursorVisible );

	GLFWInputHandling::setup();

	glfwSetKeyCallback( GLFWInputHandling::keyboardCallback );
	glfwSetCharCallback( GLFWInputHandling::keyboardCharCallback );
	glfwSetMousePosCallback( GLFWInputHandling::mouseMoveCallback );
	glfwSetMouseButtonCallback( GLFWInputHandling::mouseButtonCallback );
	glfwSetMouseWheelCallback( GLFWInputHandling::mouseWheelCallback );

	GL_TEST_ERROR("end");

	return true;
}

void GLFWVideo::setTitle(std::string head)
{
	title = head;
}

std::string GLFWVideo::getTitle()
{
	return title;
}

void GLFWVideo::apply(const VideoMode & mode)
{
}

void GLFWVideo::listVideoModes(std::vector<VideoMode> & modes) const
{
}

RenderTarget& GLFWVideo::getRenderTarget()
{
	return rendertarget;
}

void GLFWVideo::flip()
{
	GL_TEST_ERROR("begin");
	glfwSwapBuffers();
	GL_TEST_ERROR("end");
}

}


 /* namespace bolt */
