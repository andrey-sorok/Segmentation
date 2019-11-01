
#include "ClassQTree.h"

#include "ClassBorder\ClassBorder.h"

#include "Data\TDataSource.h"

ClassQTree::ClassQTree()
{
	QTree = NULL;
}

//test

void ClassQTree::mergeInArray(QTreeStruct*& tQTree)
{
	while (tQTree->NW != NULL)
	{
		tQTree = tQTree->NW;
		
		
	}

	tQTree->visited = 1;

	sgmArr.push_back(tQTree);

	cout << sgmArr.size()  << endl;

	bool isOut = 0;

	while (isOut != 1)
	{
		stack<QTreeStruct*> inWait;
		QTreeStruct* tmp = sgmArr[sgmArr.size()-1];

		

	}


}

void  ClassQTree::mergeQTree(QTreeStruct*& tQTree)
{
	if (tQTree == NULL)
	{ 
		return; 
	}

	cout << tQTree->Child << endl;

	if ((tQTree->Child == 0)&&(tQTree->visited == 0))
	{
		int tmpDst = 0;
		//North
		if (tQTree->ptrNorthID != NULL)
		{
			tmpDst = (int)checkEvcDst (tQTree->AvgColor, tQTree->ptrNorthID->AvgColor);

			cout << tmpDst << endl;
			if (tmpDst <= mrgT)
			{
				tQTree->ptrNorthID->AvgColor = tQTree->AvgColor;
				tQTree->ptrNorthID->visited;
			}
		}
		//East
		if (tQTree->ptrEastID != NULL)
		{
			tmpDst = (int)checkEvcDst (tQTree->AvgColor, tQTree->ptrEastID->AvgColor);

			cout << tmpDst << endl;
			if (tmpDst <= mrgT)
			{
				tQTree->ptrEastID->AvgColor = tQTree->AvgColor;
				tQTree->ptrEastID->visited;
			}
		}
		//South
		if (tQTree->ptrSouthID != NULL)
		{
			tmpDst =(int)checkEvcDst (tQTree->AvgColor, tQTree->ptrSouthID->AvgColor);

			cout << tmpDst << endl;
			if (tmpDst <= mrgT)
			{
				tQTree->ptrSouthID->AvgColor = tQTree->AvgColor;
				tQTree->ptrEastID->visited;
			}
		}
		//West
		if (tQTree->ptrWestID != NULL)
		{
			tmpDst = (int)checkEvcDst (tQTree->AvgColor, tQTree->ptrWestID->AvgColor);

			cout << tmpDst << endl;
			if (tmpDst <= mrgT)
			{
				tQTree->ptrWestID->AvgColor = tQTree->AvgColor;
				tQTree->ptrWestID->visited;
			}
		}

		tQTree->visited = 1;
	}
	else
	{
		mergeQTree (tQTree->NW);
		mergeQTree (tQTree->NE);
		mergeQTree (tQTree->SW);
		mergeQTree (tQTree->SE);
	}

}

void ClassQTree::findeNgbr(QTreeStruct*& Node, QTreeStruct*& tQTree)
{
	if (tQTree == NULL)
	{ 
		return; 
	}

	if (tQTree->isEnd == 0)
	{
		findeNgbr (Node, tQTree->NW);
		findeNgbr (Node, tQTree->NE);
		findeNgbr (Node, tQTree->SW);
		findeNgbr (Node, tQTree->SE);
	}
	else
	{
		//1
		if ((Node->Rect.Right == tQTree->Rect.Left -1)&&
			(Node->Rect.Top >= tQTree->Rect.Top)&&	//
			(Node->Rect.Bottom <= tQTree->Rect.Bottom))	//
		{
			int dst = (int)checkEvcDst(Node->AvgColor, tQTree->AvgColor);
			//cout << "dst: " << dst << endl;
			if (dst < mrgT)
			{
				tQTree->AvgColor = Node->AvgColor;
			}
		}

		//2
		if ((Node->Rect.Left == tQTree->Rect.Right +1)&&
			(Node->Rect.Top <= tQTree->Rect.Top)&&
			(Node->Rect.Bottom >= tQTree->Rect.Bottom))
		{
			int dst = (int)checkEvcDst(Node->AvgColor, tQTree->AvgColor);
			//cout << "dst: " << dst << endl;
			if (dst < mrgT)
			{
				tQTree->AvgColor = Node->AvgColor;
			}
		}

		//3
		if ((Node->Rect.Right ==  tQTree->Rect.Left -1)&&
			(Node->Rect.Top <=  tQTree->Rect.Top)&&
			(Node->Rect.Bottom >=  tQTree->Rect.Bottom))
		{
			int dst = (int)checkEvcDst(Node->AvgColor, tQTree->AvgColor);
			//cout << "dst: " << dst << endl;
			if (dst < mrgT)
			{
				tQTree->AvgColor = Node->AvgColor;
			}
		}
						
		//4
		if ((Node->Rect.Left == tQTree->Rect.Right +1)&&
			(Node->Rect.Top >= tQTree->Rect.Top)&&			
			(Node->Rect.Bottom <= tQTree->Rect.Bottom))
		{
			int dst = (int)checkEvcDst(Node->AvgColor, tQTree->AvgColor);
			//cout << "dst: " << dst << endl;
			if (dst < mrgT)
			{
				tQTree->AvgColor = Node->AvgColor;
			}
		}

		//5
		if ((Node->Rect.Bottom == tQTree->Rect.Top -1)&&
			(Node->Rect.Left >= tQTree->Rect.Left)&&
			(Node->Rect.Right <= tQTree->Rect.Right))
		{
			int dst = (int)checkEvcDst(Node->AvgColor, tQTree->AvgColor);
			//cout << "dst: " << dst << endl;
			if (dst < mrgT)
			{
				tQTree->AvgColor = Node->AvgColor;
			}
		}

		//6
		if ((Node->Rect.Top == tQTree->Rect.Bottom +1)&&
			(Node->Rect.Left <= tQTree->Rect.Left)&&
			(Node->Rect.Right >= tQTree->Rect.Right))
		{
			int dst = (int)checkEvcDst(Node->AvgColor, tQTree->AvgColor);
			//cout << "dst: " << dst << endl;
			if (dst < mrgT)
			{
				tQTree->AvgColor = Node->AvgColor;
			}
		}

		//7
		if ((Node->Rect.Bottom == tQTree->Rect.Top - 1)&&
			(Node->Rect.Left <= tQTree->Rect.Left)&&
			(Node->Rect.Right >= tQTree->Rect.Right))
		{
			int dst = (int)checkEvcDst(Node->AvgColor, tQTree->AvgColor);
			//cout << "dst: " << dst << endl;
			if (dst < mrgT)
			{
				tQTree->AvgColor = Node->AvgColor;
			}
		}

		//8
		if ((Node->Rect.Top == tQTree->Rect.Bottom +1)&&
			(Node->Rect.Left >= tQTree->Rect.Left)&&
			(Node->Rect.Right <= tQTree->Rect.Right))
		{
			int dst = (int)checkEvcDst(Node->AvgColor, tQTree->AvgColor);
			//cout << "dst: " << dst << endl;
			if (dst < mrgT)
			{
				tQTree->AvgColor = Node->AvgColor;
			}
		}
	
	}	


}

void ClassQTree::compareNgbr(QTreeStruct*& tQTree)
{
	if (tQTree == NULL)
	{ 
		return; 
	}

	//cout << tQTree->Child << endl;
//	cout << "RegionID: " << tQTree->RegionID << endl;
	
	if (tQTree->isEnd == 1)
	{
		if (tQTree->visited == 0)
		{
			findeNgbr (tQTree, QTree);
			//tQTree->visited = 1;	
		}
	}
	else
	{
		compareNgbr (tQTree->NW);
		compareNgbr (tQTree->NE);
		compareNgbr (tQTree->SW);
		compareNgbr (tQTree->SE);
	}

}

//end_test

void ClassQTree::listArrTest()
{
	cout << "y" << endl;

	listArr tmp;

	tmp.listAvgColor[0] = 10;
	tmp.listAvgColor[1] = 20;
	tmp.listAvgColor[2] = 30;

	cout << tmp.listAvgColor[0] << endl;

	tmp.Node.push_back(QTree);

	cout << tmp.Node[0]->Child <<endl;

	treeLists.push_back(tmp);

	vector<listArr>::iterator it = treeLists.begin();
	while(it != treeLists.end())
	{
		cout << it->Node[0]->Child << endl;
		
		++it;
	}
}

