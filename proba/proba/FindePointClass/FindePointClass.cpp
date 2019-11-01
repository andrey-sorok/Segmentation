#include "FindePointClass.h"


FindePointClass::FindePointClass(void)
{

}

bool FindePointClass::getPoint2(const bool arr[5][5])
{
	bool rtn = 1;

	bool centor = 1;
	bool env = 0;

// 1 1 0 1 1
// 1 1 0 1 1
// 0 0 0 1 1
// 1 1 1 1 1
// 1 1 1 1 1 

	//rtn = arr[0][2] || arr[1][2] || arr[2][0] || arr[2][1] || arr[2][2];

// 1 1 0 1 1
// 1 1 0 1 1
// 0 0 0 0 0
// 1 1 0 1 1
// 1 1 0 1 1 

	//rtn = arr[0][2] || arr[1][2] || arr[2][0] || arr[2][1] ||arr[2][2] || arr[2][3] || arr[2][4] || arr[3][2] || arr[4][2];


// 1 1 1 1 1
// 1 1 1 1 1
// 1 1 0 1 1
// 0 0 1 0 0
// 1 1 1 1 1 

	centor = arr[2][2] || arr[3][0] || arr[3][1] || arr[3][3] || arr[3][4];

	env = arr[0][0] && arr[0][1] && arr[0][2] && arr[0][3] && arr[0][4] 
			&& arr[1][0] && arr[1][1] && arr[1][2] && arr[1][3] && arr[1][4] 
			&& arr[2][0] && arr[2][1]&& arr[2][3] && arr[2][4]
			&& arr[4][0] && arr[4][1] && arr[4][2] && arr[4][3] && arr[4][4] ;

	if ((centor == 0)&&(env == 1))
	{
		rtn = 0;
	}

// 0 0 1 1 1
// 1 0 0 1 1
// 1 1 0 0 1
// 1 1 1 0 0
// 1 1 1 1 0 

	centor = arr[0][0] || arr[0][1] || arr[1][1] || arr[1][2] || arr[2][2]
			|| arr[2][3]|| arr[3][3] || arr[3][4] || arr[4][4];

	env = arr[0][2] && arr[0][3] && arr[0][4] && arr[1][0] && arr[1][3] 
			&& arr[1][4] && arr[2][0] && arr[2][1] && arr[2][4] && arr[3][0] 
			&& arr[3][1] && arr[3][2]&& arr[4][0] && arr[4][1]
			&& arr[4][2] && arr[4][3];

	if ((centor == 0)&&(env == 1))
	{
		rtn = 0;
	}


	return rtn;

}

void FindePointClass::findePoint2(cv::Mat& img)
{
	for (int i = 2; i < img.rows -3; ++i)
	{
		for (int j = 2; j < img.cols -3; ++j)
		{
	
			bool arr[5][5];
							
			arr[0][0] = (bool)img.at<cv::Vec3b>(i-2,j-2).val[0];
			arr[0][1] = (bool)img.at<cv::Vec3b>(i-2,j-1).val[0];
			arr[0][2] = (bool)img.at<cv::Vec3b>(i-2,j).val[0];
			arr[0][3] = (bool)img.at<cv::Vec3b>(i-2,j+1).val[0];
			arr[0][4] = (bool)img.at<cv::Vec3b>(i-2,j+2).val[0];

			arr[1][0] = (bool)img.at<cv::Vec3b>(i-1,j-2).val[0];
			arr[1][1] = (bool)img.at<cv::Vec3b>(i-1,j-1).val[0];
			arr[1][2] = (bool)img.at<cv::Vec3b>(i-1,j).val[0];
			arr[1][3] = (bool)img.at<cv::Vec3b>(i-1,j+1).val[0];
			arr[1][4] = (bool)img.at<cv::Vec3b>(i-1,j+2).val[0];

			arr[2][0] = (bool)img.at<cv::Vec3b>(i,j-2).val[0];
			arr[2][1] = (bool)img.at<cv::Vec3b>(i,j-1).val[0];
			arr[2][2] = (bool)img.at<cv::Vec3b>(i,j).val[0];
			arr[2][3] = (bool)img.at<cv::Vec3b>(i,j+1).val[0];
			arr[2][4] = (bool)img.at<cv::Vec3b>(i,j+2).val[0];

			arr[3][0] = (bool)img.at<cv::Vec3b>(i+1,j-2).val[0];
			arr[3][1] = (bool)img.at<cv::Vec3b>(i+1,j-1).val[0];
			arr[3][2] = (bool)img.at<cv::Vec3b>(i+1,j).val[0];
			arr[3][3] = (bool)img.at<cv::Vec3b>(i+1,j+1).val[0];
			arr[3][4] = (bool)img.at<cv::Vec3b>(i+1,j+2).val[0];

			arr[4][0] = (bool)img.at<cv::Vec3b>(i+2,j-2).val[0];
			arr[4][1] = (bool)img.at<cv::Vec3b>(i+2,j-1).val[0];
			arr[4][2] = (bool)img.at<cv::Vec3b>(i+2,j).val[0];
			arr[4][3] = (bool)img.at<cv::Vec3b>(i+2,j+1).val[0];
			arr[4][4] = (bool)img.at<cv::Vec3b>(i+2,j+2).val[0];

			bool isPoint = getPoint2(arr);

			if (isPoint == 0)
			{
				img.at<cv::Vec3b>(i,j).val[0] = 0;
				img.at<cv::Vec3b>(i,j).val[1] = 0;
				img.at<cv::Vec3b>(i,j).val[2] = 255;
			}
		}

	}
}

