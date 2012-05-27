/*
 * circle.h
 *
 *  Created on: 27.5.2012
 *      Author: akin
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "commongeometry.h"

namespace bolt
{

class Circle : public glm::vec2
{
public:
	Circle();
	Circle( float x , float y , float r );
	Circle( const Circle& other );
	virtual ~Circle();

	float radius;
};

} /* namespace bolt */
#endif /* CIRCLE_H_ */
