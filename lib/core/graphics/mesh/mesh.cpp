/*
 * mesh.cpp
 *
 *  Created on: 17.11.2011
 *      Author: akin
 */

#include "mesh.hpp"
#include <iostream>
#include <cstring>

namespace bolt
{
MeshData::MeshData()
: vertexCoordinates( NULL ),
  textureCoordinates( NULL ),
  normalCoordinates( NULL ),
  colorCoordinates( NULL ),
  count( 0 )
{
}

MeshData::MeshData(const MeshData & other)
: vertexCoordinates( NULL ),
  textureCoordinates( NULL ),
  normalCoordinates( NULL ),
  colorCoordinates( NULL ),
  count( other.count )
{
	copy( other );
}

MeshData::~MeshData()
{
	MeshData::clear();
}

void MeshData::clear()
{
	if( vertexCoordinates != NULL ||
		textureCoordinates != NULL ||
		normalCoordinates != NULL ||
		colorCoordinates != NULL )
	{
		delete[] vertexCoordinates;
		delete[] textureCoordinates;
		delete[] normalCoordinates;
		delete[] colorCoordinates;

		vertexCoordinates = NULL;
		textureCoordinates = NULL;
		normalCoordinates = NULL;
		colorCoordinates = NULL;

		count = 0;
	}
}

void MeshData::copy(const MeshData & other)
{
	if( other.count > 0 )
	{
		MeshData::clear();
		count = other.count;

		vertexCoordinates = new VertexType[count];
		textureCoordinates = new TextureType[count];
		normalCoordinates = new NormalType[count];
		colorCoordinates = new ColorType[count];

		::memcpy( vertexCoordinates , other.vertexCoordinates , count * sizeof( VertexType ) );
		::memcpy( textureCoordinates , other.textureCoordinates , count * sizeof( TextureType ) );
		::memcpy( normalCoordinates , other.normalCoordinates , count * sizeof( NormalType ) );
		::memcpy( colorCoordinates , other.colorCoordinates , count * sizeof( ColorType ) );
	}
}





//////////////////////
// MeshDataBuffer
/////////////////////

MeshDataBuffer::MeshDataBuffer()
: count( 0 )
{
}

MeshDataBuffer::~MeshDataBuffer()
{
}




//////////////////////
// MeshIndex
/////////////////////

MeshIndex::MeshIndex()
: indexArray( NULL ),
  count( 0 ),
  type( Graphics::triangles )
{
}

MeshIndex::MeshIndex(const MeshIndex & other)
: indexArray( NULL ),
  count( other.count )
{
	copy( other );
}

MeshIndex::~MeshIndex()
{
	MeshIndex::clear();
}

void MeshIndex::clear()
{
	if( indexArray != NULL )
	{
		delete[] indexArray;
		indexArray = NULL;
		count = 0;
	}
}

void MeshIndex::copy(const MeshIndex & other)
{
	if( other.count > 0 )
	{
		MeshIndex::clear();
		count = other.count;

		indexArray = new IndexType[count];

		::memcpy( indexArray , other.indexArray , count * sizeof( IndexType ) );
	}
}




//////////////////////
// MeshIndexBuffer
/////////////////////

MeshIndexBuffer::MeshIndexBuffer()
: count( 0 ),
  type( Graphics::triangles )
{
}

MeshIndexBuffer::~MeshIndexBuffer()
{
}
}
