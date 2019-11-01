#include "ClassZSThin.h"

#pragma once
class KWThin: public ClassZSThin 
{
protected:
	void kwScelets();

	void inclinedLine();
public:
	
	KWThin(cv::Mat& img);

	void createThinMtx(cv::Mat& img);
	void invertBinarImg(cv::Mat img); 

	//One Chanel IMG //WHITE Contours
	void dellMinContours(cv::Mat& img);
	
	~KWThin(void);
};

