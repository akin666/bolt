/*
 * framebuffer.cpp
 *
 *  Created on: 3.4.2010
 *      Author: akin
 */

#include "framebuffer.hpp"
#include <opengl>
#include "texture/gtexture.hpp"

namespace bolt
{
	Framebuffer::Framebuffer()
	{
		m_depth = 0;
		m_width = 0;
		m_height = 0;
		m_id = 0;
	}

	Framebuffer::~Framebuffer()
	{
		if( m_id != 0 ) {
			glDeleteFramebuffers( 1 , &m_id );
			m_id = 0;
		}

		GL_TEST_ERROR("Framebuffer Destructor")
	}

	void Framebuffer::attachTexture( GTexture& texture )
	{
		attachTexture( texture.getWidth() , texture.getHeight() , texture.getTextureId() );
	}

	void Framebuffer::attachTexture( unsigned int width , unsigned int height , unsigned int texture_id )
	{
		m_width = width;
		m_height = height;

		bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id , 0);

		GL_TEST_ERROR("Framebuffer attachTexture")
	}

	void Framebuffer::attachDepth()
	{
		bind();
		glGenRenderbuffers(1, &m_depth);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth);

		GL_TEST_ERROR("Framebuffer attachDepth")
	}

	void Framebuffer::removeDepth()
	{
		if( m_depth == 0 )
		{
			return;
		}

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
		GL_TEST_ERROR("Framebuffer removeDepth")

		m_depth = 0;
	}

	unsigned int Framebuffer::getDepthId()
	{
		return m_depth;
	}

	void Framebuffer::bind()
	{
		if( m_id == 0 )
		{
			glGenFramebuffers(1 , &m_id );
			GL_TEST_ERROR("Framebuffer Construction")
		}

		glBindFramebuffer( GL_FRAMEBUFFER , m_id );

		GL_TEST_ERROR("Framebuffer bind")
	}

	int Framebuffer::getWidth()
	{
		return m_width;
	}

	int Framebuffer::getHeight()
	{
		return m_height;
	}

	bool Framebuffer::invariant()
	{
		GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);

		switch( status )
		{
			case GL_FRAMEBUFFER_COMPLETE :
				return true;
			case GL_FRAMEBUFFER_UNDEFINED :
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT :
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT :
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER :
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER :
			case GL_FRAMEBUFFER_UNSUPPORTED :
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE :
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS :
			default:
				return false;
		}

		return true;
	}

	void Framebuffer::bindDefault()
	{
		glBindFramebuffer( GL_FRAMEBUFFER , 0 );

		GL_TEST_ERROR("");
	}
}

