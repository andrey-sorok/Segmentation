#include "ClassFName.h"

ClassFName::ClassFName(void)
{
}

string ClassFName::FPath(string Path, string fName)
{
	Path = Path + '\\' + fName;

	return Path;
}

string ClassFName::crtNameToPath(string Path, string fName, string adName)
{
	Path = Path + '\\' + adName + '_' + fName;

	return Path;
}

string ClassFName::getDirPath(string Path, string fName)
{
	return Path +  '\\' + fName.substr(0, fName.find_first_of( "."));
}

bool ClassFName::DirectoryExists(const char* FileName)
{
  int Code = GetFileAttributes(FileName);
  return (Code != -1) && (FILE_ATTRIBUTE_DIRECTORY & Code);
}



ClassFName::~ClassFName(void)
{
}
