/*
 * dataunit.cpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#include "dataunit.hpp"
#include <iostream>
#include <fstream>
#include <singleton>
#include <threadpool>
#include <log>

namespace bolt
{

DataUnit::DataUnitWork::DataUnitWork( DataUnit& parent )
: parent( parent )
{
}

bool DataUnit::DataUnitWork::begin()
{
	return true;
}

void DataUnit::DataUnitWork::run()
{
	// Load the file.
	// in its fullest.
	std::fstream stream;

	stream.open( parent.getPath().c_str() , std::fstream::in | std::fstream::binary );

	if( !stream.is_open() )
	{
		stream.close();
		LOG_ERROR << "Stream does not exist." << std::endl;
		return;
	}

	if( !stream.good() )
	{
		stream.close();
		LOG_ERROR << "Stream is bad." << std::endl;
		return;
	}

	stream.seekg (0, std::ios::end);
	int length = stream.tellg();
	stream.seekg (0, std::ios::beg);

	unsigned char *data = new unsigned char[ length ];

	stream.read( (char*)data , length );

	if( stream.gcount() != length )
	{
		// ERROR!
		LOG_ERROR << "Read data length is different than what was intended." << std::endl;
	}

	parent.setData( data , length );
}

void DataUnit::DataUnitWork::end()
{
}

DataUnit::DataUnit( std::string path )
: data( NULL ),
  length( 0 ),
  path( path ),
  unitWork( *this )
{
}

DataUnit::~DataUnit()
{
	clear();
}

void DataUnit::startLoading()
{
	LOG_OUT << "Start loading" << std::endl;
	setLoadingComplete( false );
	setLoadingStarted( true );
	bolt::Singleton<bolt::ThreadPool>::get()->schedule( &unitWork );
}

void DataUnit::clear()
{
	delete[] data;
	data = NULL;
	length = 0;
}

void DataUnit::reload()
{
}

void DataUnit::setData( unsigned char *newData , uint newLength )
{
	LOG_OUT << "Set data" << std::endl;
	clear();

	data = newData;
	length = newLength;

	setLoadingComplete( true );
	setLoadingStarted( true );
}

std::string DataUnit::getPath()
{
	return path;
}

unsigned char *DataUnit::accessData()
{
	return data;
}

uint DataUnit::size()
{
	return length;
}

} /* namespace bolt */
