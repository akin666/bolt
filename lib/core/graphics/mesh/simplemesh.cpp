/*
 * simplemesh.cpp
 *
 *  Created on: 9.7.2011
 *      Author: akin
 */

#include "simplemesh.hpp"
#include <opengl>
#include <iostream>

namespace bolt
{
	#define SM_WHITE 1.0f,1.0f,1.0f,1.0f
	#define SM_BLACK 0.0f,0.0f,0.0f,1.0f
	#define SM_RED 1.0f,0.0f,0.0f,1.0f
	#define SM_GREEN 0.0f,1.0f,0.0f,1.0f
	#define SM_BLUE 0.0f,0.0f,1.0f,1.0f
	#define SM_SEA 0.2f,0.4f,0.6f,1.0f

	SimpleMesh::SimpleMesh()
	: shader(NULL),
	  texture(NULL)
	{
		debug = false;
	}

	void SimpleMesh::setShader( ShaderProgram *prog )
	{
		shader = prog;

		if( shader != NULL )
		{
			modelo = shader->getUniform( "model" );
			tex = shader->getUniform( "tex" );

			vertex = shader->getAttribute( "vertex" );
			coordinates = shader->getAttribute( "coordinates" );

			if( modelo == NULL ||
				tex == NULL ||
				vertex == NULL ||
				coordinates == NULL )
			{
				shader = NULL;
				std::cout << "One or more shader attributes missing for simplemesh" << std::endl;
			}
		}
	}

	SimpleMesh::~SimpleMesh()
	{
	}

	void SimpleMesh::setPrimitiveType( Graphics::Primitives primitiveType )
	{
		switch( primitiveType )
		{
			case Graphics::triangles :
				glPrimitive = GL_TRIANGLES;
				break;
			case Graphics::triangleStrips :
				glPrimitive = GL_TRIANGLE_STRIP;
				break;
			case Graphics::triangleFan :
				glPrimitive = GL_TRIANGLE_FAN;
				break;
			case Graphics::points :
				glPrimitive = GL_POINTS;
				break;
			case Graphics::lines :
				glPrimitive = GL_LINES;
				break;
			case Graphics::quads :
				glPrimitive = GL_QUADS;
				break;
			default :
				glPrimitive = GL_TRIANGLES;
				break;
		}
	}

	void SimpleMesh::draw( glm::mat4x4& model )
	{
		if( shader != NULL && texture != NULL )
		{
			shader->bind();

			modelo->set( model );

			vertex->enable();
			coordinates->enable();

			tex->bindTexture( 0 , texture->getG()->getTextureId() );

			vertexBuffer.bind( Graphics::arrayBuffer );
			vertex->setPointer( 3 , GL_FLOAT , 0 );

			textureBuffer.bind( Graphics::arrayBuffer );
			coordinates->setPointer( 2 , GL_FLOAT , 0 );

			glDrawArrays( glPrimitive , 0 , vertexCount );
		}

		return;
	}

	void SimpleMesh::print()
	{
		std::cout << "< << <<< <__Mesh__> >>> >> >" << std::endl;
		std::cout << " - Vertexes " << vertexes.size() << std::endl;
		std::cout << " - TextureCoordinates " << textureCoordinates.size() << std::endl;
		std::cout << " - GTexture " << ( texture == NULL ? "NO" : "YES" ) << std::endl;
	}

	void SimpleMesh::apply()
	{
		vertexCount = vertexes.size();

		vertexBuffer.set(
				vertexCount * sizeof(glm::vec3) ,
				&vertexes[0],
				Graphics::write,
				Graphics::gpu,
				Graphics::once );

		textureBuffer.set(
				vertexCount * sizeof(glm::vec2) ,
				&textureCoordinates[0],
				Graphics::write,
				Graphics::gpu,
				Graphics::once );

		vertexes.clear();
		textureCoordinates.clear();
	}

	void SimpleMesh::setPlane( SimpleMesh& mesh , float width , float height , Texture *texture )
	{
		mesh.vertexes.clear();
		mesh.textureCoordinates.clear();

		if( texture == NULL )
		{
			std::cout << "SimpleMesh::setPlane texture is NULL" << std::endl;
			return;
		}

		mesh.texture = texture;
		mesh.setPrimitiveType( Graphics::quads );

		glm::vec2 td( texture->getMin().x , texture->getMax().y );
		glm::vec2 tc( texture->getMax().x , texture->getMax().y );
		glm::vec2 tb( texture->getMax().x , texture->getMin().y );
		glm::vec2 ta( texture->getMin().x , texture->getMin().y );

		if( mesh.texture != NULL )
		{
			mesh.textureCoordinates.reserve( 4 );

			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( tc );
			mesh.textureCoordinates.push_back( td );
			mesh.textureCoordinates.push_back( ta );
		}

		mesh.vertexes.reserve( 4 );

		mesh.vertexes.push_back( glm::vec3( width 	, 0 		, 0 ));
		mesh.vertexes.push_back( glm::vec3( width 	, height 	, 0 ));
		mesh.vertexes.push_back( glm::vec3( 0 		, height 	, 0 ));
		mesh.vertexes.push_back( glm::vec3( 0 		, 0 		, 0 ));

		mesh.apply();
	}

