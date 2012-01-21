/*
 * state.hpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#ifndef STATE_HPP_
#define STATE_HPP_

#include <common>

namespace bolt
{

class State
{
public:
	State();
	virtual ~State();

	virtual bool initialize() = 0;
	virtual bool cleanup() = 0;

	virtual void update( MicroSeconds delta ) = 0;
};

} /* namespace bolt */
#endif /* STATE_HPP_ */
