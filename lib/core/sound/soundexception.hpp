/*
 * SoundException.hpp
 *
 *  Created on: 31.1.2012
 *      Author: akin
 */

#ifndef SOUNDEXCEPTION_HPP_
#define SOUNDEXCEPTION_HPP_

#include <stdexcept>

namespace bolt
{

class SoundException : public std::runtime_error
{
public:
	SoundException( std::string msg );
	virtual ~SoundException() throw();
};

} /* namespace bolt */
#endif /* SOUNDEXCEPTION_HPP_ */
