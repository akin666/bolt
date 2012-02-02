/*
 * GTexture.cpp
 *
 *  Created on: 1.4.2010
 *      Author: akin
 */

#include "gtexture.hpp"
#include <iostream>
#include <opengl>
#include <log>
#include <stdexcept>

namespace bolt
{
	GTexture::GTexture()
	: mode( RGBA ),
	  newMode( RGBA ),
	  glMode(GL_RGBA),
	  bytes(4),
	  texture_id(GL_NULL),
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
		// http://www.parashift.com/c++-faq-lite/exceptions.html#faq-17.9
//		Write a message to a log-file. Or call Aunt Tilda. But do not throw an exception!
//		Here's why (buckle your seat-belts):
//		The C++ rule is that you must never throw an exception from a destructor that is being called during the "stack unwinding" process of another exception. For example, if someone says throw Foo(), the stack will be unwound so all the stack frames between the throw Foo() and the } catch (Foo e) { will get popped. This is called stack unwinding.
//		During stack unwinding, all the local objects in all those stack frames are destructed. If one of those destructors throws an exception (say it throws a Bar object), the C++ runtime system is in a no-win situation: should it ignore the Bar and end up in the } catch (Foo e) { where it was originally headed? Should it ignore the Foo and look for a } catch (Bar e) { handler? There is no good answer — either choice loses information.
//		So the C++ language guarantees that it will call terminate() at this point, and terminate() kills the process. Bang you're dead.
//		The easy way to prevent this is never throw an exception from a destructor. But if you really want to be clever, you can say never throw an exception from a destructor while processing another exception. But in this second case, you're in a difficult situation: the destructor itself needs code to handle both throwing an exception and doing "something else", and the caller has no guarantees as to what might happen when the destructor detects an error (it might throw an exception, it might do "something else"). So the whole solution is harder to write. So the easy thing to do is always do "something else". That is, never throw an exception from a destructor.
//		Of course the word never should be "in quotes" since there is always some situation somewhere where the rule won't hold. But certainly at least 99% of the time this is a good rule of thumb.

