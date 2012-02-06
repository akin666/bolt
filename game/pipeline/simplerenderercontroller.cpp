/*
 * simpletenderercomponent.cpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#include "simplerenderercontroller.hpp"
#include <common>
#include <singleton>
#include <component/common/positionproperty.hpp>
#include <component/common/fencecontroller.hpp>
#include <opengl>

#include <graphics/shader/shaderprogram.hpp>
#include <graphics/shader/uniform.hpp>
#include <graphics/shader/attribute.hpp>
#include <graphics/rendertarget.hpp>
#include <graphics/graphics.hpp>

#include <resource/registry.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "backgroundrenderer.hpp"

const std::string SimpleRendererController::KEY("simplerenderer");

/*
 * Vertex array
 */
float SRCnum = 3;
float SRCvertices[] = {
      -SRCnum,-SRCnum, SRCnum, // vertex v0
       SRCnum,-SRCnum, SRCnum, // vertex v1
       SRCnum,-SRCnum,-SRCnum, // vertex v2
      -SRCnum,-SRCnum,-SRCnum, // vertex v3

      -SRCnum, SRCnum, SRCnum, // vertex v4
       SRCnum, SRCnum, SRCnum, // vertex v5
       SRCnum, SRCnum,-SRCnum, // vertex v6
      -SRCnum, SRCnum,-SRCnum, // vertex v7

      -SRCnum,-SRCnum, SRCnum, // vertex v0 8
       SRCnum,-SRCnum, SRCnum, // vertex v1 9
       SRCnum, SRCnum, SRCnum, // vertex v2 10
      -SRCnum, SRCnum, SRCnum, // vertex v3 11

      -SRCnum,-SRCnum,-SRCnum, // vertex v0 12
       SRCnum,-SRCnum,-SRCnum, // vertex v1 13
       SRCnum, SRCnum,-SRCnum, // vertex v2 14
      -SRCnum, SRCnum,-SRCnum, // vertex v3 15

       SRCnum,-SRCnum,-SRCnum, // vertex v0 16
       SRCnum, SRCnum,-SRCnum, // vertex v1 17
       SRCnum, SRCnum, SRCnum, // vertex v2 18
       SRCnum,-SRCnum, SRCnum, // vertex v3 19

      -SRCnum,-SRCnum,-SRCnum, // vertex v0 20
      -SRCnum, SRCnum,-SRCnum, // vertex v1 21
      -SRCnum, SRCnum, SRCnum, // vertex v2 22
      -SRCnum,-SRCnum, SRCnum, // vertex v3 23
      };

/*
 * TextureCoordinate array (matching those vertexes defined above)
 */
float SRCtexCoords[]={
        0.0, 0.0, // mapping coordinates for vertex v0
        1.0, 0.0, // mapping coordinates for vertex v1
        1.0, 1.0, // mapping coordinates for vertex v2
        0.0, 1.0, // mapping coordinates for vertex v3

        0.0, 1.0, // mapping coordinates for vertex v4
        1.0, 1.0, // mapping coordinates for vertex v5
        1.0, 0.0, // mapping coordinates for vertex v6
        0.0, 0.0, // mapping coordinates for vertex v7

        0.0, 1.0, // mapping coordinates for vertex v8
        1.0, 1.0, // mapping coordinates for vertex v9
        1.0, 0.0, // mapping coordinates for vertex v10
        0.0, 0.0, // mapping coordinates for vertex v11

        0.0, 1.0, // mapping coordinates for vertex v12
        1.0, 1.0, // mapping coordinates for vertex v13
        1.0, 0.0, // mapping coordinates for vertex v14
        0.0, 0.0, // mapping coordinates for vertex v15

        0.0, 1.0, // mapping coordinates for vertex v16
        1.0, 1.0, // mapping coordinates for vertex v17
        1.0, 0.0, // mapping coordinates for vertex v18
        0.0, 0.0, // mapping coordinates for vertex v19

        0.0, 1.0, // mapping coordinates for vertex v20
        1.0, 1.0, // mapping coordinates for vertex v21
        1.0, 0.0, // mapping coordinates for vertex v22
        0.0, 0.0  // mapping coordinates for vertex v23
        };

