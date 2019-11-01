#include "standartIncl.h"
#include "ClassQTree.h"


#pragma once

struct StTree
{
	unsigned long int Level;
	unsigned long int RegionID;
	
	cv::Vec3b AvgColor;
	
	int numBorder;

	unsigned long int Left;
	unsigned long int Right;
	unsigned long int Top;
	unsigned long int Bottom;

	unsigned long int MaxPoint;
	
	bool Child;
	bool visited;
	bool isQBrd;

	//Ngbr
	int NorthID;
	int EastID;
	int SouthID;
	int WestID;

	int segmentnumber;

};

class ClassLinerQTree
{
private:
	vector<vector<cv::Point> > contours;
	vector<QTreeStruct*> LTree;
	vector<listTree> sgLTree;

	vector<int> vec;

	//DrawLiner
	void imgDraw (StTree Node, cv::Mat &img);
	
	void outContours();
	int colorCompare (cv::Vec3b color1, cv::Vec3b color2);
	
	//LinerCreate
	void addToLineQTree(QTreeStruct *Node);

public:

	vector<StTree> tLTree;

	ClassLinerQTree(void);


//DrawLiner
	void imgRewrite (vector<StTree> &vLTree, cv::Mat &img);//
//end_DrawLiner

//TestCode

	void calcCenterSgm();

	void createSgmArr();

	void nullVisited();

	void initSgnNum();

	void mergeLinerRegions (vector<StTree> &vLTree);

	void mergeFastLinerRegions (vector<StTree> &vLTree);

//end_TestCode

//DebugCode

	void outInFile(ofstream &f);

	void outFilesgLTree(ofstream &f);

//end_DebugCode

//LinerCreate

	void createLineQTree(QTreeStruct *tQTree); 

//end_LinerCreate

//Main

	void main(QTreeStruct *tQTree, string fName);

//end_Main

	~ClassLinerQTree(void);
};

