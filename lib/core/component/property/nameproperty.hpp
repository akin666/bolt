/*
 * nameproperty.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef NAMEPROPERTY_HPP_
#define NAMEPROPERTY_HPP_

#include <component/property.hpp>
#include <map>
#include <string>

namespace bolt
{
class NameProperty: public bolt::Property
{
public:
	const static std::string KEY;
protected:
	typedef std::map< uint , std::string > NameMap;
	NameMap data;
public:
	NameProperty();
	virtual ~NameProperty();

	virtual void initialize() throw (std::exception);

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	std::string& get( bolt::Entity& entity );
};
}

#endif /* NAMEPROPERTY_HPP_ */
