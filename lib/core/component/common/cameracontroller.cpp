/*
 * cameracontroller.cpp
 *
 *  Created on: 10.2.2012
 *      Author: akin
 */

#include "cameracontroller.hpp"

namespace bolt
{

const std::string CameraController::KEY("camera");

CameraController::CameraController()
: Controller( KEY , true )
{
}

CameraController::~CameraController()
{
}

void CameraController::initialize() throw (std::exception)
{
}

void CameraController::getDependencies(StringSet & dep)
{
}

void CameraController::attach(Entity & entity)
{
}

void CameraController::detach(Entity & entity)
{
}

void CameraController::clear()
{
}

void CameraController::start(ControllerNode & node) throw (std::exception)
{
}

} /* namespace bolt */
