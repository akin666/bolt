/*
 * position.hpp
 *
 *  Created on: 10.2.2012
 *      Author: akin
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <glm/ext.hpp>

namespace bolt
{

class Position
{
public:
	Position();
	virtual ~Position();

	glm::vec3 point;
	glm::gtc::quaternion::quat orientation;

	glm::mat4 toMatrix();
};

} /* namespace bolt */
#endif /* POSITION_HPP_ */
