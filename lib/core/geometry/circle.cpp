/*
 * circle.cpp
 *
 *  Created on: 27.5.2012
 *      Author: akin
 */

#include "circle.h"

namespace bolt
{

Circle::Circle()
{
}

Circle::Circle( float x , float y , float r )
: glm::vec2( x , y ),
  radius( r )
{
}

Circle::Circle( const Circle& other )
: glm::vec2( other.x , other.y ),
  radius( other.radius )
{
}

Circle::~Circle()
{
}

} // namespace bolt
