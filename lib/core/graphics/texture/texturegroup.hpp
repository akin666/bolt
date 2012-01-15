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

		bool initialize( const int maxwidth = TG_DEFAULT_TEXTURE_SIZE , const int maxheight = TG_DEFAULT_TEXTURE_SIZE , const int padding = TG_DEFAULT_PAD , const ColorMode mode = RGBA );
		bool initialize( const glm::ivec2& maxsize , const int padding = TG_DEFAULT_PAD , const ColorMode mode = RGBA );

		bool request( Texture& texture );
	};
} /* namespace ice */
#endif /* TEXTUREGROUP_H_ */
