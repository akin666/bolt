/*
 * attribute.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <iostream>
#include <opengl>
#include <exception>
#include <common>

namespace bolt
{
	class Attribute
	{
	protected:
		uint m_program_id;
		int m_attribute_id;
		std::string m_name;
	public:
		Attribute();
		virtual ~Attribute();

		void setProgram( uint program );
		void attach( std::string name ) throw (std::exception);
		std::string getName();

		void setPointer( int size , GLenum type , void *ptr );
		void setPointer( int data_size , GLenum data_type , GLsizei stride );

		void enable();
		void disable();

		void set( float v );
		void set( float v , float v2 );
		void set( float v , float v2 , float v3 );
		void set( float v , float v2 , float v3 , float v4 );
		void set( double v );
		void set( double v , double v2 );
		void set( double v , double v2 , double v3 );
		void set( double v , double v2 , double v3 , double v4 );
		void set( short v );
		void set( short v , short v2 );
		void set( short v , short v2 , short v3 );
		void set( short v , short v2 , short v3 , short v4 );

		void set( float *v );
		void set2( float *v );
		void set3( float *v );
		void set4( float *v );

		void set( double *v );
		void set2( double *v );
		void set3( double *v );
		void set4( double *v );

		void set( short *v );
		void set2( short *v );
		void set3( short *v );
		void set4( short *v );

		void set4( int *v );
		void set4( char *v );
		void set4( unsigned char *v );
		void set4( unsigned short *v );
		void set4( uint *v );

		// normalized
		void setN( unsigned char v , unsigned char v2 , unsigned char v3 , unsigned char v4 );
		void set4N( char *v );
		void set4N( short *v );
		void set4N( int *v );
		void set4N( unsigned char *v );
		void set4N( unsigned short *v );
		void set4N( uint *v );
	};
}

#endif /* ATTRIBUTE_H_ */
