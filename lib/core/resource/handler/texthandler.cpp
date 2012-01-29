/*
 * texthandler.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "texthandler.hpp"

#include <resource/registry.hpp>
#include <resource/dictionary.hpp>

#include <data>
#include <iostream>
#include <fstream>
#include <log>

namespace bolt
{
namespace resource
{

class ByteDataWork : public Work
{
protected:
	std::string alias;
	std::string path;
public:
	ByteDataWork( const std::string& alias , const std::string path )
	: alias( alias ),
	  path( path )
	{
	}
	virtual ~ByteDataWork()
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

		bool has = createSingleton<Registry<TextData> >()->hasObject( key );

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

		TextData *data = new TextData( length );

		stream.read( data->access() , length );

		if( stream.gcount() != length )
		{
			// ERROR!
			delete data;
			LOG_ERROR << "Read data length is different than what was intended." << std::endl;
			return;
		}

		// Give the ownership to Handle.
		createSingleton<Registry<TextData> >()->setObject( key , data );
	}

	virtual void end()
	{
		// All is done.. Kill yourself.
		delete this;
	}
};

TextHandler::TextHandler()
{
}

TextHandler::~TextHandler()
{
}

bool TextHandler::canHandle( const std::string& extension )
{
	if( extension == "txt" ||
		extension == "cfg" )
	{
		return true;
	}
	return false;
}

Work *TextHandler::handle( std::string alias , std::string path , std::string type )
{
	Work *work = new ByteDataWork( alias , path );

	return work;
}



}
} /* namespace bolt */
