//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : LauncherScene.cpp
//  @ Date : 2012-11-6
//  @ Author : 
//
//

#include <Animation/gkAnimationManager.h>
#include "LauncherScene.h"
#include "Block.h"

#define _LAUNCHER_EMENU_ITEM1_	"Plane_xa01"
#define _LAUNCHER_EMENU_ITEM2_	"Plane_xa02"
#define _LAUNCHER_EMENU_ITEM3_	"Plane_xa03"
#define _LAUNCHER_EMENU_ITEM4_	"Plane_xa04"
#define _LAUNCHER_EMENU_ITEM0_	"Plane_x09"	// PARENT
#define _LAUNCHER_EMENU_ITEMNUM_	4

#define _LAUNCHER_EMENU_ANM0_	"Plane_xa01Action"
#define _LAUNCHER_EMENU_ANM1_	"Plane_xa01Action.001"
#define _LAUNCHER_EMENU_ANM2_	"Plane_xa02Action"
#define _LAUNCHER_EMENU_ANM3_	"Plane_xa02Action.001"
#define _LAUNCHER_EMENU_ANM4_	"Plane_xa03Action"
#define _LAUNCHER_EMENU_ANM5_	"Plane_xa03Action.001"
#define _LAUNCHER_EMENU_ANM6_	"Plane_xa04Action"
#define _LAUNCHER_EMENU_ANM7_	"Plane_xa04Action.001"
#define _LAUNCHER_EMENU_ANMNUM_		8

gkHashedString g_AnmArray[] = {
	_LAUNCHER_EMENU_ANM0_,
	_LAUNCHER_EMENU_ANM1_,
	_LAUNCHER_EMENU_ANM2_,
	_LAUNCHER_EMENU_ANM3_,
	_LAUNCHER_EMENU_ANM4_,
	_LAUNCHER_EMENU_ANM5_,
	_LAUNCHER_EMENU_ANM6_,
	_LAUNCHER_EMENU_ANM7_,
};
gkVector3 g_ItemPosArray[_LAUNCHER_EMENU_ITEMNUM_];

gkVector3 
getItemPos(int index,int num)
{
	int index0 = (_LAUNCHER_EMENU_ITEMNUM_ - num)/2;
	_ASSERT_((index0+index)<_LAUNCHER_EMENU_ITEMNUM_);

	return num%2==0?g_ItemPosArray[index0+index]:(g_ItemPosArray[index0+index]+g_ItemPosArray[index0+index+1])/2;
}

void 
LauncherScene::initEditMenu()
{
	//EDIT下，TV block不能获取焦点
	//m_MenuItemNum = 0;
	m_ppMenuNode = new ViewNode*[_LAUNCHER_EMENU_ITEMNUM_+1];
	m_ppMenuNode[0] = new ViewNode(m_pScene,_LAUNCHER_EMENU_ITEM1_);
	m_ppMenuNode[1] = new ViewNode(m_pScene,_LAUNCHER_EMENU_ITEM2_);
	m_ppMenuNode[2] = new ViewNode(m_pScene,_LAUNCHER_EMENU_ITEM3_);
	m_ppMenuNode[3] = new ViewNode(m_pScene,_LAUNCHER_EMENU_ITEM4_);
	m_ppMenuNode[4] = new ViewNode(m_pScene,_LAUNCHER_EMENU_ITEM0_);

	for(int i = 0;i<_LAUNCHER_EMENU_ITEMNUM_;i++)
	{
		m_ppMenuNode[i]->getGameObj()->setObjectRenderPriority(60);
		g_ItemPosArray[i] = m_ppMenuNode[i]->getGameObj()->getPosition();
	}
	m_ppEditMenuAnm = new BlenderAnimation*[_LAUNCHER_EMENU_ANMNUM_];

	for (int i = 0;i<_LAUNCHER_EMENU_ANMNUM_;i++)
	{
		m_ppEditMenuAnm[i] = new BlenderAnimation(m_pScene,m_ppMenuNode[i/2]->getGameObj(),g_AnmArray[i]);
	}
}

void 
LauncherScene::destoryEditMenu()
{
	ui_deleteArray(m_ppMenuNode,_LAUNCHER_EMENU_ITEMNUM_);
	ui_deleteArray(m_ppEditMenuAnm,_LAUNCHER_EMENU_ANMNUM_);
}

