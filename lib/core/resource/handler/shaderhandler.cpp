/*
 * shaderhandler.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "shaderhandler.hpp"

#include <resource/registry.hpp>
#include <resource/data/bytedata.hpp>
#include <resource/dictionary.hpp>


#include <iostream>
#include <fstream>
#include <log>

namespace bolt
{
namespace resource
{

ShaderHandler::ShaderHandler()
{
}

ShaderHandler::~ShaderHandler()
{
}




bool ShaderHandler::canHandle( const std::string& extension )
{
	// im not gonna bring boost into the project _just_for_ strUp() function.
	if( extension == "fs" ||
		extension == "fS" ||
		extension == "Fs" ||
		extension == "FS" ||
		extension == "vs" ||
		extension == "vS" ||
		extension == "Vs" ||
		extension == "VS" ||
		// CFG!
		extension == "gs" ||
		extension == "gS" ||
		extension == "Gs" ||
		extension == "GS"  )
	{
		return true;
	}
	return false;
}

Work *ShaderHandler::handle( const std::string& alias , const std::string path )
{
	Work *work = new ShaderWork( alias , path );

	return work;
}





ShaderWork::ShaderWork( const std::string& alias , const std::string path )
: alias( alias ),
  path( path )
{
}

ShaderWork::~ShaderWork()
{
}

bool ShaderWork::begin()
{
	return true;
}

void ShaderWork::run()
{
	// Check if resource has been loaded,
	// if not, load it.
	uint key = Singleton<Dictionary>::get()->resolveKey( alias );

	bool has = bolt::Singleton<Registry<ByteData> >::create()->hasObject( key );

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

	unsigned char *data = new unsigned char[ length ];

	stream.read( (char*)data , length );

	if( stream.gcount() != length )
	{
		// ERROR!
		delete[] data;
		LOG_ERROR << "Read data length is different than what was intended." << std::endl;
		return;
	}

	ByteData *bdata = new ByteData( data, length );

	// Give the ownership to Handle.
	if( !bolt::Singleton<Registry<ByteData> >::create()->setObject( key , bdata ) )
	{
		delete bdata;
		return;
	}

	return;
}

void ShaderWork::end()
{
	// All is done.. Kill yourself.
	delete this;
}

}
} /* namespace bolt */
