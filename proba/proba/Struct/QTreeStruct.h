#include "standartIncl.h"

using namespace std;

struct TRect
{
	unsigned long int Left, Right, Top, Bottom;
};

struct Neighbor
{
	int NorthID;
	int EastID;
	int SouthID;
	int WestID;
};

struct QTreeStruct
{
	unsigned long int Level;
	
	unsigned long int RegionID;
	unsigned long int ChildNum;
	unsigned long int PartitionID;

	unsigned long int MaxPoint;
	cv::Vec3b AvgColor;
	int numBorder;

//	string Field;
	TRect Rect;

	bool Child;
	bool visited;
	bool isEnd;
	bool isQBrd;

	int segmentnumber;

	//unsigned long int numSegment;
	Neighbor Env;

	QTreeStruct *ptrNorthID, *ptrEastID, *ptrSouthID, *ptrWestID;

	//vector <QTreeStruct*> ngbr;

	QTreeStruct *NW, *NE, *SW, *SE;
};

struct listArr
{
	cv::Vec3b listAvgColor;

	vector<QTreeStruct*> Node;
};

struct StLTree
{
	unsigned long int Level;
	
	unsigned long int RegionID;
	unsigned long int ChildNum;
	unsigned long int PartitionID;

	cv::Vec3b AvgColor;
	TRect Rect;

	int numBorder;

	unsigned long int MaxPoint;

	bool Child;
	bool visited;
	bool isEnd;

};

struct listTree
{
	cv::Vec3b AvgColor;

	vector<int> ItemLTree;
};