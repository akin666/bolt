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
	enum SurfaceType {
		Point 			= 0,
		Line 			= 1,
		LineStrip 		= 2,
		Triangle 		= 3,
		TriangleStrip 	= 4,
		Quad 			= 5,
		QuadStrip 		= 6,
		TriangleFan 	= 7,
		Polygon 		= 8,
	};

	enum ContentType {
		VertexArray2D 				= 0,
		VertexArray3D 				= 1,
		VertexArray4D 				= 2,
		TextureCoordinateArray1D 	= 3,
		TextureCoordinateArray2D 	= 4,
		TextureCoordinateArray3D 	= 5,
		NormalArray 				= 6,
		ColorArray1D 				= 7,
		ColorArray3D 				= 8,
		ColorArray4D 				= 9,
		IndexArray					= 10,
	};

	enum DataType {
		Float16 	= 0,
		Float32 	= 1,
		Float64 	= 2,
		int8 		= 3,
		int16 		= 4,
		int32 		= 5,
		int64 		= 6,
	};

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
