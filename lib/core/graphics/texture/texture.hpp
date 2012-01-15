/*
 * Texture.h
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <glm/glm>
#include "gtexture.hpp"

namespace bolt
{
	class Texture
	{
	protected:
		glm::ivec2 pixelDimension;
		glm::ivec2 pixelPosition;

		GTexture *parent;
	public:
		Texture();
		Texture( const Texture& other );
		virtual ~Texture();

		glm::ivec2& getDimension();
		glm::ivec2& getPosition();

		glm::vec2 getMax();
		glm::vec2 getMin();

		int getWidth() const;
		int getHeight() const;

		GTexture *getG();

		void bind();
		void release();
		void setTexture( GTexture *texture );

		unsigned int getId() const;
	};
} /* namespace ice */
#endif /* TEXTURE_H_ */
