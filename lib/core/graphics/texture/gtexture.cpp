/*
 * GTexture.cpp
 *
 *  Created on: 1.4.2010
 *      Author: akin
 */

#include "gtexture.hpp"
#include <iostream>
#include <opengl.hpp>

namespace bolt
{
	GTexture::GTexture()
	: mode( RGBA ),
	  newMode( RGBA ),
	  glMode(GL_RGBA),
	  bytes(4),
	  texture_id(GL_NULL_BUFFER),
	  minificationFilter(LINEAR),
	  magnificationFilter(LINEAR),
	  sWrap(CLAMP),
	  tWrap(CLAMP),
	  mipmapped(false)
	{
	}

	GTexture::GTexture( const GTexture& other )
	: mode( other.mode ),
	  newMode( other.newMode ),
	  glMode( other.glMode ),
	  bytes( other.bytes ),
	  texture_id( other.texture_id ),
	  minificationFilter( other.minificationFilter ),
	  magnificationFilter( other.magnificationFilter ),
	  sWrap( other.sWrap ),
	  tWrap( other.tWrap ),
	  mipmapped( other.mipmapped )
	{
	}

	GTexture::~GTexture()
	{
		destroy();
	}

	void GTexture::destroy()
	{
		if( texture_id != GL_NULL_BUFFER )
		{
			glDeleteTextures( 1 , &texture_id );
			texture_id = GL_NULL_BUFFER;
			GL_TEST_ERROR("GTexture:dtr delete texture.");
		}
	}

