/*
 * Graphics.cpp
 *
 *  Created on: 9.7.2011
 *      Author: akin
 */

#include "graphics.hpp"
#include <opengl>

namespace bolt
{
	int Graphics::resolveResidenceUpdates( const Residence residence , const Updates updates )
	{
		 //stream = disposable (single use)
		 //static = STATIIC
		 //dynamic = update whenever you want
		 //
		 //DRAW = Jou  GPU read cpu write stuff
		 //READ = Jou , GPU Write, CPU read
		 //COPY = Jou GPU CPU access, probably a copy in both buffs
		 //  GL_STREAM_DRAW,
		 //  GL_STREAM_READ,
		 //  GL_STREAM_COPY,
		 //  GL_STATIC_DRAW,
		 //  GL_STATIC_READ,
		 //  GL_STATIC_COPY,
		 //  GL_DYNAMIC_DRAW,
		 //  GL_DYNAMIC_READ,GPU
		 //  GL_DYNAMIC_COPY

		switch( residence ) {
			case Graphics::gpu : {
				switch( updates ) {
					case Graphics::everyFrame : {
						return GL_STREAM_DRAW;
						break;
					}
					case Graphics::once : {
						return GL_STATIC_DRAW;
						break;
					}
					case Graphics::multipleTimes : {
						return GL_DYNAMIC_DRAW;
						break;
					}
				}
				break;
			}
			case Graphics::cpu : {
				switch( updates ) {
					case Graphics::everyFrame : {
						return GL_STREAM_READ;
						break;
					}
					case Graphics::once : {
						return GL_STATIC_READ;
						break;
					}
					case Graphics::multipleTimes : {
						return GL_DYNAMIC_READ;
						break;
					}
				}
				break;
			}
			case Graphics::cpugpu : {
				switch( updates ) {
					case Graphics::everyFrame : {
						return GL_STREAM_COPY;
						break;
					}
					case Graphics::once : {
						return GL_STATIC_COPY;
						break;
					}
					case Graphics::multipleTimes : {
						return GL_DYNAMIC_COPY;
						break;
					}
				}
				break;
			}
		}
		return GL_DYNAMIC_COPY;
	}
}
