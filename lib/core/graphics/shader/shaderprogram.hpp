/*
 * shaderprogram.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <exception>
#include <map>
#include "shader.hpp"
#include "uniform.hpp"
#include "attribute.hpp"

namespace bolt
{
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

		Attribute *insertAttribute( std::string key ) throw (std::exception);
		Uniform *insertUniform( std::string key ) throw (std::exception);

		Attribute *getAttribute( std::string key ) throw (std::exception);
		Uniform *getUniform( std::string key ) throw (std::exception);

		void bind() throw (std::exception);
		static void bindDefault();

		// Shader creation functionality:
		void attach( Shader *piece ) throw (std::exception);
		void link() throw (std::exception);

		std::string getError();

		bool linked();
	};
}

#endif /* SHADERPROGRAM_H_ */
