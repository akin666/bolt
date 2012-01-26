/*
 * texthandler.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "texthandler.hpp"
#include <resource/work/bytedatawork.hpp>

namespace bolt
{
namespace resource
{

TextHandler::TextHandler()
{
}

TextHandler::~TextHandler()
{
}

bool TextHandler::canHandle( const std::string& extension )
{
	// im not gonna bring boost into the project _just_for_ strUp() function.
	if( extension == "txt" ||
		extension == "txT" ||
		extension == "tXt" ||
		extension == "tXT" ||
		extension == "Txt" ||
		extension == "TxT" ||
		extension == "TXt" ||
		extension == "TXT" ||
		// CFG!
		extension == "cfg" ||
		extension == "cfG" ||
		extension == "cFg" ||
		extension == "cFG" ||
		extension == "Cfg" ||
		extension == "CfG" ||
		extension == "CFg" ||
		extension == "CFG" )
	{
		return true;
	}
	return false;
}

Work *TextHandler::handle( const std::string& alias , const std::string path )
{
	Work *work = new ByteDataWork( alias , path );

	return work;
}

}
} /* namespace bolt */
