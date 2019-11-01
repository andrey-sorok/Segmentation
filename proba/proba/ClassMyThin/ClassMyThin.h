#include "standartIncl.h"

#pragma once

struct TrectSize
{
	int Left;
	int Up;
	int Width;
	int Height;
};

class ClassZSThin
{

public:

	TrectSize rectSize;

	//cv::Mat img;
	vector<vector<int>> ImgMatrix;
	vector<vector<int>> ImgMatrix_2;

	vector<int> aa;
	bool pixelDell;

	unsigned int T;
	cv::Mat crow;

	int Iter;
	int z;
	
	ClassZSThin(cv::Mat &img);
	
//threads
	
	void ThcreateImgMatrix(cv::Mat &img);

	void ThzsScelet();

	void ThReWriteImg(cv::Mat &img);

//end_threads

//_______

	bool pixelCheck(int i, int j);

	void imgBinar(cv:: Mat &img);

	int getData(int i, int j, int &B);

	int getEnvPixels(int i, int j);

	void filterPixel(cv::Mat &img);

	void dellBrdPixels();

	void initaa();

//_______

	~ClassZSThin(void);
};