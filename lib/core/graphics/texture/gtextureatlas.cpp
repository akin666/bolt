/*
 * gtextureatlas.cpp
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#include "gtextureatlas.hpp"
#include <log>
#include <stdexcept>

namespace bolt
{
	GTextureAtlas::GTextureAtlas()
	: initialized(false)
	{
	}

	GTextureAtlas::~GTextureAtlas()
	{
	}

	void GTextureAtlas::initialize( const glm::ivec2& dimensions , const int padding , const ColorMode mode ) throw (GraphicsException)
	{
		if( !initialized )
		{
			texture.setDimensions( dimensions );
			texture.setColorMode( mode );

			texture.initialize( );

			atlas.initialize( dimensions , padding );

			initialized = true;
		}
		else
		{
			throw std::runtime_error("Texture atlas already initialized!");
		}
	}

	void GTextureAtlas::resize( const glm::ivec2& val ) throw (GraphicsException)
	{
		//	// TODO! reverting ATLAS back to previous state
		//	// GTexture probably doesn't change if it fails
		//	// so, need to code logic to revert ATLAS back
		//	// to previous size.

		// new comment:
		// both should be throwing.. the most likely to give up, is the texture,
		// atlas should be more resiliant in resize situations..
		// if atlas fails, we would need to revert texture resize, but that is.. i have no idea how.
		// so TODO still.. the previous comment, im not sure about it.
		texture.resize( val );
		atlas.resize( val );
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