bool FindePointClass::getPoint1(const bool arr[8]) 
{
	bool rtn = 1;

// 1 0 1
// 0 0 1
// 1 1 1

	rtn = arr[1] || arr[3] || arr[4];

// 1 0 1
// 1 0 0
// 1 1 1

	rtn = arr[1] || arr[4] || arr[5];

// 1 1 1
// 1 0 0
// 1 0 1

	rtn = arr[4] || arr[5] || arr[7];

// 1 1 1
// 0 0 1
// 1 0 1

	rtn = arr[3] || arr[4] || arr[7];

/*
// 1 1 0 1 1
// 1 1 0 1 1
// 0 0 0 1 1
// 1 1 1 1 1
// 1 1 1 1 1 

	rtn = arr[1] || arr[3] || arr[4] || arr[5] || arr[7];

// 1 0 1
// 1 0 0
// 1 0 1

	rtn = arr[1] || arr[4] || arr[5] || arr[7];

// 1 0 1
// 0 0 1
// 1 0 1
	rtn = arr[1] || arr[3] || arr[4] || arr[7];

// 1 0 1
// 0 0 0
// 1 1 1
	rtn = arr[1] || arr[3] || arr[4] || arr[5];

// 1 1 1
// 0 0 0
// 1 0 1
	rtn = arr[3] || arr[4] || arr[5] || arr[7];

// 1 1 1 0
// 0 0 0 0
// 1 0 1 0
// 1 0 1 0
*/

	return rtn;
}

void FindePointClass::findePoint1(cv::Mat& img)
{
	for (int i = 1; i < img.rows -2; ++i)
	{
		for (int j = 1; j < img.cols -2; ++j)
		{
		
			bool arr[8];
			//0
			arr[0] = (bool)img.at<cv::Vec3b>(i-1,j-1).val[0];
			//1
			arr[1] = (bool)img.at<cv::Vec3b>(i-1,j).val[0];
			//2
			arr[2] = (bool)img.at<cv::Vec3b>(i-1,j+1).val[0];

			//3
			arr[3] = (bool)img.at<cv::Vec3b>(i,j-1).val[0];
			//4
			arr[4] = (bool)img.at<cv::Vec3b>(i,j).val[0];
			//5
			arr[5] = (bool)img.at<cv::Vec3b>(i,j+1).val[0];

			//6
			arr[6] = (bool)img.at<cv::Vec3b>(i+1,j-1).val[0];
			//7
			arr[7] = (bool)img.at<cv::Vec3b>(i+1,j).val[0];
			//8
			arr[8] = (bool)img.at<cv::Vec3b>(i+1,j+1).val[0];
/*
			cout << arr[0] << "	  ";
			cout << arr[1] << "	  ";
			cout << arr[2] << "	  ";

			cout << endl;

			cout << arr[3] << "	  ";
			cout << arr[4] << "	  ";
			cout << arr[5] << "	  ";

			cout << endl;

			cout << arr[6] << "	  ";
			cout << arr[7] << "	  ";
			cout << arr[8] << "	  ";
*/
			bool isPoint = getPoint1(arr);

			//cout << isPoint << endl;


			if (isPoint == 0)
			{
				img.at<cv::Vec3b>(i,j).val[0] = 0;
				img.at<cv::Vec3b>(i,j).val[1] = 0;
				img.at<cv::Vec3b>(i,j).val[2] = 255;
			/*
				img.at<cv::Vec3b>(i-1,j+1).val[0] = 0;
				img.at<cv::Vec3b>(i-1,j+1).val[1] = 0;
				img.at<cv::Vec3b>(i-1,j+1).val[2] = 255;

				img.at<cv::Vec3b>(i-1,j-1).val[0] = 0;
				img.at<cv::Vec3b>(i-1,j-1).val[1] = 0;
				img.at<cv::Vec3b>(i-1,j-1).val[2] = 255;

				img.at<cv::Vec3b>(i+1,j-1).val[0] = 0;
				img.at<cv::Vec3b>(i+1,j-1).val[1] = 0;
				img.at<cv::Vec3b>(i+1,j-1).val[2] =255;

				img.at<cv::Vec3b>(i+1,j+1).val[0] = 0;
				img.at<cv::Vec3b>(i+1,j+1).val[1] = 0;
				img.at<cv::Vec3b>(i+1,j+1).val[2] = 255;

			*/

			}

		}
	}

}

void FindePointClass::writeBorder(vector<vector<unsigned int>> brdMatrix, cv::Mat& img)
{
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			if (brdMatrix[i][j] == 0)
			{
				img.at<cv::Vec3b>(i,j).val[0] = 0;
				img.at<cv::Vec3b>(i,j).val[1] = 0;
				img.at<cv::Vec3b>(i,j).val[2] = 0;
			}
		}

	}
}


FindePointClass::~FindePointClass(void)
{
}
