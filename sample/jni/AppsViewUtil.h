//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : AppsViewUtil.h.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_BACKGROUNDVIEWUTIL_H)
#define _BACKGROUNDVIEWUTIL_H

#include "gkMathUtils.h"
#include "Util.h"
#include "ViewNode.h"

class AaAppsViewImpl;
class ScrollViewImpl;
class LetterViewImpl;

class AppsViewUtil
{
public:
	AppsViewUtil();
	~AppsViewUtil();
	void setAaViewImpl(AaAppsViewImpl* pImpl);
	void setScrollImpl(ScrollViewImpl* pImpl);
	void setLetterImpl(LetterViewImpl* pImpl);
	ViewNode* getCurrentFirstNode(); // 获取当前显示位置的第一个node
	void onAaNumChange();
	void syncViews();

	void setMoveVector(gkVector3 vt,bool anm = false,bool isPixUnit = false);	// 设置aaView的移动向量
	void nRowScroll(eFlyDirection drct,unsigned int num = 1,bool anm = false);	// 翻一行	
	void onePageScroll(eFlyDirection drct,bool anm = false);					// 翻一页面
	void reset();								// 初始化到起点位置
	void setLetter(char ch,bool anm = false);
	

	void setScrollMoveVector(gkVector3 vt,bool anm = false);			// 设置scroll的移动向量
	void setScrollPos(gkVector3 pos,bool anm = false);					// 设置scroll的位置
	//void oneRowScroll_Scroll(eFlyDirection drct,bool anm = false);		// 翻行
	//void onePageScroll_Scroll(eFlyDirection drct,bool anm = false);		// 翻页

	//void setLtViewLetter(char ch);
	eFlyDirection getNodePosInClip(int vIndex);	// 获取node在裁剪区域中的位置；return NON在裁剪区域，其他不在.vIndex:在容器中的索引
	float getClipScreenHight();
	static AppsViewUtil* getInstance();
private:
	char getAaViewCurrentLetter();
	gkVector3 getPosByChar(char ch);
	bool isOutofRange(float yVec);
	float getAaViewRowSpace();
private:
	static AppsViewUtil* m_This;

	tScrollData		m_ScrollData;
	AaAppsViewImpl* m_pAaViewImpl;
	ScrollViewImpl* m_pScrollImpl;
	LetterViewImpl* m_pLetterImpl;
	float m_Ratio;
};

#endif  //_BACKGROUNDVIEWUTIL_H
