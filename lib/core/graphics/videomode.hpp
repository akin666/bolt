/*
 * videomode.hpp
 *
 *  Created on: 10.1.2012
 *      Author: akin
 */

#ifndef VIDEOMODE_HPP_
#define VIDEOMODE_HPP_

namespace bolt
{

class VideoMode
{
protected:
	int width;
	int height;

	int redBits;
	int greenBits;
	int blueBits;
	int alphaBits;
	int stencilBits;
	int depthBits;
public:
	VideoMode();
	VideoMode( const VideoMode& other );
	virtual ~VideoMode();

	VideoMode& operator = ( const VideoMode& other );

    int getBlueBits() const;
    int getDepthBits() const;
    int getGreenBits() const;
    int getRedBits() const;
    int getAlphaBits() const;
    int getStencilBits() const;

    int getHeight() const;
    int getWidth() const;

    void setBlueBits(int blueBits);
    void setDepthBits(int depthBits);
    void setGreenBits(int greenBits);
    void setRedBits(int redBits);
    void setAlphaBits(int alphaBits);
    void setStencilBits(int stencilBits);

    void setHeight(int height);
    void setWidth(int width);
};

} /* namespace bolt */
#endif /* VIDEOMODE_HPP_ */
