/*
 * GetTextFileName.cpp
 *
 *  Created on: Jun 23, 2016
 *      Author: Anjan Dutta
 */

#include "../Headers/WordSegmentation.h"

char* GetTextFileName(char *str)
{
	static char fn_ret[5000] = "\0";

	std::string fullfn(str);

	size_t found = fullfn.find_last_of("/");
	std::string fn = fullfn.substr(found+1);

	found = fn.find_last_of(".");
	std::string fnwoext = fn.substr(0,found);

	fn = fnwoext + ".txt";

	strcpy(fn_ret, (char*)fn.c_str());

	return fn_ret;
}





