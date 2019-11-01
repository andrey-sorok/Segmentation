#include "ClassBorder\ClassBorder.h"
#include "ClassFName\ClassFName.h"

#include "ClassMyThin\KWThin.h"

#include "ClassLinerQTree.h"
#include "ClassQTree.h"

#include "FindePointClass\FindePointClass.h"

//BordrThins
DWORD WINAPI calcMtx01(LPVOID Mtx)
{
	float start, end;
	float seconds;

	cv::Mat timg = *((cv::Mat*)Mtx);

	ClassZSThin *CThin = new ClassZSThin(timg);

	CThin->rectSize.Up = 1;
	CThin->rectSize.Left = 1;

	CThin->rectSize.Width = (timg.cols -2)/2;
	CThin->rectSize.Height = (timg.rows -2)/2;

	start = (float)clock();

	CThin->ThcreateImgMatrix(timg);
	
	end = (float)clock();

	seconds = end - start;

	cout << "Thread01 Time(mls): " << seconds/1000 << endl;

	return 0;
}

DWORD WINAPI calcMtx02(LPVOID Mtx)
{
	float start, end;
	float seconds;

	cv::Mat timg = *((cv::Mat*)Mtx);

	ClassZSThin *CThin = new ClassZSThin(timg);

	CThin->rectSize.Up = (timg.rows -2)/2;
	CThin->rectSize.Left = 1;

	CThin->rectSize.Width = (timg.cols -2)/2;
	CThin->rectSize.Height = (timg.rows -2);

	start = (float)clock();
	
	CThin->ThcreateImgMatrix(timg);
	
	end = (float)clock();

	seconds = end - start;

	cout << "Thread02 Time(mls): " << seconds/1000 << endl;

	return 0;
}

DWORD WINAPI calcMtx03(LPVOID Mtx)
{
	float start, end;
	float seconds;

	cv::Mat timg = *((cv::Mat*)Mtx);

	ClassZSThin *CThin = new ClassZSThin(timg);

	CThin->rectSize.Up = 1;
	CThin->rectSize.Left = (timg.cols -2)/2;

	CThin->rectSize.Width = (timg.cols -2);
	CThin->rectSize.Height = (timg.rows -2)/2;

	start = (float)clock();
	
	CThin->ThcreateImgMatrix(timg);
	
	end = (float)clock();

	seconds = end - start;

	cout << "Thread03 Time(mls): " << seconds/1000 << endl;

	return 0;
}

DWORD WINAPI calcMtx04(LPVOID Mtx)
{
	float start, end;
	float seconds;

	cv::Mat timg = *((cv::Mat*)Mtx);

	ClassZSThin *CThin = new ClassZSThin(timg);

	CThin->rectSize.Up = (timg.rows -2)/2;
	CThin->rectSize.Left = (timg.cols -2)/2;

	CThin->rectSize.Width = (timg.cols -2);
	CThin->rectSize.Height = (timg.rows -2);

	start = (float)clock();
	
	CThin->ThcreateImgMatrix(timg);

	end = (float)clock();

	seconds = end - start;

	cout << "Thread04 Time(mls): " << seconds/1000 << endl;
	
	return 0;
}
//end_BordrThins

//______________

