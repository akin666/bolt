/*
 * position.cpp
 *
 *  Created on: 10.2.2012
 *      Author: akin
 */

#include "position.hpp"

namespace bolt
{

Position::Position()
{
}

Position::~Position()
{
}

glm::mat4 Position::toMatrix()
{
	return glm::translate( glm::mat4(1.0f), point ) * glm::gtc::quaternion::mat4_cast( orientation );
}

} /* namespace bolt */
