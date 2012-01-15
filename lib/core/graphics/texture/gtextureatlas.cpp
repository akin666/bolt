/*
 * gtextureatlas.cpp
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#include "gtextureatlas.hpp"

namespace bolt
{
	GTextureAtlas::GTextureAtlas()
	: initialized(false)
	{
	}

	GTextureAtlas::~GTextureAtlas()
	{
	}

	bool GTextureAtlas::initialize( const glm::ivec2& dimensions , const int padding , const ColorMode mode )
	{
		if( !initialized )
		{
			texture.setDimensions( dimensions );
			texture.setColorMode( mode );

			if( !texture.initialize( ) )
			{
				return false;
			}

			atlas.initialize( dimensions , padding );

			initialized = true;
		}
		return initialized;
	}

	bool GTextureAtlas::resize( const glm::ivec2& val )
	{
		// TODO! reverting ATLAS back to previous state
		// GTexture probably doesn't change if it fails
		// so, need to code logic to revert ATLAS back
		// to previous size.
		if( atlas.resize( val ) && texture.resize( val ) )
		{
			return true;
		}
		return false;
	}

	bool GTextureAtlas::request( const glm::ivec2& dimensions , glm::ivec2& position )
	{
		return atlas.request( dimensions , position );
	}

	bool GTextureAtlas::release( const glm::ivec2& dimensions , const glm::ivec2& position )
	{
		return atlas.release( dimensions , position );
	}

	unsigned int GTextureAtlas::getPadding()
	{
		return atlas.getPadding();
	}

	glm::ivec2 GTextureAtlas::getDimension()
	{
		return texture.getDimension();
	}

	GTexture& GTextureAtlas::getTexture()
	{
		return texture;
	}
} /* namespace ice */
