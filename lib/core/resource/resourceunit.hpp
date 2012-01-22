/*
 * resourceunit.hpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#ifndef RESOURCEUNIT_HPP_
#define RESOURCEUNIT_HPP_

#include <thread>

namespace bolt
{

class ResourceUnit
{
protected:
public:
	ResourceUnit();
	virtual ~ResourceUnit();

	void setLoadingComplete( bool state );
	bool hasLoaded();
};

} /* namespace bolt */
#endif /* RESOURCEUNIT_HPP_ */
