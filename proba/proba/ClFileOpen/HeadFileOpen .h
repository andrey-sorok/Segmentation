//HeadFileOpen.h

#include "QTreeStruct.h"

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <windows.h>

#pragma once

using namespace std;

class ClFileOpen
{
public:
	ClFileOpen();
	~ClFileOpen();

	void GetFiles(LPCSTR Dir);

	vector<string> FNameArr;
private:
	

};


