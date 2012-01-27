/*
 * stringtools.cpp
 *
 *  Created on: 27.1.2012
 *      Author: akin
 */

#include "stringtools"
#include <functional>
#include <algorithm>
//and <string.h>

namespace stringtools
{
void toUpper( std::string& str )
{
	std::transform(str.begin(), str.end(), str.begin(), toupper );
}

void toLower( std::string& str )
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}

}


