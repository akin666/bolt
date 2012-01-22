/*
 * resourceunit.cpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#include "resourceunit.hpp"

namespace bolt
{

ResourceUnit::ResourceUnit()
: state( LOADING_NONE )
{
}

ResourceUnit::~ResourceUnit()
{
}

void ResourceUnit::setLoadingComplete( bool state )
{
	if( state )
	{
		state |= LOADING_COMPLETE;
	}
	else
	{
		state &= ~LOADING_COMPLETE;
	}
}

void ResourceUnit::setLoadingStarted( bool state )
{
	if( state )
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
	return (state & LOADING_COMPLETE) != 0;
}

bool ResourceUnit::isLoading()
{
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
