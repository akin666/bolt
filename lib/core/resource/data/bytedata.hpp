/*
 * bytedata.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef BYTEDATA_HPP_
#define BYTEDATA_HPP_

#include <common>

namespace bolt
{

class ByteData
{
protected:
	unsigned char *data;
	uint length;
public:
	ByteData( unsigned char *newData , uint newLength );
	virtual ~ByteData();

	unsigned char *accessData();
	uint size();
};

} /* namespace bolt */
#endif /* BYTEDATA_HPP_ */
