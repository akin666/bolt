/*
 * attribute.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "attribute.hpp"
#include <stdexcept>


namespace bolt
{
	Attribute::Attribute( )
	{
		m_program_id = 0;
	}

	Attribute::~Attribute()
	{
	}

	void Attribute::setProgram( uint program )
	{
		m_program_id = program;
	}

	void Attribute::attach( std::string name ) throw (std::exception)
	{
		GL_TEST_ERROR("begin")
		m_name = name;

		m_attribute_id = glGetAttribLocation( m_program_id , (const GLchar*)name.c_str() );

		if( m_attribute_id < 0 )
		{
			throw std::runtime_error("Attribute location was not found.");
		}

		GL_TEST_ERROR("end")
	}

	std::string Attribute::getName()
	{
		return m_name;
	}

	void Attribute::enable()
	{
		GL_TEST_ERROR("begin")
		glEnableVertexAttribArray( m_attribute_id );
		GL_TEST_ERROR("end")
	}

	void Attribute::disable()
	{
		GL_TEST_ERROR("begin")
		glDisableVertexAttribArray( m_attribute_id );
		GL_TEST_ERROR("end")
	}

	void Attribute::setPointer( int data_size , GLenum data_type , GLsizei stride )
	{
		GL_TEST_ERROR("begin")
		//glEnableVertexAttribArray(0);
		//We like submitting vertices on stream 0 for no special reason //The starting point of the VBO, for the vertices
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(0));
		//glEnableVertexAttribArray(1);
		//We like submitting normals on stream 1 for no special reason //The starting point of normals, 12 bytes away
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(12));
		//glEnableVertexAttribArray(2);
		//We like submitting texcoords on stream 2 for no special reason //The starting point of texcoords, 24 bytes away
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(24));
		// A (starting point), How many datas, normalized?, size of whole element (0=packed data), position in data ??
	//	glBindBuffer( GL_ARRAY_BUFFER , buffer_id );
		glEnableVertexAttribArray( m_attribute_id );
		// GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer
		glVertexAttribPointer( m_attribute_id , data_size , data_type , GL_FALSE , stride , NULL );
		//glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
		//glEnableVertexAttribArray(VETEX_POS_INDX);
		//glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, vtxStrides[0], 0);
		GL_TEST_ERROR("end")
	}

	void Attribute::setPointer(int size, GLenum type, void *ptr)
	{
		GL_TEST_ERROR("begin")
		// glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
		glVertexAttribPointer( 0 , size, type, GL_FALSE , 0 , ptr );
		GL_TEST_ERROR("end")
	}

	void Attribute::set(float v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib1f( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(float v, float v2)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib2f( m_attribute_id , v , v2 );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(float v, float v2, float v3)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib3f( m_attribute_id , v , v2 , v3 );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(float v, float v2, float v3, float v4)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4f( m_attribute_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(double v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib1d( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(double v, double v2)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib2d( m_attribute_id , v , v2 );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(double v, double v2, double v3)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib3d( m_attribute_id , v , v2 , v3 );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(double v, double v2, double v3, double v4)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4d( m_attribute_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(short v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib1s( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(short v, short v2)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib2s( m_attribute_id , v , v2 );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(short v, short v2, short v3)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib3s( m_attribute_id , v , v2 , v3 );
		GL_TEST_ERROR("end")
	}
	void Attribute::set(short v, short v2, short v3, short v4)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4s( m_attribute_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("end")
	}

	void Attribute::set(float *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib1fv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set2(float *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib2fv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set3(float *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib3fv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4(float *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4fv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}

	void Attribute::set(double *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib1dv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set2(double *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib2dv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set3(double *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib3dv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4(double *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4dv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}

	void Attribute::set(short *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib1sv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set2(short *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib2sv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set3(short *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib3sv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4(short *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4sv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}

	void Attribute::set4(int *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4iv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4(char *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4bv( m_attribute_id , (GLbyte*)v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4(unsigned char *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4ubv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4(unsigned short *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4usv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4(uint *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4uiv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}

	// normalized
	void Attribute::setN(unsigned char v, unsigned char v2, unsigned char v3, unsigned char v4)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4Nub( m_attribute_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4N(char *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4Nbv( m_attribute_id , (GLbyte*)v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4N(short *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4Nsv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4N(int *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4Niv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4N(unsigned char *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4Nubv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4N(unsigned short *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4Nusv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
	void Attribute::set4N(uint *v)
	{
		GL_TEST_ERROR("begin")
		glVertexAttrib4Nuiv( m_attribute_id , v );
		GL_TEST_ERROR("end")
	}
}
