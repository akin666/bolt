/*
 * workdestroyer.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef WORKDESTROYER_HPP_
#define WORKDESTROYER_HPP_

namespace bolt
{

template <class cwork>
class WorkDestroyer : public cwork
{
public:
	WorkDestroyer() {}
	virtual ~WorkDestroyer() {}

	virtual void end()
	{
		cwork::end();
		delete this;
	}
};

} /* namespace bolt */
#endif /* WORKDESTROYER_HPP_ */
