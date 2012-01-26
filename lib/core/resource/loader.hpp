/*
 * loader.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef LOADER_HPP_
#define LOADER_HPP_

#include <string>

namespace bolt
{
namespace resource
{

class Loader
{
public:
	Loader();
	virtual ~Loader();

	virtual bool load( std::string alias , std::string path );
	virtual bool load( std::string alias );
};

} // namespace resource
} // namespace bolt
#endif /* LOADER_HPP_ */
