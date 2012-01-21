/*
 * simplemesh.h
 *
 *  Created on: 9.7.2011
 *      Author: akin
 */

#ifndef SIMPLEMESH_H_
#define SIMPLEMESH_H_

#include <glm/glm>
#include <graphics/bufferobject.hpp>
#include <graphics/texture/texture.hpp>
#include <graphics/shader/shaderprogram.hpp>
#include <graphics/shader/uniform.hpp>
#include <graphics/shader/attribute.hpp>
#include <graphics/graphics.hpp>
#include <common>

#include <vector>

namespace bolt
{
	class SimpleMesh
	{
	protected:
		uint glPrimitive;
		ShaderProgram *shader;

		Uniform *tex;
		Uniform *modelo;

		Attribute *vertex;
		Attribute *coordinates;

		BufferObject vertexBuffer;
		BufferObject textureBuffer;

		uint vertexCount;
	public:
		bool debug;

		SimpleMesh();
		virtual ~SimpleMesh();

		void setShader( ShaderProgram *prog );

		void setPrimitiveType( Graphics::Primitives primitiveType );

		Texture *texture;

		std::vector< glm::vec3 > vertexes;
		std::vector< glm::vec2 > textureCoordinates;

		void draw( glm::mat4x4& model );

		void apply();

		void print();

		static void setPlane( SimpleMesh& mesh , float width , float height , Texture *texture );
		static void setPlane2( SimpleMesh& mesh , float width , float height , Texture *texture );
		static void setBox( SimpleMesh& mesh , float width , float height , float depth , Texture *texture );
	};
}

#endif /* SIMPLEMESH_H_ */