	bool GTexture::initialize( const unsigned char *data )
	{
		GL_TEST_ERROR("GTexture:initialize START.");
		if( texture_id == GL_NULL_BUFFER )
		{
			glGenTextures( 1 , &texture_id );

			bind();

			glPixelStorei( GL_UNPACK_ALIGNMENT , 1 );
			glPixelStorei( GL_PACK_ALIGNMENT , 1 );

			// fits into mem?
			if( !testMemory() )
			{
				destroy();
				return false;
			}

			int para;

			// MIN
			{
				switch( minificationFilter )
				{
					case NEAREST :
						para = GL_NEAREST;
						break;
					case MIPMAP_NEAREST :
						para = GL_NEAREST_MIPMAP_NEAREST;
						break;
					case MIPMAP_LINEAR :
						para = GL_LINEAR_MIPMAP_LINEAR;
						break;
					default:
						para = GL_LINEAR;
						break;
				}
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, para );
			}
			// MAG
			{
				switch( magnificationFilter )
				{
					case NEAREST :
						para = GL_NEAREST;
						break;
					case MIPMAP_NEAREST :
						para = GL_NEAREST_MIPMAP_NEAREST;
						break;
					case MIPMAP_LINEAR :
						para = GL_LINEAR_MIPMAP_LINEAR;
						break;
					default:
						para = GL_LINEAR;
						break;
				}
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, para );
			}
			// SWRAP
			{
				switch( sWrap )
				{
					case CLAMP :
						para = GL_CLAMP_TO_EDGE;
						break;
					default:
						para = GL_REPEAT;
						break;
				}
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, para );
			}
			// TWRAP
			{
				switch( tWrap )
				{
					case CLAMP :
						para = GL_CLAMP_TO_EDGE;
						break;
					default:
						para = GL_REPEAT;
						break;
				}
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, para );
			}
			// ColorMode
			{
				mode = newMode;

				switch( mode )
				{
					case RGB :
						glMode = GL_RGB;
						bytes = 3;
						break;
					case RGBA :
						glMode = GL_RGBA;
						bytes = 4;
						break;
					case ARGB :
						break;
					case ALPHA :
						glMode = GL_ALPHA;
						bytes = 1;
						break;
					case LUMINANCE :
						glMode = GL_LUMINANCE;
						bytes = 1;
						break;
					case INTENSITY :
						glMode = GL_INTENSITY;
						bytes = 1;
						break;
					case RGBA12 :
						glMode = GL_RGBA12;
						bytes = 6;
						break;
					case RGBA16 :
						glMode = GL_RGBA16;
						bytes = 8;
						break;
					case RGBA32 :
						break;
					default :
						glMode = GL_RGBA;
						bytes = 4;
						break;
				}
			}
			// Dimensions
			{
				dimensions = newDimensions;
			}

			// Create correct sized buffer.
			glTexImage2D(
					GL_TEXTURE_2D,
					0,
					glMode,
					dimensions.x,
					dimensions.y,
					0,
					glMode,
					GL_UNSIGNED_BYTE, // TODO is this correct for GL_RGBA16 formats etc
					NULL
			);
			GL_TEST_ERROR("GTexture:initialize END.");

			if( data != NULL )
			{
				renderSubTexture( glm::ivec2(0,0) , dimensions , data );
			}

			GL_TEST_ERROR("GTexture:initialize END.");
			return true;
		}

		return false;
	}

	bool GTexture::isInitialized() const
	{
		return texture_id != GL_NULL_BUFFER;
	}

	bool GTexture::testMemory()
	{
		// ColorMode
		unsigned int tMode;
//		unsigned int tBytes;
		{
			switch( newMode )
			{
				case RGB :
					tMode = GL_RGB;
//					tBytes = 3;
					break;
				case RGBA :
					tMode = GL_RGBA;
//					tBytes = 4;
					break;
				case ARGB :
					break;
				case ALPHA :
					tMode = GL_ALPHA;
//					tBytes = 1;
					break;
				case LUMINANCE :
					tMode = GL_LUMINANCE;
//					tBytes = 1;
					break;
				case INTENSITY :
					tMode = GL_INTENSITY;
//					tBytes = 1;
					break;
				case RGBA12 :
					tMode = GL_RGBA12;
//					tBytes = 6;
					break;
				case RGBA16 :
					tMode = GL_RGBA16;
//					tBytes = 8;
					break;
				case RGBA32 :
					break;
				default :
					tMode = GL_RGBA;
//					tBytes = 4;
					break;
			}
		}

		bind();

		// Dimensions
		glTexImage2D(
				GL_PROXY_TEXTURE_2D,
				0,
				tMode,
				newDimensions.x,
				newDimensions.y,
				0,
				tMode,
				GL_UNSIGNED_BYTE,
				NULL
				);

		int width;

		glGetTexLevelParameteriv(
				GL_PROXY_TEXTURE_2D,
				0,
				GL_TEXTURE_WIDTH,
				&width
				);

		if( glGetError() != GL_NO_ERROR || width == 0 )
		{
			while( glGetError() != GL_NO_ERROR );
			glBindTexture(GL_TEXTURE_2D, GL_NULL_BUFFER );

			return false;
		}
		return true;
	}

	GTexture& GTexture::setMinificationFilter( TextureFilter filter )
	{
		if( texture_id != GL_NULL_BUFFER && filter != minificationFilter )
		{
			bind();
			int para = GL_LINEAR;

			switch( filter )
			{
				case NEAREST :
					para = GL_NEAREST; break;
				case MIPMAP_NEAREST :
					para = GL_NEAREST_MIPMAP_NEAREST; break;
				case MIPMAP_LINEAR :
					para = GL_LINEAR_MIPMAP_LINEAR; break;
				default: break;
			}

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, para );
			GL_TEST_ERROR("GTexture:setMinificationFilter END.");
		}
		minificationFilter = filter;

		return *this;
	}

	GTexture& GTexture::setMagnificationFilter( TextureFilter filter )
	{
		if( texture_id != GL_NULL_BUFFER && filter != magnificationFilter )
		{
			bind();
			int para = GL_LINEAR;

			switch( filter )
			{
				case NEAREST :
					para = GL_NEAREST; break;
				case MIPMAP_NEAREST :
					para = GL_NEAREST_MIPMAP_NEAREST; break;
				case MIPMAP_LINEAR :
					para = GL_LINEAR_MIPMAP_LINEAR; break;
				default: break;
			}

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, para );
			GL_TEST_ERROR("GTexture:setMinificationFilter END.");
		}

		magnificationFilter = filter;

		return *this;
	}

	GTexture& GTexture::setSWrapMode( WrapMode wrap )
	{
		if( texture_id != GL_NULL_BUFFER && wrap != sWrap )
		{
			bind();
			int para = GL_CLAMP_TO_EDGE;

			if( wrap == REPEAT )
			{
				para = GL_REPEAT;
			}

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, para );
			GL_TEST_ERROR("GTexture:setMinificationFilter END.");
		}

		sWrap = wrap;

		return *this;
	}

	GTexture& GTexture::setTWrapMode( WrapMode wrap )
	{
		if( texture_id != GL_NULL_BUFFER && wrap != tWrap )
		{
			bind();
			int para = GL_CLAMP_TO_EDGE;

			if( wrap == REPEAT )
			{
				para = GL_REPEAT;
			}

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, para );
			GL_TEST_ERROR("GTexture:setMinificationFilter END.");
		}

		tWrap = wrap;

		return *this;
	}

	GTexture& GTexture::setWidth( int width )
	{
		newDimensions.x = width;

		return *this;
	}

	GTexture& GTexture::setHeight( int height )
	{
		newDimensions.y = height;

		return *this;
	}

	GTexture& GTexture::setDimensions( glm::ivec2 dimension )
	{
		newDimensions = dimension;

		return *this;
	}

	GTexture& GTexture::setColorMode( ColorMode color )
	{
		newMode = color;

		return *this;
	}

	WrapMode GTexture::getSWrapMode() const
	{
		return sWrap;
	}

	WrapMode GTexture::getTWrapMode() const
	{
		return tWrap;
	}

	TextureFilter GTexture::getMinificationFilter() const
	{
		return minificationFilter;
	}

	TextureFilter GTexture::getMagnificationFilter() const
	{
		return magnificationFilter;
	}

	void GTexture::generateMipMap()
	{
		if( texture_id != GL_NULL_BUFFER )
		{
			GL_TEST_ERROR("GTexture:generateMipMap START.");
			bind();
			glGenerateMipmap(GL_TEXTURE_2D);
			GL_TEST_ERROR("GTexture:generateMipMap END.");
		}
		mipmapped = true;
	}

	ColorMode GTexture::getColorMode() const
	{
		return mode;
	}

	int GTexture::getWidth() const
	{
		return dimensions.x;
	}

	int GTexture::getHeight() const
	{
		return dimensions.y;
	}

	glm::ivec2 GTexture::getDimension() const
	{
		return dimensions;
	}

	unsigned int GTexture::getTextureId() const
	{
		return texture_id;
	}

	void GTexture::bind()
	{
		GL_TEST_ERROR("GTexture:bind START.");
		glBindTexture( GL_TEXTURE_2D , texture_id );
		GL_TEST_ERROR("GTexture:bind END.");
	}

	void GTexture::release()
	{
		GL_TEST_ERROR("GTexture:bind release.");
		glBindTexture( GL_TEXTURE_2D , GL_NULL_BUFFER );
		GL_TEST_ERROR("GTexture:bind release.");
	}

	bool GTexture::resize( glm::ivec2 newDimensions )
	{
		GL_TEST_ERROR("GTexture:resize START.");

		BufferObject bo;

		bo.reserve( dimensions.x*dimensions.y*bytes , Graphics::gpu , Graphics::multipleTimes );

		glBindTexture(GL_TEXTURE_2D, texture_id );

		// read texture to bufferobject
		bo.bind( Graphics::write );
		glGetTexImage(
				GL_TEXTURE_2D,
				0, // level
				glMode,
				GL_UNSIGNED_BYTE,
				0
				);
		bo.release( Graphics::write );

		glTexImage2D(
				GL_PROXY_TEXTURE_2D,
				0,
				glMode,
				newDimensions.x,
				newDimensions.y,
				0,
				glMode,
				GL_UNSIGNED_BYTE,
				NULL
				);

		int width;

		glGetTexLevelParameteriv(
				GL_PROXY_TEXTURE_2D,
				0,
				GL_TEXTURE_WIDTH,
				&width
				);

		if( glGetError() != GL_NO_ERROR || width == 0 )
		{
			while( glGetError() != GL_NO_ERROR );
			glBindTexture(GL_TEXTURE_2D, GL_NULL_BUFFER );
			return false;
		}

		// resize
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				glMode,
				newDimensions.x,
				newDimensions.y,
				0,
				glMode,
				GL_UNSIGNED_BYTE,
				NULL
				);

		// read texture from bufferobject
		bo.bind( Graphics::read );
		glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0,
					0,
					dimensions.x,
					dimensions.y,
					glMode,
					GL_UNSIGNED_BYTE,
					0
			);
		bo.release( Graphics::read );

		dimensions = newDimensions;

		if( mipmapped )
		{
			generateMipMap();
		}

		glBindTexture(GL_TEXTURE_2D, GL_NULL_BUFFER );

		GL_TEST_ERROR("GTexture:resize END.");

		return true;
	}

	void GTexture::renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , const unsigned char *data )
	{
		glm::ivec2 pos2( pos.x + dim.x , pos.y + dim.y );

		if( pos.x < 0 || pos.y < 0 )
		{
			return;
		}

		if( pos2.x > dimensions.x || pos2.y > dimensions.y )
		{
			glm::ivec2 max;

			max.x = dimensions.x > pos2.x ? dimensions.x : pos2.x;
			max.y = dimensions.y > pos2.y ? dimensions.y : pos2.y;

			resize( max );
		}

		GL_TEST_ERROR("GTexture:renderSubGTexture START.");
		bind();

		BufferObject bo;

		bo.set( dim.x*dim.y*bytes , data , Graphics::cpu , Graphics::once );

		// stream from PBO
		bo.bind( Graphics::read );
		glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					pos.x,
					pos.y,
					dim.x,
					dim.y,
					glMode,
					GL_UNSIGNED_BYTE,
					0
					);
		bo.release( Graphics::read );

		GL_TEST_ERROR("GTexture:renderSubGTexture END.");
	}

	void GTexture::renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , BufferObject& bo )
	{
		glm::ivec2 pos2( pos.x + dim.x , pos.y + dim.y );

		if( pos.x < 0 || pos.y < 0 )
		{
			return;
		}

		if( pos2.x > dimensions.x || pos2.y > dimensions.y )
		{
			glm::ivec2 max;

			max.x = dimensions.x > pos2.x ? dimensions.x : pos2.x;
			max.y = dimensions.y > pos2.y ? dimensions.y : pos2.y;

			resize( max );
		}

		GL_TEST_ERROR("GTexture:renderSubGTexture START.");
		bind();

		// Bind buffer for reading.
		bo.bind( Graphics::read );

		// Bind current texture
		glBindTexture(GL_TEXTURE_2D, texture_id );

		// stream from PBO
		glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					pos.x,
					pos.y,
					dim.x,
					dim.y,
					glMode,
					GL_UNSIGNED_BYTE,
					0
					);

		bo.release( Graphics::read );;

		GL_TEST_ERROR("GTexture:renderSubGTexture END.");
	}

	void GTexture::renderSubArea( glm::ivec2 pos , glm::ivec2 dim , const unsigned char color )
	{
		GL_TEST_ERROR("GTexture:renderSubArea START.");

		unsigned char data[dim.x*dim.y*bytes];

		for( int i = dim.x*dim.y*bytes-1 ; i>= 0 ; --i)
		{
			data[i] = color;
		}

		renderSubTexture( pos , dim , data );

		GL_TEST_ERROR("GTexture:renderSubArea END.");
	}

	bool GTexture::resize( int new_width , int new_height )
	{
		return resize( glm::ivec2(new_width,new_height) );
	}

	void GTexture::renderSubTexture( int x , int y , int width , int height , const unsigned char *data )
	{
		renderSubTexture( glm::ivec2(x,y) , glm::ivec2(width,height) , data );
	}

	void GTexture::renderSubTexture( int x , int y , int width , int height , BufferObject& bo )
	{
		renderSubTexture( glm::ivec2(x,y) , glm::ivec2(width,height) , bo );
	}

	void GTexture::renderSubArea( int x , int y , int width , int height , const unsigned char color )
	{
		renderSubArea( glm::ivec2(x,y) , glm::ivec2(width,height) , color );
	}
}
