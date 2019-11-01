//HeadClassQTree.h
#pragma once;

#include "Includes\standartIncl.h"
#include "QTreeStruct.h"


class ClassQTree
{
public:
	cv::Mat img;
	
	QTreeStruct* QTree;
	
	vector<cv::Vec3b> segmentColor;

	vector<listArr> treeLists;
	int T;
	vector<vector<unsigned int>> brdMatrix;
	int maxL;


	ClassQTree(void);

	void InitQTree(cv::Mat timg);

//test

	vector<QTreeStruct*> sgmArr;

	void mergeInArray(QTreeStruct*& tQTree);

	void mergeQTree(QTreeStruct*& tQTree);

	
	void findeNgbr(QTreeStruct*& Node, QTreeStruct*& tQTree);

	void compareNgbr(QTreeStruct*& tQTree);

//end_test

//QAdd	
	void boolVarsQTree(QTreeStruct *&Node);
	void initEnv(Neighbor &Env);
	void insQDat(QTreeStruct *&Node, int L, int ChildNum, int PartitionID, TRect TR);
	void CalcTR(TRect &TR, TRect R, int N);
	void EndTree(QTreeStruct *&tQTree);

	void QAdd (QTreeStruct *&tQTree, int L, int Sq, TRect R, int PartitionID);
	
	//color
	cv::Vec3b AvgClr(TRect TR);
	int CheckMDst(QTreeStruct Node, TRect TR);
	
	//border

	int MatrixDif(int i, int j, const int (*Mtx)[3], cv::Vec3b cPoint);
	void dRGBCalc(int i, int j);

	//New_border
	void getPseudoBrd(int Width, int Height);

	void getBrdMatrix(cv::Mat &tmpMtx);
	int newBorderCheck(TRect TR);
//end_QAdd

	template <typename T1, typename T2>
	float checkEvcDst(const T1& color1, const T2& color2);

//Table

	char cmpTable(char Q, int &Direct);

	void calcQNgbr(int Direct, Neighbor &Env, unsigned long int regionID);

	void getNgbr(QTreeStruct *&tQTree);

//end_Table

//CorrecTable

	int findeCorrectNgbr(QTreeStruct*& tQTree, string target);

	void calcBigToSmall(QTreeStruct*& tQTree);

//end_CorrecTable

//Merge

	void ClassQTree::mrgDraw(QTreeStruct Node);

	void rewriteMergeImg(QTreeStruct*& tQTree);
	
	void calcColorDst(QTreeStruct*& tQTree);

	void mergeRegions(QTreeStruct*& tQTree);

	
	void colorCompare (QTreeStruct& Node, QTreeStruct& Tree);

	QTreeStruct* getNgbrNode (QTreeStruct& Node, QTreeStruct*& tQTree, int target);

	void mergeNgbrRegions(QTreeStruct*& tQTree);

//end_Merge

//ImageBorder

	void getBrdImage(QTreeStruct *&Node);

	void getCornerImage(QTreeStruct *&Node);

	void calcBrdImage(QTreeStruct *&tQTree);

//end_ImageBorder

//InNode
	void mergeInNode(QTreeStruct *&Node, QTreeStruct *&tQTree);
	void dellNode(QTreeStruct *&Node);
	void merge(QTreeStruct *&Node, QTreeStruct *&tQTree);
//end_InNode


//AdjacenNode
//In Working
	//id mergeAdjacentNode(QTreeStruct *&tQTree);
	int reflectdNgbr(QTreeStruct *&Node, int initRegID, int findRegID, string direction);
	QTreeStruct *&getNgbrNode(QTreeStruct *&tQTree, int findRegID);
	
//Work	
	void crtConnect(QTreeStruct *&Node, QTreeStruct *&tQTree);
	void level0(QTreeStruct *&Node);
	void createAdjConnect(QTreeStruct *&Node, QTreeStruct *&tQTree);
//end work
//end_AdjacenNode

//BorderOut
	bool checkSize(QTreeStruct *&Node);
	void brdLight(QTreeStruct *&tQTree);
//end_BorderOut

//test_Container

	void addRectToVector(QTreeStruct *&Node);
	void listArrTest();

//end_test_Container

//RewriteAdjNode
	void addInVector(QTreeStruct *&Node);
	bool checkVector(QTreeStruct *&Node);
//end_Rewrite AdjImg

//outImage	
	void ImgDraw(QTreeStruct Node);
	void ImgReWrite(QTreeStruct *&tQTree);
//end_outImage

//outData	
	void TreeOutF(QTreeStruct *&tQTree, ostream &f);
	void OutNodeV(QTreeStruct Node);
//end_outData
	private:
		cv::Vec3b clr1;
		cv::Vec3b clr2;

		int dx;
		int dy;

		int dR, dG, dB;

		int Check;

		int tmpDF;

		int rekursOut;

		QTreeStruct *tmpNode;

		string rtnway;
};

