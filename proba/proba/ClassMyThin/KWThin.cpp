#include "KWThin.h"

#include "TDataSource.h"

KWThin::KWThin(cv::Mat & img): ClassZSThin(img)
{

}

//One Chanel IMG //WHITE Contours
void KWThin::dellMinContours(cv::Mat& img)
{
	invertBinarImg(img);

	vector<vector<cv::Point> > contour;
	vector<cv::Vec4i> hierarchy;

	cv::findContours(img, contour, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE); 

	int tmpl = 0;

	int max = 0;

	for(int idx = 0; idx < (int)hierarchy.size(); ++idx)
    {
		if (max < contour[idx].size())
		{
			max = contour[idx].size();
		}
	}
	
	cout << "max: " << max << endl;

	tmpl = max/2;

	cout << "tmpl: " << tmpl << endl;

	cout << "tmpl*k: " << tmpl*brd << endl;

	tmpl = 1200;

	cv::Mat tmp = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
	cv::Scalar color = ( 255, 255, 255 );

	cv::Mat imtmp = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

	for(int idx = 0; idx < (int)hierarchy.size(); ++idx)
    {
		//if (cv::arcLength(contour[idx], false) > 500)
		if(contour[idx].size() > (int)(tmpl))
		{
			cv::drawContours(tmp, contour, idx, color, 0, 8, hierarchy, 1);

			//cout << contour[idx].size() << endl ;
		}    
    }

	invertBinarImg(tmp);

	img = tmp;
}

void  KWThin::invertBinarImg(cv::Mat img)
{
	for(int i = 0 ; i < img.rows ; i++)
	{
		for(int j = 0 ; j < img.cols ; j++)
		{
			if(img.at<uchar>(i,j) > 0)
			{
				img.at<uchar>(i,j) = 0;
			}	
			else
			{
				img.at<uchar>(i,j) = 255;
				
			}	
		}
	}

}

void KWThin::inclinedLine()
{
	pixelDell = 0;

	for(int i = rectSize.Up; i <= rectSize.Height; i++)
	{
		for(int j = rectSize.Left; j <= rectSize.Width; j++)
		{
			if(ImgMatrix[i][j] == 0)
			{
				ImgMatrix_2[i][j] = 0;
				continue;
			}
				int tmp = getEnvPixels(i, j);
				
				bool isOne = aa[0] && aa[7] && aa[5];// && aa[2];	
				bool isTwo = aa[2] && aa[3] && aa[5];//  && aa[0];		
				bool isThree = aa[4] && aa[5] && aa[7];//  && aa[2];		
				bool isFour = aa[3] && aa[5] && aa[6];// && aa[0];

				if(((isOne == 1)&&(aa[2] == 0))||((isTwo == 1)&&(aa[0] == 0))||((isThree ==1)&&(aa[2] == 0))||((isFour == 1)&&(aa[0]==0)))
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
}

void KWThin::kwScelets()
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

				bool isB = (B >= 3)&&(B <= 6);

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

void KWThin::createThinMtx(cv::Mat& img)
{
	imgBinar(img);
	initaa();

	pixelDell = 1;

	while(pixelDell)
	{
		kwScelets();
	}

	pixelDell = 1;

	while(pixelDell)
	{
		inclinedLine();
	}

	for(int i = rectSize.Up -1; i <= rectSize.Height+1; i++)
	{
		for(int j = rectSize.Left -1; j <= rectSize.Width+1; j++)
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

KWThin::~KWThin(void)
{
}