		try
		{
			destroy();
		}
		catch ( ... )
		{
			// "#!%!¤!!
		}
	}

	void GTexture::destroy() throw (GraphicsException)
	{
		if( texture_id != GL_NULL )
		{
			glDeleteTextures( 1 , &texture_id );
			texture_id = GL_NULL;
			GL_TEST_ERROR("GTexture:dtr delete texture.");
		}
	}

	void GTexture::initialize( const unsigned char *data ) throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
		if( texture_id != GL_NULL )
		{
			throw GraphicsException("Texture already initialized.");
		}

		glGenTextures( 1 , &texture_id );

		bind();

		glPixelStorei( GL_UNPACK_ALIGNMENT , 1 );
		glPixelStorei( GL_PACK_ALIGNMENT , 1 );

		// fits into mem?
		if( !testMemory() )
		{
			destroy();
			throw GraphicsException("Texture does not fit into memory.");
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

		GL_TEST_ERROR("mid.");

		if( data != NULL )
		{
			renderSubTexture( glm::ivec2(0,0) , dimensions , data );
		}

		GL_TEST_ERROR("end");
	}

	bool GTexture::isInitialized() const
	{
		return texture_id != GL_NULL;
	}

	bool GTexture::testMemory() throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
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

		// Test for errors, if width is 0, that means that the
		// memory could not be allocated.
		if( glGetError() != GL_NO_ERROR || width == 0 )
		{
			while( glGetError() != GL_NO_ERROR );
			glBindTexture(GL_TEXTURE_2D, GL_NULL );

			GL_TEST_ERROR("err end");
			return false;
		}
		GL_TEST_ERROR("end");
		return true;
	}

	GTexture& GTexture::setMinificationFilter( TextureFilter filter ) throw (GraphicsException)
	{
		if( texture_id != GL_NULL && filter != minificationFilter )
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

			GL_TEST_ERROR("begin");
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, para );
			GL_TEST_ERROR("end");
		}
		minificationFilter = filter;

		return *this;
	}

	GTexture& GTexture::setMagnificationFilter( TextureFilter filter ) throw (GraphicsException)
	{
		if( texture_id != GL_NULL && filter != magnificationFilter )
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

			GL_TEST_ERROR("begin");
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, para );
			GL_TEST_ERROR("end");
		}

		magnificationFilter = filter;

		return *this;
	}

	GTexture& GTexture::setSWrapMode( WrapMode wrap ) throw (GraphicsException)
	{
		if( texture_id != GL_NULL && wrap != sWrap )
		{
			bind();
			int para = GL_CLAMP_TO_EDGE;

			if( wrap == REPEAT )
			{
				para = GL_REPEAT;
			}

			GL_TEST_ERROR("begin");
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, para );
			GL_TEST_ERROR("end");
		}

		sWrap = wrap;

		return *this;
	}

	GTexture& GTexture::setTWrapMode( WrapMode wrap ) throw (GraphicsException)
	{
		if( texture_id != GL_NULL && wrap != tWrap )
		{
			bind();
			int para = GL_CLAMP_TO_EDGE;

			if( wrap == REPEAT )
			{
				para = GL_REPEAT;
			}

			GL_TEST_ERROR("begin");
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, para );
			GL_TEST_ERROR("end");
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

	void GTexture::generateMipMap() throw (GraphicsException)
	{
		if( texture_id != GL_NULL )
		{
			bind();
			GL_TEST_ERROR("begin");
			glGenerateMipmap(GL_TEXTURE_2D);
			GL_TEST_ERROR("end");
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

	void GTexture::bind() throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
		glBindTexture( GL_TEXTURE_2D , texture_id );
		GL_TEST_ERROR("end");
	}

	void GTexture::release() throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
		glBindTexture( GL_TEXTURE_2D , GL_NULL );
		GL_TEST_ERROR("end");
	}

	void GTexture::resize( glm::ivec2 newDimensions ) throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");

		BufferObject bo;

		bo.reserve( dimensions.x*dimensions.y*bytes , Graphics::write , Graphics::gpu , Graphics::multipleTimes );

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
			glBindTexture(GL_TEXTURE_2D, GL_NULL );
			throw GraphicsException("Could not allocate memory for texture.");
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

		glBindTexture(GL_TEXTURE_2D, GL_NULL );

		GL_TEST_ERROR("end");
	}

	void GTexture::renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , const unsigned char *data ) throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");

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

		GL_TEST_ERROR("mid");

		bind();

		BufferObject bo;

		bo.set( dim.x*dim.y*bytes , data , Graphics::write , Graphics::cpu , Graphics::once );

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

		GL_TEST_ERROR("end");
	}

	void GTexture::renderSubTexture( glm::ivec2 pos , glm::ivec2 dim , BufferObject& bo ) throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
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

		GL_TEST_ERROR("mid");
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

		GL_TEST_ERROR("end");
	}

	void GTexture::renderSubArea( glm::ivec2 pos , glm::ivec2 dim , const unsigned char color ) throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");

		unsigned char data[dim.x*dim.y*bytes];

		for( int i = dim.x*dim.y*bytes-1 ; i>= 0 ; --i)
		{
			data[i] = color;
		}

		renderSubTexture( pos , dim , data );

		GL_TEST_ERROR("end");
	}

	void GTexture::resize( int new_width , int new_height ) throw (GraphicsException)
	{
		return resize( glm::ivec2(new_width,new_height) );
	}

	void GTexture::renderSubTexture( int x , int y , int width , int height , const unsigned char *data ) throw (GraphicsException)
	{
		renderSubTexture( glm::ivec2(x,y) , glm::ivec2(width,height) , data );
	}

	void GTexture::renderSubTexture( int x , int y , int width , int height , BufferObject& bo ) throw (GraphicsException)
	{
		renderSubTexture( glm::ivec2(x,y) , glm::ivec2(width,height) , bo );
	}

	void GTexture::renderSubArea( int x , int y , int width , int height , const unsigned char color ) throw (GraphicsException)
	{
		renderSubArea( glm::ivec2(x,y) , glm::ivec2(width,height) , color );
	}
}
