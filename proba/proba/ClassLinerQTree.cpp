#include "ClassLinerQTree.h"

#include "Data\TDataSource.h"

void ClassLinerQTree::calcCenterSgm()
{
	for (int i = 0; i < contours.size(); ++i)
	{
		cv::Point tmpP;
		tmpP.x = 0;
		tmpP.y = 0;

		int sum = 0;
		//cout << "SegmentNumber: " << i << endl;
		for (int j = 0; j < contours[i].size()-1; ++j)
		{
			tmpP.x =tmpP.x +contours[i][j].x;
			tmpP.y = tmpP.y +contours[i][j].y;
			sum = sum +1;
		}

		tmpP.x = tmpP.x/sum;
		tmpP.y = tmpP.y/sum;

		contours[i].push_back(tmpP);
	
	}
}

void ClassLinerQTree::outContours()
{
	for (int i = 0; i < contours.size(); ++i)
	{
		cout << "SegmentNumber: " << i << endl;
		for (int j = 0; j < contours[i].size(); ++j)
		{
			cout << "Point in Contour: " << contours[i][j].x << "; " << contours[i][j].y << endl;
		}
	}

}

void ClassLinerQTree::createSgmArr()
{
	int ind = -1;

	for (int i = 0; i < tLTree.size(); ++i)
	{
		//cout << "tLTree[i].visited: " << tLTree[i].visited << endl;
		if (tLTree[i].visited ==0)
		{
			cv::Point p1;

			p1.x = (int)(tLTree[i].Left + tLTree[i].Right)/2;
			p1.y = (int)(tLTree[i].Top + tLTree[i].Bottom)/2;

			//cout << "p1.x: " << p1.x << endl;
			//cout << "p1.y: " << p1.y << endl;

			ind = ind +1;
			contours.resize(ind+1);
			contours[ind].push_back(p1);

			cv::Point tmpSize;
			tmpSize.x = tLTree[i].MaxPoint;
			tmpSize.y = ind;

			tLTree[i].visited = 1;
			for (int j = 1; j < tLTree.size(); ++j)
			{
				if(i != j)
				{
				//cout << "tLTree[j].visited: " << tLTree[j].visited << endl;
					if ((tLTree[j].visited ==0)&&(tLTree[i].segmentnumber == tLTree[j].segmentnumber))
					{
					//	cout << "tLTree[i].segmentnumber: " << tLTree[i].segmentnumber << endl;
					//	cout << "tLTree[j].segmentnumber: " << tLTree[j].segmentnumber << endl;
					
						p1.x = (int)(tLTree[j].Left + tLTree[j].Right)/2;
						p1.y = (int)(tLTree[j].Top + tLTree[j].Bottom)/2;

					//	cout << "p1.x: " << p1.x << endl;
					//	cout << "p1.y: " << p1.y << endl;

						//contours.resize(ind+1);
						tmpSize.x = tmpSize.x + tLTree[j].MaxPoint;
						
						contours[ind].push_back(p1);

						tLTree[j].visited = 1;
					}
				}
			}	

			contours[ind].push_back(tmpSize);
		}
	}
}

void ClassLinerQTree::nullVisited()
{
	for (int i = 0; i < tLTree.size(); ++i)
	{
		tLTree[i].visited = 0;
	}
}

void ClassLinerQTree::initSgnNum()
{
	for (int i = 0; i < tLTree.size(); ++i)
	{
		//cout << i << endl;
		tLTree[i].segmentnumber = i;
	}
}

void ClassLinerQTree::imgDraw (StTree Node, cv::Mat &img)
{
	for(unsigned long int y = Node.Top; y <= Node.Bottom; y++)
	{
		for(unsigned long int x = Node.Left; x <= Node.Right; x++)
		{ 

			img.at<cv::Vec3b>(y,x).val[0] = Node.AvgColor.val[0];
			img.at<cv::Vec3b>(y,x).val[1] = Node.AvgColor.val[1];
			img.at<cv::Vec3b>(y,x).val[2] = Node.AvgColor.val[2];
			
		}
	}
}

void ClassLinerQTree::imgRewrite (vector<StTree> &vLTree, cv::Mat &img)
{
	for (int i = 0; i < vLTree.size(); ++i)
	{
		imgDraw (vLTree[i], img);
	}

	for (int i = 0; i < contours.size(); ++i)
	{
		cv::Point point;

		if (contours[i][contours[i].size()-2].x > 100)
		{

			point.x = contours[i][contours[i].size()-1].x;
			point.y = contours[i][contours[i].size()-1].y;
		
			img.at<cv::Vec3b>(point.y,point.x).val[0] = 255;
			img.at<cv::Vec3b>(point.y,point.x).val[1] = 0;
			img.at<cv::Vec3b>(point.y,point.x).val[2] = 0;

		}
	}
}

