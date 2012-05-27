/*
 * Rectangle.h
 *
 *  Created on: 26.5.2012
 *      Author: akin
 *
 *
 *  The x,y is in the middle of the rectangle.
 *  !No method overloading!
 *  !glm::vec2 does not have virtual destructor!
 *  !Meaning, that destructor calling is not certain!
 *
 *      width
 *  |<------------|
 *  *-------------*---
 *  |             | /|\
 *  |      X,Y    |  | height
 *  |      x      |  |
 *  |             |  |
 *  |             | \|/
 *  *-------------*---
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "commongeometry.h"

namespace bolt
{

class Rectangle : public glm::vec2
{
public:
	Rectangle();
	Rectangle( float x , float y , float width , float height );
	Rectangle( const Rectangle& other );
	virtual ~Rectangle();

	glm::vec2 dimension;
};

} /* namespace bolt */
#endif /* RECTANGLE_H_ */
