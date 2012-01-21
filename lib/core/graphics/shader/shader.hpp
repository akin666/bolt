/*
 * shader.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <exception>
#include <common>

namespace bolt
{
	class Shader
	{
	public:
		enum Type {
			UNKNOWN = 0,   // 0.0
			FRAGMENT = 1,  // 2.0
			VERTEX = 2,    // 2.0
			GEOMETRY = 3,  // 3.2
			CONTROL = 4,   // 4.0
			EVALUATION = 5 // 4.0
		};
	protected:
		Type m_type;
		uint id;
	public:
		Shader();
		virtual ~Shader();

		void setType( Type type );
		void setTypeString( std::string type );

		uint getId();

		bool load( const unsigned char *data , int length ) throw (std::exception);
	};
}

#endif /* SHADER_H_ */
