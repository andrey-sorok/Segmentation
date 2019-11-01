#include "ClassMyThin.h"
#include "TDataSource.h"


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

bool ClassZSThin::pixelCheck(int i, int j)
{
//Corners
	//1
	if((i == rectSize.Up)&&(j == rectSize.Left))
	{
		//==4
		aa[0] = ImgMatrix[i+1][j+1];
		//==5
		aa[1] = ImgMatrix[i+1][j];
		
		aa[2] = 0;
		
		aa[3] = ImgMatrix[i][j+1];
		aa[4] = ImgMatrix[i+1][j+1];
		aa[5] = ImgMatrix[i+1][j];
		
		aa[6] = 0;
		//==3
		aa[7] = ImgMatrix[i][j+1];
		
		return 1;
	}
	//2
	if((i == rectSize.Up)&&(j == rectSize.Width))
	{
		aa[0] = 0;
		//==5
		aa[1] = ImgMatrix[i+1][j];
		//==6
		aa[2] = ImgMatrix[i+1][j-1];
		//==7
		aa[3] = ImgMatrix[i][j-1];
	
		aa[4] = 0;
		
		aa[5] = ImgMatrix[i+1][j];
		aa[6] = ImgMatrix[i+1][j-1];
		aa[7] = ImgMatrix[i][j-1];

		return 1;
	}
	//3
	if((i == rectSize.Height)&&(j == rectSize.Width))
	{
		aa[0] = ImgMatrix[i-1][j-1];
		aa[1] = ImgMatrix[i-1][j];
		
		aa[2] = 0;
		//==7
		aa[3] = ImgMatrix[i][j-1];
		//==0
		aa[4] = ImgMatrix[i-1][j-1];
		//==1
		aa[5] = ImgMatrix[i-1][j-1];

		aa[6] = 0;
		
		aa[7] = ImgMatrix[i][j-1];

		return 1;
	}
	//4
	if((i == rectSize.Height)&&(j == rectSize.Left))
	{
		aa[0] = 0;
		
		aa[1] = ImgMatrix[i-1][j];
		aa[2] = ImgMatrix[i-1][j+1];
		aa[3] = ImgMatrix[i][j+1];
	
		aa[4] = 0;
		//==1
		aa[5] = ImgMatrix[i-1][j];
		//==2
		aa[6] = ImgMatrix[i-1][j+1];
		//==3
		aa[7] = ImgMatrix[i][j+1];
		return 1;

	}
//end_Corners

//Edges
	//Up
	if((i == rectSize.Up)&&(j > rectSize.Left)&&(j < rectSize.Width ))
	{
		//==6
		aa[0] = ImgMatrix[i+1][j-1];
		//==5
		aa[1] = ImgMatrix[i+1][j];
		//==4
		aa[2] = ImgMatrix[i+1][j+1];
		
		aa[3] = ImgMatrix[i][j+1];
		aa[4] = ImgMatrix[i+1][j+1];
		aa[5] = ImgMatrix[i+1][j];
		aa[6] = ImgMatrix[i+1][j-1];
		aa[7] = ImgMatrix[i][j-1];

		return 1;
	}
	//Right
	if((j == rectSize.Width)&&(i > rectSize.Up)&&(i < rectSize.Height ))
	{
		aa[0] = ImgMatrix[i-1][j-1];
		aa[1] = ImgMatrix[i-1][j];
		//==0
		aa[2] = ImgMatrix[i+1][j-1];
		//==7
		aa[3] = ImgMatrix[i][j+1];
		//==6
		aa[4] = ImgMatrix[i+1][j+1];
		
		aa[5] = ImgMatrix[i+1][j];
		aa[6] = ImgMatrix[i+1][j-1];
		aa[7] = ImgMatrix[i][j-1];
		
		return 1;
	}
	//Down
	if((i == rectSize.Height)&&(j > rectSize.Left)&&(j < rectSize.Width ))
	{
		aa[0] = ImgMatrix[i-1][j-1];
		aa[1] = ImgMatrix[i-1][j];
		aa[2] = ImgMatrix[i-1][j+1];
		aa[3] = ImgMatrix[i][j+1];

		//==2
		aa[4] = ImgMatrix[i-1][j+1];;
		//==1
		aa[5] = ImgMatrix[i-1][j];
		//==0
		aa[6] = ImgMatrix[i-1][j-1];

		aa[7] = ImgMatrix[i][j-1];

		return 1;
	}
	//Left
	if((j == rectSize.Left)&&(i > rectSize.Up)&&(i < rectSize.Height ))
	{
		//==2
		aa[0] = ImgMatrix[i-1][j+1];
		
		aa[1] = ImgMatrix[i-1][j];
		aa[2] = ImgMatrix[i-1][j+1];
		aa[3] = ImgMatrix[i][j+1];
		aa[4] = ImgMatrix[i+1][j+1];
		aa[5] = ImgMatrix[i+1][j];
		//==4
		aa[6] = ImgMatrix[i+1][j+1];
		//==3
		aa[7] = ImgMatrix[i][j+1];

		return 1;
	}
//end_Edges

}

int ClassZSThin::getEnvPixels(int i, int j)
{
//	cout << "i: " << i << endl;
//	cout << "j: " << j << endl;

	//bool isCheck = 0;
   // isCheck = pixelCheck(i, j);
	//cout << "isCheck: " << isCheck << endl;

	//if(!isCheck)
	{

		aa[0] = ImgMatrix[i-1][j-1];
		aa[1] = ImgMatrix[i-1][j];

		aa[2] = ImgMatrix[i-1][j+1];
		aa[3] = ImgMatrix[i][j+1];
	
		aa[4] = ImgMatrix[i+1][j+1];
		aa[5] = ImgMatrix[i+1][j];

		aa[6] = ImgMatrix[i+1][j-1];
		aa[7] = ImgMatrix[i][j-1];
	}
	
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
				pixelDell = 1;
			}
		}
	}
}

void ClassZSThin::ThzsScelet()
{
	pixelDell = 0;

//Fist_iteration
	for(int i = rectSize.Up; i < rectSize.Height; i++)
	{
		for(int j = rectSize.Left; j < rectSize.Width; j++)
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

				if((A == 1)&&((B >= 2)||(B <= 6))&&(p1 == 0)&&(p2 == 0))
				{
					ImgMatrix_2[i][j] = 1;
				}
				else
				{
					ImgMatrix_2[i][j] = 0;
				}	
			}

			
	}

//end Fist_iteration

	dellBrdPixels();

	for(int i = rectSize.Up -1; i < rectSize.Height +1; ++i)
	{
		for(int j = rectSize.Left -1; j < rectSize.Width +1; ++j)
		{
			ImgMatrix_2[i][j] = 0; 

		}
	}



//Second_iteration
	for(int i = rectSize.Up; i < rectSize.Height; i++)
	{
		for(int j = rectSize.Left; j < rectSize.Width; j++)
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

				if((A == 1)&&((B >= 2)||(B <= 6))&&(p1 == 0)&&(p2 == 0))
				{
					ImgMatrix_2[i][j] = 1;
				}
				else
				{
					ImgMatrix_2[i][j] = 0;
				}	
			}
			
	}
//end Second_iteration

	dellBrdPixels();
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

	while(pixelDell)
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