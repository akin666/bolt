/*
 * graphicslandcontroller.cpp
 *
 *  Created on: 17.2.2012
 *      Author: akin
 */

#include "graphicslandcontroller.hpp"
#include <common>
#include <singleton>
#include <component/property/positionproperty.hpp>
#include <opengl>
#include <graphics/shader/shaderprogram.hpp>
#include <graphics/shader/uniform.hpp>
#include <graphics/rendertarget.hpp>


#include <component/property/cameraproperty.hpp>
#include <graphics/shader/attribute.hpp>
#include <graphics/graphics.hpp>
#include <resource/registry.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace bolt
{
const std::string GraphicsLandController::KEY("graphicslandcontroller");

static const float SRCnum = 100;

float land_v[] = {
    -SRCnum,  0, -SRCnum,
     SRCnum,  0, -SRCnum,
     SRCnum,  0,  SRCnum,
    -SRCnum,  0,  SRCnum,
  };

unsigned short land_i[] = {
  // bottom
  0,1,2,
  0,2,3
};

GraphicsLandController::GraphicsLandController(std::string name, bolt::StringSet & dependencies)
: bolt::Controller( name , false ),
  dependencies( dependencies )
{
}

GraphicsLandController::~GraphicsLandController()
{
}

void GraphicsLandController::initialize()
{
	// already initialized?
	if( initialized )
	{
		return;
	}

	vertexBuffer.set( 12*sizeof(float) , land_v , bolt::Graphics::arrayBuffer , bolt::Graphics::gpu , bolt::Graphics::once );
	indexBuffer.set( 6*sizeof(unsigned short) , land_i , bolt::Graphics::elementArrayBuffer , bolt::Graphics::gpu , bolt::Graphics::once );

	bolt::createSingleton<bolt::PositionProperty>()->initialize();
}

void GraphicsLandController::attach(bolt::Entity& entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->attach( entity );

	if( entities.find( entity.getId() ) != entities.end() )
	{
		return;
	}

	entities.insert( entity.getId() );
}

void GraphicsLandController::detach(bolt::Entity& entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->detach( entity );

	entities.erase( entity.getId() );
}

void GraphicsLandController::getDependencies(bolt::StringSet & dep)
{
	dep = dependencies;
}

void GraphicsLandController::start(bolt::ControllerNode & node)
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
		glm::mat4 cameraLense = bolt::createSingleton<bolt::CameraProperty>()->lenseMatrix( currentCamera.getId() );
		glm::mat4 cameraPosition = bolt::createSingleton<bolt::CameraProperty>()->positionMatrix( currentCamera.getId() );

    	glm::mat4 tMatrix = cameraLense * cameraPosition;

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
			glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_SHORT, 0);

			GL_TEST_ERROR("mid");
	    }

		glDisable(GL_DEPTH_TEST);
		GL_TEST_ERROR("end");
	}
}

} /* namespace bolt */
