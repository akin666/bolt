/*
 * dataunit.hpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#ifndef DATAUNIT_HPP_
#define DATAUNIT_HPP_

#include "resourceunit.hpp"
#include <string>
#include <common>
#include <work>

namespace bolt
{

class DataUnit: public bolt::ResourceUnit
{
protected:
	unsigned char *data;
	uint length;
	std::string path;

	class DataUnitWork : public Work
	{
	protected:
		DataUnit& parent;
	public:
		DataUnitWork( DataUnit& parent );
		virtual bool begin();
		virtual void run();
		virtual void end();
	};

	DataUnitWork unitWork;
public:
	DataUnit( std::string path );
	virtual ~DataUnit();

	virtual void startLoading();
	virtual void clear();
	virtual void reload();

	void setData( unsigned char *newData , uint newLength );

	std::string getPath();
	unsigned char *accessData();
	uint size();
};

} /* namespace bolt */
#endif /* DATAUNIT_HPP_ */
