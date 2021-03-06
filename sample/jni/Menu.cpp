//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Menu.cpp
//  @ Date : 2012-11-6
//  @ Author : 
//
//


#include "Menu.h"
#include "Util.h"
#include "ViewNode.h"
#include "FocusMovePath.h"

#define _MENU_NODE_NAME_		"Plane_x06"
#define _MENU_NODE_BACKGROUND_	"Plane_y00"
#define _MENU_HOMENODE_NAME_	"Plane_ya01"
#define _MENU_NODE_PLANE0_		"Plane_ya02"
#define _MENU_WALLNODE_NAME_	"Plane_yb01"
#define _MENU_NODE_PLANE1_		"Plane_yb02"
#define _MENU_NODE_NUM_			6	

#define _MENU_ANM_NAME_		"Plane_x06Action"
#define _MENU_NODE_BGANM0_	"Plane_y00Action.001"
#define _MENU_NODE_BGANM1_	"Plane_y00Action"
#define _MENU_NODE_BGANM2_	"Plane_ya01Action"
#define _MENU_NODE_BGANM3_	"Plane_ya02Action"
#define _MENU_NODE_BGANM4_	"Plane_yb01Action"
#define _MENU_NODE_BGANM5_	"Plane_yb02Action"
#define _MENU_NODE_ANMNUM_	7

#define _SHOW_ANM_START_	480
#define _SHOW_ANM_END_		500
#define _HIDE_ANM_START_	500
#define _HIDE_ANM_END_		520

#define _MENU_COLNUM_		2
static gkHashedString g_ObjArray[] = {
	_MENU_NODE_BACKGROUND_,
	_MENU_NODE_NAME_,
	_MENU_HOMENODE_NAME_,
	_MENU_NODE_PLANE0_,
	_MENU_WALLNODE_NAME_,
	_MENU_NODE_PLANE1_,
};

static gkHashedString g_AnmArray[] = {
	_MENU_NODE_BGANM0_,
	_MENU_NODE_BGANM1_,
	_MENU_ANM_NAME_,
	_MENU_NODE_BGANM2_,
	_MENU_NODE_BGANM3_,
	_MENU_NODE_BGANM4_,
	_MENU_NODE_BGANM5_,
};

Menu::Menu(gkScene* pScene):RootView(false),m_pScene(pScene),m_bMenuVisible(false)
{
	if (m_pScene)
	{
		m_ppViewNodeList = new ViewNode*[_MENU_NODE_NUM_];
		
		for (int i = 0;i<_MENU_NODE_NUM_;i++)
		{
			m_ppViewNodeList[i] = new ViewNode(m_pScene,g_ObjArray[i]);
			m_ppViewNodeList[i]->getGameObj()->setObjectRenderPriority(80);
		}
		m_ppViewNodeList[2]->setIndex(0,0);
		m_ppViewNodeList[4]->setIndex(1,1);
		setViewNodeList(m_ppViewNodeList);
		setViewNodeNum(_MENU_NODE_NUM_);
		m_ppBldAnm = new BlenderAnimation*[_MENU_NODE_ANMNUM_];
		for (int i = 0;i<_MENU_NODE_ANMNUM_;i++)
		{
			if(i == 0 || i == 1)
			{
				m_ppBldAnm[i] = new BlenderAnimation(m_pScene,m_ppViewNodeList[0]->getGameObj(),g_AnmArray[i]);
				m_ppBldAnm[i]->setAnmInterface(this);
			}
			else
				m_ppBldAnm[i] = new BlenderAnimation(m_pScene,m_ppViewNodeList[i-1]->getGameObj(),g_AnmArray[i]);
		}
	}
}

Menu::~Menu()
{
	ui_deleteArray(m_ppBldAnm,_MENU_NODE_ANMNUM_);
}

void 
Menu::setMenuVisible(bool b)
{
	if (m_bMenuVisible == b)
	{
		return;
	}
	m_bMenuVisible = b;
	m_bMenuVisible?showMenu():hideMenu();
}

bool 
Menu::getMenuVisible()
{
	return m_bMenuVisible;
}

bool 
Menu::isHitHomeEdit(Ogre::RaySceneQueryResult& hitList)
{
	return isObjInArray(hitList,m_ppViewNodeList[2]->getGameObj());
}

bool 
Menu::isHitWallpaperSetting(Ogre::RaySceneQueryResult& hitList)
{	
	return isObjInArray(hitList,m_ppViewNodeList[4]->getGameObj());
}

bool 
Menu::isFocusOnHomeEdit()
{
	return getFocus() == m_ppViewNodeList[2];
}

bool 
Menu::isFocusOnWallpaper()
{
	return getFocus() == m_ppViewNodeList[4];
}

bool 
Menu::MoveFocus(eFlyDirection eDir)
{
	ViewNode* pNode = FocusMovePath::getNextFocusNode_AA(getViewNodeList(),
		getViewNodeNum(),getFocus()->getMinIndex(),eDir,_MENU_COLNUM_);
	return pNode?setFocus(pNode):false;
}

void 
Menu::showMenu()
{
	setTimePosition(_SHOW_ANM_START_,_SHOW_ANM_END_);
	for (int i = 0;i<_MENU_NODE_ANMNUM_;i++)
	{
		m_ppBldAnm[i]->play();
	}
}

void 
Menu::hideMenu()
{
	setTimePosition(_HIDE_ANM_START_,_HIDE_ANM_END_);
	for (int i = 0;i<_MENU_NODE_ANMNUM_;i++)
	{
		m_ppBldAnm[i]->play();
	}
	RootView::setFocusVisible(false);
}

void 
Menu::setTimePosition(int start,int end)
{
	for (int i = 0;i<_MENU_NODE_ANMNUM_;i++)
	{
		m_ppBldAnm[i]->setFrameScope(start,end);
	}
}

bool 
Menu::setFocus(ViewNode* node,bool isCircle)
{
	return RootView::setFocus(node,isCircle);
}

bool 
Menu::setFocus(int index,bool isCircle)
{
	return RootView::setFocus(index,isCircle);
}

void 
Menu::onBlenderAnmFinish(BlenderAnimation* p,int s,int e)
{
	if(m_bMenuVisible && p == m_ppBldAnm[0])
	{
		RootView::setFocusVisible(true);
		setFocus(0);
	}
}