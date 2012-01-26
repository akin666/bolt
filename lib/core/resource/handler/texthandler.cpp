/*
 * texthandler.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "texthandler.hpp"

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

TextHandler::TextHandler()
{
}

TextHandler::~TextHandler()
{
}

bool TextHandler::canHandle( const std::string& extension )
{
	// im not gonna bring boost into the project _just_for_ strUp() function.
	if( extension == "txt" ||
		extension == "txT" ||
		extension == "tXt" ||
		extension == "tXT" ||
		extension == "Txt" ||
		extension == "TxT" ||
		extension == "TXt" ||
		extension == "TXT" ||
		// CFG!
		extension == "cfg" ||
		extension == "cfG" ||
		extension == "cFg" ||
		extension == "cFG" ||
		extension == "Cfg" ||
		extension == "CfG" ||
		extension == "CFg" ||
		extension == "CFG" )
	{
		return true;
	}
	return false;
}

Work *TextHandler::handle( const std::string& alias , const std::string path )
{
	Work *work = new ByteDataWork( alias , path );

	return work;
}



















ByteDataWork::ByteDataWork( const std::string& alias , const std::string path )
: alias( alias ),
  path( path )
{
}

ByteDataWork::~ByteDataWork()
{
}

bool ByteDataWork::begin()
{
	return true;
}

void ByteDataWork::run()
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

void ByteDataWork::end()
{
	// All is done.. Kill yourself.
	delete this;
}



}
} /* namespace bolt */
