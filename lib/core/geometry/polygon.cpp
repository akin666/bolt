/*
 * Polygon.cpp
 *
 *  Created on: 26.5.2012
 *      Author: akin
 */

#include "polygon.h"

namespace bolt
{

Polygon::Polygon( )
: type( UNKNOWN )
{
}

Polygon::Polygon( const Polygon& other )
: vertexes( other.vertexes ),
  indexes( other.indexes ),
  type( type )
{
}

Polygon::~Polygon()
{
}

SurfaceType Polygon::getType() const
{
	return type;
}

Polygon& Polygon::setType( SurfaceType type )
{
	this->type = type;
	return *this;
}

VertexVector& Polygon::access()
{
	return vertexes;
}

IndexVector& Polygon::indices()
{
	return indexes;
}

} /* namespace bolt */
