/*
 * Graphics.h
 *
 *  Created on: 9.7.2011
 *      Author: akin
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

namespace bolt
{
	class Graphics
	{
	public:
		enum BindStyle
		{
			read = 0,
			write = 1,
			readAndWrite = 2,
			arrayBuffer = 3,
			elementArrayBuffer = 4
		};

		enum Residence
		{
			gpu,
			cpu,
			cpugpu
		};

		enum Updates
		{
			everyFrame,
			once,
			multipleTimes
		};

		enum Primitives
		{
			triangles,
			triangleStrips,
			triangleFan,
			points,
			lines,
			quads,
		};

		static int resolveResidenceUpdates( const Residence residence , const Updates updates );
	};
}

#endif /* GRAPHICS_H_ */
