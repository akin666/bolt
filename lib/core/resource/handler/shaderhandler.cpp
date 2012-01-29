/*
 * shaderhandler.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "shaderhandler.hpp"

#include <singleton>
#include <resource/registry.hpp>
#include <resource/dictionary.hpp>

#include <graphics/shader/shader.hpp>

#include <iostream>
#include <fstream>
#include <log>

namespace bolt
{
namespace resource
{

class ShaderWork : public Work
{
protected:
	std::string alias;
	std::string path;
	Shader::Type type;
public:
	ShaderWork( const std::string& alias , const std::string path , Shader::Type type )
	: alias( alias ),
	  path( path ),
	  type( type )
	{
	}
	virtual ~ShaderWork()
	{
	}

	virtual bool begin()
	{
		return true;
	}

	virtual void run()
	{
		// Check if resource has been loaded,
		// if not, load it.
		uint key = getSingleton<Dictionary>()->resolveKey( alias );

		bool has = createSingleton<Registry<Shader> >()->hasObject( key );

		if( has )
		{
			return;
		}

		// Load the file.
		// in its fullest.
		std::fstream stream;

		stream.open( path.c_str() , std::fstream::in | std::fstream::binary );

		if( !stream.is_open() )
		{
			stream.close();
			LOG_ERROR << "Stream does not exist." << std::endl;
			return;
		}

		if( !stream.good() )
		{
			stream.close();
			LOG_ERROR << "Stream is bad." << std::endl;
			return;
		}

		stream.seekg (0, std::ios::end);
		int length = stream.tellg();
		stream.seekg (0, std::ios::beg);

		TextData data( length );

		stream.read( data.access() , length );

		if( stream.gcount() != length )
		{
			// ERROR!
			LOG_ERROR << "Read data length is different than what was intended." << std::endl;
			return;
		}

		Shader *shader = new Shader( );
		shader->setType( type );

		shader->set( data );

		// Give the ownership to Handle.
		createSingleton<Registry<Shader> >()->setObject( key , shader );
	}

	virtual void end()
	{
		// All is done.. Kill yourself.
		delete this;
	}
};

Shader::Type resolveFromFileType( std::string type )
{
	if( type ==  ShaderHandler::fragmentExtension ) return Shader::FRAGMENT;
	else if( type == ShaderHandler::vertexExtension ) return Shader::VERTEX;
	else if( type == ShaderHandler::geometryExtension ) return Shader::GEOMETRY;
	else if( type == ShaderHandler::controlExtension ) return Shader::CONTROL;
	else if( type == ShaderHandler::evaluationExtension ) return Shader::EVALUATION;
	return Shader::UNKNOWN;
}

std::string resolveFileTypeFrom( Shader::Type type )
{
	switch( type )
	{
		case Shader::FRAGMENT : return ShaderHandler::fragmentExtension;
		case Shader::VERTEX : return ShaderHandler::vertexExtension;
		case Shader::GEOMETRY : return ShaderHandler::geometryExtension;
		case Shader::CONTROL : return ShaderHandler::controlExtension;
		case Shader::EVALUATION : return ShaderHandler::evaluationExtension;
		default : return "";
	}
	return "";
}

const std::string ShaderHandler::fragmentExtension("fs");
const std::string ShaderHandler::vertexExtension("vs");
const std::string ShaderHandler::geometryExtension("gs");
const std::string ShaderHandler::controlExtension("cs");
const std::string ShaderHandler::evaluationExtension("es");

ShaderHandler::ShaderHandler()
{
}

ShaderHandler::~ShaderHandler()
{
}

bool ShaderHandler::canHandle( const std::string& extension )
{
	return resolveFromFileType( extension ) != Shader::UNKNOWN;
}

Work *ShaderHandler::handle( std::string alias , std::string path , std::string type )
{
	Shader::Type shaderType = resolveFromFileType( type );

	Work *work = new ShaderWork( alias , path , shaderType );

	return work;
}

}
} /* namespace bolt */
