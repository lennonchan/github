//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : ScrollbarView.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_SCROLLBARVIEW_H)
#define _SCROLLBARVIEW_H
#include "RootView.h"
#include "BlenderAnmInterface.h"

class BlenderAnimation;
class ScrollbarView :public RootView,public BlenderAnmInterface
{
public:
	ScrollbarView();
	~ScrollbarView();
	virtual void loseViewFocus();
	bool setFocus(ViewNode* node = NULL);

	void setScrollBarScale(gkVector3 gScale);
	void setScrollBarPosition(gkVector3 gPosition);

	//void setSBRawPosition(gkVector3 rawpos);
	//gkVector3 getSBRawPosition();
	gkVector3 getScrollBarPosition();
	gkVector3 getScrollBarScale();
	bool isHitScrollBar(Ogre::RaySceneQueryResult&);
	bool isHitScrollTrack(Ogre::RaySceneQueryResult&);
	virtual void onBlenderAnmFinish(BlenderAnimation* p,int s,int e);
	//void setVisible(bool visible = true);;
private:
	void showView();
	void hideView();
private:
	//bool m_bVisible;
	gkVector3 m_SBRawPos;
	gkVector3 m_SBCurPos;
	ViewNode** m_ppViewNode;
	BlenderAnimation** m_ppBldAnm;
	BlenderAnimation** m_ppBldTexAnm;

};

#endif  //_SCROLLBARVIEW_H