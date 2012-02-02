/*
 *
 *  Created on: 5.7.2011
 *      Author: akin
 *
 *
 *  NOT MULTITHREAD FRIENDLY!
 *  The class is meant to be used:
 *
 *  bind();
 *  dostuff();
 *  with();
 *  it();
 *  release();
 *
 *  NOT!:
 *  memcpy( first.bindMemoryMap() , second.bindMemoryMap() , 666 );
 *
 *  ONLY ONE CAN BE BOUND AT A TIME!
 */

#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_

#include "graphics.hpp"
#include "graphicsexception.hpp"

namespace bolt
{
	class BufferObject
	{
	protected:
		unsigned int bsize;
		unsigned int id;
	public:
		BufferObject();
		virtual ~BufferObject();

		bool hasInitialized();
		void initialize() throw (GraphicsException);
		void reserve( unsigned int bytesize , Graphics::BindStyle style = Graphics::write , Graphics::Residence residence = Graphics::gpu , Graphics::Updates updates = Graphics::multipleTimes ) throw (GraphicsException);
		void set( unsigned int bytesize , const void *data , Graphics::BindStyle style = Graphics::write , Graphics::Residence residence = Graphics::gpu , Graphics::Updates updates = Graphics::multipleTimes ) throw (GraphicsException);

		unsigned int size() const;
		unsigned int getID() const;

		void bind( Graphics::BindStyle style = Graphics::read ) const throw (GraphicsException);
		void release( Graphics::BindStyle style = Graphics::read ) const throw (GraphicsException);

		unsigned char *bindMemoryMap( Graphics::BindStyle style = Graphics::read ) const throw (GraphicsException);
		void releaseMemoryMap( Graphics::BindStyle style = Graphics::read ) const throw (GraphicsException);
	};
}

#endif /* BUFFEROBJECT_H_ */