bool
LauncherScene::onContextMenu_EM(int& currentIndex,Ogre::RaySceneQueryResult& objArray)
{
#if _LAUNCHER_EDITMENU_OLDSTYLE_
#define MenuCount 4

	gkGameObject* contextMenu[MenuCount] = {
		m_ppMenuNode[0]->getGameObj(),
		m_ppMenuNode[1]->getGameObj(),
		m_ppMenuNode[2]->getGameObj(),
		m_ppMenuNode[3]->getGameObj(),
	};
	int  chooseContextMenuIndex = -1;

	currentIndex = chooseContextMenuIndex;
	for (int i =0; i < sizeof(contextMenu)/ sizeof(gkGameObject*); ++i)
	{
		if (contextMenu[i] 
		&& contextMenu[i]->isInstanced()
			&& contextMenu[i]->getVisible()
			)
		{
			// process mouse clicked event
			if (isObjInArray(objArray,contextMenu[i]))
			{
				currentIndex = i;
				return true;
			}
		}
	}
	return false;  // no contexMenu ok or clicked
#else
	Block* pCurrentBlock = getBlockByID(getCurrentFocusIndex_EM());
	gkGameObject** ppMenuList = pCurrentBlock->getMenuObjList();
	if(!pCurrentBlock || !ppMenuList)
	{
		currentIndex = -1;
		return false;
	}
	currentIndex = pCurrentBlock->getMenuItemFocusIdx();
	int iMenuItemNum = pCurrentBlock->getMenuItemNum();
	for (int i = 0;i<iMenuItemNum;i++)
	{
		if(isObjInArray(objArray,ppMenuList[i]))
		{
			currentIndex = i;
			return true;
		}
	}
	return false;
#endif
}

void 
LauncherScene::setMenuFocus_EM(unsigned int index)
{
	_ASSERT_(index<_LAUNCHER_EMENU_ITEMNUM_);
// 	if (m_ppMenuNode[index]->getGameObj()->getVisible() == false)
// 		setMenuFocus_EM(--index);
// m_MenuItemFocusOfCurBlk = index;
	m_ppBlocklist[m_editBlockFocusID]->setMenuItemFocusIdx(index);
}

unsigned int 
LauncherScene::getMenuFocus_EM()
{
	if (!getBlockByID(getCurrentFocusIndex_EM())->isDelete())
	{
		return getBlockByID(getCurrentFocusIndex_EM())->getMenuItemFocusIdx();
	}
	else
	{
		return 4;
	}
	//return m_ppBlocklist[m_editBlockFocusID]->getMenuItemFocusIdx();
}

void 
LauncherScene::setEditMenuFlag(int flag)
{
//  	m_MenuItemNum = 0;
//  	for (int i = 0;i<_LAUNCHER_EMENU_ITEMNUM_;i++)
//  	{
//  		if((flag&(1<<i)) != 0)
//  		{
//  			m_MenuItemNum++;
//  			m_ppMenuNode[i]->getGameObj()->setVisible(true);
//  		}
//  		else
//  		{
//  			m_ppMenuNode[i]->getGameObj()->setVisible(false);
//  		}
//  	}
//  
//  	for (int i = 0,j = 0;i<_LAUNCHER_EMENU_ITEMNUM_;i++)
//  	{
//  		if (m_ppMenuNode[i]->getGameObj()->getVisible() == false)
//  		{
//  			continue;
//  		}
//  		m_ppMenuNode[i]->getGameObj()->setPosition(getItemPos(j,m_MenuItemNum));
//  		j++;
//  	}
//  	setMenuFocus_EM(m_MenuItemFocusOfCurBlk);
}

void 
LauncherScene::setEditMenuPos(gkVector3 pos)
{
	m_ppMenuNode[_LAUNCHER_EMENU_ITEMNUM_]->getGameObj()->setPosition(pos);
}

#define _LAUNCHER_EMANM_SHOW_START_		849	
#define _LAUNCHER_EMANM_SHOW_END_		876
#define _LAUNCHER_EMANM_HIDE_START_		876
#define _LAUNCHER_EMANM_HIDE_END_		902
void 
LauncherScene::showEditMenu_Four()
{
	for (int i = 0;i<_LAUNCHER_EMENU_ANMNUM_;i++)
	{
		m_ppEditMenuAnm[i]->setFrameScope(_LAUNCHER_EMANM_SHOW_START_,_LAUNCHER_EMANM_SHOW_END_);
		m_ppEditMenuAnm[i]->play();
	}
}

void 
LauncherScene::hideEditMenu_Four()
{
	for (int i = 0;i<_LAUNCHER_EMENU_ANMNUM_;i++)
	{
		m_ppEditMenuAnm[i]->setFrameScope(_LAUNCHER_EMANM_HIDE_START_,_LAUNCHER_EMANM_HIDE_END_);
		m_ppEditMenuAnm[i]->play();
	}
}