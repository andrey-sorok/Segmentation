//FindePointClass
#include "standartIncl.h"

#pragma once
class FindePointClass
{
private:
	bool getPoint2(const bool arr[5][5]);

	bool getPoint1(const bool arr[8]);

public:
	FindePointClass(void);

	void findePoint2(cv::Mat& img);

	void findePoint1(cv::Mat& img);

	void writeBorder(vector<vector<unsigned int>> brdMatrix, cv::Mat& resultImg);

	~FindePointClass(void);
};