void ClassQTree::InitQTree(cv::Mat timg)
{

	if(QTree == NULL)
	{
		QTree = new (QTreeStruct);
	}
	
	QTree->Rect.Left = 0;
	QTree->Rect.Right = timg.cols -1;
	QTree->Rect.Top = 0;
	QTree->Rect.Bottom = timg.rows -1;
		
	QTree->Level = 0;

	QTree->RegionID= 0;
	QTree->ChildNum = 0;

	QTree->PartitionID = 0;

//	QTree->Field = "I";

	QTree->MaxPoint = timg.rows*timg.cols;

	QTree->AvgColor[0] = 0;
	QTree->AvgColor[1] = 0;
	QTree->AvgColor[2] = 0;

	QTree->numBorder = 0;

	QTree->Child = true;
	QTree->visited = false;

	QTree->isEnd = false;

	img = timg.clone();
	//cin >> this->T;

	T = TT;

	//this->QTree->ngbr = new(QTreeStruct);;
	
	QTree->NW = new(QTreeStruct);
	QTree->NE = new(QTreeStruct);
	QTree->SW = new(QTreeStruct);
	QTree->SE = new(QTreeStruct);
	
	cout << endl;

	cout << "Left: " << QTree->Rect.Left << endl;
	cout << "Right: " << QTree->Rect.Right << endl;
	cout << "Top: " << QTree->Rect.Top << endl;
	cout << "Buttom: " << QTree->Rect.Bottom << endl;

	cout << "Color Average: " << int(QTree->AvgColor.val[0])<< ";" << int(QTree->AvgColor.val[1]) << ";" << int(QTree->AvgColor.val[2]) << endl;

	cout << "_________" << endl;

}

float e;

inline int dClr(int a, int b)
{
	return (a - b)*(a - b);
}

void ClassQTree::dRGBCalc(int i, int j)
{
	int minR = 255, minG = 255, minB = 255;
	int maxR = 0, maxG = 0, maxB = 0;

	for( int m = -1; m <= 1; m++)
	{
		//0
		//minR
		if(this->img.at<cv::Vec3b>(i-1,j+m).val[2] < minR)
		{
			minR = this->img.at<cv::Vec3b>(i-1,j+m).val[2];
		}
		//maxR
		if(this->img.at<cv::Vec3b>(i-1,j+m).val[2] > maxR)
		{
			maxR = this->img.at<cv::Vec3b>(i-1,j+m).val[2];
		}

		//minG
		if(this->img.at<cv::Vec3b>(i-1,j+m).val[1] < minG)
		{
			minG = this->img.at<cv::Vec3b>(i-1,j+m).val[1];
		}
		//maxG
		if(this->img.at<cv::Vec3b>(i-1,j+m).val[1] > maxG)
		{
			maxG = this->img.at<cv::Vec3b>(i-1,j+m).val[1];
		}
		//minB
		if(this->img.at<cv::Vec3b>(i-1,j+m).val[0] < minB)
		{
			minB = this->img.at<cv::Vec3b>(i-1,j+m).val[0];
		}
		//maxB
		if(this->img.at<cv::Vec3b>(i-1,j+m).val[0] > maxB)
		{
			maxB = this->img.at<cv::Vec3b>(i-1,j+m).val[0];
		}

		//1
		if(this->img.at<cv::Vec3b>(i,j+m).val[2] < minR)
		{
			minR = this->img.at<cv::Vec3b>(i,j+m).val[2];
		}

		//maxR
		if(this->img.at<cv::Vec3b>(i,j+m).val[2] > maxR)
		{
			maxR = this->img.at<cv::Vec3b>(i,j+m).val[2];
		}

		if(this->img.at<cv::Vec3b>(i,j+m).val[1] < minG)
		{
			minG = this->img.at<cv::Vec3b>(i,j+m).val[1];
		}
		//maxG
		if(this->img.at<cv::Vec3b>(i,j+m).val[1] > maxG)
		{
			maxG = this->img.at<cv::Vec3b>(i,j+m).val[1];
		}
		
		if(this->img.at<cv::Vec3b>(i,j+m).val[0] < minB)
		{
			minB = this->img.at<cv::Vec3b>(i,j+m).val[0];
		}
		//maxB
		if(this->img.at<cv::Vec3b>(i,j+m).val[0] > maxB)
		{
			maxB = this->img.at<cv::Vec3b>(i,j+m).val[0];
		}

		//2
		if(this->img.at<cv::Vec3b>(i+1,j+m).val[2] < minR)
		{
			minR = this->img.at<cv::Vec3b>(i+1,j+m).val[2];
		}
		//maxR
		if(this->img.at<cv::Vec3b>(i+1,j+m).val[2] > maxR)
		{
			maxR = this->img.at<cv::Vec3b>(i+1,j+m).val[2];
		}

		if(this->img.at<cv::Vec3b>(i+1,j+m).val[1] < minG)
		{
			minG = this->img.at<cv::Vec3b>(i+1,j+m).val[1];
		}
		//maxG
		if(this->img.at<cv::Vec3b>(i+1,j+m).val[1] > maxG)
		{
			maxG = this->img.at<cv::Vec3b>(i+1,j+m).val[1];
		}
		
		if(this->img.at<cv::Vec3b>(i+1,j+m).val[0] < minB)
		{
			minB = this->img.at<cv::Vec3b>(i+1,j+m).val[0];
		}
		//maxB
		if(this->img.at<cv::Vec3b>(i+1,j+m).val[0] > maxB)
		{
			maxB = this->img.at<cv::Vec3b>(i+1,j+m).val[0];
		}
	}

	dR = abs(maxR - minR);
	dG = abs(maxG - minG);
	dB = abs(maxB - minB);
}

int ClassQTree::MatrixDif(int i, int j, const int (*Mtx)[3], cv::Vec3b cPoint)
{

	this->dRGBCalc(i, j);
	bool isNull = (dR == 0)&&(dG==0)&&(dB==0);
	
	if(!isNull)
	{

		bool trR = (dR > dG)&&(dR > dB);

		if(trR)
		{
			dR = 6;
			dG = 1;
			dB = 1;
		}

		bool trG = (dG > dR)&&(dG > dB);

		if(trG)
		{
			dR = 1;
			dG = 6;
			dB = 1;
		}
	
		bool trB = (dB > dG)&&(dB > dR);

		if(trB)
		{
			dR = 1;
			dG = 1;
			dB = 6;
		}


		tmpDF = 0;

		for(int m = -1; m <= 1; ++m)
		{
			tmpDF = tmpDF + (((dB * int(this->img.at<cv::Vec3b>(i-1,j+m).val[0])) 
						  +  (dG * int(this->img.at<cv::Vec3b>(i-1,j+m).val[1])) 
						  +  (dR * int(this->img.at<cv::Vec3b>(i-1,j+m).val[2])))*Mtx[0][m+1]);

			tmpDF = tmpDF + (((dB * int(this->img.at<cv::Vec3b>(i,j+m).val[0]) 
						 +  dG * int(this->img.at<cv::Vec3b>(i,j+m).val[1]) 
						 +	 dR * int(this->img.at<cv::Vec3b>(i,j+m).val[2])))*Mtx[1][m+1]);
	
			tmpDF = tmpDF + (((dB * int(this->img.at<cv::Vec3b>(i+1,j+m).val[0]) 
						 +  dG * int(this->img.at<cv::Vec3b>(i+1,j+m).val[1]) 
						 +  dR * int(this->img.at<cv::Vec3b>(i+1,j+m).val[2])))*Mtx[2][m+1]);

	
			tmpDF = abs(tmpDF);
		}

		return tmpDF;
	}
	else
	{
		return 0;
	}
}

void ClassQTree::getPseudoBrd(int Width, int Height)
{
	brdMatrix.resize(Height);
	
	for(int i = 0; i < Height; i++)
	{
		brdMatrix[i].resize(Width);
	}

	for(int i = 0; i < brdMatrix.size(); i++)
	{
		for(int j = 0; j < brdMatrix[i].size(); j++)
		{
			brdMatrix[i][j] = 1;

			cout << brdMatrix[i][j];
		}
		cout << endl;
	}

	

}


void ClassQTree::getBrdMatrix(cv::Mat &tmpMtx)
{

	//cv::namedWindow("input", CV_WINDOW_NORMAL);
	//cv::imshow("input", tmpMtx);


	brdMatrix.resize(tmpMtx.rows);

	int size = brdMatrix.size();

	for(int i = 0; i < size; i++)
	{
		brdMatrix[i].resize(tmpMtx.cols);
	}

	for(int i = 0; i < tmpMtx.rows; i++)
	{
		for(int j = 0; j < tmpMtx.cols; j++)
		{
			if((int)tmpMtx.at<uchar>(i,j) >0)
			{
				brdMatrix[i][j] = 1;
			}
			else
			{
				brdMatrix[i][j] = 0;
			}
		}
	}
}

