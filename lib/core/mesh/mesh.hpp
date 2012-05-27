/*
 * mesh.hpp
 *
 *  Created on: 19.2.2012
 *      Author: akin
 */

#ifndef MESH_HPP_
#define MESH_HPP_

#include <common>
#include <vector>

namespace bolt
{

class Mesh
{
public:
	class Part {
	public:
		uint begin;
		uint count;
		SurfaceType type;
	};
protected:
	std::vector<Part> parts;
	// VertexArray
	// ColorArray
	// NormalArray
	// TextureCoordinateArray
	// IndexArray
	uint *indexArray;
	float *normalArray;
	float *textureCoordArray;

public:
	Mesh();
	virtual ~Mesh();
};

} /* namespace bolt */
#endif /* MESH_HPP_ */
