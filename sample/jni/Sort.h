//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Sort.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_SORT_H)
#define _SORT_H

#include "AppUnit.h"
#include <vector>

using namespace std;

class Sort
{
public:
	static void sortbyfrequence(vector <AppUnit*> &sAppList);
	static void sortbyname(vector<AppUnit*> &sAppList);
	static void sortbydefault(vector<AppUnit*> &sAppList);
};

#endif  //_SORT_H