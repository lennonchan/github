//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : SortordView.cpp
//  @ Date : 2012-11-10
//  @ Author : 
//
//


#include "SortordView.h"
#include "ViewNode.h"
#include "Aabridge.h"
#include "BlenderAnimation.h"


#define _SORTORD_DEFAULT_		"Plane_v08"
#define _SORTORD_FREQUENCE_		"Plane_v09"
#define _SORTORD_LETTER_		"Plane_v10"

#define _SORTORD_DEFAULT_ANM_	"Plane_v08Action"
#define _SORTORD_FREQUENCE_ANM_	"Plane_v09Action"
#define _SORTORD_LETTER_ANM_	"Plane_v10Action"

#define _SORTORD_DEFAULT_TEX_ANM_	"Plane_v08Action.001"
#define _SORTORD_FREQUENCE_TEX_ANM_	"Plane_v09Action.001"
#define _SORTORD_LETTER_TEX_ANM_	"Plane_v10Action.001"


#define _SORTORD_ETAA_START_	580	// 进入all app开始帧
#define _SORTORD_ETAA_END_		609	// 进入all app结束帧
#define _SORTORD_EXAA_START_	700	// 退出all app开始帧
#define _SORTORD_EXAA_END_		720	// 退出all app结束帧

#define _SORTORD_ENTER_START_	610
#define _SORTORD_ENTER_END_		634
#define _SORTORD_EXIT_START_	634
#define _SORTORD_EXIT_END_		658

#define _SORTORD_NODE_NUM_	3

#define _SORTORD_COLO_NUM_	1		// 一列的view个数

SortordView::SortordView() :RootView(false),m_ppViewNodeList(NULL),m_SortordVisible(false),m_ppBldAnm(NULL), m_ppBldTexAnm(NULL)
{
	m_ppViewNodeList = getViewNodeList();
	setViewNodeNum(_SORTORD_NODE_NUM_);

	m_ppViewNodeList = new ViewNode*[_SORTORD_NODE_NUM_];
	m_ppBldAnm = new BlenderAnimation*[_SORTORD_NODE_NUM_];
	m_ppBldTexAnm = new BlenderAnimation*[_SORTORD_NODE_NUM_];

	m_ppViewNodeList[0] = (new ViewNode(Aabridge::getScene(),_SORTORD_DEFAULT_))->setIndex(0,0);
	m_ppViewNodeList[1] = (new ViewNode(Aabridge::getScene(),_SORTORD_FREQUENCE_))->setIndex(1,1);
	m_ppViewNodeList[2] = (new ViewNode(Aabridge::getScene(),_SORTORD_LETTER_))->setIndex(2,2);
	
	m_ppBldAnm[0] = new BlenderAnimation(Aabridge::getScene(),m_ppViewNodeList[0]->getGameObj(),_SORTORD_DEFAULT_ANM_);
	m_ppBldAnm[1] = new BlenderAnimation(Aabridge::getScene(),m_ppViewNodeList[1]->getGameObj(),_SORTORD_FREQUENCE_ANM_);
	m_ppBldAnm[2] = new BlenderAnimation(Aabridge::getScene(),m_ppViewNodeList[2]->getGameObj(),_SORTORD_LETTER_ANM_);

	m_ppBldTexAnm[0] = new BlenderAnimation(Aabridge::getScene(), m_ppViewNodeList[0]->getGameObj(), _SORTORD_DEFAULT_TEX_ANM_);
	m_ppBldTexAnm[1] = new BlenderAnimation(Aabridge::getScene(), m_ppViewNodeList[1]->getGameObj(), _SORTORD_FREQUENCE_TEX_ANM_);
	m_ppBldTexAnm[2] = new BlenderAnimation(Aabridge::getScene(), m_ppViewNodeList[2]->getGameObj(), _SORTORD_LETTER_TEX_ANM_);


	setViewNodeList(m_ppViewNodeList);
}

SortordView::~SortordView()
{
	m_ppViewNodeList = NULL;
	ui_deleteArray(m_ppBldAnm,_SORTORD_NODE_NUM_);
	ui_deleteArray(m_ppBldTexAnm,_SORTORD_NODE_NUM_);
}

void 
SortordView::setSortordVisible(bool flag)
{
	if (m_SortordVisible == flag)
	{
		return;
	}
	m_SortordVisible = flag;
	m_SortordVisible?showView():hideView();
}

bool 
SortordView::getSortordVisible()
{
	return m_SortordVisible;
}

bool 
SortordView::isHitStDefault(Ogre::RaySceneQueryResult& objArray)
{
	return isObjInArray(objArray,m_ppViewNodeList[0]->getGameObj());
}

bool 
SortordView::isHitStFrequence(Ogre::RaySceneQueryResult& objArray)
{
	return isObjInArray(objArray,m_ppViewNodeList[1]->getGameObj());
}

bool 
SortordView::isHitStLetter(Ogre::RaySceneQueryResult& objArray)
{
	return isObjInArray(objArray,m_ppViewNodeList[2]->getGameObj());
}

bool 
SortordView::isFocusOnStDefault()
{
	return getFocus() == m_ppViewNodeList[0];
}

bool 
SortordView::isFocusOnStFrequence()
{
	return getFocus() == m_ppViewNodeList[1];
}

bool 
SortordView::isFocusOnHitStLetter()
{
	return getFocus() == m_ppViewNodeList[2];
}

void 
SortordView::enterAaMode()
{
	for(int i = 0;i < _SORTORD_NODE_NUM_;i++)
	{
		m_ppBldAnm[i]->setFrameScope(_SORTORD_ETAA_START_,_SORTORD_ETAA_END_);
		m_ppBldAnm[i]->play();	
	}

}

void 
SortordView::exitAaMode()
{
	for(int i = 0;i < _SORTORD_NODE_NUM_;i++)
	{
		m_ppBldAnm[i]->setFrameScope(_SORTORD_EXAA_START_,_SORTORD_EXAA_END_);
		m_ppBldAnm[i]->play();	
	}
}

void 
SortordView::showView()
{
	for(int i = 0;i < _SORTORD_NODE_NUM_;i++)
	{
		m_ppBldAnm[i]->setFrameScope(_SORTORD_ENTER_START_,_SORTORD_ENTER_END_);
		m_ppBldAnm[i]->play();	
		m_ppBldTexAnm[i]->setFrameScope(_SORTORD_ENTER_START_, _SORTORD_ENTER_END_);
		m_ppBldTexAnm[i]->play();
	}
}

void 
SortordView::hideView()
{
	for(int i = 0;i < _SORTORD_NODE_NUM_;i++)
	{
		m_ppBldAnm[i]->setFrameScope(_SORTORD_EXIT_START_,_SORTORD_EXIT_END_);
		m_ppBldAnm[i]->play();	
		m_ppBldTexAnm[i]->setFrameScope(_SORTORD_EXIT_START_,_SORTORD_EXIT_END_);
		m_ppBldTexAnm[i]->play();
	}
}

void 
SortordView::loseViewFocus()
{

}