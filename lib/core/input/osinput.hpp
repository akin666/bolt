/*
 * OSInput.hpp
 *
 *  Created on: 15.2.2012
 *      Author: akin
 */

#ifndef OSINPUT_HPP_
#define OSINPUT_HPP_

namespace bolt
{

class OSInput
{
public:
	OSInput();
	virtual ~OSInput();

	virtual bool handleClose();
	virtual void handleMemoryWarning();
	virtual bool handleMinimize();
	virtual bool handleMaximize();
	virtual void handleRefresh();
	virtual bool handleResize( int width , int height );
};

} /* namespace bolt */
#endif /* OSINPUT_HPP_ */



