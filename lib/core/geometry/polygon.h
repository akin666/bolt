/*
 * Polygon.h
 *
 *  Created on: 26.5.2012
 *      Author: akin
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include "commongeometry.h"

namespace bolt
{

class Polygon
{
protected:
	VertexVector vertexes;
	IndexVector indexes;
	SurfaceType type;
public:
	Polygon( );
	Polygon( const Polygon& other );
	virtual ~Polygon();

	SurfaceType getType() const;
	Polygon& setType( SurfaceType type );

	VertexVector& access();
	IndexVector& indices();
};

} /* namespace bolt */
#endif /* POLYGON_H_ */
