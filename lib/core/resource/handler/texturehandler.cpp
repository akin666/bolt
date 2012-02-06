/*
 * texthandler.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "texturehandler.hpp"

#include <resource/registry.hpp>
#include <resource/dictionary.hpp>

#include <iostream>
#include <fstream>
#include <log>

#include <data>
#include <graphics/texture/gtexture.hpp>
#include <stb_image.h>

namespace bolt
{
namespace resource
{

class TextureDataWork : public Work
{
protected:
	std::string alias;
	std::string path;
public:
	TextureDataWork( const std::string& alias , const std::string path )
	: alias( alias ),
	  path( path )
	{
	}
	virtual ~TextureDataWork()
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

		bool has = createSingleton<Registry<GTexture> >()->hasObject( key );

		if( has )
		{
			return;
		}

		// Load the file.
		// in its fullest.
		Data<unsigned char> data;


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

		data.set( length );
		stream.read( (char*)data.access() , data.size() );

		if( stream.gcount() != length )
		{
			// ERROR!
			LOG_ERROR << "Read data length is different than what was intended." << std::endl;
			return;
		}

		int comp = 4; // req RGBA..
		int x,y;
		stbi_uc *rgbadata = stbi_load_from_memory( data.access() , data.size() , &x , &y, &comp , comp);

		GTexture *texture = new GTexture;

		texture->setDimensions( glm::ivec2( x , y ) );
		texture->setColorMode( RGBA );

// NONO! texture->initialize( rgbadata );
// NOT THE MAIN THREAD!


	}

	virtual void end()
	{
		// All is done.. Kill yourself.
		delete this;
	}
};

TextureHandler::TextureHandler()
{
}

TextureHandler::~TextureHandler()
{
}

bool TextureHandler::canHandle( const std::string& extension )
{
	if( extension == "png" ||
		extension == "jpg" ||
		extension == "psd" )
	{
		return true;
	}
	return false;
}

Work *TextureHandler::handle( std::string alias , std::string path , std::string type )
{
	Work *work = new TextureDataWork( alias , path );

	return work;
}

}
} /* namespace bolt */
