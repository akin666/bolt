/*
 * simpletenderercomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "graphicsdebugcontroller.hpp"
#include <common>
#include <singleton>
#include <component/property/positionproperty.hpp>
#include <component/property/cameraproperty.hpp>
#include <opengl>

#include <graphics/shader/shaderprogram.hpp>
#include <graphics/shader/uniform.hpp>
#include <graphics/shader/attribute.hpp>
#include <graphics/graphics.hpp>

#include <resource/registry.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace bolt
{
const std::string GraphicsDebugController::KEY("simplerenderer");

/*
 * Vertex array
 */
static const float SRCnum = 1;

float cube_v[] = {
    // front
    -SRCnum, -SRCnum,  SRCnum,
     SRCnum, -SRCnum,  SRCnum,
     SRCnum,  SRCnum,  SRCnum,
    -SRCnum,  SRCnum,  SRCnum,
    // back
    -SRCnum, -SRCnum, -SRCnum,
     SRCnum, -SRCnum, -SRCnum,
     SRCnum,  SRCnum, -SRCnum,
    -SRCnum,  SRCnum, -SRCnum,
  };

unsigned short cube_i[] = {
  // front
  0, 1, 2,
  2, 3, 0,
  // top
  1, 5, 6,
  6, 2, 1,
  // back
  7, 6, 5,
  5, 4, 7,
  // bottom
  4, 0, 3,
  3, 7, 4,
  // left
  4, 5, 1,
  1, 0, 4,
  // right
  3, 2, 6,
  6, 7, 3,
};

GraphicsDebugController::GraphicsDebugController( std::string name , bolt::StringSet& dependencies )
: bolt::Controller( name , false ),
  initialized( false ),
  dependencies(dependencies)
{
}

GraphicsDebugController::~GraphicsDebugController()
{
}

void GraphicsDebugController::initialize() throw (std::exception)
{
	// already initialized?
	if( initialized )
	{
		return;
	}

	vertexBuffer.set( 24*sizeof(float) , cube_v , bolt::Graphics::arrayBuffer , bolt::Graphics::gpu , bolt::Graphics::once );
	indexBuffer.set( 36*sizeof(unsigned short) , cube_i , bolt::Graphics::elementArrayBuffer , bolt::Graphics::gpu , bolt::Graphics::once );

	bolt::createSingleton<bolt::PositionProperty>()->initialize();
}

void GraphicsDebugController::getDependencies(bolt::StringSet & dep)
{
	dep = dependencies;
}

void GraphicsDebugController::attach(bolt::Entity& entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->attach( entity );

	if( entities.find( entity.getId() ) != entities.end() )
	{
		return;
	}

	entities.insert( entity.getId() );
}

void GraphicsDebugController::detach(bolt::Entity& entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->detach( entity );

	entities.erase( entity.getId() );
}

void GraphicsDebugController::start(bolt::ControllerNode& node)
{
	// do the rendering here.
	if( entities.size() > 0 && bolt::resource::hasObject<bolt::ShaderProgram>( "GenericShader" ) )
	{
		GL_TEST_ERROR("start");

		glEnable(GL_DEPTH_TEST);
		glClear( GL_DEPTH_BUFFER_BIT );
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

	    glEnableClientState( GL_VERTEX_ARRAY );
	    glEnableClientState( GL_INDEX_ARRAY );

	    // Bind program & set node there..
	    bolt::ShaderProgram *program = bolt::resource::getObject<bolt::ShaderProgram>( "GenericShader" );

	    // get current camera data.
		bolt::Entity currentCamera = bolt::createSingleton<bolt::CameraProperty>()->getCurrent();
		glm::mat4 cameraLense = bolt::createSingleton<bolt::CameraProperty>()->toMatrix( currentCamera.getId() );
		glm::mat4 cameraPosition = bolt::getSingleton<bolt::PositionProperty>()->toMatrix( currentCamera.getId() );

    	glm::mat4 tMatrix = cameraLense * cameraPosition;
    	// Get Lense & Camera position.. put them together.. etc. TODO!


	    program->bind();

	    bolt::Uniform *umodel = program->getUniform( "model" );
	    bolt::Uniform *ulense = program->getUniform( "lense" );

	    ulense->set( tMatrix );

		vertexBuffer.bind( bolt::Graphics::arrayBuffer );
		glVertexPointer( 3, GL_FLOAT , 3*sizeof(float) , 0 );

	    indexBuffer.bind( bolt::Graphics::elementArrayBuffer );

	    bolt::PositionProperty *pproperty = bolt::getSingleton<bolt::PositionProperty>();

	    int size;
	    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	    for( EntitySet::iterator iter = entities.begin() ; iter != entities.end() ; ++iter )
	    {
		    umodel->set( pproperty->toMatrix( *iter ) );
			//glDrawArrays( GL_TRIANGLES , 0 , 36 );
			glDrawElements(GL_TRIANGLES, 36 , GL_UNSIGNED_SHORT, 0);

			GL_TEST_ERROR("mid");
	    }

		glDisable(GL_DEPTH_TEST);
		GL_TEST_ERROR("end");
	}
}
}
