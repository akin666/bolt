/*
 * defaultloader.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef DEFAULTLOADER_HPP_
#define DEFAULTLOADER_HPP_

#include <resource/loader.hpp>
#include <common>
#include <string>
#include <tpool/compositework.hpp>

namespace bolt
{
namespace resource
{

class DefaultLoader : public Loader
{
protected:
	CompositeWork composite;

	bool loadPath( const std::string& alias , const std::string& path );
public:
	DefaultLoader();
	virtual ~DefaultLoader();

	virtual bool load( std::string alias , std::string path );
	virtual bool load( std::string alias );
};

}
} /* namespace bolt */
#endif /* DEFAULTLOADER_HPP_ */
