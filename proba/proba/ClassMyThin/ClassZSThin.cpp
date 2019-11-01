#include "ClassZSThin.h"
//#include "StructBorder.h"


ClassZSThin::ClassZSThin(cv::Mat &img)
{
	ImgMatrix.resize(img.rows);
	ImgMatrix_2.resize(img.rows);

	int size = ImgMatrix.size();

	for(int i = 0; i < size; i++)
	{
		ImgMatrix[i].resize(img.cols);
		ImgMatrix_2[i].resize(img.cols);
	}

}

void ClassZSThin::initMatrix_2()
{
	for(int i = rectSize.Up -1; i < rectSize.Height +1; ++i)
	{
		for(int j = rectSize.Left -1; j < rectSize.Width +1; ++j)
		{
			ImgMatrix_2[i][j] = 0; 
		}
	}
}

int ClassZSThin::getEnvPixels(int i, int j)
{
	aa[0] = ImgMatrix[i-1][j-1];
	aa[1] = ImgMatrix[i-1][j];

	aa[2] = ImgMatrix[i-1][j+1];
	aa[3] = ImgMatrix[i][j+1];
	
	aa[4] = ImgMatrix[i+1][j+1];
	aa[5] = ImgMatrix[i+1][j];

	aa[6] = ImgMatrix[i+1][j-1];
	aa[7] = ImgMatrix[i][j-1];
	
	int B = 0;
	B = aa[0] + aa[1] + aa[2] + aa[3] + aa[4] + aa[5] + aa[6] + aa[7];

	return B;
}



int ClassZSThin::getData(int i, int j, int &B)
{
	B = getEnvPixels(i, j);
	
	int rtn = 0;
//___
	
	if((aa[0] == 0)&&(aa[1] == 1))
	{	++rtn;	}

	if((aa[1] == 0)&&(aa[2] == 1))
	{	++rtn;	}

	if((aa[2] == 0)&&(aa[3] == 1))
	{	++rtn;	}

	if((aa[3] == 0)&&(aa[4] == 1))
	{	++rtn;	}

	if((aa[4] == 0)&&(aa[5] == 1))
	{	++rtn;	}

	if((aa[5] == 0)&&(aa[6] == 1))
	{	++rtn;	}

	if((aa[6] == 0)&&(aa[7] == 1))
	{	++rtn;	}

//____
	if((aa[7] == 0)&&(aa[0] == 1))
	{	++rtn;	}

	return rtn;
}



void ClassZSThin::ThReWriteImg(cv::Mat &img)
{
	for(int i = rectSize.Left -1; i <= rectSize.Width +1; i++)
	{
		for(int j = rectSize.Up -1; j <= rectSize.Height +1; j++)
		{
			if(ImgMatrix[j][i] == 0)
			{
				img.at<cv::Vec3b>(j,i).val[0] = 255;
				img.at<cv::Vec3b>(j,i).val[1] = 255;
				img.at<cv::Vec3b>(j,i).val[2] = 255;
			}	
			if(ImgMatrix[j][i] == 1)
			{
				img.at<cv::Vec3b>(j,i).val[0] = 0;
				img.at<cv::Vec3b>(j,i).val[1] = 0;
				img.at<cv::Vec3b>(j,i).val[2] = 0;
			}

			
		}
	}
}

void ClassZSThin::dellBrdPixels()
{

	for(int i = rectSize.Up -1; i < rectSize.Height +1; ++i)
	{
		for(int j = rectSize.Left -1; j < rectSize.Width +1; ++j)
		{
			if(ImgMatrix_2[i][j] == 1)
			{
				ImgMatrix[i][j] = 0;
			}
		}
	}
}

