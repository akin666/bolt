
#include "atlasnode.h"
#include <iostream>

	AtlasNode::AtlasNode()
	: x(0),
	  y(0),
	  width(0)
	{
	}

	AtlasNode::AtlasNode( const AtlasNode& other )
	: x(other.x),
	  y(other.y),
	  width( other.width )
	{
	}

	AtlasNode::AtlasNode( const int& ax , const int& ay , const int& width )
	: x(ax),
	  y(ay),
	  width( width )
	{
	}

	AtlasNode::~AtlasNode()
	{
	}

