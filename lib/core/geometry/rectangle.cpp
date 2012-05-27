/*
 * Rectangle.cpp
 *
 *  Created on: 26.5.2012
 *      Author: akin
 */

#include "rectangle.h"

namespace bolt
{

Rectangle::Rectangle()
{
}

Rectangle::Rectangle( float x , float y , float width , float height )
: glm::vec2( x , y ),
  dimension( width , height )
{
}

Rectangle::Rectangle( const Rectangle& other )
: glm::vec2( other.x , other.y ),
  dimension( other.dimension )
{
}

Rectangle::~Rectangle()
{
}

} // namespace bolt
