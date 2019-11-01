//Head_ClassClassZSThinr.h

#include "standartIncl.h"



class ClassZSThin
{

private:
	struct TrectSize
	{
		int Left;
		int Up;
		int Width;
		int Height;
	};

protected:

	void initMatrix_2();
	
	int getData(int i, int j, int &B);

	int getEnvPixels(int i, int j);

	void dellBrdPixels();

	void initaa();

	void imgBinar(cv:: Mat &img);
	
	vector<vector<int>> ImgMatrix;
	vector<vector<int>> ImgMatrix_2;

	vector<int> aa;
	
	int pixelDell;

	cv::Mat crow;

public:
	
	TrectSize rectSize;
	
	ClassZSThin(cv::Mat &img);
	
//threads
	
	void ThcreateImgMatrix(cv::Mat &img);

	void ThzsScelet();

	void ThReWriteImg(cv::Mat &img);

//end_threads

//_______
	void filterPixel(cv::Mat &img);
//_______

	~ClassZSThin(void);

};

