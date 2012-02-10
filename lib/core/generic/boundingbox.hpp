/*
 * boundingbox.hpp
 *
 *  Created on: 10.2.2012
 *      Author: akin
 */

#ifndef BOUNDINGBOX_HPP_
#define BOUNDINGBOX_HPP_

#include <glm/ext.hpp>

namespace bolt
{

class BoundingBox
{
public:
	BoundingBox();
	virtual ~BoundingBox();

	glm::vec3 offset;
	glm::vec3 bound;
};

} /* namespace bolt */
#endif /* BOUNDINGBOX_HPP_ */