void ClassLinerQTree::mergeFastLinerRegions (vector<StTree> &vLTree)
{
	bool isExit = 0;
	while (isExit == 0)
	{
		unsigned int begin = 0;
		unsigned int end = 20;
	
		for (unsigned i = begin; i <= end; ++i)
		{

			for (unsigned j = begin +1; j <= end; ++j)
			{
				if (vLTree[i].visited == 0)
				{
					if (i != j)
					{
				//	cout << vLTree[j].visited << endl;
					if (vLTree[j].visited == 0)
					{
						//1
						if ((vLTree[i].Right == vLTree[j].Left -1)&&
							(vLTree[i].Top >= vLTree[j].Top)&&	//
							(vLTree[i].Bottom <= vLTree[j].Bottom))	//
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
								
							}
							continue;
						}

						//2
						if ((vLTree[i].Left == vLTree[j].Right +1)&&
							(vLTree[i].Top <= vLTree[j].Top)&&
							(vLTree[i].Bottom >= vLTree[j].Bottom))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
								
							}
							continue;
						}

						//3
						if ((vLTree[i].Right == vLTree[j].Left -1)&&
							(vLTree[i].Top <= vLTree[j].Top)&&
							(vLTree[i].Bottom >= vLTree[j].Bottom))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}

						//4
						if ((vLTree[i].Left == vLTree[j].Right +1)&&
							(vLTree[i].Top >= vLTree[j].Top)&&
							(vLTree[i].Bottom <= vLTree[j].Bottom))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
								
							}
							continue;

						}

						//5
						if ((vLTree[i].Bottom == vLTree[j].Top -1)&&
							(vLTree[i].Left >= vLTree[j].Left)&&
							(vLTree[i].Right <= vLTree[j].Right))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}

						//6
						if ((vLTree[i].Top == vLTree[j].Bottom +1)&&
							(vLTree[i].Left <= vLTree[j].Left)&&
							(vLTree[i].Right >= vLTree[j].Right))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}

						//7
						if ((vLTree[i].Bottom == vLTree[j].Top - 1)&&
							(vLTree[i].Left <= vLTree[j].Left)&&
							(vLTree[i].Right >= vLTree[j].Right))
						{
							int dst = colorCompare (vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}

						//8
						if ((vLTree[i].Top == vLTree[j].Bottom +1)&&
							(vLTree[i].Left >= vLTree[j].Left)&&
							(vLTree[i].Right <= vLTree[j].Right))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}
					}
					}
				}

			}
			
		}
	}
}

int ClassLinerQTree::colorCompare (cv::Vec3b color1, cv::Vec3b color2)
{	
	float dif1;
	dif1 = (float)(color1.val[0]-color2.val[0]);

	float dif2;
	dif2 = (float)(color1.val[1]-color2.val[1]);

	float dif3;
	dif3 = (float)(color1.val[2]-color2.val[2]);

	return (int)sqrt((dif1*dif1)+(dif2*dif2)+(dif3*dif3));	
}


void ClassLinerQTree::mergeLinerRegions (vector<StTree> &vLTree)
{
	//cout << vLTree.size() << endl;
	int ind = 0;

	for (int i = 0; i < vLTree.size(); ++i)
	{
		
	//	cout << vLTree[i].visited << endl;
		if (vLTree[i].visited == 0)
		{
			for (int j = 1; j < vLTree.size(); ++j)
			{
				if (i != j)
				{
				//	cout << vLTree[j].visited << endl;
					if (vLTree[j].visited == 0)
					{
						//1
						if ((vLTree[i].Right == vLTree[j].Left -1)&&
							(vLTree[i].Top >= vLTree[j].Top)&&	//
							(vLTree[i].Bottom <= vLTree[j].Bottom))	//
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
								
							}
							continue;
						}

						//2
						if ((vLTree[i].Left == vLTree[j].Right +1)&&
							(vLTree[i].Top <= vLTree[j].Top)&&
							(vLTree[i].Bottom >= vLTree[j].Bottom))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
								
							}
							continue;
						}

						//3
						if ((vLTree[i].Right == vLTree[j].Left -1)&&
							(vLTree[i].Top <= vLTree[j].Top)&&
							(vLTree[i].Bottom >= vLTree[j].Bottom))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}

						//4
						if ((vLTree[i].Left == vLTree[j].Right +1)&&
							(vLTree[i].Top >= vLTree[j].Top)&&
							(vLTree[i].Bottom <= vLTree[j].Bottom))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
								
							}
							continue;

						}

						//5
						if ((vLTree[i].Bottom == vLTree[j].Top -1)&&
							(vLTree[i].Left >= vLTree[j].Left)&&
							(vLTree[i].Right <= vLTree[j].Right))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}

						//6
						if ((vLTree[i].Top == vLTree[j].Bottom +1)&&
							(vLTree[i].Left <= vLTree[j].Left)&&
							(vLTree[i].Right >= vLTree[j].Right))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}

						//7
						if ((vLTree[i].Bottom == vLTree[j].Top - 1)&&
							(vLTree[i].Left <= vLTree[j].Left)&&
							(vLTree[i].Right >= vLTree[j].Right))
						{
							int dst = colorCompare (vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}

						//8
						if ((vLTree[i].Top == vLTree[j].Bottom +1)&&
							(vLTree[i].Left >= vLTree[j].Left)&&
							(vLTree[i].Right <= vLTree[j].Right))
						{
							int dst = colorCompare(vLTree[i].AvgColor, vLTree[j].AvgColor);
						//	cout << "dst: " << dst << endl;
							if (dst < mrgT)
							{
								vLTree[j].AvgColor = vLTree[i].AvgColor;
								vLTree[j].segmentnumber = vLTree[i].segmentnumber;
								vLTree[i].visited = 1;
							}
							continue;
						}
					}
				}
			}
		}
	}
}