void ClassQTree::OutNodeV(QTreeStruct Node)
{
//	cout << "Field: " << Node.Field << endl;

	if(Node.Child)
	{
		cout << "Child: True"  << endl;
	}
	else
	{
		cout << "Child: False"  << endl;
	}

	cout << "Visited: " << Node.visited << endl;

	if(Node.visited)
	{
		cout << "Visited: True"  << endl;
	}
	else
	{
		cout << "Visited: False"  << endl;
	}


	//cout << "Child: " << Node.Child << endl;

	//cout << "Visited : " << Node.visited << endl;
	
	cout << "Left: " << Node.Rect.Left << endl;
	cout << "Right: " << Node.Rect.Right << endl;
	cout << "Top: " << Node.Rect.Top << endl;
	cout << "Bottom: " << Node.Rect.Bottom << endl;

	cout << "Level: " << Node.Level << endl; 

	cout << "PrtitionID: " << Node.PartitionID << endl;

	cout << "ChildNumber: " << Node.ChildNum << endl;

	cout << "RegionID: " << Node.RegionID << endl;

	cout << "NorthID : " << Node.Env.NorthID << endl;
	cout << "EastID: " << Node.Env.EastID << endl;
	cout << "SouthID : " << Node.Env.SouthID << endl;
	cout << "WestID: " << Node.Env.WestID << endl;

	cout << "________" << endl;
}


inline int dXY(int a, int b)
{
	return (a - b)/2;
}

inline int diff(int a, int b)
{
	return a-b;
}
//Average color
cv::Vec3b ClassQTree::AvgClr(TRect TR)
{
	int RedSum = 0;
	int GreenSum = 0;
	int BlueSum = 0;

	for(unsigned long int y = TR.Top; y <= TR.Bottom; y++)
	{
		cv::Mat currow = this->img.row(y);
	
		for(unsigned long int x = TR.Left; x <= TR.Right; x++)
		{
		
			clr1 = currow.at<cv::Vec3b>(0,x);

			RedSum = RedSum + int(clr1.val[2]);
			GreenSum = GreenSum + int(clr1.val[1]);
			BlueSum = BlueSum + int(clr1.val[0]);

		}
	}
	int area = (abs(diff(TR.Bottom, TR.Top)) +1) * (abs(diff(TR.Right,TR.Left)) +1);

	//Average

 	clr1.val[2] = int(RedSum/area);
	clr1.val[1] = int(GreenSum/area);
	clr1.val[0] = int(BlueSum/area);

	return clr1;
}
//End_Average color

//Manhetten Distance
int ClassQTree::CheckMDst(QTreeStruct Node, TRect TR)
{

	int ColorSum = 0;

	for(unsigned long int y = Node.Rect.Top; y<= Node.Rect.Bottom; y++)
	{
		cv::Mat currow = this->img.row(y);
	
		for(unsigned long int x = TR.Left; x <= TR.Right; x++)
		{
			clr1 = currow.at<cv::Vec3b>(0,x);

			ColorSum = ColorSum + abs(diff(Node.AvgColor.val[0], clr1.val[0]));
			ColorSum = ColorSum + abs(diff(Node.AvgColor.val[1], clr1.val[1]));
			ColorSum = ColorSum + abs(diff(Node.AvgColor.val[2], clr1.val[2]));

		}

	}

	return  int(ColorSum / (3 * Node.MaxPoint));
}
//End_Manhetten Distance

//Table
char ClassQTree::cmpTable(char Q, int &Direct)
{
	char rtn;
	string tmps = tmps+Q;
	int tmpQ = atoi(tmps.c_str());

	string transit = transitMtx[Direct][tmpQ];
	if(transit.length() == 1)
	{
		rtn = transit[0];
		Direct = 0;
	}
	else
	{
		rtn = transit[0];
		char drt = transit[transit.length() -1];

		string sdrt = sdrt+drt;
		Direct = atoi(sdrt.c_str());
	}
	return rtn;
}

void ClassQTree::calcQNgbr(int Direct, Neighbor &Env, unsigned long int regionID)
{
	stringstream tmpStr;
	tmpStr << regionID;
	string strID = tmpStr.str();

	switch(Direct){
		//R
		case 1:
		{	
			if(Env.EastID != 0)
			{
				int tmpDirect = Direct;
				for(int i = strID.length() -1; i >= 0; --i)
				{
					strID[i] = cmpTable(strID[i], tmpDirect);
					Env.EastID = atoi(strID.c_str());
					
					if(tmpDirect == 0)
					{
						return;
					}
				}				
			}
			break;
		}
		//L
		case 2:
		{
			if(Env.WestID != 0)
			{
				int tmpDirect = Direct;
				for(int i = strID.length() -1; i >= 0; --i)
				{
					strID[i] = cmpTable(strID[i], tmpDirect);
					Env.WestID = atoi(strID.c_str());
					if(tmpDirect == 0)
					{
						return;
					}
				}
			}
			break;
		}
		//D
		case 3:
		{
			if(Env.SouthID != 0)
			{
				int tmpDirect = Direct;
				for(int i = strID.length() -1; i >= 0; --i)
				{
					strID[i] = cmpTable(strID[i], tmpDirect);
					Env.SouthID = atoi(strID.c_str());
					if(tmpDirect == 0)
					{
						return;
					}
				}

			}
			break;
		}
		//U
		case 4:
		{
			if(Env.NorthID != 0)
			{
				int tmpDirect = Direct;
				for(int i = strID.length() -1; i >= 0; --i)
				{
					strID[i] = cmpTable(strID[i], tmpDirect);
					Env.NorthID= atoi(strID.c_str());
					if(tmpDirect == 0)
					{
						return;
					}
				}

				
			}
			break;
		}		
	}
}

void ClassQTree::getNgbr(QTreeStruct *&tQTree)
{
	if (tQTree == NULL)
	{ 
		return; 
	}

	//cout << tQTree->Child << endl;
//	cout << "RegionID: " << tQTree->RegionID << endl;
	
	if (!tQTree->isEnd)
	{
		getNgbr (tQTree->NW);
		getNgbr (tQTree->NE);
		getNgbr (tQTree->SW);
		getNgbr (tQTree->SE);
	}
	else
	{
		calcQNgbr(1 ,tQTree->Env ,tQTree->RegionID);
		//cout << tQTree->Env.EastID << endl;
		
		calcQNgbr(2 ,tQTree->Env ,tQTree->RegionID);
		//cout << tQTree->Env.WestID << endl;

		calcQNgbr(3 ,tQTree->Env ,tQTree->RegionID);
		//cout << tQTree->Env.SouthID << endl;

		calcQNgbr(4 ,tQTree->Env ,tQTree->RegionID);
		//cout << tQTree->Env.NorthID << endl;

	}
}

//end_Table

int ClassQTree::findeCorrectNgbr(QTreeStruct*& tQTree, string target)
{
//	cout << "target: " << target.c_str() << endl;

	if (tQTree == NULL)
	{ 
//		cout << "rtnway: " << rtnway.c_str() << endl;
		return atoi (rtnway.c_str()); 
	}
	
	if ((target.length() == 0)&&(tQTree->Child == 1))
	{
//		cout << "rtnway: " << rtnway.c_str() << endl;

		tmpNode = NULL;

		rtnway.clear();
		return atoi (rtnway.c_str());
	}
	
	if ((target.length() == 0)&&(tQTree->Child == 0))
	{
//		cout << "rtnway: " << rtnway.c_str() << endl;
		
		tmpNode = tQTree;

		return atoi (rtnway.c_str());	
	}
	
//	cout << "tQTree->Child: " << tQTree->Child << endl;
	if (tQTree->Child == 1)
	{

		
		rtnway = rtnway + target[0];
//		cout << "rtnway: " << rtnway.c_str() << endl;

		string tmpway = tmpway + target[0];
//		cout << "tmpway: " << tmpway.c_str() << endl;
		
		target.erase (0,1);
//		cout << "target: " << target.c_str() << endl;
	
		int  intway = atoi (tmpway.c_str());

//		cout << "intway: " << intway << endl;

		switch (intway)
		{
			case 1:
				{			
					findeCorrectNgbr (tQTree->NW, target);
					break;
				}

			case 2:
				{
					findeCorrectNgbr (tQTree->NE, target);
					break;
				}
			case 3:
				{
					findeCorrectNgbr (tQTree->SW, target);
					break;
				}
			case 4:
				{
					findeCorrectNgbr (tQTree->SE, target);
					break;
				}
		}
	}
	else
	{
//		cout << "rtnway: " << rtnway.c_str() << endl;
		tmpNode = tQTree;

		return atoi (rtnway.c_str());
	}
	
//	cout << "rtnway: " << rtnway.c_str() << endl;
	return atoi (rtnway.c_str());
	
}


