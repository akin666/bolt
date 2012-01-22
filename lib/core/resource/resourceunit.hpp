/*
 * resourceunit.hpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#ifndef RESOURCEUNIT_HPP_
#define RESOURCEUNIT_HPP_

#include <thread>
#include <common>

namespace bolt
{

class ResourceUnit
{
public:
	static uint LOADING_NONE = 		0x0;
	static uint LOADING_STARTED = 	0x000001;
	static uint LOADING_COMPLETE = 	0x000002;
protected:
	std::mutex mutex;
	unsigned short state;

	void setLoadingComplete( bool state );
	void setLoadingStarted( bool state );
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
