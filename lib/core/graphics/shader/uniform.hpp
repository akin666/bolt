/*
 * uniform.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef UNIFORM_H_
#define UNIFORM_H_

#include <iostream>
#include <glm/glm>
#include <graphics/texture/texture.hpp>
#include <graphics/graphicsexception.hpp>
#include <common>

namespace bolt
{
	class Uniform
	{
	protected:
		uint m_program_id;
		int m_uniform_id;
		std::string m_name;
	public:
		Uniform( );
		virtual ~Uniform();

		void setProgram( uint program );
		void attach( std::string name ) throw (GraphicsException);
		std::string getName();

		void set( float v ) throw (GraphicsException);
		void set( float v , float v2 ) throw (GraphicsException);
		void set( float v , float v2 , float v3 ) throw (GraphicsException);
		void set( float v , float v2 , float v3 , float v4 ) throw (GraphicsException);
		void set( int v ) throw (GraphicsException);
		void set( int v , int v2 ) throw (GraphicsException);
		void set( int v , int v2 , int v3 ) throw (GraphicsException);
		void set( int v , int v2 , int v3 , int v4 ) throw (GraphicsException);

		void set( float *v , int size ) throw (GraphicsException);
		void set2( float *v , int size ) throw (GraphicsException);
		void set3( float *v , int size ) throw (GraphicsException);
		void set4( float *v , int size ) throw (GraphicsException);
		void set( int *v , int size ) throw (GraphicsException);
		void set2( int *v , int size ) throw (GraphicsException);
		void set3( int *v , int size ) throw (GraphicsException);
		void set4( int *v , int size ) throw (GraphicsException);

		void setMatrix4( const float *v , int size ) throw (GraphicsException);

		void set( const glm::mat4x4& matrix ) throw (GraphicsException);
		void set( const glm::vec2& vec ) throw (GraphicsException);
		void set( const glm::vec3& vec ) throw (GraphicsException);
		void set( const glm::vec4& vec ) throw (GraphicsException);
		void set( const glm::ivec2& vec ) throw (GraphicsException);
		void set( const glm::ivec3& vec ) throw (GraphicsException);
		void set( const glm::ivec4& vec ) throw (GraphicsException);

		void bindTexture( int texture_unit , uint texture_id ) throw (GraphicsException);
		void bindTexture( const Texture& texture , int texture_unit = 0 ) throw (GraphicsException);
	};
}

#endif /* UNIFORM_H_ */
