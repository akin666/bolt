/*
 * cameraproperty.hpp
 *
 *  Created on: 13.2.2012
 *      Author: akin
 */

#ifndef CAMERAPROPERTY_HPP_
#define CAMERAPROPERTY_HPP_

#include <component/property.hpp>
#include <map>
#include <generic/camera.hpp>

namespace bolt
{
class CameraProperty : public bolt::Property
{
public:
	const static std::string KEY;
protected:
	typedef std::map< bolt::uint , Camera > CameraMap;

	CameraMap data;
	Entity current;
public:
	CameraProperty();
	virtual ~CameraProperty();

	virtual void initialize() throw (std::exception);

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	Camera& get( bolt::uint entity );

	glm::mat4 toMatrix( bolt::uint entity );

	Entity getCurrent();
	void setCurrent( Entity& entity );
};

} /* namespace bolt */
#endif /* CAMERAPROPERTY_HPP_ */
