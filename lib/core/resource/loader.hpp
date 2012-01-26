/*
 * loader.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef LOADER_HPP_
#define LOADER_HPP_

#include <common>
#include <string>
#include <tpool/workcomposite.hpp>

namespace bolt
{
namespace resource
{

class Loader
{
protected:
	WorkComposite composite;

	bool loadPath( const std::string& alias , const std::string& path );
public:
	Loader();
	virtual ~Loader();

	bool load( std::string alias , std::string path );

	bool load( std::string alias );
};

} // namespace resource
} // namespace bolt
#endif /* LOADER_HPP_ */
