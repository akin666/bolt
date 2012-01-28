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

		uint state;

		void setLoaded( bool status );
		void setCompiled( bool status );

		static const uint LOADED = 		0x0001;
		static const uint COMPILED =	0x0002;
	public:
		Shader();
		virtual ~Shader();

		void setType( Type type );
		void setTypeString( std::string type );
		Type getType();

		uint getId();

		bool isLoaded();

		void set( const Data<char>& newData );
		char *access();
		uint size();
	public:
		// GL commands! only call from GL thread.
		void createId();
		void compile() throw (std::exception);
		void load() throw (std::exception);
		void reset();
	};
}

#endif /* SHADER_H_ */
