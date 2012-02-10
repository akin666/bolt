/*
 * boundingsphere.hpp
 *
 *  Created on: 10.2.2012
 *      Author: akin
 */

#ifndef BOUNDINGSPHERE_HPP_
#define BOUNDINGSPHERE_HPP_

#include <glm/ext.hpp>

namespace bolt
{

class BoundingSphere
{
public:
	BoundingSphere();
	virtual ~BoundingSphere();

	glm::vec3 offset;
	float bound;
};

} /* namespace bolt */
#endif /* BOUNDINGSPHERE_HPP_ */
