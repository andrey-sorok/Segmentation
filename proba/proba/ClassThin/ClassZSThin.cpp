#include "ClassZSThin.h"


ClassZSThin::ClassZSThin(vector<vector<unsigned int>> Mtx)
{

	ImgMatrix.resize(Mtx.size());

	int size = ImgMatrix.size();

	for(int i = 0; i < size; i++)
	{
		ImgMatrix[i].resize(Mtx[i].size());
	}

	ImgMatrix = Mtx;

	myThin(ImgMatrix.size(),ImgMatrix[0].size());

	for(int i = 0; i < ImgMatrix.size(); ++i)
	{
		for(int j = 0; j < ImgMatrix[i].size(); ++j)
		{
			if(ImgMatrix[i][j] == 0)
			{
				ImgMatrix[i][j] = 1; 
			}
			else
			{
				if(ImgMatrix[i][j] == 1)
				{
					ImgMatrix[i][j] = 0; 
				}
			}
		}
	}

}

int ClassZSThin::ReWriteImg()
{
	
	for(int i = 0; i <= this->img.cols -1; i++)
	{
		for(int j = 0; j <= this->img.rows -1; j++)
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

	return 1;

}

inline int Check(int a, int b)
{
	if( (a == 0) && (b == 1))
	{
		return 1;
	}

	return 0;
}

int ClassZSThin::Gap(int i, int j)
{
	int A = 0;

	z = 0;
	
	//x2 && x3
	A = A + Check(this->ImgMatrix[i-1][j], this->ImgMatrix[i-1][j+1]);

	//x3 && x4
	A = A + Check(this->ImgMatrix[i-1][j+1], this->ImgMatrix[i][j+1]);

	//x4 && x5
	A = A + Check(this->ImgMatrix[i][j+1], this->ImgMatrix[i+1][j+1]);

	//x5 && x6
	A = A + Check(this->ImgMatrix[i+1][j+1], this->ImgMatrix[i+1][j]);

	//x6 && x7
	A = A + Check(this->ImgMatrix[i+1][j], this->ImgMatrix[i+1][j-1]);

	//x7 && x8
	A = A + Check(this->ImgMatrix[i+1][j-1], this->ImgMatrix[i][j-1]);

	//x8 && x9
	A = A + Check(this->ImgMatrix[i][j-1], this->ImgMatrix[i-1][j-1]);

	//x9 && x2
	A = A + Check(this->ImgMatrix[i-1][j-1], this->ImgMatrix[i-1][j]);

	return A;
}

void ClassZSThin::myThin(int Width, int Height)
{
	
	int B = 0;
	int A = 0;

	for(int i = 1; i < Height; i++)
	{
		
		for(int j = 1; j < Width; j++)
		{
			if(ImgMatrix[i][j] == 1)
			{
				//x1 = p(i,j)
				
				//B
				//x2
				if(ImgMatrix[i-1][j] == 1) { B++; }

				//x3
				if(ImgMatrix[i-1][j+1] == 1) { B++; }

				//x4
				if(ImgMatrix[i][j+1] == 1) { B++; }

				//x5
				if(ImgMatrix[i+1][j+1] == 1) { B++; }

				//x6
				if(ImgMatrix[i+1][j] == 1) { B++; }

				//x7
				if(ImgMatrix[i+1][j-1] == 1) { B++; }

				//x8
				if(ImgMatrix[i][j-1] == 1) { B++; }

				//x9
				if(ImgMatrix[i-1][j-1] == 1) { B++; }

				//A
				A = Gap(i, j);

				//c
				int tmp_1 = ((ImgMatrix[i-1][j])*(ImgMatrix[i][j+1])*(ImgMatrix[i+1][j]));
	
				bool IsNul_1 = false;
				if (tmp_1 == 0)
				{
					IsNul_1 = true;
				}

				//d
				int tmp_2 =((ImgMatrix[i][j+1])*(ImgMatrix[i+1][j])*(ImgMatrix[i][j-1]));

				bool IsNul_2 = false;
				if (tmp_2 == 0)
				{
					IsNul_2 = true;
					
				}

				if((A == 1))
				{
					if ((2 <= B)&&( B <= 6))
					{
						if((IsNul_1 && IsNul_2))
						{
							ImgMatrix[i][j] = 0;
							Iter++;
						}
					}
				}

				//c'
				tmp_1 = ((this->ImgMatrix[i-1][j])*(this->ImgMatrix[i][j+1])*(this->ImgMatrix[i][j-1]));

				IsNul_1 = false;
				if (tmp_1 == 0)
				{
					IsNul_1 = true;
				}
				
				//d'
				tmp_2 =((ImgMatrix[i-1][j])*(ImgMatrix[i+1][j])*(ImgMatrix[i][j-1]));
				
				IsNul_2 = false;
				if (tmp_2 == 0)
				{
					IsNul_2 = true;
				}

				if((A == 1))
				{
					if ((2 <= B)&&( B <= 6))
					{
						if((IsNul_1 && IsNul_2))
						{
							ImgMatrix[i][j] = 0;
							Iter++;
						}
					}
				}

				A = 0;
				B = 0;
			}
			
		}

	}

}

void ClassZSThin::createImgMatrix()
{

	this->Iter = 0;

	int dfA = 0, dfB = 0, dfC = 0, dfD = 0;
	int dfG = 0, dfV = 0;

	int Width = this->img.cols -1;
	int Height = this->img.rows -1;

	int rowsCount;

	cv::Vec3b clr;

	vector<int> dFs;

	for(int i = 0; i < Height+1; i++)
	{
		crow = this->img.row(i);

		for(int j = 0; j < Width+1; j++)
		{
			if(crow.at<cv::Vec3b>(0,j).val[0] > 0)
			{
				this->ImgMatrix[i][j] = 0;
			}
			else
			{
				this->ImgMatrix[i][j] = 1;
			}

		}
	}

	myThin(Width, Height);

	for(int i = 0; i < Height; i++)
	{	

		for(int j = 0; j < Width; j++)
		{
			if(this->ImgMatrix[i][j] == 1)
			{
				this->img.at<cv::Vec3b>(i,j).val[0] = 0;
				this->img.at<cv::Vec3b>(i,j).val[1] = 0;
				this->img.at<cv::Vec3b>(i,j).val[2] = 0;

			}
		}
	}

	ReWriteImg();

}


ClassZSThin::~ClassZSThin(void)
{
}