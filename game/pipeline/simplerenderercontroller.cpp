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
#include <graphics/rendertarget.hpp>
#include <graphics/graphics.hpp>

#include <resource/registry.hpp>

const std::string SimpleRendererController::KEY("simplerenderer");

/*
 * Vertex array
 */
float SRCvertices[] = {
      -1,-1, 1, // vertex v0
       1,-1, 1, // vertex v1
       1,-1,-1, // vertex v2
      -1,-1,-1, // vertex v3

      -1, 1, 1, // vertex v4
       1, 1, 1, // vertex v5
       1, 1,-1, // vertex v6
      -1, 1,-1, // vertex v7

      -1,-1, 1, // vertex v0 8
       1,-1, 1, // vertex v1 9
       1, 1, 1, // vertex v2 10
      -1, 1, 1, // vertex v3 11

      -1,-1,-1, // vertex v0 12
       1,-1,-1, // vertex v1 13
       1, 1,-1, // vertex v2 14
      -1, 1,-1, // vertex v3 15

       1,-1,-1, // vertex v0 16
       1, 1,-1, // vertex v1 17
       1, 1, 1, // vertex v2 18
       1,-1, 1, // vertex v3 19

      -1,-1,-1, // vertex v0 20
      -1, 1,-1, // vertex v1 21
      -1, 1, 1, // vertex v2 22
      -1,-1, 1, // vertex v3 23
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

	bolt::createSingleton<bolt::PositionProperty>()->initialize();
}

void SimpleRendererController::getDependencies(bolt::StringSet & dep)
{
	dep = dependecies;
}

void SimpleRendererController::attach(bolt::Entity & entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->attach( entity );
}

void SimpleRendererController::detach(bolt::Entity & entity)
{
	bolt::getSingleton<bolt::PositionProperty>()->detach( entity );
}

void SimpleRendererController::start(bolt::ControllerNode& node)
{
	// do the rendering here.

	if( bolt::resource::hasObject<bolt::ShaderProgram>( "GenericShader" ) )
	{
	    glEnableClientState( GL_VERTEX_ARRAY );
	    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	    glEnableClientState( GL_INDEX_ARRAY );

	    // Bind program & set node there..
	    bolt::ShaderProgram *program = bolt::resource::getObject<bolt::ShaderProgram>( "GenericShader" );

	    program->bind();

	    /*
	    Uniform *gg = program->getUniform("resolution");
		GL_TEST_ERROR("start");


		float currentTime = myTime.getCurrentTime() * 0.001f;
		glm::vec2 windowResolution;

		VideoMode& videomode = Singleton<RenderTarget>::get()->getVideoMode();

		windowResolution.x = videomode.getWidth();
		windowResolution.y = videomode.getHeight();

		time->set( currentTime );
		resolution->set( windowResolution );

		glViewport( 0 , 0 , windowResolution.x , windowResolution.y );

	    vertexBuffer.bind( Graphics::arrayBuffer );
	    indexBuffer.bind( Graphics::elementArrayBuffer );

	    // point to vertex data..
		glVertexPointer( 3, GL_FLOAT , 3*sizeof(float) , 0 );

		glDrawElements(GL_TRIANGLE_STRIP, 4 , GL_UNSIGNED_INT, 0 );
		GL_TEST_ERROR("end");
		*/

	    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	}
}



