/*
 * texturegroup.h
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#ifndef TEXTUREGROUP_H_
#define TEXTUREGROUP_H_

#include <vector>
#include <glm/glm>
#include "gtextureatlas.hpp"
#include "texture.hpp"
#include <graphics/graphicsexception.hpp>

#define TG_DEFAULT_TEXTURE_SIZE 2048
#define TG_DEFAULT_PAD 1

namespace bolt
{
	class TextureGroup
	{
	protected:
		std::vector<GTextureAtlas*> atlases;
		glm::ivec2 max;
		int pad;
		ColorMode channels;
		bool initialized;
	public:
		TextureGroup();
		virtual ~TextureGroup();

		void initialize( int maxwidth = TG_DEFAULT_TEXTURE_SIZE , int maxheight = TG_DEFAULT_TEXTURE_SIZE , int padding = TG_DEFAULT_PAD , ColorMode mode = RGBA );
		void initialize( const glm::ivec2& maxsize , int padding = TG_DEFAULT_PAD , ColorMode mode = RGBA );

		void request( Texture& texture ) throw (GraphicsException);
	};
} /* namespace ice */
#endif /* TEXTUREGROUP_H_ */