int main()
{
	unsigned int start, end;
	float seconds;

	string getPath = "D:\\Sourse\\test_Proba";
	string outPath = "D:\\Sourse\\Result\\Segmentation";

	char * adName;
	char * fName = "groad_1.bmp";

	ClassFName * FPath = new ClassFName;
	
	if (FPath->DirectoryExists(outPath.c_str()) == 0)
	{
		int result;
		result = mkdir(outPath.c_str());
		cout << "Directory is created: " << outPath.c_str() << endl;; 
	}

	outPath = FPath->getDirPath(outPath, fName);

	cv::Mat img = cv::imread(FPath->FPath(getPath, fName).c_str(), 1);
	
	if ((img.rows == 0)&&(img.cols == 0))
	{
		cout << "Image is not load" << endl;
		system("pause");

	}
	else
	{
		if (FPath->DirectoryExists(outPath.c_str()) == 1)
		{
			cout << "Directory is exist: " << outPath.c_str() << endl;
		}
		if (FPath->DirectoryExists(outPath.c_str()) == 0)
		{
			int result;
			result = mkdir(outPath.c_str());
			cout << "Directory is created: " << outPath.c_str() << endl;
		}
	}
//Border

	ClassBorder *CBorder = new ClassBorder(img);

	start = clock();

	CBorder->OneMeasure(img);

	end = clock();

	seconds = float(end - start);

	cout << "GetBorder Time(mls): " << seconds/1000 << endl;

	CBorder->ReWriteImg();

	cv::namedWindow("border", CV_WINDOW_NORMAL);
	cv::imshow("border", CBorder->img);

	adName = "1_Border";

	cv::imwrite(FPath->crtNameToPath(outPath, fName, adName).c_str(), CBorder->img);

//end_Border

//tgreadThin
	//cv:: Mat dst = CBorder->img.clone();
/*
	HANDLE thread01 = CreateThread (NULL, 0, calcMtx01, &CBorder->img, 0, NULL);
	HANDLE thread02 = CreateThread (NULL, 0, calcMtx02, &CBorder->img, 0, NULL);
	HANDLE thread03 = CreateThread (NULL, 0, calcMtx03, &CBorder->img, 0, NULL);
	HANDLE thread04 = CreateThread (NULL, 0, calcMtx04, &CBorder->img, 0, NULL);

	WaitForSingleObject (thread01, INFINITE);
	WaitForSingleObject (thread02, INFINITE);
	WaitForSingleObject (thread03, INFINITE);
	WaitForSingleObject (thread04, INFINITE);
	
	CloseHandle (thread01);
	CloseHandle (thread02);
	CloseHandle (thread03);
	CloseHandle (thread04);
*/
//end_tgreadThin

//Filter

	KWThin* KW = new KWThin(CBorder->img);
	
	KW->rectSize.Up = 1;
	KW->rectSize.Left = 1;

	KW->rectSize.Width = (CBorder->img.cols -2);
    KW->rectSize.Height = (CBorder->img.rows -2);


	KW->createThinMtx(CBorder->img);

	cv::imwrite("tmp\\1.bmp", CBorder->img);
	delete CBorder;

	cv::Mat im = cv::imread("tmp\\1.bmp", CV_LOAD_IMAGE_GRAYSCALE);

	KW->dellMinContours(im);

	adName = "2_Thin";

	cv::imwrite(FPath->crtNameToPath(outPath, fName, adName).c_str(), im);

	cv::namedWindow("img", CV_WINDOW_NORMAL);
	cv::imshow("img", im); 
	
	
	ClassQTree *CQTree = new ClassQTree;
	
//initQ
	CQTree->InitQTree(img);
//end initQ

	CQTree->getBrdMatrix(im);

//CreateQ

	start = clock();

	CQTree->QAdd(CQTree->QTree, CQTree->QTree->Level+1, CQTree->QTree->MaxPoint, CQTree->QTree->Rect, CQTree->QTree->PartitionID);

	end = clock();

	seconds = float(end - start);

	cout << "QAdd Time(mls): " << seconds/1000 << endl;

//end_CreateQ

//Table

	//	CQTree->calcBrdImage(CQTree->QTree);

	start = clock();

	//	CQTree->getNgbr(CQTree->QTree);

	end = clock();
	
	seconds = float(end - start);

	cout << "getNgbr Time(mls): " << seconds/1000 << endl;


		CQTree->ImgReWrite(CQTree->QTree);

	adName = "3_splitTree";

	cv::imwrite(FPath->crtNameToPath(outPath, fName, adName).c_str(), CQTree->img);
	
	cv::namedWindow("img1", CV_WINDOW_NORMAL);
	cv::imshow("img1", CQTree->img); 
/*	
	
	//delete CThin;

	start = clock();

		CQTree->calcBigToSmall (CQTree->QTree);
	
	end = clock();
	
	seconds = float(end - start);

	cout << "reFindeNgbr: " << seconds/1000 << endl;

//end_Table
/*

//MergeQTree
/*	
	start = clock();

		//CQTree->mergeQTree (CQTree->QTree);

		//CQTree->mergeInArray(CQTree->QTree);

		CQTree->compareNgbr(CQTree->QTree);
	
	end = clock();
	
	seconds = float(end - start);

	cout << "mergeQTree: " << seconds/1000 << endl;

	
	CQTree->ImgReWrite (CQTree->QTree);

*/
//end_MergeQTree

/*
	ClassLinerQTree *CLinerQTree = new ClassLinerQTree;
	
		CLinerQTree->createLineQTree(CQTree->QTree);

	start = clock();

		CLinerQTree->initSgnNum();

		CLinerQTree->mergeLinerRegions (CLinerQTree->tLTree);


	end = clock();
	
	seconds = float(end - start);

	cout << "mergeLinerRegions: " << seconds/1000 << endl;

		CLinerQTree->nullVisited();

	start = clock();

		CLinerQTree->createSgmArr();

	end = clock();
	
	seconds = float(end - start);

	cout << "CreateSgmArr: " << seconds/1000 << endl;

	start = clock();

		CLinerQTree->calcCenterSgm();

	end = clock();
	
	seconds = float(end - start);

	cout << "calcCenterSgm: " << seconds/1000 << endl;

/*		
	char* name = "out.txt";
	char* str = "";

	ofstream f;
	f.open(FPath->crtNameToPath(outPath, name, str));
	if (f.is_open())
	{
		//CLinerQTree->outInFile(f);
		CQTree->TreeOutF(CQTree->QTree, f);
	}


*/
//Merge

	//CLinerQTree->imgRewrite(CLinerQTree->tLTree, CQTree->img);
/*
	FindePointClass* FPClass = new FindePointClass;

		FPClass->writeBorder(CQTree->brdMatrix, CQTree->img);
	
*/
	//adName = "4_mergeTree";

	//cv::imwrite(FPath->crtNameToPath(outPath, fName, adName).c_str(), CQTree->img);

	cout << outPath.c_str() << endl;
	
	//cv::namedWindow("imgL", CV_WINDOW_NORMAL);
	//cv::imshow("imgL", CQTree->img); 

//end_Merge


//additionally

	cout << "Complite" << endl;

	//cv::namedWindow("img1", CV_WINDOW_NORMAL);
	//cv::imshow("img1", img);
	

//end_additionally
	cv::waitKey(0);
	
	return 0;
}