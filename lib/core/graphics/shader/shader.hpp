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
#include <data>

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
		uint id;
		Type m_type;

		Data<char> data;
	public:
		Shader();
		virtual ~Shader();

		void setType( Type type );
		void setTypeString( std::string type );

		uint getId();

		// GL commands! only call from GL thread.
		bool load() throw (std::exception);

		// set can be called from any thread.
		void set( const Data<char>& newData );
	};
}

#endif /* SHADER_H_ */
