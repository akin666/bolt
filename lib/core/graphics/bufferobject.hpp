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
		void initialize();
		void reserve( const unsigned int bytesize , Graphics::Residence residence = Graphics::gpu , Graphics::Updates updates = Graphics::multipleTimes );
		void set( const unsigned int bytesize , const void *data , Graphics::Residence residence = Graphics::gpu , Graphics::Updates updates = Graphics::multipleTimes );

		unsigned int size() const;
		unsigned int getID() const;

		void bind( const Graphics::BindStyle style = Graphics::read ) const;
		void release( const Graphics::BindStyle style = Graphics::read ) const;

		unsigned char *bindMemoryMap( const Graphics::BindStyle style = Graphics::read ) const;
		void releaseMemoryMap( const Graphics::BindStyle style = Graphics::read ) const;
	};
}

#endif /* BUFFEROBJECT_H_ */
