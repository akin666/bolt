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
#include <common>
#include <graphics/graphicsexception.hpp>

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
		void attach( std::string name ) throw (GraphicsException);
		std::string getName();

		void setPointer( int size , GLenum type , void *ptr ) throw (GraphicsException);
		void setPointer( int data_size , GLenum data_type , GLsizei stride ) throw (GraphicsException);

		void enable() throw (GraphicsException);
		void disable() throw (GraphicsException);

		void set( float v ) throw (GraphicsException);
		void set( float v , float v2 ) throw (GraphicsException);
		void set( float v , float v2 , float v3 ) throw (GraphicsException);
		void set( float v , float v2 , float v3 , float v4 ) throw (GraphicsException);
		void set( double v ) throw (GraphicsException);
		void set( double v , double v2 ) throw (GraphicsException);
		void set( double v , double v2 , double v3 ) throw (GraphicsException);
		void set( double v , double v2 , double v3 , double v4 ) throw (GraphicsException);
		void set( short v ) throw (GraphicsException);
		void set( short v , short v2 ) throw (GraphicsException);
		void set( short v , short v2 , short v3 ) throw (GraphicsException);
		void set( short v , short v2 , short v3 , short v4 ) throw (GraphicsException);

		void set( float *v ) throw (GraphicsException);
		void set2( float *v ) throw (GraphicsException);
		void set3( float *v ) throw (GraphicsException);
		void set4( float *v ) throw (GraphicsException);

		void set( double *v ) throw (GraphicsException);
		void set2( double *v ) throw (GraphicsException);
		void set3( double *v ) throw (GraphicsException);
		void set4( double *v ) throw (GraphicsException);

		void set( short *v ) throw (GraphicsException);
		void set2( short *v ) throw (GraphicsException);
		void set3( short *v ) throw (GraphicsException);
		void set4( short *v ) throw (GraphicsException);

		void set4( int *v ) throw (GraphicsException);
		void set4( char *v ) throw (GraphicsException);
		void set4( unsigned char *v ) throw (GraphicsException);
		void set4( unsigned short *v ) throw (GraphicsException);
		void set4( uint *v ) throw (GraphicsException);

		// normalized
		void setN( unsigned char v , unsigned char v2 , unsigned char v3 , unsigned char v4 ) throw (GraphicsException);
		void set4N( char *v ) throw (GraphicsException);
		void set4N( short *v ) throw (GraphicsException);
		void set4N( int *v ) throw (GraphicsException);
		void set4N( unsigned char *v ) throw (GraphicsException);
		void set4N( unsigned short *v ) throw (GraphicsException);
		void set4N( uint *v ) throw (GraphicsException);
	};
}

#endif /* ATTRIBUTE_H_ */
