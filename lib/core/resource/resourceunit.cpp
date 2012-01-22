/*
 * resourceunit.cpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#include "resourceunit.hpp"
#include <log>

namespace bolt
{

ResourceUnit::ResourceUnit()
: state( LOADING_NONE )
{
}

ResourceUnit::~ResourceUnit()
{
}

void ResourceUnit::setLoadingComplete( bool val )
{
	std::lock_guard<std::mutex> lock( mutex );
	if( val )
	{
		state |= LOADING_COMPLETE;
	}
	else
	{
		state &= ~LOADING_COMPLETE;
	}
}

void ResourceUnit::setLoadingStarted( bool val )
{
	std::lock_guard<std::mutex> lock( mutex );
	if( val )
	{
		state |= LOADING_STARTED;
	}
	else
	{
		state &= ~LOADING_STARTED;
	}
}

bool ResourceUnit::isLoadingComplete()
{
	std::lock_guard<std::mutex> lock( mutex );
	return (state & LOADING_COMPLETE) != 0;
}

bool ResourceUnit::isLoading()
{
	std::lock_guard<std::mutex> lock( mutex );
	return (state & LOADING_STARTED) != 0;
}

void ResourceUnit::startLoading()
{
}

void ResourceUnit::clear()
{
}

void ResourceUnit::reload()
{
}

} /* namespace bolt */
