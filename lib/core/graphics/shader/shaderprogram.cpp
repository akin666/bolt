/*
 * shaderprogram.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "shaderprogram.hpp"

#include <opengl>
#include <iostream>
#include "attribute.hpp"
#include "uniform.hpp"
#include "shader.hpp"
#include <stdexcept>

namespace bolt
{
	void tryCreatingShaderProgram( uint &id )
	{
		if( id == GL_NULL )
		{
			GL_TEST_ERROR("begin")
			id = glCreateProgram();

			GL_TEST_ERROR("end")
		}
	}

	ShaderProgram::ShaderProgram()
	{
		m_id = GL_NULL;
		linking = false;
	}

	ShaderProgram::~ShaderProgram()
	{
		if( m_id != GL_NULL )
		{
			GL_TEST_ERROR("begin")
			glDeleteProgram( m_id );
			GL_TEST_ERROR("end")
		}
	}

	uint ShaderProgram::getId()
	{
		return m_id;
	}

	Attribute *ShaderProgram::insertAttribute( std::string key ) throw (GraphicsException)
	{
		Attribute *att = NULL;

		try
		{
			att = new Attribute;
			att->setProgram( m_id );
			att->attach( key );
			attributes[key] = att;

			return att;
		}
		catch( ... ) {
			delete att;
			att = NULL;
		}
		throw GraphicsException("Insert attribute failed.");
	}

	Uniform *ShaderProgram::insertUniform( std::string key ) throw (GraphicsException)
	{
		Uniform *uni = NULL;
		try
		{
			uni = new Uniform;
			uni->setProgram( m_id );
			uni->attach( key );
			uniforms[key] = uni;

			return uni;
		}
		catch( ... ) {
			delete uni;
			uni = NULL;
		}
		throw GraphicsException("Insert uniform failed.");
	}

	Attribute *ShaderProgram::getAttribute( std::string key ) throw (GraphicsException)
	{
		std::map< std::string , Attribute * >::iterator iter = attributes.find( key );

		if( iter == attributes.end() )
		{
			// Try to see if it has the uniform
			GL_TEST_ERROR("begin")
			int m_fff = glGetAttribLocation( m_id , (const GLchar*)key.c_str() );
			GL_TEST_ERROR("end")

			if( m_fff < 0 )
			{
				throw GraphicsException(std::string("[attribute location not found] ") + key );
				return NULL;
			}

			return insertAttribute( key );
		}

		return iter->second;
	}

	Uniform *ShaderProgram::getUniform( std::string key ) throw (GraphicsException)
	{
		std::map< std::string , Uniform * >::iterator iter = uniforms.find( key );

		if( iter == uniforms.end() )
		{
			// Try to see if it has the uniform
			GL_TEST_ERROR("begin")
			int m_fff = glGetUniformLocation( m_id , (const GLchar*)key.c_str() );
			GL_TEST_ERROR("end")

			if( m_fff < 0 )
			{
				throw GraphicsException(std::string("[uniform location not found] ") + key );
				return NULL;
			}

			return insertUniform( key );
		}

		return iter->second;
	}

	void ShaderProgram::bind() throw (GraphicsException)
	{
		GL_TEST_ERROR("begin")
		glUseProgram( m_id );
		GL_TEST_ERROR("end")
	}

	void ShaderProgram::bindDefault() throw (GraphicsException)
	{
		GL_TEST_ERROR("begin")
		glUseProgram( 0 );
		GL_TEST_ERROR("end")
	}

	// Shader creation functionality:
	void ShaderProgram::attach( Shader *piece ) throw (GraphicsException)
	{
		GL_TEST_ERROR("begin")
		if( piece == NULL )
		{
			throw GraphicsException("Error, cannot attach NULL shader to program");
		}
		tryCreatingShaderProgram( m_id );
		linking = false;

		glAttachShader( m_id , piece->getId() );
		GL_TEST_ERROR("end")
	}

	void ShaderProgram::link() throw (GraphicsException)
	{
		GL_TEST_ERROR("begin")
		glLinkProgram( m_id );

		GLint tmp;
		glGetProgramiv( m_id , GL_LINK_STATUS , &tmp );
		GL_TEST_ERROR("end")
		if( tmp ) {
			linking = true;
		}
		else {
			linking = false;
		}
	}

	std::string ShaderProgram::getError() throw (GraphicsException)
	{
		GL_TEST_ERROR("begin")
		if( m_id == GL_NULL )
		{
			return "";
		}

		GLint loglen = 0;
		glGetProgramiv( m_id , GL_INFO_LOG_LENGTH , &loglen );
		GL_TEST_ERROR("mid")
		if (loglen > 0)
		{
			//GLchar* log = (GLchar*)malloc(sizeof(GLchar)*loglen);
			GLchar* log = new GLchar[loglen];
			glGetProgramInfoLog( m_id , loglen , NULL , log );
			GL_TEST_ERROR("end")

			std::string data( log );
			delete[] log;

			return data;
		}

		return "";
	}

	bool ShaderProgram::linked()
	{
		return (linking && m_id != GL_NULL);
	}
}
