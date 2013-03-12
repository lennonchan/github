//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : TV Block.cpp
//  @ Date : 2012-11-6
//  @ Author : 
//
//


#include "Favorite_Block.h"

#define _FT_BLOCK_PARENT_	"Plane_x05"
#define _FT_BLOCK_PARENTMK_	"Plane_x05c"
#define _FT_BLOCK_PLANE0_	"Plane_ea05"	// ϲ��Ӧ��
#define _FT_BLOCK_PLANE1_	"Plane_eb01"	// �ͷ�����
#define _FT_BLOCK_PLANE2_	"Plane_eb02"	// 
#define _FT_BLOCK_PLANE3_	"Plane_eb03"	// 
#define _FT_BLOCK_PLANE4_	"Plane_eb04"	// 
#define _FT_BLOCK_PLANE5_	"Plane_eb05"	// 
#define _FT_BLOCK_PLANE6_	"Plane_eb06"	// 
#define _FT_BLOCK_PLANE7_	"Plane_eb07"	// 
#define _FT_BLOCK_PLANE8_	"Plane_eb08"	// 
#define _FT_BLOCK_PLANE9_	"Plane_eb09"	// 
#define _FT_BLOCK_PLANE10_	"Plane_eb10"	// 
#define _FT_BLOCK_PLANE11_	"Plane_eb11"	// 
#define _FT_BLOCK_ANM_NAME_ "Plane_x05Action"
#define _FT_BLOCK_PLANENUM_	12	// 

#define _FT_BLOCK_EDITMENU_ITEM_ 2
#define _FT_BLICK_ITEM0_		"Plane_x05b1"
#define _FT_BLICK_ITEM0_ANM0_	"Plane_xa01Action.004"
#define _FT_BLICK_ITEM0_ANM1_	"Plane_xa01Action.001"
#define _FT_BLICK_ITEM0_ANM2_	"Plane_xa01bAction.002"
#define _FT_BLICK_ITEM1_		"Plane_x05b2"
#define _FT_BLICK_ITEM1_ANM0_	"Plane_xa02Action.004"
#define _FT_BLICK_ITEM1_ANM1_	"Plane_xa02Action.001"
#define _FT_BLICK_ITEM1_ANM2_	"Plane_xa02bAction"

FavoriteBlock::FavoriteBlock(gkScene* pscene):Block(pscene) 
{
	if (m_pScene)
	{
		m_ppShortcutList = new AppUnitShortcut*[_FT_BLOCK_PLANENUM_];
		m_ppShortcutList[0] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE0_,NULL,true))->setIndex(-3,-1);
		m_ppShortcutList[1] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE1_,NULL,true))->setIndex(0,1);
		m_ppShortcutList[2] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE2_))->setIndex(2,2);
		m_ppShortcutList[3] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE3_))->setIndex(3,3);
		m_ppShortcutList[4] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE4_))->setIndex(4,4);
		m_ppShortcutList[5] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE5_))->setIndex(5,5);
		m_ppShortcutList[6] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE6_))->setIndex(6,6);
		m_ppShortcutList[7] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE7_))->setIndex(7,7);
		m_ppShortcutList[8] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE8_))->setIndex(8,8);
		m_ppShortcutList[9] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE9_))->setIndex(9,9);
		m_ppShortcutList[10] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE10_))->setIndex(10,10);
		m_ppShortcutList[11] = (new AppUnitShortcut(m_pScene,_FT_BLOCK_PLANE11_))->setIndex(11,11);

		m_ShortCutNum = _FT_BLOCK_PLANENUM_;
		m_BlockParentPlane = m_pScene->getObject(_FT_BLOCK_PARENT_);
		m_BlockParentPlane->setVisible(false);
		m_pBldAnm = new BlenderAnimation(m_pScene,m_BlockParentPlane,_FT_BLOCK_ANM_NAME_);
		m_pMaskPlane = m_pScene->getObject(_FT_BLOCK_PARENTMK_);
		m_pMaskPlane->setVisible(false);
		setXVisible(false);
#if !_LAUNCHER_EDITMENU_OLDSTYLE_
		initEditMenu();
#endif
	}
}
FavoriteBlock::~FavoriteBlock() 
{
	ui_deleteArray(m_ppMenuAnmList,_BLOCK_EDITMENU_ANM_*_FT_BLOCK_EDITMENU_ITEM_);
}

BlockEnum
FavoriteBlock::getBlockEnum()
{
	return Favorite_Block;
}

int 
FavoriteBlock::getMenuFlag()
{
	return 1<<1|1;
}

int 
FavoriteBlock::getVacantPosParentID()
{
	return 5;
}

void 
FavoriteBlock::initEditMenu()
{
	m_MenuItemNum = _FT_BLOCK_EDITMENU_ITEM_;
	m_MenuItemFocus = 0;

	m_ppMenuAnmList = new BlenderAnimation*[_BLOCK_EDITMENU_ANM_*_FT_BLOCK_EDITMENU_ITEM_];
	m_ppMenuAnmList[0] = new BlenderAnimation(m_pScene,m_pScene->getObject(_FT_BLICK_ITEM0_),_FT_BLICK_ITEM0_ANM0_);
	m_ppMenuAnmList[1] = new BlenderAnimation(m_pScene,m_pScene->getObject(_FT_BLICK_ITEM0_),_FT_BLICK_ITEM0_ANM1_);
	m_ppMenuAnmList[2] = new BlenderAnimation(m_pScene,m_pScene->getObject(_FT_BLICK_ITEM0_),_FT_BLICK_ITEM0_ANM2_);
	m_ppMenuAnmList[3] = new BlenderAnimation(m_pScene,m_pScene->getObject(_FT_BLICK_ITEM1_),_FT_BLICK_ITEM1_ANM0_);
	m_ppMenuAnmList[4] = new BlenderAnimation(m_pScene,m_pScene->getObject(_FT_BLICK_ITEM1_),_FT_BLICK_ITEM1_ANM1_);
	m_ppMenuAnmList[5] = new BlenderAnimation(m_pScene,m_pScene->getObject(_FT_BLICK_ITEM1_),_FT_BLICK_ITEM1_ANM2_);
	m_ppMenuAnmList[0]->setAnmInterface(this);

	m_ppMenuObjList = new gkGameObject*[_FT_BLOCK_EDITMENU_ITEM_];
	m_ppMenuObjList[0] = m_pScene->getObject(_FT_BLICK_ITEM0_);
	m_ppMenuObjList[1] = m_pScene->getObject(_FT_BLICK_ITEM1_);
	m_ppMenuObjList[0]->setVisible(false);
	m_ppMenuObjList[1]->setVisible(false);
}