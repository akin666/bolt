/*
 * resourceunit.hpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#ifndef RESOURCEUNIT_HPP_
#define RESOURCEUNIT_HPP_

#include <common>
#include <thread>

namespace bolt
{

class ResourceUnit
{
public:
	static const uint LOADING_NONE = 		0x0000;
	static const uint LOADING_STARTED = 	0x0001;
	static const uint LOADING_COMPLETE = 	0x0002;
protected:
	std::mutex mutex;
	unsigned short state;

	void setLoadingComplete( bool val );
	void setLoadingStarted( bool val );
public:
	ResourceUnit();
	virtual ~ResourceUnit();

	bool isLoadingComplete();
	bool isLoading();

	virtual void startLoading();
	virtual void clear();
	virtual void reload();
};

} /* namespace bolt */
#endif /* RESOURCEUNIT_HPP_ */
