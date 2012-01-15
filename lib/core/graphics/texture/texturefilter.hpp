/*
 * texturefilter.h
 *
 *  Created on: 12.6.2011
 *      Author: akin
 */

#ifndef TEXTUREFILTER_H_
#define TEXTUREFILTER_H_

namespace bolt
{
	enum TextureFilter
	{
		NEAREST = 1,
		LINEAR = 2,
		MIPMAP_NEAREST = 3,
		MIPMAP_LINEAR = 4
	};
}

#endif /* TEXTUREFILTER_H_ */