void ClassQTree::calcBigToSmall(QTreeStruct*& tQTree)
{

	if (tQTree == NULL)
	{ 
		return; 
	}

//	cout << "tQTree->RegionID: " << tQTree->RegionID << endl;
	if (tQTree->isEnd == 0)
	{
		calcBigToSmall (tQTree->NW);
		calcBigToSmall (tQTree->NE);
		calcBigToSmall (tQTree->SW);
		calcBigToSmall (tQTree->SE);
	}
	else
	{
//		cout << "tQTree->Env.NorthID: " << tQTree->Env.NorthID << endl;
		tQTree->ptrNorthID = NULL;
		tQTree->ptrEastID = NULL;
		tQTree->ptrSouthID = NULL;
		tQTree->ptrWestID = NULL;

		//North
		if (tQTree->Env.NorthID > 0)
		{
			stringstream sstr;
			sstr << tQTree->Env.NorthID;
			string str1;
			str1 = str1 + sstr.str();

			tmpNode = NULL;

			int rtn = findeCorrectNgbr (QTree, str1);
			rtnway.clear();

			tQTree->Env.NorthID = rtn;

			tQTree->ptrNorthID = tmpNode;

		}
		//East
//		cout << "tQTree->Env.EastID: " << tQTree->Env.EastID << endl;
		if (tQTree->Env.EastID > 0)
		{
			stringstream sstr;
			sstr << tQTree->Env.EastID;
			string str1;
			str1 = str1 + sstr.str();
			
			tmpNode = NULL;
			int rtn = findeCorrectNgbr (QTree, str1);
			rtnway.clear();

			tQTree->Env.EastID = rtn;

			tQTree->ptrEastID = tmpNode;
		}
		//South
//		cout << "tQTree->Env.SouthID: " << tQTree->Env.SouthID << endl;
		if (tQTree->Env.SouthID > 0)
		{
			stringstream sstr;
			sstr << tQTree->Env.SouthID;
			string str1;
			str1 = str1 + sstr.str();
			
			tmpNode = NULL;
			int rtn = findeCorrectNgbr (QTree, str1);
			rtnway.clear();

			tQTree->Env.SouthID= rtn;

			tQTree->ptrSouthID = tmpNode;
		}
		//West
//		cout << "tQTree->Env.WestID: " << tQTree->Env.WestID << endl;
		if (tQTree->Env.WestID > 0)
		{
			stringstream sstr;
			sstr << tQTree->Env.WestID;
			string str1;
			str1 = str1 + sstr.str();
			
			tmpNode = NULL;
			int rtn = findeCorrectNgbr (QTree, str1);
			rtnway.clear();

			tQTree->Env.WestID= rtn;

			tQTree->ptrWestID = tmpNode;
		}
	}
}

//Split
void ClassQTree::mrgDraw(QTreeStruct Node)
{
	//cout << Node.Rect.Bottom << endl;

	for(unsigned long int y = Node.Rect.Top; y <= Node.Rect.Bottom; y=y+1)
	{
		for(unsigned long int x = Node.Rect.Left; x <= Node.Rect.Right; x++)
		{
			img.at<cv::Vec3b>(y,x).val[0] = segmentColor[Node.segmentnumber].val[0];
			img.at<cv::Vec3b>(y,x).val[1] = segmentColor[Node.segmentnumber].val[1];
			img.at<cv::Vec3b>(y,x).val[2] = segmentColor[Node.segmentnumber].val[2];
			
		}
	}

	if ((Node.MaxPoint > 10))//&&((Node.MaxPoint < 200)))
	{
	
		int tmpy = (Node.Rect.Top + Node.Rect.Bottom)/2;
		int tmpx = (Node.Rect.Left + Node.Rect.Right)/2;
	
		img.at<cv::Vec3b>(tmpy,tmpx).val[0] = 255;
		img.at<cv::Vec3b>(tmpy,tmpx).val[1] = 255;
		img.at<cv::Vec3b>(tmpy,tmpx).val[2] = 255;
	}

}


void ClassQTree::rewriteMergeImg(QTreeStruct*& tQTree)
{

	if (tQTree == NULL)
	{ 
		return; 
	}

	//cout << tQTree->Child << endl;

	if (tQTree->isEnd == 1) 
	{
		mrgDraw(*tQTree);
	}
		
 	if (tQTree->NW != NULL)
	{
		rewriteMergeImg(tQTree->NW);
	}
		
	if (tQTree->NE != NULL)
	{
		rewriteMergeImg(tQTree->NE);
	}
    

	if (tQTree->SW != NULL)
	{
		rewriteMergeImg(tQTree->SW);
	}
   
	if (tQTree->SE != NULL)
	{ 
		rewriteMergeImg(tQTree->SE);
	}

}

void ClassQTree::calcColorDst (QTreeStruct*& tQTree)
{

	for (int i = 0; i < segmentColor.size(); ++i)
	{
		int dst = (int)checkEvcDst(tQTree->AvgColor, segmentColor[i]);

		//cout << "dst: " << dst  << endl;

		if (dst < mrgT)
		{
			//cout << "i: " << i << endl;
			tQTree->segmentnumber = i;
			return;
		}
	}

	//cout << "segmentColor.size() -1: " << segmentColor.size() -1 << endl;

	segmentColor.push_back(tQTree->AvgColor);
	tQTree->segmentnumber = segmentColor.size() - 1;
}

void ClassQTree::mergeRegions (QTreeStruct*& tQTree)
{
	if (tQTree == NULL)
	{ 
		return; 
	}

	if (tQTree->isEnd == 0)
	{
		mergeRegions (tQTree->NW);
		mergeRegions (tQTree->NE);
		mergeRegions (tQTree->SW);
		mergeRegions (tQTree->SE);
	}
	else
	{	
		//cout << "tQTree->isEnd: " << tQTree->isEnd  << endl;

		if (segmentColor.size() == 0)
		{
			segmentColor.push_back(tQTree->AvgColor);
			tQTree->segmentnumber = segmentColor.size() -1;
		}	
		else
		{
			calcColorDst (tQTree);
		}
	}
}

void ClassQTree::colorCompare (QTreeStruct& Node, QTreeStruct& Tree)
{
	int dst = (int)checkEvcDst(Node.AvgColor, Tree.AvgColor);

	//cout << "dst: " << dst  << endl;

	if (dst < mrgT)
	{
		Node.AvgColor = Tree.AvgColor ;
		Node.visited = 1;
	}	
	
	//cout << "tQTree->visited: " << tQTree->visited  << endl;

}

QTreeStruct* ClassQTree::getNgbrNode (QTreeStruct& Node, QTreeStruct*& tQTree, int target)
{
	if (tQTree == NULL)
	{ 
		//cout << "tmpNode: " << tmpNode  << endl;
		return tmpNode; 
	}

	if (tmpNode != NULL)
	{
		//cout << "tmpNode: " << tmpNode  << endl;
		return tmpNode; 
	}

	if ((tQTree->RegionID != target)||(tmpNode != NULL))
	{
		getNgbrNode (Node, tQTree->NW, target);
		getNgbrNode (Node, tQTree->NE, target);
		getNgbrNode (Node, tQTree->SW, target);
		getNgbrNode (Node, tQTree->SE, target);
	}
	else
	{
		tmpNode = tQTree;

		return tmpNode;		
	}

	//cout << "tmpNode: " << tmpNode  << endl;
	return tmpNode;
}

void ClassQTree::mergeNgbrRegions (QTreeStruct*& tQTree)
{
	if (tQTree == NULL)
	{ 
		return; 
	}

	if (tQTree->isEnd == 0)
	{
		mergeNgbrRegions (tQTree->NW);
		mergeNgbrRegions (tQTree->NE);
		mergeNgbrRegions (tQTree->SW);
		mergeNgbrRegions (tQTree->SE);
	}
	if (tQTree->isEnd == 1)
	{	
		//if (tQTree->visited == 0)
		{
			//cout << "tQTree->Env.NorthID: " << tQTree->Env.NorthID  << endl;
			if (tQTree->Env.NorthID > 0)
			{
				tmpNode = NULL;
				tmpNode  = getNgbrNode (*tQTree, QTree, tQTree->Env.NorthID);

				if (tmpNode->visited == 0)
				{
					//colorCompare (*tmpNode, *tQTree);

				}
			}
			//cout << "tQTree->Env.EastID: " << tQTree->Env.EastID  << endl;
			if (tQTree->Env.EastID > 0)
			{
				tmpNode = NULL;
				tmpNode  = getNgbrNode (*tQTree, QTree, tQTree->Env.EastID);

				if (tmpNode->visited == 0)
				{
					//colorCompare (*tmpNode, *tQTree);

				}
			//	cout << "tQTree->visited: " << tQTree->visited  << endl;
				//return;
			}
			//cout << " tQTree->Env.SouthID: " << tQTree->Env.SouthID  << endl;
			if (tQTree->Env.SouthID > 0)
			{
				tmpNode = NULL;
				tmpNode  = getNgbrNode (*tQTree, QTree, tQTree->Env.SouthID);

				if (tmpNode->visited == 0)
				{
					//colorCompare (*tmpNode, *tQTree);

				}
			//	cout << "tQTree->visited: " << tQTree->visited  << endl;
				//return;
			}
			//cout << " tQTree->Env.WestID: " << tQTree->Env.WestID  << endl;
			if (tQTree->Env.WestID> 0)
			{
				tmpNode = NULL;
				tmpNode  = getNgbrNode (*tQTree, QTree, tQTree->Env.WestID);

				if (tmpNode->visited == 0)
				{
					//colorCompare (*tmpNode, *tQTree);

				}
			//	cout << "tQTree->visited: " << tQTree->visited  << endl;
				//return;
			}
		}
	}
}
//end_Split

