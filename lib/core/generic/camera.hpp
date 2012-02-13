/*
 * camera.hpp
 *
 *  Created on: 10.2.2012
 *      Author: akin
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/ext.hpp>

namespace bolt
{

class Camera
{
public:
	Camera();
	virtual ~Camera();

	glm::mat4 lense;
};

} /* namespace bolt */
#endif /* CAMERA_HPP_ */
