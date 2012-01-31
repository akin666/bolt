/*
 * framebuffer.h
 *
 *  Created on: 3.4.2010
 *      Author: akin
 */

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include "texture/gtexture.hpp"
#include "graphicsexception.hpp"

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

		void attachTexture( GTexture& texture ) throw (GraphicsException);
		void attachTexture( unsigned int width , unsigned int height , unsigned int texture_id ) throw (GraphicsException);
		void attachDepth() throw (GraphicsException);

		void removeDepth() throw (GraphicsException);
		unsigned int getDepthId();

		void bind() throw (GraphicsException);

		int getWidth();
		int getHeight();

		bool invariant() throw (GraphicsException);

		static void bindDefault() throw (GraphicsException);
	};
}

#endif /* FRAMEBUFFER_H_ */
