//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : LetterView.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_LETTERVIEW_H)
#define _LETTERVIEW_H

#include "RootView.h"

class ViewNode;
class BlenderAnimation;
class LetterView :public RootView
{
public:
	LetterView();
	~LetterView();
	virtual void loseViewFocus();
private:
	virtual void showView();
	virtual void hideView();
private:
	ViewNode** m_ppViewNodeList;
	BlenderAnimation** m_ppAnmList;
	BlenderAnimation** m_ppTexAnmList;
};

#endif  //_LETTERVIEW_H