	void SimpleMesh::setPlane2( SimpleMesh& mesh , float width , float height , Texture *texture )
	{
		mesh.vertexes.clear();
		mesh.textureCoordinates.clear();

		if( texture == NULL )
		{
			std::cout << "SimpleMesh::setPlane2 texture is NULL" << std::endl;
			return;
		}

		const float hwidth = width / 2.0f;
		const float hheight = height / 2.0f;

		mesh.texture = texture;
		mesh.setPrimitiveType( Graphics::quads );

		glm::vec2 td( texture->getMin().x , texture->getMax().y );
		glm::vec2 tc( texture->getMax().x , texture->getMax().y );
		glm::vec2 tb( texture->getMax().x , texture->getMin().y );
		glm::vec2 ta( texture->getMin().x , texture->getMin().y );

		if( mesh.texture != NULL )
		{
			mesh.textureCoordinates.reserve( 4 );

			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( tc );
			mesh.textureCoordinates.push_back( td );
			mesh.textureCoordinates.push_back( ta );
		}

		mesh.vertexes.reserve( 4 );
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight , 0 ));
		mesh.vertexes.push_back( glm::vec3(  hwidth ,  hheight , 0 ));
		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight , 0 ));
		mesh.vertexes.push_back( glm::vec3( -hwidth , -hheight , 0 ));

		mesh.apply();
	}

	void SimpleMesh::setBox( SimpleMesh& mesh , float width , float height , float depth , Texture *texture )
	{
		mesh.vertexes.clear();
		mesh.textureCoordinates.clear();

		if( texture == NULL )
		{
			std::cout << "SimpleMesh::setBox texture is NULL" << std::endl;
			return;
		}

		const float hwidth = width / 2.0f;
		const float hheight = height / 2.0f;
		const float hdepth = depth / 2.0f;

		const glm::vec2 ta( texture->getMin().x , texture->getMax().y );
		const glm::vec2 tb( texture->getMax().x , texture->getMax().y );
		const glm::vec2 tc( texture->getMax().x , texture->getMin().y );
		const glm::vec2 td( texture->getMin().x , texture->getMin().y );

		mesh.texture = texture;
		mesh.setPrimitiveType( Graphics::triangles );

		if( mesh.texture != NULL )
		{
			mesh.textureCoordinates.reserve( 6 * 6 );

			// 1
			mesh.textureCoordinates.push_back( ta );
			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( tc );

			mesh.textureCoordinates.push_back( ta );
			mesh.textureCoordinates.push_back( tc );
			mesh.textureCoordinates.push_back( td );

			// 2
			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( tc );
			mesh.textureCoordinates.push_back( td );

			mesh.textureCoordinates.push_back( ta );
			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( td );

			// 3
			mesh.textureCoordinates.push_back( td );
			mesh.textureCoordinates.push_back( tc );
			mesh.textureCoordinates.push_back( tb );

			mesh.textureCoordinates.push_back( td );
			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( ta );

			// 4
			mesh.textureCoordinates.push_back( tc );
			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( ta );

			mesh.textureCoordinates.push_back( td );
			mesh.textureCoordinates.push_back( tc );
			mesh.textureCoordinates.push_back( ta );

			// 5
			mesh.textureCoordinates.push_back( ta );
			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( tc );

			mesh.textureCoordinates.push_back( ta );
			mesh.textureCoordinates.push_back( tc );
			mesh.textureCoordinates.push_back( td );

			// 6
			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( tc );
			mesh.textureCoordinates.push_back( td );

			mesh.textureCoordinates.push_back( ta );
			mesh.textureCoordinates.push_back( tb );
			mesh.textureCoordinates.push_back( td );
		}

		mesh.vertexes.reserve( 6 * 6 );

		// 1
		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth ,  hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,   hdepth ));

		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth , -hheight ,   hdepth ));

		// 2
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth ,  hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,  -hdepth ));

		mesh.vertexes.push_back( glm::vec3( -hwidth , -hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,  -hdepth ));

		// 3
		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth ,  hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth ,  hheight ,  -hdepth ));

		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth ,  hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,  -hdepth ));

		// 4
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth , -hheight ,   hdepth ));

		mesh.vertexes.push_back( glm::vec3( -hwidth , -hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth , -hheight ,   hdepth ));

		// 5
		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth , -hheight ,   hdepth ));

		mesh.vertexes.push_back( glm::vec3( -hwidth ,  hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth , -hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3( -hwidth , -hheight ,  -hdepth ));

		// 6
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth ,  hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth ,  hheight ,  -hdepth ));

		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,  -hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth , -hheight ,   hdepth ));
		mesh.vertexes.push_back( glm::vec3(  hwidth ,  hheight ,  -hdepth ));

		mesh.apply();
	}
}