void ClassLinerQTree::outFilesgLTree(ofstream &f)
{
	for(int i = 0; i < sgLTree.size(); ++i)
	{
		f << "Color: " << (int)sgLTree[i].AvgColor.val[0]<< "; " << (int)sgLTree[i].AvgColor.val[1] << "; " << (int)sgLTree[i].AvgColor.val[2] << endl;
		for(int j = 0; j < sgLTree[i].ItemLTree.size(); ++j)
		{
			f << "Index: " << sgLTree[i].ItemLTree[j]<< endl;

		}

		f << "______________________" << endl;
		
	}
}


void ClassLinerQTree::outInFile(ofstream &f)
{
	
	for(int i = 0; i < tLTree.size(); ++i)
	{
		f << "Level: " << tLTree[i].Level << endl;

		f << "Color Average: " << int(tLTree[i].AvgColor.val[0])<< ";" << int(tLTree[i].AvgColor.val[1]) << ";" << int(tLTree[i].AvgColor.val[2]) << endl;

		f << "Rect Left: " << int(tLTree[i].Left)<< "; Right: " << int(tLTree[i].Right) << "; Top: " << int(tLTree[i].Top) << "; Bottom: " << int(tLTree[i].Bottom) <<endl;

		f << " RegionID: " << tLTree[i].RegionID << endl;
		f <<  "visited: " << tLTree[i].visited << endl;

		f <<  "NortnID: " << tLTree[i].NorthID << endl;
		f <<  "EastID: " << tLTree[i].EastID << endl;
		f <<  "SouthID: " << tLTree[i].SouthID << endl;
		f <<  "WestID: " << tLTree[i].WestID << endl;

		if (tLTree[i].visited == 0)
		{
			f << "Visited: " << "False" << endl;
		}

		if (tLTree[i].visited == 1)
		{
			f << "Visited: " << "True" << endl;
		}

		f << "sgmNumber: " << tLTree[i].segmentnumber << endl;

		f << "______________________" << endl;
		
	}
	
}

void ClassLinerQTree::addToLineQTree(QTreeStruct *Node)
{

	StTree tmpStL;

	tmpStL.Level = Node->Level;

	tmpStL.AvgColor = Node->AvgColor;
	
	tmpStL.Left = Node->Rect.Left;
	tmpStL.Right = Node->Rect.Right;
	tmpStL.Top = Node->Rect.Top;
	tmpStL.Bottom = Node->Rect.Bottom;

	tmpStL.MaxPoint = Node->MaxPoint;


	tmpStL.Child = Node->Child;
	tmpStL.visited = 0;
	tmpStL.RegionID = Node->RegionID;

	tmpStL.NorthID = Node->Env.NorthID;
	tmpStL.EastID = Node->Env.EastID;
	tmpStL.SouthID = Node->Env.SouthID;
	tmpStL.WestID = Node->Env.WestID;
	
	tLTree.push_back(tmpStL);
}


void ClassLinerQTree::createLineQTree(QTreeStruct *tQTree)
{

	if (tQTree == NULL)
	{ 
		return; 
	}

	//cout << tQTree->Child << endl;
	//cout << "RegionID: " << tQTree->RegionID << endl;
	if (tQTree->Child == 0)
	{
		addToLineQTree(tQTree);
	}
		createLineQTree(tQTree->NW);
		createLineQTree(tQTree->NE);
		createLineQTree(tQTree->SW);
		createLineQTree(tQTree->SE);

}

ClassLinerQTree::ClassLinerQTree(void)
{
}

ClassLinerQTree::~ClassLinerQTree(void)
{
}
