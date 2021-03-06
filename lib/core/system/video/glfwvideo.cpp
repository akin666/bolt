/*
 * glfwvideo.cpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#include "glfwvideo.hpp"
#include <log>
#include <opengl>

#include <stdexcept>

// if components are not initialized/set, SET EM!
#include <singleton>
#include <input/touch.hpp>
#include <input/keyboard.hpp>
#include <input/mouse.hpp>
#include <input/joystick.hpp>
#include <input/osinput.hpp>

namespace bolt
{

// GLFW INPUT HANDLING
namespace GLFWInputHandling
{

//Touch *touch = getSingleton<Touch>();
//Joystick *joystick = getSingleton<Joystick>();

	int mouseX = 0;
	int mouseY = 0;
	int mouseWheel = 0;

	void setup()
	{
		glfwGetMousePos( &mouseX , &mouseY );
		mouseWheel = glfwGetMouseWheel();
	}

	void keyboardCharCallback(int key, int action)
	{
		Keyboard *keyboard = getSingleton<Keyboard>();
		if(keyboard != NULL) keyboard->handleKeyboardCharacter( (unsigned int)key , (action == GLFW_PRESS ? 1.0f : 0.0f ) );
	}

	void keyboardCallback(int key, int action)
	{
		Keyboard *keyboard = getSingleton<Keyboard>();
		if(keyboard != NULL) keyboard->handleKeyboard( (unsigned int)key , (action == GLFW_PRESS ? 1.0f : 0.0f ) );
	}

	void mouseWheelCallback(int wheel)
	{
		Mouse* mouse = getSingleton<Mouse>();
		int diff;

		diff = wheel - mouseWheel;
		mouseWheel = wheel;

		if(mouse == NULL)
		{
			return;
		}

		// invert Y .. the up is UP .. not DOWN.
		mouse->handleMouseWheel( diff );
	}

	void mouseButtonCallback(int button, int action)
	{
		Mouse* mouse = getSingleton<Mouse>();

		if(mouse == NULL)
		{
			return;
		}

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
		Mouse* mouse = getSingleton<Mouse>();
		int diffX, diffY;

		diffX = x - mouseX;
		diffY = y - mouseY;

		mouseX = x;
		mouseY = y;

		if(mouse == NULL)
		{
			return;
		}

		// invert Y .. the up is UP .. not DOWN.
		mouse->handleMouseMove( diffX , -diffY );
	}

	int windowCloseCallback()
	{
		OSInput* osinput = getSingleton<OSInput>();

		if( osinput == NULL )
		{
			return GL_TRUE;
		}

		return osinput->handleClose() ? GL_TRUE : GL_FALSE;
	}

	void windowSizeCallback( int w , int h )
	{
		OSInput* osinput = getSingleton<OSInput>();

		if( osinput == NULL )
		{
			return;
		}

		osinput->handleResize( w , h );
	}

	void windowRefreshCallback()
	{
		OSInput* osinput = getSingleton<OSInput>();

		if( osinput == NULL )
		{
			return;
		}

		osinput->handleRefresh();
	}

}
// GLFW INPUT HANDLING

GLFWVideo::GLFWVideo()
: dpi(96),
  windowed(true),
  cursorVisible( true ),
  major(3),
  minor(1),
  title("GLFWBolt"),
  initialized( false )
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

void GLFWVideo::initialize()
{
	if (glfwInit() != GL_TRUE)
	{
		throw std::runtime_error("glfwInit failed!.");
	}

	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR , major );
	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR , minor );

	// Initialize render target..
	rendertarget.initialize();

	// Enable gl1+ functionality!.
	if( !GL_INITIALIZATION )
	{
		throw std::runtime_error("Failed to initialize GL Extended.");
	}

	glfwSetWindowTitle( title.c_str() );

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
	glfwSetWindowCloseCallback( GLFWInputHandling::windowCloseCallback );
	glfwSetWindowSizeCallback( GLFWInputHandling::windowSizeCallback );
	glfwSetWindowRefreshCallback( GLFWInputHandling::windowRefreshCallback );

	GL_TEST_ERROR("end");

	initialized = true;
}

void GLFWVideo::setTitle(std::string head)
{
	title = head;

	if( initialized )
	{
		glfwSetWindowTitle( title.c_str() );
	}
}

std::string GLFWVideo::getTitle()
{
	return title;
}

void GLFWVideo::apply(const VideoMode & mode)
{
	rendertarget.getVideoMode() = mode;
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
