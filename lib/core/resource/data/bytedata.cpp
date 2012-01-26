/*
 * bytedata.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "bytedata.hpp"
#include <iostream>

namespace bolt
{
namespace resource
{


ByteData::ByteData( unsigned char *newData , uint newLength )
: data( newData ),
  length( newLength )
{
}

ByteData::~ByteData()
{
	delete[] data;
	data = NULL;
}

unsigned char *ByteData::accessData()
{
	return data;
}

uint ByteData::size()
{
	return length;
}

}
} /* namespace bolt */

