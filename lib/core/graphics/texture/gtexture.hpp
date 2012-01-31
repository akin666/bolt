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
#include <graphics/bufferobject.hpp>
#include <graphics/graphicsexception.hpp>

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

		void initialize( const unsigned char *data = NULL ) throw (GraphicsException);
		void destroy() throw (GraphicsException);

		bool testMemory() throw (GraphicsException);

		bool isInitialized() const;

		GTexture& setMinificationFilter( TextureFilter filter ) throw (GraphicsException);
		GTexture& setMagnificationFilter( TextureFilter filter ) throw (GraphicsException);

		GTexture& setSWrapMode( WrapMode wrap ) throw (GraphicsException);
		GTexture& setTWrapMode( WrapMode wrap ) throw (GraphicsException);

		GTexture& setWidth( int width );
		GTexture& setHeight( int height );
		GTexture& setDimensions( glm::ivec2 dimension );

		GTexture& setColorMode( ColorMode color );

		WrapMode getSWrapMode() const;
		WrapMode getTWrapMode() const;

		TextureFilter getMinificationFilter() const;
		TextureFilter getMagnificationFilter() const;

		void generateMipMap() throw (GraphicsException);

		void resize( glm::ivec2 newDimensions ) throw (GraphicsException);

		ColorMode getColorMode() const;

		void renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , const unsigned char *data ) throw (GraphicsException);
		void renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , BufferObject& bo ) throw (GraphicsException);
		void renderSubArea( glm::ivec2 pos , glm::ivec2 dim , const unsigned char color ) throw (GraphicsException);

		void resize( int new_width , int new_height ) throw (GraphicsException);
		void renderSubTexture( int x , int y , int width , int height , const unsigned char *data ) throw (GraphicsException);
		void renderSubTexture( int x , int y , int width , int height , BufferObject& bo ) throw (GraphicsException);
		void renderSubArea( int x , int y , int width , int height , unsigned char color ) throw (GraphicsException);

		int getWidth() const;
		int getHeight() const;

		glm::ivec2 getDimension() const;

		unsigned int getTextureId() const;

		void bind() throw (GraphicsException);
		void release() throw (GraphicsException);
	};
}

#endif /* GTEXTURE_H_ */