void ClassQTree::getBrdImage(QTreeStruct *&Node)
{
	//Top
	if(Node->Rect.Top == 0)
	{
		Node->Env.NorthID = 0;
	}
	//Right
	if(Node->Rect.Right == img.cols -1)
	{
		Node->Env.EastID = 0;
	}
	//Bottom
	if(Node->Rect.Bottom == img.rows -1)
	{
		Node->Env.SouthID = 0;
	}
	//Left
	if(Node->Rect.Left == 0)
	{
		Node->Env.WestID= 0;
	}
	
}

void  ClassQTree::getCornerImage(QTreeStruct *&Node)
{
	//LeftTop
	if((Node->Rect.Left == 0)&&(Node->Rect.Top == 0))
	{
		Node->Env.NorthID = 0;
		Node->Env.WestID = 0;
	}
	//RightTop
	if((Node->Rect.Right == img.cols -1)&&(Node->Rect.Top == 0))
	{
		Node->Env.NorthID = 0;
		Node->Env.EastID = 0;
	}
	//RightBottom
	if((Node->Rect.Right == img.cols -1)&&(Node->Rect.Bottom == img.rows -1))
	{
		Node->Env.SouthID= 0;
		Node->Env.EastID = 0;
	}
	//LeftBottom
	if((Node->Rect.Left == 0)&&(Node->Rect.Bottom == img.rows -1))
	{
		Node->Env.SouthID = 0;
		Node->Env.WestID = 0;
	}

}

void ClassQTree::calcBrdImage(QTreeStruct *&tQTree)
{
	if (tQTree == NULL)
	{ 
		return; 
	}
	
	if (!tQTree->isEnd)
	{
		calcBrdImage(tQTree->NW);
		calcBrdImage(tQTree->NE);
		calcBrdImage(tQTree->SW);
		calcBrdImage(tQTree->SE);
	}
	else
	{
		getCornerImage(tQTree);
		getBrdImage(tQTree);
		

	}

}


inline float quad(float x)
{
	return (x*x);	
}

template <typename T1, typename T2>
float ClassQTree::checkEvcDst (const T1& color1, const T2& color2)
{
	return sqrt(quad((float)diff(color1.val[0], color2.val[0]))+quad((float)diff(color1.val[1],color2.val[1]))+quad((float)diff(color1.val[2],color2.val[2])));
}

void ClassQTree::dellNode (QTreeStruct *&Node)
{ 
	if((Node->NE == NULL)&&(Node->SW == NULL))
	{
		if((Node->NW != NULL)&&(Node->SE != NULL))
		{
			if(checkEvcDst(Node->NW->AvgColor,Node->SE->AvgColor) < tInNode)
			{
				Node->NW = NULL;
				Node->SE = NULL;
				Node->Child = 0;
			}
		}
	}
	
	if((Node->NW == NULL)&&(Node->SE == NULL))
	{
		if((Node->NE != NULL)&&(Node->SW != NULL))
		{
			if(checkEvcDst(Node->NE->AvgColor,Node->SW->AvgColor) < tInNode)
			{
				Node->NE = NULL;
				Node->SW = NULL;
				Node->Child = 0;
			}
		}
	}

}

void ClassQTree::merge(QTreeStruct *&Node, QTreeStruct *&tQTree)
{
	
//	this->OutNodeV(*Node);
//	this->OutNodeV(*tQTree);
//	cout << "_________" << endl;


	switch (tQTree->ChildNum)
	{
		case 1:
		{
			if((Node->NE != NULL)&&(!Node->NW->visited)&&(!Node->NE->visited))
			{
				if(checkEvcDst(Node->NW->AvgColor,Node->NE->AvgColor) < tInNode)
				{
					Node->NW->MaxPoint = Node->NW->MaxPoint + Node->NE->MaxPoint;
					Node->NW->Rect.Right = Node->NE->Rect.Right;
					Node->NW->Rect.Bottom = Node->NE->Rect.Bottom;

					Node->NW->visited = 1;

					Node->NE = NULL;
					//cout << Node->NE << endl;
				}
				else
				{
					if((Node->SW != NULL)&&(!Node->SW->visited)&&(!Node->NW->visited))
					{
						if(checkEvcDst(Node->NW->AvgColor,Node->SW->AvgColor) < tInNode)
						{
							Node->NW->MaxPoint = Node->NW->MaxPoint + Node->SW->MaxPoint;
							Node->NW->Rect.Right = Node->SW->Rect.Right;
							Node->NW->Rect.Bottom = Node->SW->Rect.Bottom;

							Node->NW->visited = 1;

							Node->SW = NULL;

						//cout << Node->SW << endl;
						}
					}
				}
			}
			break;
		}
		case 2:
		{	
			if((Node->NW != NULL)&&(!Node->NW->visited)&&(!Node->NE->visited))
			{
				if(checkEvcDst(Node->NW->AvgColor,Node->NE->AvgColor) < tInNode)
				{
					Node->NW->MaxPoint = Node->NW->MaxPoint + Node->NE->MaxPoint;
					Node->NW->Rect.Right = Node->NE->Rect.Right;
					Node->NW->Rect.Bottom = Node->NE->Rect.Bottom;

					Node->NW->visited = 1;

					Node->NE = NULL;
					//cout << Node->NE << endl;
				}
				else
				{
					if((Node->SE != NULL)&&(!Node->SE->visited)&&(!Node->NE->visited))
					{
						if(checkEvcDst(Node->SE->AvgColor,Node->NE->AvgColor) < tInNode)
						{
							Node->NE->MaxPoint = Node->NE->MaxPoint + Node->SE->MaxPoint;
							Node->NE->Rect.Right = Node->SE->Rect.Right;
							Node->NE->Rect.Bottom = Node->SE->Rect.Bottom;

							Node->NE->visited = 1;

							Node->SE = NULL;
							//cout << Node->SE << endl;
						}
					}
				}
			}			
			break;
		}
		
		case 3:
		{
			if((Node->SE != NULL)&&(!Node->SW->visited)&&(!Node->SE->visited))
			{
				if(checkEvcDst(Node->SE->AvgColor,Node->SW->AvgColor) < tInNode)
				{
					Node->SE->MaxPoint = Node->SE->MaxPoint + Node->SW->MaxPoint;
					Node->SE->Rect.Left = Node->SW->Rect.Left;
					Node->SE->Rect.Top = Node->SW->Rect.Top;

					Node->SE->visited = 1;

					Node->SW = NULL;
					//cout << Node->SW << endl;

				}
				else
				{
					if((Node->NW != NULL)&&(!Node->NW->visited)&&(!Node->SW->visited))
					{
						if(checkEvcDst(Node->NW->AvgColor,Node->SW->AvgColor) < tInNode)
						{
							Node->SW->MaxPoint = Node->SW->MaxPoint + Node->NW->MaxPoint;
							Node->SW->Rect.Right = Node->NW->Rect.Right;
							Node->SW->Rect.Bottom = Node->NW->Rect.Bottom;

							Node->SW->visited = 1;

							Node->NW = NULL;
							//cout << Node->NW << endl;

						}
		
					}
				}
			}
			break;
		}	
		case 4:
		{
			
			if((Node->SW != NULL)&&(!Node->SW->visited)&&(!Node->SE->visited))
			{
				if(checkEvcDst(Node->SW->AvgColor,Node->SE->AvgColor) < tInNode)
				{
					Node->SE->MaxPoint = Node->NW->MaxPoint + Node->SW->MaxPoint;
					Node->SE->Rect.Left = Node->SW->Rect.Left;
					Node->SE->Rect.Top = Node->SW->Rect.Top;
					
					Node->SE->visited = 1;

					//cout << Node->SE->visited << endl;
					
					Node->SW = NULL;
					//cout << Node->SW << endl;

				}
				else
				{
					if((Node->NE != NULL)&&(!Node->NE->visited)&&(!Node->SE->visited))
					{
						if(checkEvcDst(Node->SE->AvgColor,Node->NE->AvgColor) < tInNode)
						{
							Node->SE->MaxPoint = Node->SE->MaxPoint + Node->NE->MaxPoint;
							Node->SE->Rect.Right = Node->NE->Rect.Right;
							Node->SE->Rect.Top = Node->NE->Rect.Top;

							Node->SE->visited = 1;

							//	cout << Node->SE->visited << endl;

							Node->NE = NULL;
							//cout << Node->NE << endl;

						}
					}
				}
			}
			break;
		}	
	}

	dellNode(Node);
}

