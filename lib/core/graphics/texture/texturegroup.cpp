/*
 * texturegroup.cpp
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#include "texturegroup.hpp"
#include <iterator>

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

	bool TextureGroup::request( Texture& texture )
	{
		if( texture.getDimension().x > max.x || texture.getDimension().y > max.y )
		{
			return false;
		}

		for( typename std::vector<GTextureAtlas*>::iterator iter = atlases.begin() ; iter != atlases.end() ; ++iter )
		{
			if( (*iter)->request( texture.getDimension() , texture.getPosition() ) )
			{
				texture.setTexture( &(*iter)->getTexture() );

				return true;
			}
		}

		GTextureAtlas *tt = new GTextureAtlas;
		if( !tt->initialize( max , pad , channels ) )
		{
			delete tt;
			return false;
		}

		if( !tt->request( texture.getDimension() , texture.getPosition() ) )
		{
			delete tt;
			return false;
		}

		atlases.push_back( tt );

		texture.setTexture( &tt->getTexture() );

		return true;
	}
} /* namespace ice */
