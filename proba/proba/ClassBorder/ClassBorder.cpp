#include "ClassBorder.h"
//#include "TDataSource.h"


ClassBorder::ClassBorder(cv::Mat &img)
{

	ImgMatrix.resize(img.rows);

	int size = ImgMatrix.size();

	for(int i = 0; i < size; i++)
	{
		ImgMatrix[i].resize(img.cols);
	}
}

void ClassBorder::dRGBCalc(int j, int dR, int dG, int dB)
{
	int min = 256;
	int max = 0;

	for( int i = 0; i <= 2; i++)
	{


	}

}

int ClassBorder::Max(vector<int> dFs)
{

	int max = 0;
	
	vector<int>::iterator it = dFs.begin();
	while(it != dFs.end())
	{
		if(*it > max)
		{
			max = *it;
		}
		it++;
	}

	return max;
}

int ClassBorder::avgT(int Width, int Height)
{
	int tmpT = 0;

	for(int i = 0; i < Height; i++)
	{

		for(int j = 0; j < Width; j++)
		{
			tmpT = tmpT + ImgMatrix[i][j];
			
		}

	}

	tmpT = tmpT/(Width*Height);

	return tmpT;

}

void ClassBorder::BinarMap(int Width, int Height)
{
	for(int i = 0; i < Height+1; i++)
	{
		
		for(int j = 0; j < Width+1; j++)
		{
			if(ImgMatrix[i][j] < T*K)
			{
				ImgMatrix[i][j] = 1;
			}
			else
			{
				ImgMatrix[i][j] = 0;
			}
		
		}

	}

}

int ClassBorder::ReWriteImg()
{
	
	for (int i = 0; i <= img.cols -1; i++)
	{
		for (int j = 0; j <= img.rows -1; j++)
		{
			if (ImgMatrix[j][i] == 1)
			{

				img.at<cv::Vec3b>(j,i).val[0] = 255;
				img.at<cv::Vec3b>(j,i).val[1] = 255;
				img.at<cv::Vec3b>(j,i).val[2] = 255;

			}	

			if (ImgMatrix[j][i] == 0)
			{
				img.at<cv::Vec3b>(j,i).val[0] = 0;
				img.at<cv::Vec3b>(j,i).val[1] = 0;
				img.at<cv::Vec3b>(j,i).val[2] = 0;
			}
			
		}
	}

	return 1;

}

void ClassBorder::finalMtx()
{
	for(int i = 0; i <= this->img.cols -1; i++)
	{
		for(int j = 0; j <= this->img.rows -1; j++)
		{
			if(ImgMatrix[j][i] == 1)
			{

				this->img.at<cv::Vec3b>(j,i).val[0] = 0;
				this->img.at<cv::Vec3b>(j,i).val[1] = 0;
				this->img.at<cv::Vec3b>(j,i).val[2] = 0;

			}	
			if(ImgMatrix[j][i] == 0)
			{
				this->img.at<cv::Vec3b>(j,i).val[0] = 255;
				this->img.at<cv::Vec3b>(j,i).val[1] = 255;
				this->img.at<cv::Vec3b>(j,i).val[2] = 255;
			}

			
		}
	}
}