void ClassQTree::mergeInNode(QTreeStruct *&Node, QTreeStruct *&tQTree)
{

	if (tQTree == NULL)
	{ 
		return; 
	}

//	cout << tQTree->Child << endl;
//	cout << "RegionID: " << tQTree->RegionID << endl;

	if ((tQTree->Child == false)&&(!tQTree->visited))
	{	

// detect border
		//if(tQTree->numBorder > borderInNode)
	//	{
			this->merge(Node, tQTree);
	//	}
	}

	if (tQTree != NULL)
	{
		mergeInNode(tQTree, tQTree->NW);
	}

	if (tQTree != NULL)
	{
		mergeInNode(tQTree, tQTree->NE);
	}

	if (tQTree != NULL)
	{
		mergeInNode(tQTree, tQTree->SW);
	}

	if (tQTree != NULL)
	{
		mergeInNode(tQTree, tQTree->SE);
	}
	
}
/*
void ClassQTree::mergeAdjacentNode(QTreeStruct *&tQTree)
{



}
*/



int ClassQTree::reflectdNgbr(QTreeStruct *&Node, int initRegID, int findRegID, string direction)
{
	//cout << Node->RegionID << endl;
	

	if(direction == "NW")
	{
		if((Node->Child)&&(Node->RegionID < initRegID))
		{
			reflectdNgbr(Node->NW, initRegID, findRegID, direction);
		}
		else
		{
			
			rekursOut = Node->RegionID;
			//cout << rekursOut<< endl;		
		}
	}

	

	if(direction == "NE")
	{
		if((Node->Child)&&(Node->RegionID < initRegID))
		{
			reflectdNgbr(Node->NE, initRegID, findRegID, direction);
		}
		else
		{
			rekursOut = Node->RegionID;
			//return Node->RegionID;
		}
	}

	if(direction == "SW")
	{
		if((Node->Child)&&(Node->RegionID < initRegID))
		{
			reflectdNgbr(Node->SW, initRegID, findRegID, direction);
		}
		else
		{
			rekursOut = Node->RegionID;
			//return Node->RegionID;
		}
	}

	
	if(direction == "SE")
	{
		if((Node->Child)&&(Node->RegionID < initRegID))
		{
			reflectdNgbr(Node->SE, initRegID, findRegID, direction);
		}
		else
		{
			rekursOut = Node->RegionID;
			//return Node->RegionID;
		}
	}

	//cout << rekursOut << endl;

	return rekursOut;

}

QTreeStruct *&ClassQTree::getNgbrNode(QTreeStruct *&tQTree, int findRegID)
{
	bool isOut = 0;
	
	if(tQTree == NULL)
	{
		return tmpNode;
	}
	//cout << isOut << endl;

	if(!isOut)
	{
		if(tQTree->RegionID == findRegID)
		{
			tmpNode = tQTree;
			isOut = 1;
		}

		

		if (tQTree->NW != NULL)
		{
			getNgbrNode(tQTree->NW, findRegID);
		}

		if (tQTree->NE != NULL)
		{
			getNgbrNode(tQTree->NE, findRegID);
		}

		if (tQTree->SW != NULL)
		{
			getNgbrNode(tQTree->SW, findRegID);
		}

		if (tQTree->SE != NULL)
		{
			getNgbrNode(tQTree->SE, findRegID);
		}
	
	}
	
		return tmpNode;

//	cout << tmpNode->Field << endl;

	

}


void ClassQTree::crtConnect(QTreeStruct *&Node, QTreeStruct *&tQTree)
{
	bool isOut = 0;
/*
	system("cls");

	OutNodeV(*Node);
	OutNodeV(*tQTree);
	cout << Node->Level << endl;
	cout << "_________" << endl;

*/	
	QTreeStruct *tmp;

 	switch(tQTree->ChildNum)
	{
		case 1:
		{
			if(Node->Env.NorthID == 0)
			{
				//cout << Node->Env.NorthID << endl;
				tQTree->Env.NorthID = Node->Env.NorthID;
			}
			else
			{
				//getNgbrNode
				tmp = getNgbrNode(QTree, Node->Env.NorthID);
				tQTree->Env.NorthID = reflectdNgbr(tmp, tQTree->RegionID, Node->Env.NorthID, "SW");
				isOut = 0;
			}	
			

			tQTree->Env.EastID = Node->NE->RegionID;
		
			tQTree->Env.SouthID =  Node->SW->RegionID;

			
			if(Node->Env.WestID == 0)
			{
				tQTree->Env.WestID = Node->Env.WestID;
			}
			else
			{
				tmp = getNgbrNode(QTree, Node->Env.WestID);
				tQTree->Env.WestID = reflectdNgbr(tmp, tQTree->RegionID, Node->Env.WestID, "NE");
				isOut = 0;
			}	
			

			break;
		}

		case 2:
		{
			
			if(Node->Env.NorthID == 0)
			{
				tQTree->Env.NorthID = Node->Env.NorthID;
			}
			else
			{
				tmp = getNgbrNode(QTree, Node->Env.NorthID);
				tQTree->Env.NorthID = reflectdNgbr(tmp, tQTree->RegionID, Node->Env.NorthID, "SE");
				isOut = 0;
			}

			if(Node->Env.EastID == 0)
			{
				tQTree->Env.EastID = Node->Env.EastID;
			}
			else
			{
				tmp = getNgbrNode(QTree, Node->Env.EastID);
				tQTree->Env.EastID = reflectdNgbr(tmp, tQTree->RegionID, Node->Env.EastID, "NW");
				isOut = 0;
				
				//cout << tQTree->Env.EastID << endl;
			}


			tQTree->Env.SouthID =  Node->SE->RegionID;

			tQTree->Env.WestID = Node->NW->RegionID;

			break;
		}

		case 3:
		{
			
			tQTree->Env.NorthID = Node->NW->RegionID;

			tQTree->Env.EastID = Node->SE->RegionID;

			if(Node->Env.SouthID == 0)
			{
				tQTree->Env.SouthID = Node->Env.SouthID;
			}
			else
			{
				tmp = getNgbrNode(QTree, Node->Env.SouthID);
				tQTree->Env.SouthID = reflectdNgbr(tmp, tQTree->RegionID, Node->Env.SouthID, "NW");
				isOut = 0;
			}	
			
			if(Node->Env.WestID == 0)
			{
				tQTree->Env.WestID = Node->Env.WestID;
			}
			else
			{
				tmp = getNgbrNode(QTree, Node->Env.WestID);
				tQTree->Env.WestID = reflectdNgbr(tmp, tQTree->RegionID, Node->Env.WestID, "SE");
				isOut = 0;
			}	

			break;
		}

		case 4:
		{
			
			tQTree->Env.NorthID = Node->NE->RegionID;

			if(Node->Env.EastID == 0)
			{
				tQTree->Env.EastID = Node->Env.EastID;
			}
			else
			{
				tmp = getNgbrNode(QTree, Node->Env.EastID);
				tQTree->Env.EastID = reflectdNgbr(tmp, tQTree->RegionID, Node->Env.EastID, "SW");
				isOut = 0;
			}

			if(Node->Env.SouthID == 0)
			{
				tQTree->Env.SouthID = Node->Env.SouthID;
			}
			else
			{
				tmp = getNgbrNode(QTree, Node->Env.SouthID);
				tQTree->Env.SouthID = reflectdNgbr(tmp, tQTree->RegionID, Node->Env.SouthID, "NE");
				isOut = 0;
			}	

			tQTree->Env.WestID = Node->SW->RegionID;

			break;
		}

	}
/*
	OutNodeV(*Node);
	OutNodeV(*tQTree);
	cout << Node->Level << endl;
	cout << "_________" << endl;
*/
}

