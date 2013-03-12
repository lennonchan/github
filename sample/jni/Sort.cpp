//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Sort.cpp
//  @ Date : 2012-11-20
//  @ Author : 
//
//

#include "Sort.h"

template<typename T,typename Type,Type(T::*F)(void)> 
inline void qkSort(vector <T*>& pData,int left,int right,bool(*cmp)(Type,Type)) 
{ 

	int i=left,j=right;
	if(left>=right) return ;
	T* middle=pData[left];

	while(i!=j)
	{
		while(i<j&& !cmp((pData[j]->*F)(),(middle->*F)()))j--;
		pData[i]=pData[j];
		while(i<j&& cmp((pData[i]->*F)(),(middle->*F)())) i++;
		pData[j]=pData[i];
	}
	pData[i]=middle;
	qkSort<T,Type,F>(pData,left,i-1,cmp);
	qkSort<T,Type,F>(pData,i+1,right,cmp);
}  

inline bool 
intDownCmp(int i0,int i1)
{
	return i0>i1;
}

inline bool 
intGrowCmp(int i0,int i1)
{
	return i0<i1;
}

inline bool 
charGrowCmp(const char* pch0,const char* pch1)
{
	return strcmp(pch0,pch1)<0;
}

void
Sort::sortbyfrequence(vector <AppUnit*> &sAppList)
{
	qkSort<AppUnit,int,&AppUnit::getUseFrequence>(sAppList,0,sAppList.size()-1,intDownCmp);
}

void 
Sort::sortbyname(vector <AppUnit*> &sAppList)
{
	qkSort<AppUnit,const char*,&AppUnit::getChar>(sAppList,0,sAppList.size()-1,charGrowCmp);
}

void 
Sort::sortbydefault(vector <AppUnit*> &sAppList)
{
	qkSort<AppUnit,int,&AppUnit::getID>(sAppList,0,sAppList.size()-1,intGrowCmp);
}

