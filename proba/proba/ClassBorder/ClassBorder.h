//Head_ClassBorder.h
#include "TDataSource.h"

#include "standartIncl.h"

#pragma once;

class ClassBorder
{

public:

	cv::Mat img;
	
	vector<vector<unsigned int>> ImgMatrix;

	unsigned int T;

	

	ClassBorder(cv::Mat &img);

	void OneMeasure(cv::Mat img);
	
	int MatrixDif(int j, const int (*Mtx)[3], int rowsCount, cv::Mat &currow0, cv::Mat &currow1, cv::Mat &currow2);
	int Max(vector<int> dFs);
	int avgT(int Width, int Height);

	void dRGBCalc(int j, int dR, int dG, int dB);

	void BinarMap(int Width, int Height);
	
	int ReWriteImg();

	void finalMtx();

	~ClassBorder(void);
};

