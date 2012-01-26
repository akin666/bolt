/*
 * bytedatawork.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef BYTEDATAWORK_HPP_
#define BYTEDATAWORK_HPP_

#include <string>
#include <work>

namespace bolt
{
namespace resource
{

class ByteDataWork : public Work
{
protected:
	std::string alias;
	std::string path;
public:
	ByteDataWork( const std::string& alias , const std::string path );
	virtual ~ByteDataWork();

	virtual bool begin();
	virtual void run();
	virtual void end();
};

}
} /* namespace bolt */
#endif /* BYTEDATAWORK_HPP_ */