void  ClassQTree::level0(QTreeStruct *&Node)
{
	Node->Env.NorthID = 0;
	Node->Env.EastID = 0;
	Node->Env.SouthID = 0;
	Node->Env.WestID = 0;

	//Node->visited = true;

	if(Node->Level == 0)
	{

		//OutNodeV(*Node);

		//NW
		Node->NW->Env.NorthID = Node->Env.NorthID;
		Node->NW->Env.EastID = Node->NE->ChildNum;
		Node->NW->Env.SouthID = Node->SW->ChildNum;
		Node->NW->Env.WestID = Node->Env.WestID;

		//Node->NW->visited = true;
		
		//NE		
		Node->NE->Env.NorthID = Node->Env.NorthID;
		Node->NE->Env.EastID = Node->Env.EastID;
		Node->NE->Env.SouthID = Node->SE->ChildNum;
		Node->NE->Env.WestID = Node->NW->ChildNum;;

		//Node->NE->visited = true;

		//SW
		Node->SW->Env.NorthID = Node->NW->ChildNum;;
		Node->SW->Env.EastID = Node->SE->ChildNum;
		Node->SW->Env.SouthID = Node->Env.SouthID;
		Node->SW->Env.WestID = Node->Env.WestID;

		//Node->SW->visited = true;

		//SE
		Node->SE->Env.NorthID = Node->NE->ChildNum;
		Node->SE->Env.EastID = Node->Env.EastID;
		Node->SE->Env.SouthID = Node->Env.SouthID;
		Node->SE->Env.WestID = Node->SW->ChildNum;	

		//Node->SE->visited = true;
	}

}


void ClassQTree::createAdjConnect(QTreeStruct *&Node, QTreeStruct *&tQTree)
{
	//OutNodeV(*tQTree);
	
	//if (tQTree == NULL)
	//{ 
	//	return; 
	//}

//	cout << tQTree->Child << endl;
//	cout << "RegionID: " << tQTree->RegionID << endl;

	
// detect border
/*
	if(tQTree->Level == 0)
	{
		level0(tQTree);
	}
*/
	if(tQTree->Level > 1)
	{
		
		crtConnect(Node, tQTree);
		
	}

	if ((tQTree != NULL)&&(tQTree->NW != NULL))
	{

		createAdjConnect(tQTree, tQTree->NW);
	}

	if ((tQTree != NULL)&&(tQTree->NE != NULL))
	{
		createAdjConnect(tQTree, tQTree->NE);
	}

	if ((tQTree != NULL)&&(tQTree->SW != NULL))
	{
		createAdjConnect(tQTree, tQTree->SW);
	}

	if ((tQTree != NULL)&&(tQTree->SE != NULL))
	{
		createAdjConnect(tQTree, tQTree->SE);
	}


}


void ClassQTree::addInVector(QTreeStruct *&Node)
{

	listArr tmpL;
	
	tmpL.listAvgColor = Node->AvgColor;
	tmpL.Node.push_back(Node);

	//cout << "tmpL: " << int(tmpL.listAvgColor[0]) << "; " << int(tmpL.listAvgColor[1]) << ": " << int(tmpL.listAvgColor[2]) << endl;

	treeLists.push_back(tmpL);

}

bool ClassQTree::checkVector(QTreeStruct *&Node)
{
	int evkDST;
	
	vector<listArr>::iterator it = treeLists.begin();
	while(it != treeLists.end())
	{
		evkDST = (int)checkEvcDst(Node->AvgColor,it->listAvgColor);

		//cout << "tmpL: " << int(it->listAvgColor[0]) << "; " << int(it->listAvgColor[1]) << ": " << int(it->listAvgColor[2]) << endl;

		//cout << "evkDST" << evkDST << endl;

		//cout << it->Node[0]->Child << endl;

		if(evkDST < mrgT)
		{
			Node->AvgColor = it->listAvgColor;
			it->Node.push_back(Node);
			return true;
		}
			
		++it;
	}

	return false;
}


void ClassQTree::addRectToVector(QTreeStruct *&Node)
{
	//cout << Node->Field << endl;

	

	if(treeLists.size() == 0)
	{
		//cout << "dfb"<< endl;
		addInVector(Node);
	}
	else
	{
		bool isInVector = checkVector(Node);

		//cout << "isInVector: " << isInVector << endl;

		if(!isInVector)
		{
			addInVector(Node);
		}
	}

}

bool ClassQTree::checkSize(QTreeStruct *&Node)
{
/*
	if((Node->MaxPoint == 1)&&(Node->numBorder < 2))
	{ return true; }
*/ //cout << Node->numBorder << endl;

	if(Node->numBorder == Node->MaxPoint)
	{ 
		//cout << Node->numBorder << endl;
		//cout << Node->MaxPoint << endl;

		return true; 
	}

	return false;
}

void ClassQTree::brdLight(QTreeStruct *&tQTree)
{
	if (tQTree == NULL)
	{ 
		return; 
	}

	//cout << tQTree->Child << endl;
//	cout << "RegionID: " << tQTree->RegionID << endl;
	
	if (!tQTree->isEnd)
	{
		brdLight(tQTree->NW);
	}
	

	if (!tQTree->isEnd)
	{
		brdLight(tQTree->NE);
	}
	

	if (!tQTree->isEnd)
	{
		brdLight(tQTree->SW);
	}
	

	if (!tQTree->isEnd)
	{
		brdLight(tQTree->SE);
	}
	

	if (tQTree->isEnd)
	{
		if(checkSize(tQTree))
		{
			//cout << "g" << endl;
			tQTree->AvgColor[0] = 255;
			tQTree->AvgColor[1] = 255;
			tQTree->AvgColor[2] = 255;
		}
	}
}

void ClassQTree::boolVarsQTree(QTreeStruct *&Node)
{
	Node->Child = true;
	Node->visited = false;
	Node->isEnd = false;
}

int ClassQTree::newBorderCheck(TRect TR)
{
	Check = 0;
	for(int i = TR.Top; i <= TR.Bottom; ++i)
	{	
		for(int j = TR.Left; j <= TR.Right; ++j)
		{
//Degug code
			if(TR.Bottom > brdMatrix.size()||(TR.Right > brdMatrix[0].size()))
			{
				system("pause");
			}
//__________
			
			if(brdMatrix[i][j] == 0)
			{
				//cout << "Height: " << i << endl;
				//cout << "Weidth: " << j << endl;
				//cout << brdMatrix[i][j] << endl;


				++Check;
			}
		}

	}

	return Check;

}

void ClassQTree::initEnv(Neighbor &Env)
{
	Env.NorthID = -1;
	Env.EastID = -1;
	Env.SouthID = -1;
	Env.WestID = -1;
}

void ClassQTree::insQDat(QTreeStruct *&Node, int L, int ChildNum, int PartitionID, TRect TR)
{

	Node->Rect = TR;
	Node->Level = L;
	
	Node->ChildNum = ChildNum;

//NW ChildNum, PartitionID, RegionID
	if(Node->Level ==1)
	{
		Node->PartitionID = Node->ChildNum; 

		Node->RegionID = Node->ChildNum;
	}
	else
	{
		Node->PartitionID = PartitionID;
		Node->RegionID = PartitionID*10+Node->ChildNum;
	}

	Node->MaxPoint = (dx+1)*(dy+1);

}


void ClassQTree::CalcTR(TRect &TR, TRect R, int N)
{
	switch (N)
	{
		case 1: //NW
			TR.Left = R.Left;
			TR.Right = R.Left + dx;
			TR.Top = R.Top;
			TR.Bottom = R.Top + dy;
			break;
		case 2: //NE
			TR.Left = R.Left + dx +1;
			TR.Right = R.Right;
			TR.Top = R.Top;
			TR.Bottom = R.Top + dy;
			break;
		case 3: //SW
			TR.Left = R.Left;
			TR.Right = R.Left+ dx;
			TR.Top = R.Top + dy +1;
			TR.Bottom = R.Bottom;
			break;
		case 4: //SE
			TR.Left = R.Left + dx +1;
			TR.Right = R.Right;
			TR.Top = R.Top + dy +1;
			TR.Bottom = R.Bottom;
			break;
	}
}

void ClassQTree::EndTree(QTreeStruct *&tQTree)
{
	tQTree->Child = false;
	tQTree->visited = false;
	tQTree->isEnd = true;

	tQTree->NW = NULL;
	tQTree->NE = NULL;
	tQTree->SW = NULL;
	tQTree->SE = NULL;
}


