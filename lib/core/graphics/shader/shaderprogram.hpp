/*
 * shaderprogram.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <common>
#include <string>
#include <graphics/graphicsexception.hpp>
#include <map>

namespace bolt
{
	class Shader;
	class Uniform;
	class Attribute;
	class ShaderProgram
	{
	protected:
		std::map< std::string , Attribute *> attributes;
		std::map< std::string , Uniform *> uniforms;

		bool linking;
		uint m_id;
	public:
		ShaderProgram();
		virtual ~ShaderProgram();

		uint getId();

		Attribute *insertAttribute( std::string key ) throw (GraphicsException);
		Uniform *insertUniform( std::string key ) throw (GraphicsException);

		Attribute *getAttribute( std::string key ) throw (GraphicsException);
		Uniform *getUniform( std::string key ) throw (GraphicsException);

		void bind() throw (GraphicsException);
		static void bindDefault() throw (GraphicsException);

		// Shader creation functionality:
		void attach( Shader *piece ) throw (GraphicsException);
		void link() throw (GraphicsException);

		std::string getError() throw (GraphicsException);

		bool linked();
	};
}

#endif /* SHADERPROGRAM_H_ */
