#include "HeadFileOpen .h"

#include <stdlib.h>
#include <stdio.h>

#include <windows.h>
#include <iostream>

ClFileOpen::ClFileOpen()
{
}

ClFileOpen::~ClFileOpen()
{
}

void ClFileOpen::GetFiles(LPCSTR Dir)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	

	string tmp = Dir;
	
	int s = tmp.find("\\");

	tmp = tmp.substr(0, s+1);
	
	hFind = FindFirstFile(Dir, &FindFileData);

	string str;

	if (hFind != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(hFind, &FindFileData))
		{
			str = FindFileData.cFileName;
			bool IsDir = (str != "..") && (str != ".")&&(str != "Thumbs.db");
			if (IsDir)
			{
				str = FindFileData.cFileName;
				str = tmp + str;
				FNameArr.push_back(str);
			}
		}
	}

	vector<string>::iterator it = FNameArr.begin();
	while (it != FNameArr.end())
	{
		str = *it;
		printf("The first file found is %s\n", str.c_str());
		it++;
	}

	system("pause");

}