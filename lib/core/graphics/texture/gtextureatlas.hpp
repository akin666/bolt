/*
 * gtextureatlas.h
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#ifndef GTEXTUREATLAS_H_
#define GTEXTUREATLAS_H_

#include <glm/glm>
#include "gtexture.hpp"
#include <atlas/atlas.h>
#include <common>
#include <graphics/graphicsexception.hpp>

namespace bolt
{
	class GTextureAtlas
	{
	protected:
		Atlas atlas;
		GTexture texture;
		bool initialized;
	public:
		GTextureAtlas();
		virtual ~GTextureAtlas();

		void initialize( const glm::ivec2& dimensions , const int padding , ColorMode mode = RGBA ) throw (GraphicsException);
		void resize( const glm::ivec2& val ) throw (GraphicsException);

		bool request( const glm::ivec2& dimensions , glm::ivec2& position );
		bool release( const glm::ivec2& dimensions , const glm::ivec2& position );

		unsigned int getPadding();
		glm::ivec2 getDimension();

		GTexture& getTexture();
	};
} /* namespace ice */
#endif /* GTEXTUREATLAS_H_ */
