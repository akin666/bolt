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
			GL_TEST_ERROR("begin");
			glDeleteBuffers( 1 , &id );
			id = GL_NULL;
			GL_TEST_ERROR("end");
		}
	}

	void BufferObject::initialize() throw (GraphicsException)
	{
		// create ID.
		if( id == GL_NULL )
		{
			GL_TEST_ERROR("begin");
			glGenBuffers( 1 , &id );
			GL_TEST_ERROR("end");
		}
	}

	bool BufferObject::hasInitialized()
	{
		return id != GL_NULL;
	}

	void BufferObject::reserve( const unsigned int bytesize , Graphics::BindStyle style , Graphics::Residence residence , Graphics::Updates updates ) throw (GraphicsException)
	{
		set( bytesize , 0 , style , residence , updates );
	}

	void BufferObject::set( unsigned int bytesize , const void *data , Graphics::BindStyle style , Graphics::Residence residence , Graphics::Updates updates ) throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
		initialize();

		int hint = Graphics::resolveResidenceUpdates( residence , updates );

		bind( style );

		int bindStyle;
		switch( style )
		{
			case Graphics::write : bindStyle = 				GL_PIXEL_PACK_BUFFER; break;
			case Graphics::read : bindStyle = 				GL_PIXEL_UNPACK_BUFFER; break;
			case Graphics::arrayBuffer : bindStyle = 		GL_ARRAY_BUFFER; break;
			case Graphics::elementArrayBuffer : bindStyle=	GL_ELEMENT_ARRAY_BUFFER; break;
			default : bindStyle = 							GL_PIXEL_PACK_BUFFER; break;
		}

		glBufferData( bindStyle , bytesize , data , hint );
		GL_TEST_ERROR("mid");
		release( style );

		GL_TEST_ERROR("end");
	}


	void BufferObject::bind( Graphics::BindStyle style ) const throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
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
		GL_TEST_ERROR("end");
	}

	void BufferObject::release( Graphics::BindStyle style ) const throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
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
		GL_TEST_ERROR("end");
	}

	unsigned char *BufferObject::bindMemoryMap( Graphics::BindStyle style ) const throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
		int buffstyle;

		switch( style )
		{
			case Graphics::read : buffstyle = 			GL_READ_ONLY; break;
			case Graphics::write : buffstyle = 			GL_WRITE_ONLY; break;
			case Graphics::readAndWrite : buffstyle = 	GL_READ_WRITE; break;
			default: buffstyle = 						GL_READ_ONLY; break;
		}

		GLubyte* ptr = (GLubyte*)glMapBufferARB( (style == Graphics::write ? GL_PIXEL_PACK_BUFFER : GL_PIXEL_UNPACK_BUFFER ) , buffstyle );

		GL_TEST_ERROR("end");

		return ptr;
	}

	void BufferObject::releaseMemoryMap( Graphics::BindStyle style ) const throw (GraphicsException)
	{
		GL_TEST_ERROR("begin");
		glUnmapBuffer( (style == Graphics::write ? GL_PIXEL_PACK_BUFFER : GL_PIXEL_UNPACK_BUFFER ) );
		GL_TEST_ERROR("end");
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
