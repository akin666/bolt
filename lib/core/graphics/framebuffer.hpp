/*
 * framebuffer.h
 *
 *  Created on: 3.4.2010
 *      Author: akin
 */

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include "texture/gtexture.hpp"

namespace bolt
{
	class Framebuffer
	{
	protected:
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_id;
		unsigned int m_depth;
	public:
		Framebuffer();
		virtual ~Framebuffer();

		void attachTexture( GTexture& texture );
		void attachTexture( unsigned int width , unsigned int height , unsigned int texture_id );
		void attachDepth();

		void removeDepth();
		unsigned int getDepthId();

		void bind();

		int getWidth();
		int getHeight();

		bool invariant();

		static void bindDefault();
	};
}

#endif /* FRAMEBUFFER_H_ */
