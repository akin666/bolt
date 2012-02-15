/*
 * video.hpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 *
 *      Current Video is saved in Singleton class.
 *      getSingleton<Video>()
 *      setSingleton<Video>( Video* )
 */

#ifndef VIDEO_HPP_
#define VIDEO_HPP_

#include <graphics/videomode.hpp>
#include <graphics/rendertarget.hpp>
#include <vector>
#include <string>

namespace bolt
{

class Video
{
public:
	Video();
	virtual ~Video();

	virtual float getDPI();
	bool isFullscreen();
	virtual bool isWindowed();

	virtual void setDPI( float val );
	void setFullscreen( bool val );
	virtual void setWindowed( bool val );

	virtual bool isCursorVisible();
	virtual void setCursorVisible( bool val );

	// OGL: 3.2 => Major: 3 Minor: 2
	virtual void setMajorVersion( int v );
	virtual void setMinorVersion( int v );

	virtual void initialize();

	virtual void setTitle( std::string head );
	virtual std::string getTitle();

	virtual void apply( const VideoMode& mode );

	virtual void listVideoModes( std::vector<VideoMode>& modes ) const;

	virtual RenderTarget& getRenderTarget() = 0;

	virtual void flip();
};

} /* namespace bolt */
#endif /* VIDEO_HPP_ */
