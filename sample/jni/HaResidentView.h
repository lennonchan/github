//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : HaResidentView.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_HARESIDENTVIEW_H)
#define _HARESIDENTVIEW_H

#include "RootView.h"

class HaResidentView :public RootView
{
public:
	HaResidentView();
	~HaResidentView();
	bool isHitMovieButton();
	bool isHitFavoriteButton();
	bool isHitExitButton();
	virtual void loseViewFocus();
};

#endif  //_HARESIDENTVIEW_H
