#include <iostream>

#include "Error.h"

Error::Error()
{
}


Error::~Error()
{
}

void Error::PrintError(const char* errorMessage)
{
	std::cout << errorMessage << std::endl;
}