int ClassBorder::MatrixDif(int j, const int (*Mtx)[3], int rowsCount, cv::Mat &currow0, cv::Mat &currow1, cv::Mat &currow2)
{
	int dR = 1, dG = 1, dB = 1; 

	int tmpDF = 0;
//{R,G,B} = {0.3, 0.59, 0.11}; 2 - All
	for( int m = 0; m < rowsCount; m++)
	{

				
		tmpDF = tmpDF + ((dB * int(currow0.at<cv::Vec3b>(0,j+(m-1)).val[0]) 
					+ dG * int(currow0.at<cv::Vec3b>(0,j+(m-1)).val[1]) 
					+ dR * int(currow0.at<cv::Vec3b>(0,j+(m-1)).val[2]))*Mtx[0][m]);
/*
		cout << "color1: " << int(currow0.at<cv::Vec3b>(0,j+(m-1)).val[0]) << endl;
		cout << "color2: " << int(currow0.at<cv::Vec3b>(0,j+(m-1)).val[1]) << endl;
		cout << "color3: " << int(currow0.at<cv::Vec3b>(0,j+(m-1)).val[2]) << endl;
		
		cout << "Mtx[0][m]: " << Mtx[0][m] << endl;
		
		cout << "tmpDF1: " << tmpDF << endl;
*/

		tmpDF = tmpDF + ((dB * int(currow1.at<cv::Vec3b>(0,j+(m-1)).val[0]) 
					+ dG * int(currow1.at<cv::Vec3b>(0,j+(m-1)).val[1]) 
					+ dR * int(currow1.at<cv::Vec3b>(0,j+(m-1)).val[2]))*Mtx[1][m]);

		
/*
		cout << "color1: " << int(currow1.at<cv::Vec3b>(0,j+(m-1)).val[0]) << endl;
		cout << "color2: " << int(currow1.at<cv::Vec3b>(0,j+(m-1)).val[1]) << endl;
		cout << "color3: " << int(currow1.at<cv::Vec3b>(0,j+(m-1)).val[2]) << endl;
		cout << "Mtx[0][m]: " << Mtx[1][m] << endl;
		cout << "tmpDF2: " << tmpDF << endl;
*/
		tmpDF = tmpDF + ((dB * int(currow2.at<cv::Vec3b>(0,j+(m-1)).val[0]) 
					+ dG * int(currow2.at<cv::Vec3b>(0,j+(m-1)).val[1]) 
					+ dR * int(currow2.at<cv::Vec3b>(0,j+(m-1)).val[2]))*Mtx[2][m]);

		
/*
		cout << "color1: " << int(currow2.at<cv::Vec3b>(0,j+(m-1)).val[0]) << endl;
		cout << "color2: " << int(currow2.at<cv::Vec3b>(0,j+(m-1)).val[1]) << endl;
		cout << "color3: " << int(currow2.at<cv::Vec3b>(0,j+(m-1)).val[2]) << endl;
		cout << "Mtx[0][m]: " << Mtx[2][m] << endl;

		cout << "tmpDF3: " << tmpDF << endl;
*/		
		tmpDF = abs(tmpDF);
	}

	return tmpDF;
}

void ClassBorder::OneMeasure(cv::Mat img)
{
	this->img = img.clone();

	int dfA = 0, dfB = 0, dfC = 0, dfD = 0;
	int dfG = 0, dfV = 0;

	int Width = img.cols -1;
	int Height = img.rows -1;

	int rowsCount;

	cv::Vec3b clr;

	vector<int> dFs;
	
	//Scroll Image
	for(int i = 1; i < Height; i++)
	{
		cv::Mat currow0 = img.row(i-1);
		cv::Mat currow1 = img.row(i);
		cv::Mat currow2 = img.row(i+1);

		for(int j = 1; j < Width; j++)
		{
			rowsCount = sizeof(a)/sizeof(a[0]);		
			dfA = this->MatrixDif(j, a, rowsCount, currow0, currow1,currow2);
			dFs.push_back(dfA);

			rowsCount = sizeof(b)/sizeof(b[0]);
			dfB = this->MatrixDif(j, b, rowsCount, currow0, currow1,currow2);
			dFs.push_back(dfB);

			ImgMatrix[i][j] = Max(dFs); 

			dFs.clear();
			
		}
	}

	T = avgT(Width, Height);

	cout << "TBorder: " << T << endl;

	//cout << "Average T: " << avgT(Width, Height) << endl;

	BinarMap(Width, Height);

	//RutovitzThin(Width, Height);

	//HilditchThin(Width, Height);

	//ReWriteImg();

}

ClassBorder::~ClassBorder(void)
{
}
