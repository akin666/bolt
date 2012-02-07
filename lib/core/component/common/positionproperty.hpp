/*
 * positionproperty.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef POSITIONPROPERTY_HPP_
#define POSITIONPROPERTY_HPP_

#include <component/property.hpp>
#include <map>
#include <glm/ext.hpp>

namespace bolt
{
class PositionProperty: public bolt::Property
{
public:
	const static std::string KEY;

	class Data
	{
	public:
		glm::vec3 position;
		glm::gtc::quaternion::quat rotation;
	};
protected:
	std::map< uint , Data > data;
public:
	PositionProperty();
	virtual ~PositionProperty();

	virtual void initialize() throw (std::exception);

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	Data& get( bolt::uint entity );
};
}

#endif /* POSITIONPROPERTY_HPP_ */