/*
 * Indices array that forms the quads i will be using..
 */
unsigned int SRCindices[] = {
		// q1
		0,1,3,
		3,2,1,

		// q2
		4,5,7,
		7,6,5,

		// q3
		8,9,11,
		11,10,9,

		// q4
		12,13,15,
		15,14,13,

		// q5
		16,17,19,
		19,18,17,

		// q6
		20,21,23,
		23,22,21,
        };

SimpleRendererController::SimpleRendererController()
: bolt::Controller( KEY , false ),
  initialized( false )
{
}

SimpleRendererController::~SimpleRendererController()
{
}

void SimpleRendererController::initialize() throw (std::exception)
{
	// already initialized?
	if( initialized )
	{
		return;
	}

	vertexBuffer.set( 72*sizeof(float) , SRCvertices , bolt::Graphics::arrayBuffer , bolt::Graphics::gpu , bolt::Graphics::once );
	textureBuffer.set( 48*sizeof(float) , SRCtexCoords , bolt::Graphics::arrayBuffer , bolt::Graphics::gpu , bolt::Graphics::once );
	indexBuffer.set( 36*sizeof(unsigned int) , SRCindices , bolt::Graphics::elementArrayBuffer , bolt::Graphics::gpu , bolt::Graphics::once );

	dependecies.insert( bolt::FenceController::LOGIC );
	dependecies.insert( bolt::BackgroundRenderer::KEY );

	bolt::createSingleton<bolt::PositionProperty>()->initialize();


	glm::vec2 windowResolution;

	bolt::VideoMode& videomode = bolt::Singleton<bolt::RenderTarget>::get()->getVideoMode();

	windowResolution.x = videomode.getWidth();
	windowResolution.y = videomode.getHeight();

	const float aspectRatio = windowResolution.y/windowResolution.x;

	lense = glm::frustum(
			-1.0f,
			 1.0f,
			-aspectRatio,
			 aspectRatio,
			0.5f,
			100.0f
			);

	model = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10 ) );
}

void SimpleRendererController::getDependencies(bolt::StringSet & dep)
{
	dep = dependecies;
}

void SimpleRendererController::attach(bolt::Entity& entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->attach( entity );

	if( entities.find( entity.getId() ) != entities.end() )
	{
		return;
	}

	entities.insert( entity.getId() );
}

void SimpleRendererController::detach(bolt::Entity& entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->detach( entity );

	entities.erase( entity.getId() );
}

void SimpleRendererController::start(bolt::ControllerNode& node)
{
	// do the rendering here.
	if( entities.size() > 0 && bolt::resource::hasObject<bolt::ShaderProgram>( "GenericShader" ) )
	{
		GL_TEST_ERROR("start");

	    glEnableClientState( GL_VERTEX_ARRAY );
	    glEnableClientState( GL_INDEX_ARRAY );

	    // Bind program & set node there..
	    bolt::ShaderProgram *program = bolt::resource::getObject<bolt::ShaderProgram>( "GenericShader" );

	    program->bind();

	    bolt::Uniform *umodel = program->getUniform( "model" );
	    bolt::Uniform *ulense = program->getUniform( "lense" );

	    umodel->set( model );
	    ulense->set( lense );

		vertexBuffer.bind( bolt::Graphics::arrayBuffer );
		glVertexPointer( 3, GL_FLOAT , 3*sizeof(float) , 0 );

	    indexBuffer.bind( bolt::Graphics::elementArrayBuffer );

	    bolt::PositionProperty *pproperty = bolt::getSingleton<bolt::PositionProperty>();

	    for( EntitySet::iterator iter = entities.begin() ; iter != entities.end() ; ++iter )
	    {
		    umodel->set( glm::translate( glm::mat4(1.0f), pproperty->get( *iter ).position ) );
			glDrawArrays( GL_TRIANGLES , 0 , 36 );

			GL_TEST_ERROR("mid");
	    }

		GL_TEST_ERROR("end");
	}
}



