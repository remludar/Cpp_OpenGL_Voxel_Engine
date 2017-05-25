#pragma once
class Error
{
public:
	Error();
	~Error();

	static void PrintError(const char* errorMessage);
};