void ClassZSThin::ThzsScelet()
{
	pixelDell = 0;

//Fist_iteration
	for(int i = rectSize.Up; i <= rectSize.Height; i++)
	{
		for(int j = rectSize.Left; j <= rectSize.Width; j++)
		{
			if(ImgMatrix[i][j] == 0)
			{
				ImgMatrix_2[i][j] = 0;
				continue;
			}
				
				int B = 0;
				int A = getData(i, j, B);
				
				int p1 = aa[1]*aa[3]*aa[5];
				int p2 = aa[3]*aa[5]*aa[7];

				bool isB = (B >= 2)&&(B <= 6);
/*
				cout << "H: " << i << endl; 
				cout << "W: " << j << endl;

				cout << "A: " << A << endl;
				cout << "B: " << B << endl;

				cout << "p1: " << p1 << endl;
				cout << "p2: " << p2 << endl;
*/
				if((A == 1)&&(isB == 1)&&(p1 == 0)&&(p2 == 0))
				{
					ImgMatrix_2[i][j] = 1;
					++pixelDell;
				}
				else
				{
					ImgMatrix_2[i][j] = 0;
				}	
			}

			
	}
	
	dellBrdPixels();

	if (pixelDell > 0)
	{
		pixelDell = 0;
	}
	else
	{
		return;
	}

	initMatrix_2();

//end Fist_iteration
	

//Second_iteration
	for(int i = rectSize.Up; i <= rectSize.Height; i++)
	{
		for(int j = rectSize.Left; j <= rectSize.Width; j++)
		{
			if(ImgMatrix[i][j] == 0)
			{
				ImgMatrix_2[i][j] = 0;
				continue;
			}
				
				int B = 0;
				int A = getData(i, j, B);
				
				int p1 = aa[1]*aa[3]*aa[7];
				int p2 = aa[1]*aa[5]*aa[7];

				bool isB = (B >= 2)&&(B <= 6);

				if((A == 1)&&(isB == 1)&&(p1 == 0)&&(p2 == 0))
				{
					ImgMatrix_2[i][j] = 1;
					++pixelDell;
				}
				else
				{
					ImgMatrix_2[i][j] = 0;
				}	
			}
			
	}

	dellBrdPixels();

	initMatrix_2();
//end Second_iteration

	
}

void ClassZSThin::imgBinar(cv:: Mat &img)
{
	for(int i = rectSize.Up -1; i < rectSize.Height +1; i++)
	{
		crow = img.row(i);

		for(int j = rectSize.Left -1; j < rectSize.Width +1; j++)
		{
			if(crow.at<cv::Vec3b>(0,j).val[0] > 0 )
			{
				ImgMatrix[i][j] = 0;
			}
			else
			{
				ImgMatrix[i][j] = 1;
			}

		}
	}
}

void ClassZSThin::initaa()
{
	aa.resize(8);

	for(int i = 0; i <= aa.size(); ++i)
	{
		aa[i] =0;
	}
}

void ClassZSThin::filterPixel(cv::Mat &img)
{
	imgBinar(img);
	initaa();

	for(int i = 1; i <= img.cols -2; i++)
	{
		for(int j = 1; j <= img.rows -2; j++)
		{
			int B = getEnvPixels(j, i);
						
			if(B == 0)
			{
				img.at<cv::Vec3b>(j,i).val[0] = 255;
				img.at<cv::Vec3b>(j,i).val[1] = 255;
				img.at<cv::Vec3b>(j,i).val[2] = 255;
			}
	
		}
	}
}

void ClassZSThin::ThcreateImgMatrix(cv::Mat &img)
{
	imgBinar(img);
	initaa();

	pixelDell = 1;

	while(pixelDell > 0)
	{
		ThzsScelet();
	}

	for(int i = rectSize.Up -1; i < rectSize.Height+1; i++)
	{
		for(int j = rectSize.Left -1; j < rectSize.Width+1; j++)
		{
			if(ImgMatrix[i][j] == 1)
			{
				img.at<cv::Vec3b>(i,j).val[0] = 0;
				img.at<cv::Vec3b>(i,j).val[1] = 0;
				img.at<cv::Vec3b>(i,j).val[2] = 0;

			}
		}
	}

	ThReWriteImg(img);
}



ClassZSThin::~ClassZSThin(void)
{
}