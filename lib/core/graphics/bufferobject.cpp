/*
 *
 *  Created on: 5.7.2011
 *      Author: akin
 */

#include "bufferobject.hpp"
#include <opengl>

namespace bolt
{
	BufferObject::BufferObject( )
	: bsize(0),
	  id(GL_NULL)
	{
	}

	BufferObject::~BufferObject()
	{
		if( id != GL_NULL )
		{
			glDeleteBuffers( 1 , &id );
			id = GL_NULL;
		}
	}

	void BufferObject::initialize() throw (GraphicsException)
	{
		// create ID.
		if( id == GL_NULL )
		{
			glGenBuffers( 1 , &id );
		}
	}

	bool BufferObject::hasInitialized()
	{
		return id != GL_NULL;
	}

	void BufferObject::reserve( const unsigned int bytesize , Graphics::Residence residence , Graphics::Updates updates ) throw (GraphicsException)
	{
		set( bytesize , 0 , residence , updates );
	}

	void BufferObject::set( const unsigned int bytesize , const void *data , Graphics::Residence residence , Graphics::Updates updates ) throw (GraphicsException)
	{
		GL_TEST_ERROR("BufferObject:set START.");
		initialize();

		const int hint = Graphics::resolveResidenceUpdates( residence , updates );

		bind( Graphics::write );
		glBufferData( GL_PIXEL_PACK_BUFFER , bytesize , data , hint );
		release( Graphics::write );

		GL_TEST_ERROR("BufferObject:set END.");
	}


	void BufferObject::bind( const Graphics::BindStyle style ) const throw (GraphicsException)
	{
		int bindStyle;

		switch( style )
		{
			case Graphics::write : bindStyle = 				GL_PIXEL_PACK_BUFFER; break;
			case Graphics::read : bindStyle = 				GL_PIXEL_UNPACK_BUFFER; break;
			case Graphics::arrayBuffer : bindStyle = 		GL_ARRAY_BUFFER; break;
			case Graphics::elementArrayBuffer : bindStyle=	GL_ELEMENT_ARRAY_BUFFER; break;
			default : bindStyle = 							GL_PIXEL_PACK_BUFFER; break;
		}

		glBindBuffer( bindStyle , id );
	}

	void BufferObject::release( const Graphics::BindStyle style ) const throw (GraphicsException)
	{
		int bindStyle;

		switch( style )
		{
			case Graphics::write : bindStyle = 				GL_PIXEL_PACK_BUFFER; break;
			case Graphics::read : bindStyle = 				GL_PIXEL_UNPACK_BUFFER; break;
			case Graphics::arrayBuffer : bindStyle = 		GL_ARRAY_BUFFER; break;
			case Graphics::elementArrayBuffer : bindStyle=	GL_ELEMENT_ARRAY_BUFFER; break;
			default : bindStyle = 							GL_PIXEL_PACK_BUFFER; break;
		}

		glBindBuffer( bindStyle , GL_NULL );
	}

	unsigned char *BufferObject::bindMemoryMap( const Graphics::BindStyle style ) const throw (GraphicsException)
	{
		GL_TEST_ERROR("BufferObject:bindMemoryMap START.");
		int buffstyle;

		switch( style )
		{
			case Graphics::read : buffstyle = 			GL_READ_ONLY; break;
			case Graphics::write : buffstyle = 			GL_WRITE_ONLY; break;
			case Graphics::readAndWrite : buffstyle = 	GL_READ_WRITE; break;
			default: buffstyle = 						GL_READ_ONLY; break;
		}

		GLubyte* ptr = (GLubyte*)glMapBufferARB( (style == Graphics::write ? GL_PIXEL_PACK_BUFFER : GL_PIXEL_UNPACK_BUFFER ) , buffstyle );

		GL_TEST_ERROR("BufferObject:bindMemoryMap END.");

		return ptr;
	}

	void BufferObject::releaseMemoryMap( const Graphics::BindStyle style ) const throw (GraphicsException)
	{
		glUnmapBuffer( (style == Graphics::write ? GL_PIXEL_PACK_BUFFER : GL_PIXEL_UNPACK_BUFFER ) );
	}

	unsigned int BufferObject::getID() const
	{
		return id;
	}

	unsigned int BufferObject::size() const
	{
		return bsize;
	}
}
