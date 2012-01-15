/*
 * GTexture.h
 *
 *  Created on: 1.4.2010
 *      Author: akin
 *
 * GTexture is abstraction of Opengl Texture.
 * Texture is something else.
 */
#ifndef GTEXTURE_H_
#define GTEXTURE_H_

#include <common>
#include <glm/glm>
#include "texturefilter.hpp"
#include "texturewrap.hpp"
#include <iostream>
#include "../bufferobject.hpp"

namespace bolt
{
	class GTexture
	{
	protected:
		glm::ivec2 dimensions;
		glm::ivec2 newDimensions;
		ColorMode mode;
		ColorMode newMode;
		unsigned int glMode;
		unsigned int bytes;
		unsigned int texture_id;

		TextureFilter minificationFilter;
		TextureFilter magnificationFilter;

		WrapMode sWrap;
		WrapMode tWrap;

		bool mipmapped;
	public:
		GTexture();
		GTexture( const GTexture& other );
		virtual ~GTexture();

		bool initialize( const unsigned char *data = NULL );
		void destroy();

		bool testMemory();

		bool isInitialized() const;

		GTexture& setMinificationFilter( TextureFilter filter );
		GTexture& setMagnificationFilter( TextureFilter filter );

		GTexture& setSWrapMode( WrapMode wrap );
		GTexture& setTWrapMode( WrapMode wrap );

		GTexture& setWidth( int width );
		GTexture& setHeight( int height );
		GTexture& setDimensions( glm::ivec2 dimension );

		GTexture& setColorMode( ColorMode color );

		WrapMode getSWrapMode() const;
		WrapMode getTWrapMode() const;

		TextureFilter getMinificationFilter() const;
		TextureFilter getMagnificationFilter() const;

		void generateMipMap();

		bool resize( glm::ivec2 newDimensions );

		ColorMode getColorMode() const;

		void renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , const unsigned char *data );
		void renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , BufferObject& bo );
		void renderSubArea( glm::ivec2 pos , glm::ivec2 dim , const unsigned char color );

		bool resize( int new_width , int new_height );
		void renderSubTexture( int x , int y , int width , int height , const unsigned char *data );
		void renderSubTexture( int x , int y , int width , int height , BufferObject& bo );
		void renderSubArea( int x , int y , int width , int height , unsigned char color );

		int getWidth() const;
		int getHeight() const;

		glm::ivec2 getDimension() const;

		unsigned int getTextureId() const;

		void bind();
		void release();
	};
}

#endif /* GTEXTURE_H_ */
