/*
 * atlas.h
 *
 *  Created on: 25.5.2011
 *      Author: akin
 */

#ifndef ATLAS_H_
#define ATLAS_H_

#define DEFAULT_ATLAS_WIDTH 1024
#define DEFAULT_ATLAS_HEIGHT 1024
#define DEFAULT_ATLAS_PADDING 1

#include <glm/glm>

#include "atlasnode.h"
#include <vector>

	class Atlas
	{
	protected:
		int dimensionX;
		int dimensionY;
		int padding;
		std::vector<AtlasNode> nodes;
		bool init;
		int usage;

		void merge();
		int fit( std::vector<AtlasNode>::iterator iter , size_t width, size_t height );
	public:
		Atlas();
		Atlas( const Atlas& other );
		virtual ~Atlas();

		void reset();

		bool initialized() const;

		void initialize( const int width = DEFAULT_ATLAS_WIDTH , const int height = DEFAULT_ATLAS_HEIGHT , const int padding = DEFAULT_ATLAS_PADDING );

		unsigned int getPadding();

		/**
		 * Request
		 * request a certain width & height, if there is space free, X and Y gets
		 * filled with the information.
		 * The X and Y will contain the padding. So if padding is 1 the real reserved
		 * area is [X-padding,X+widht+padding][Y-padding,Y+height+padding].
		 *
		 * IF the request cannot be satisfied false is returned.
		 */
		bool request( const int req_width , const int req_height , int& x , int& y );

		/**
		 * proxyRequest
		 * request a certain width & height, if there is space free returns true,
		 * but does not reserve the space.
		 *
		 * IF the request cannot be satisfied false is returned.
		 */
		bool proxyRequest( const int req_width , const int req_height );

		/**
		 * Release
		 * request to release a certain area.
		 * Width, Height, X and Y should be the same that were handled with request() function,
		 * the function will take into account the padding.
		 */
		bool release( const int width , const int height , const int x , const int y );

		/**
		 * Resize
		 * resize will resize the atlas to a specified size, also keeping the previously
		 * acquired areas intact and alive.
		 */
		bool resize( const int new_width , const int new_height );

		void initialize( const glm::ivec2& dimensions , const int padding = DEFAULT_ATLAS_PADDING );
		bool request( const glm::ivec2& dimensions ,glm::ivec2& spot );
		bool release( const glm::ivec2& dimensions , const glm::ivec2& spot );
		bool resize( const glm::ivec2& dimensions );

		int getWidth();

		int getHeight();
	};

#endif /* ATLAS_H_ */
