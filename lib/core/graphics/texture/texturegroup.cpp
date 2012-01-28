/*
 * texturegroup.cpp
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#include "texturegroup.hpp"
#include <iterator>
#include <log>
#include <stdexcept>

namespace bolt
{
	TextureGroup::TextureGroup()
	: pad(TG_DEFAULT_PAD),
	  initialized(false)
	{
	}

	TextureGroup::~TextureGroup()
	{
		for( typename std::vector<GTextureAtlas*>::iterator iter = atlases.begin() ; iter != atlases.end() ; ++iter )
		{
			delete *iter;
		}
		atlases.clear();
	}

	bool TextureGroup::initialize( const int maxwidth , const int maxheight , const int padding , const ColorMode mode )
	{
		if( !initialized )
		{
			max.x = maxwidth;
			max.y = maxheight;
			pad = padding;

			channels = mode;

			initialized = true;
		}

		return initialized;
	}

	bool TextureGroup::initialize( const glm::ivec2& maxsize , const int padding , const ColorMode mode )
	{
		return initialize( maxsize.x , maxsize.y , padding , mode );
	}

	void TextureGroup::request( Texture& texture ) throw (std::exception)
	{
		if( texture.getDimension().x > max.x || texture.getDimension().y > max.y )
		{
			throw std::runtime_error("TextureGroup: texture dimensions, bigger than MAX dimensions.");
		}

		for( typename std::vector<GTextureAtlas*>::iterator iter = atlases.begin() ; iter != atlases.end() ; ++iter )
		{
			if( (*iter)->request( texture.getDimension() , texture.getPosition() ) )
			{
				texture.setTexture( &(*iter)->getTexture() );
			}
		}

		GTextureAtlas *tt = new GTextureAtlas;

		try
		{
			tt->initialize( max , pad , channels );
		}
		catch( std::exception& e )
		{
			delete tt;
			throw std::runtime_error("TextureGroup: could not initialize texture.");
		}

		if( !tt->request( texture.getDimension() , texture.getPosition() ) )
		{
			delete tt;
			throw std::runtime_error("TextureGroup: could not grant request, even from new atlas texture.");
		}

		atlases.push_back( tt );

		texture.setTexture( &tt->getTexture() );
	}
} /* namespace ice */