void ClassQTree::QAdd(QTreeStruct *&tQTree, int L, int Sq, TRect R, int PartitionID)
{
	TRect TR;
	int dd;

	if(Sq < 2)
	{
		EndTree(tQTree);
		return;
	}
	dx = dXY(R.Right, R.Left); 
	dy = dXY(R.Bottom, R.Top);

//NW
	CalcTR(TR, R, 1);
/*
	cout << "TR.Left: " << TR.Left << endl;
	cout << "TR.Right: " << TR.Right<< endl;
	cout << "TR.Top: " << TR.Top << endl;
	cout << "TR.Bottom: " << TR.Bottom << endl;
*/
	tQTree->NW = NULL;
	tQTree->NW = new QTreeStruct;

	insQDat(tQTree->NW, L, 1, PartitionID, TR);	

	initEnv(tQTree->NW->Env);
		
//Need Optimization 
	tQTree->NW->AvgColor = AvgClr(TR);

	//cout << "tQTree->NW->AvgColor: " << (int)tQTree->NW->AvgColor.val[0] << "; " << (int)tQTree->NW->AvgColor.val[1] << "; " 
	//								 << (int)tQTree->NW->AvgColor.val[2] << endl;


	dd = CheckMDst(*tQTree->NW, TR);

	//cout << "dd: " << dd << endl;

	tQTree->NW->numBorder = newBorderCheck(TR);

	//cout << "tQTree->NW->numBorder: " << tQTree->NW->numBorder << endl;

//END Optimization

	if((dd > this->T)||(tQTree->NW->numBorder >= tt))//(tQTree->NW->numBorder > tt))
	{
		boolVarsQTree(tQTree->NW);
		QAdd(tQTree->NW, tQTree->NW->Level+1, tQTree->NW->MaxPoint, tQTree->NW->Rect, tQTree->NW->RegionID);
	}
	else
	{
		EndTree(tQTree->NW);
	}
	
//NW_End

	dx = dXY(R.Right, R.Left); 
	dy = dXY(R.Bottom, R.Top);


//NE
	CalcTR(TR, R, 2);

	tQTree->NE = NULL;
	tQTree->NE = new QTreeStruct;

	insQDat(tQTree->NE, L, 2, PartitionID, TR);	

	initEnv(tQTree->NE->Env);
	
	
//Need Optimization 
	tQTree->NE->AvgColor = AvgClr(TR);
	
	dd = CheckMDst(*tQTree->NE, TR);

	tQTree->NE->numBorder = newBorderCheck(TR); 

//END Optimization 

	if((dd > this->T)||(tQTree->NE->numBorder  >= tt))//(tQTree->NE->numBorder > tt))
	{
		boolVarsQTree(tQTree->NE);
		QAdd(tQTree->NE, tQTree->NE->Level+1, tQTree->NE->MaxPoint, tQTree->NE->Rect, tQTree->NE->RegionID);
	}
	else
	{
		EndTree(tQTree->NE);
	}

//NE_End

	dx = dXY(R.Right, R.Left); 
	dy = dXY(R.Bottom, R.Top);

//SW
	this->CalcTR(TR, R, 3);

	tQTree->SW = NULL;
	tQTree->SW = new QTreeStruct;
	
	insQDat(tQTree->SW, L, 3, PartitionID, TR);	

	initEnv(tQTree->SW->Env);

//Need Optimization 
	tQTree->SW->AvgColor = this->AvgClr(TR);

	dd = CheckMDst(*tQTree->SW, TR);

	tQTree->SW->numBorder = newBorderCheck(TR);
//END Optimization 

	if((dd > this->T)||(tQTree->SW->numBorder >= tt))//(tQTree->SW->numBorder > tt))
	{
		boolVarsQTree(tQTree->SW);
		QAdd(tQTree->SW, tQTree->SW->Level+1, tQTree->SW->MaxPoint, tQTree->SW->Rect, tQTree->SW->RegionID);
	}
	else
	{
		EndTree(tQTree->SW);
	}

//SW_End

	dx = dXY(R.Right, R.Left); 
	dy = dXY(R.Bottom, R.Top);

//SE
	this->CalcTR(TR, R, 4);

	tQTree->SE = NULL;
	tQTree->SE = new QTreeStruct;
	
	insQDat(tQTree->SE, L, 4, PartitionID, TR);	

	initEnv(tQTree->SE->Env);

//Need Optimization 
	tQTree->SE->AvgColor = this->AvgClr(TR);

	dd = CheckMDst(*tQTree->SE, TR);

	tQTree->SE->numBorder = newBorderCheck(TR); 
//END Optimization 


	if((dd > this->T)||(tQTree->SE->numBorder >= tt))//(tQTree->SE->numBorder > tt))
	{
		boolVarsQTree(tQTree->SE);
		QAdd(tQTree->SE, tQTree->SE->Level+1, tQTree->SE->MaxPoint, tQTree->SE->Rect, tQTree->SE->RegionID);
	}
	else
	{
		EndTree(tQTree->SE);
	}
	
//SE_End
}


void ClassQTree::ImgReWrite(QTreeStruct *&tQTree)
{
	if (tQTree == NULL)
	{ 
		return; 
	}

	//cout << tQTree->Child << endl;

	if (tQTree->Child == false) 
	{
		ImgDraw(*tQTree);

	}
		
	if (tQTree->NW != NULL)
	{
		ImgReWrite(tQTree->NW);
	}
		
	if (tQTree->NE != NULL)
	{
		ImgReWrite(tQTree->NE);
	}
    

	if (tQTree->SW != NULL)
	{
		ImgReWrite(tQTree->SW);
	}
   
	if (tQTree->SE != NULL)
	{ 
		ImgReWrite(tQTree->SE);
	}
}

void ClassQTree::ImgDraw(QTreeStruct Node)
{
	//cout << Node.Rect.Bottom << endl;

	for(unsigned long int y = Node.Rect.Top; y <= Node.Rect.Bottom; y++)
	{
		for(unsigned long int x = Node.Rect.Left; x <= Node.Rect.Right; x++)
		{
			
		//	cout << int(Node.AvgColor.val[0])<< endl;
		//	cout << int(Node.AvgColor.val[1])<< endl;
		//	cout << int(Node.AvgColor.val[2])<< endl;

			img.at<cv::Vec3b>(y,x).val[0] = Node.AvgColor.val[0];
			img.at<cv::Vec3b>(y,x).val[1] = Node.AvgColor.val[1];
			img.at<cv::Vec3b>(y,x).val[2] = Node.AvgColor.val[2];
			
		}
	}
/*
	if (Node.MaxPoint > 5)
	{

		int tmpy = (Node.Rect.Top + Node.Rect.Bottom)/2;
		int tmpx = (Node.Rect.Left + Node.Rect.Right)/2;
	
		img.at<cv::Vec3b>(tmpy,tmpx).val[0] = 255;
		img.at<cv::Vec3b>(tmpy,tmpx).val[1] = 255;
		img.at<cv::Vec3b>(tmpy,tmpx).val[2] = 255;
	}
*/
}

void ClassQTree::TreeOutF(QTreeStruct *&tQTree, ostream &f)
{
	if(tQTree == NULL)
	{
		return;
	}
	
	if (tQTree->Child == 0)
	{

		f << "Level: " << tQTree->Level << endl;
		f << "Left: " << tQTree->Rect.Left << endl;
		f << "Right: " << tQTree->Rect.Right << endl;
		f << "Top: " << tQTree->Rect.Top << endl;
		f << "Bottom: " << tQTree->Rect.Bottom << endl;

		f << "MaxPoint: " << tQTree->MaxPoint << endl;
	
		f << "ChildNum: " << tQTree->ChildNum << endl;
		f << "PartitionID: " << tQTree->PartitionID << endl;
		f << "RegionID: " << tQTree->RegionID<< endl;

		f << "Color Average: " << int(tQTree->AvgColor.val[0])<< ";" << int(tQTree->AvgColor.val[1]) << ";" << int(tQTree->AvgColor.val[2]) << endl;
	
		f << "Border Points: " << tQTree->numBorder << endl;
	
		if(tQTree->Child)
		{
			f << "Child: True"  << endl;
		}
		else
		{
			f << "Child: False"  << endl;
		}

		if(tQTree->visited)
		{
			f << "Visited: True"  << endl;
		}
		else
		{
			f << "Visited: False"  << endl;
		}
		f << "  "  << endl;

		//if(tQTree->Level > 0)
		{
			f << "NorthID: " << tQTree->Env.NorthID << endl;
			f << "EastID: " << tQTree->Env.EastID<< endl;
			f << "SouthID: " << tQTree->Env.SouthID << endl;
			f << "WestID: " << tQTree->Env.WestID<< endl;
		}

			if (tQTree->ptrNorthID == NULL)
			{
				f << "ptrNorthID: 0" << endl;
			}
			else
			{
				f << "ptrNorthID: " << tQTree->ptrNorthID->RegionID << endl;
			}

			if (tQTree->ptrEastID != NULL)
			{
				f << "ptrEastID: " << tQTree->ptrEastID->RegionID << endl;
			}
			else
			{
				f << "ptrEastID: 0" << endl;
			}

			if (tQTree->ptrSouthID != NULL)
			{
				f << "ptrSouthID: " << tQTree->ptrSouthID->RegionID << endl;
			}
			else
			{
				f << "ptrSouthID: 0" << endl;
			}

			if (tQTree->ptrWestID != NULL)
			{
				f << "ptrWestID: " << tQTree->ptrWestID->RegionID << endl;
			}
			else
			{
				f << "ptrWestID: 0" << endl;
			}
	}

	f << "________" << endl;

	

	TreeOutF(tQTree->NW, f);
	TreeOutF(tQTree->NE, f);
	TreeOutF(tQTree->SW, f);
	TreeOutF(tQTree->SE, f);

}