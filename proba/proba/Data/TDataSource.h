#pragma once

#include "standartIncl.h"

//_1 (split)
//Detect step
//const int t = 400;

const double K = 0.8; 

//Border step
const int tt = 1;

//Color step
const int TT = 500;
//end_1



//_____________

const int mrgT = 80;

//_____________

//_2(merge INNode)
//color InNode
const int tInNode = 10;

//borderInnode
const int borderInNode = 20;
//end_2

//_3(Adjacent)
//Adjacent color
const int adjColor = 20;
//end_3


//int prn = 20;

//___________

//0
const int a[3][3] = {
			{0, 0, 0},
			{4, 0, -4},
			{0, 0, 0}
		};

//90
const int b[3][3] = {
			{0, 4, 0},
			{0, 0, 0},
			{0,-4, 0}
		};

//135
const int c[3][3] = {
			{4, 0, 0},
			{0, 0, 0},
			{0, 0,-4}
		};

//45
const int d[3][3] = {
			{0, 0,-4},
			{0, 0, 0},
			{4, 0, 0}
		};

//Table

const string transitMtx[5][5] ={
	//0
	{"0", "0", "0", "0", "0"},
	//1
	{"R", "2", "1,1", "4", "3,1"},
	//2
	{"L", "2,2", "1", "4,2", "3"},
	//3
	{"D", "3", "4", "1,3" , "2,3"},
	//4
	{"U", "3,4", "4,4", "1", "2"}
};
//end_Table