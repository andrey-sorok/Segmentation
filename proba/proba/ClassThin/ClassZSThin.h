//Head_ClassClassZSThinr.h
#pragma once;

#include "standartIncl.h"


class ClassZSThin
{

public:

	cv::Mat img;
	vector<vector<unsigned int>> ImgMatrix;

	unsigned int T;
	cv::Mat crow;

	int Iter;
	int z;
	

	ClassZSThin(vector<vector<unsigned int>> Mtx);
	
	void createImgMatrix();

	void myThin(int Width, int Height);

	int Gap(int i, int j);

	int ReWriteImg();

	~ClassZSThin(void);
};

