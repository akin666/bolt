/*
 * testapplicationgame.hpp
 *
 *  Created on: 29.1.2012
 *      Author: akin
 */

#ifndef TESTAPPLICATIONGAME_HPP_
#define TESTAPPLICATIONGAME_HPP_

#include <component/controller.hpp>

namespace bolt
{
class ShaderProgram;
}

class TestApplicationGame: public bolt::Controller
{
public:
	const static std::string KEY;
protected:
	bool initialized;
	bolt::StringSet dependecies;
	bolt::ShaderProgram *shaderProgram;

	int times;
public:
	TestApplicationGame();
	virtual ~TestApplicationGame();

	virtual void initialize() throw (std::exception);
	virtual void start( bolt::ControllerNode& node );
};

#endif /* TESTAPPLICATIONGAME_HPP_ */
