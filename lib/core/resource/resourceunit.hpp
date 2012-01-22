/*
 * resourceunit.hpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#ifndef RESOURCEUNIT_HPP_
#define RESOURCEUNIT_HPP_

#include <common>

namespace bolt
{

class ResourceUnit
{
public:
	static const uint LOADING_NONE = 		0x0;
	static const uint LOADING_STARTED = 	0x000001;
	static const uint LOADING_COMPLETE = 	0x000002;
protected:
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
