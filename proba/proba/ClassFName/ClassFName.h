#include "standartIncl.h"

#pragma once

class ClassFName
{
public:
	ClassFName(void);

	string FPath(string Path, string fName);

	string crtNameToPath(string Path, string fName, string adName);

	string getDirPath(string Path, string fName);

	bool DirectoryExists(const char* FileName);

	~ClassFName(void);
};

