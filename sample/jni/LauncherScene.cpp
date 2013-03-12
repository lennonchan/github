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
#include "TV_Block.h"
#include "Recommend_Block.h"
#include "Movieinfo_Block.h"
#include "Videoaudio_Block.h"
#include "Favorite_Block.h"
#include "My_Block.h"
#include "Title_Block.h"
#include "FocusMovePath.h"
#include "DataBaseImpl.h"
#include "StateBarViewImpl.h"
#include "RootView.h"
#include "gkEntity.h"

#define PARENT_ANM_NAME "Plane_x00Action" //"PlaneAction"
#define _LAUNCHER_EEM_ICON_ANM_ "Plane_w01Action"
#define _LAUNCHER_EM_WORD_ANM_  "Plane_w02Action"
#define PARENT_PLANE_NAME "Plane_x00" //"Plane"
#define _LAUNCHER_EEM_ICON_ "Plane_w02"
#define _LAUNCHER_EM_WORD_ "Plane_w01"
#define _LAUNCHER_BG_		"bg_a01"
#define _LAUNCHER_BG_ANM_	"bg_a01Action"

#define _LAUNCHER_PAGE_STEP_	60
#define _LAUNCHER_PAGE_MAX_		240

LauncherScene* LauncherScene::m_this = 0;
int LauncherScene::g_BGColor[_GLOBLE_BG_COLORNUM_]={0,0,0,0,0,0,0,0,0,0,0,0};
LauncherScene::LauncherScene(gkScene* pscene):m_isEditMode(false),m_currentID(1),m_editBlockFocusID(1),m_pExitEditModeIcon(NULL),m_pEditPageNode(NULL),m_pEditPageAnm(NULL),m_pExitEMAnm(NULL),
	m_totalBlockNumEdit(6),/* m_MenuItemFocusOfCurBlk(0),*/m_ppMenuNode(NULL),m_pBgAnm(NULL),m_FocusOnTitle(false),m_pTitleBlock(NULL),m_ppEditMenuAnm(NULL),m_pDataBase(NULL),
	nextEditBlockBldAni(None),deletedBlockNum(0),hasEnterEditAniFinished(false),hasFinishEditSBA(true)
{
	m_pScene = pscene;
	m_this = this;
	m_curEditBlockIdxPerScreen = EditBlockIdx(0, _MAX_BLOCKS_EDIT_PER_SCREEN - 1);
	m_editblockLeftTranNum = 0;
	m_editblockRightTranNum = getTotalBlockNum() - _MAX_BLOCKS_EDIT_PER_SCREEN;
	if(m_pScene)
	{
		m_pSceneParentPlane = m_pScene->getObject(PARENT_PLANE_NAME);
		//m_pSceneParentPlane->setObjectRenderPriority(40);
		m_pExitEditModeIcon = m_pScene->getObject(_LAUNCHER_EEM_ICON_);
		m_pEditPageNode = m_pScene->getObject(_LAUNCHER_EM_WORD_);
		m_pSceneParentPlane->setVisible(false);
		m_pBldAnm = new BlenderAnimation(m_pScene,m_pSceneParentPlane,PARENT_ANM_NAME);
		m_pBldAnm->setAnmInterface(this);
		m_pEditPageAnm = new BlenderAnimation(m_pScene,m_pEditPageNode,_LAUNCHER_EEM_ICON_ANM_);
		m_pEditPageAnm->setAnmInterface(this);
		m_pExitEMAnm = new BlenderAnimation(m_pScene,m_pExitEditModeIcon,_LAUNCHER_EM_WORD_ANM_);
		m_pExitEMAnm->setAnmInterface(this);
		m_pBgAnm = new BlenderAnimation(m_pScene,m_pScene->getObject(_LAUNCHER_BG_),_LAUNCHER_BG_ANM_);
		m_pTitleBlock = new TitleBlock(m_pScene);
		m_ppBlocklist = new Block*[__MAX_BLOCK_NUM];
		m_ppBlocklist[0] = new TVBlock(m_pScene);
		m_ppBlocklist[1] = new RecommendBlock(m_pScene);
		m_ppBlocklist[2] = new MovieinfoBlock(m_pScene);
		m_ppBlocklist[3] = new VideoaudioBlock(m_pScene);
		m_ppBlocklist[4] = new FavoriteBlock(m_pScene);
		m_ppBlocklist[5] = new MyBlock(m_pScene);
		m_ppBlocklist[6] = m_pTitleBlock;

		m_ppEditBkSwitchAnm = new TranslationAnm*[2];
		m_ppEditBkSwitchAnm[0] = m_ppEditBkSwitchAnm[1] = NULL;
		m_ppEditBkFocusAnm = new TranslationAnm*[2];
		m_ppEditBkFocusAnm[0] = m_ppEditBkFocusAnm[1] = NULL;

		m_pDataBase = DataBaseImpl::getInstance();
		m_pStateBar = new StateBarViewImpl();
		loadHomeApps();
		createEditBkFocusAnm_EM();
#if _LAUNCHER_EDITMENU_OLDSTYLE_
		initEditMenu();
#endif // _LAUNCHER_EDITMENU_OLDSTYLE_

		for (int i = 0;i < _GLOBLE_BG_COLORNUM_;i++)
		{
			g_BGColor[i] = m_ppBlocklist[3]->getShortcutsList()[i+1]->getGameObj()->getEntity()->getGLTextureID(_APP_BACKGROUND_INDEX_,0);
		}
	}
}

LauncherScene::~LauncherScene()
{
	ui_delete(m_pStateBar);
	ui_delete(m_pBldAnm);
	ui_delete(m_pBgAnm);
	ui_deleteArray(m_ppBlocklist,__MAX_BLOCK_NUM);
	ui_deleteArray(m_ppEditBkSwitchAnm,1);
	m_ppEditBkSwitchAnm = NULL;
	m_pTitleBlock = NULL;
#if _LAUNCHER_EDITMENU_OLDSTYLE_
	destoryEditMenu();
#endif // _LAUNCHER_EDITMENU_OLDSTYLE_
}

bool 
LauncherScene::setPageTimePosition(unsigned int startPage,unsigned int endPage)
{
	int istart = 0, iend = 0;
	if(startPage > endPage)
	{
		if (startPage == 1)
		{
			//m_currentID--;
			return false;
		}
		istart = (__MAX_BLOCK_NUM - 2 - startPage)*_LAUNCHER_PAGE_STEP_ + _LAUNCHER_PAGE_MAX_;
		iend = istart+_LAUNCHER_PAGE_STEP_*(startPage - endPage);
		m_pBldAnm->setFrameScope(istart,iend);			// ���ø��ڵ㶯����Χ
		m_pBgAnm->setFrameScope(istart,iend);
		for (int i = 0;i<__MAX_BLOCK_NUM;i++)
		{
			m_ppBlocklist[i]->setAnmFrameScope(istart,iend);		// ���ø���block�ĸ��ڵ㶯����Χ
		}
		m_pTitleBlock->setAnmTimeScope(istart,iend);

		return true;
		
	}
	else //(endPage > startPage)
	{
		if (startPage == 0)
		{
			//m_currentID++;
			return false;
		}
		istart = (startPage-1)*_LAUNCHER_PAGE_STEP_;
		iend = istart+_LAUNCHER_PAGE_STEP_*(endPage-startPage);
		m_pBldAnm->setFrameScope(istart,iend);
		m_pBgAnm->setFrameScope(istart,iend);
		for(int i = 0;i<__MAX_BLOCK_NUM;i++)
		{
			m_ppBlocklist[i]->setAnmFrameScope(istart,iend);		// ���ø���block�ĸ��ڵ㶯����Χ
		}
		//m_currentID++;
		m_pTitleBlock->setAnmTimeScope(istart,iend);
		return true;
	}

	return false;
}

void 
LauncherScene::tick(gkScalar time)
{
	//printf("LauncherScene::Update(gkScalar %f)\n",time);
	if(Block::getFocusAnm())
		Block::getFocusAnm()->Update(time);
	if(m_ppEditBkSwitchAnm[0])
		m_ppEditBkSwitchAnm[0]->Update(time);
	if(m_ppEditBkSwitchAnm[1])
		m_ppEditBkSwitchAnm[1]->Update(time);
	if(m_ppEditBkFocusAnm[0])
		m_ppEditBkFocusAnm[0]->Update(time);
	if(m_ppEditBkFocusAnm[1])
		m_ppEditBkFocusAnm[1]->Update(time);
	if (Block::getFocusEditAnm())
		Block::getFocusEditAnm()->Update(time);
	

}

bool 
LauncherScene::setBlockWholePosition(int pos)
{
	m_pBldAnm->setFrameTime(pos);
	return true;
}

bool 
LauncherScene::setBlockWholePage(int i)
{
	switch(i)
	{
	case 0:
	case 1:
		setBlockWholePosition(0);
		break;
	case 2:
		setBlockWholePosition(30);
		break;
	case 3:
		setBlockWholePosition(60);
		break;
	case 4:
		setBlockWholePosition(60);
		break;
	default:
		return false;
	}
	return true;
}

bool 
LauncherScene::blockWholeTranslation(eFlyDirection e) 
{
	int currentId = m_currentID;
	blockWholeTranslation(currentId,e==RIGHT?m_currentID == __MAX_BLOCK_NUM-2?m_currentID:++m_currentID:e!=LEFT?m_currentID:m_currentID==0?m_currentID:--m_currentID);
	//if(!setPageTimePosition(currentId,e==RIGHT?m_currentID == __MAX_BLOCK_NUM-2?m_currentID:++m_currentID:e!=LEFT?m_currentID:m_currentID==0?m_currentID:--m_currentID))
	//	return false;
	//m_pBldAnm->play();
	//m_pBgAnm->play();
	//for (int i = 0;i<__MAX_BLOCK_NUM;i++)
	//{
	//	m_ppBlocklist[i]->playAnimation();		// ����block�ĸ��ڵ㶯��
	//}
	return true;
}

bool 
LauncherScene::blockWholeTranslation(unsigned int startPage,unsigned int endPage)
{
	_ASSERT_(startPage < __MAX_BLOCK_NUM && endPage < __MAX_BLOCK_NUM);
	if(startPage == endPage)
		return true;
	m_pTitleBlock->finishAllAnm();
	if(setPageTimePosition(startPage,endPage))
	{
		m_pBldAnm->play();
		m_pBgAnm->play();  //background animation
		for (int i = 0;i<__MAX_BLOCK_NUM;i++)
		{
			m_ppBlocklist[i]->playAnimation();		// ����block�ĸ��ڵ㶯��
		}
		m_pTitleBlock->playPageAnm();
	}
	return true;
}

bool 
LauncherScene::blockFocusTranslation(eFlyDirection e) 
{
	if(m_FocusOnTitle)
	{
		if (!m_pTitleBlock->flyfocus(e))
		{
			if (DOWN == e)
			{
				m_FocusOnTitle = false;
				((gkEntity*)Block::getFocus())->setGLTextureID(0,0,RootView::getRectTextureID());
				m_ppBlocklist[m_currentID]->flyfocus(DOWN,m_pTitleBlock->getCurrentFocus());
				m_pTitleBlock->onLoseFocus();
			}
		}
		return false;
	}

	if (!m_ppBlocklist[m_currentID]->flyfocus(e))
	{
		//���ҿ�Խ��һ��block
		if (LEFT == e && m_currentID >0)
		{
			m_ppBlocklist[m_currentID]->onLoseFocus();
			m_ppBlocklist[m_currentID-1]->flyfocus(e,m_ppBlocklist[m_currentID]->getCurrentFocus());
			return true;
		}
		else if(RIGHT == e && m_currentID < __MAX_BLOCK_NUM - 2 - deletedBlockNum)
		{
			m_ppBlocklist[m_currentID]->onLoseFocus();
			m_ppBlocklist[m_currentID+1]->flyfocus(e,m_ppBlocklist[m_currentID]->getCurrentFocus());
			return true;
		}
		//�����ƶ�focus��������
		else if(UP == e)
		{
			m_ppBlocklist[m_currentID]->onLoseFocus();
			m_ppBlocklist[__MAX_BLOCK_NUM - 1]->flyfocus(e,m_ppBlocklist[m_currentID]->getCurrentFocus());
			m_FocusOnTitle = true;
			return true;
		}
	}
	return false;
}

unsigned int  
LauncherScene::getCurrentBlockID()
{
	return m_currentID;
}

Block*  
LauncherScene::getBlockByID(unsigned int iId)
{
	_ASSERT_(iId < __MAX_BLOCK_NUM);
	return m_ppBlocklist[iId];
}

ViewNode* 
LauncherScene::isHitGameObj(Ogre::RaySceneQueryResult& objArray)
{
	ViewNode* result = NULL;

	for (int i = 0;i<__MAX_BLOCK_NUM;i++)
	{
		result =  m_ppBlocklist[i]->isHitGameObj(objArray);
		if (result)
		{
			return result;
		}
	}

	return result;
}

bool 
LauncherScene::setCurrentFocus(const int index)
{
	int subIndex = 0;
	for (int i = 0;i<m_ppBlocklist[m_currentID]->getShortcutsNum();i++)
	{
		if(m_ppBlocklist[m_currentID]->getShortcutsList()[i]->getMinIndex() == index)
			subIndex = i;
	}
	m_ppBlocklist[m_currentID]->flyfocus(m_ppBlocklist[m_currentID]->getShortcutsList()[subIndex]);
	
	return true;
}

eFlyDirection 
LauncherScene::setCurrentFocus(ViewNode* pObj)
{
	if(!pObj)
	{
		return NON;
	}

	bool bResult = FocusMovePath::isInvolved((ViewNode**)(m_ppBlocklist[m_currentID]->getShortcutsList()),pObj,m_ppBlocklist[m_currentID]->getShortcutsNum());
	if(bResult)
	{
		m_ppBlocklist[m_currentID]->flyfocus(pObj);
	}
	else if(FocusMovePath::isInvolved((ViewNode**)m_pTitleBlock->getShortcutsList(),pObj,m_ppBlocklist[m_currentID]->getShortcutsNum()))
	{	// title ���⴦��
		m_FocusOnTitle = true;
		m_pTitleBlock->flyfocus(pObj);
	}
	else if (m_currentID > 0 &&
		FocusMovePath::isInvolved((ViewNode**)m_ppBlocklist[m_currentID-1]->getShortcutsList(),pObj,m_ppBlocklist[m_currentID-1]->getShortcutsNum())
		)	// ����ҳ
	{
		return LEFT;
	}
	else if (m_currentID < __MAX_BLOCK_NUM-1 &&
		FocusMovePath::isInvolved((ViewNode**)m_ppBlocklist[m_currentID+1]->getShortcutsList(),pObj,m_ppBlocklist[m_currentID+1]->getShortcutsNum())
		)	// ���ҷ�ҳ
	{
		return RIGHT;
	}
	else if(m_currentID == 0&&
		FocusMovePath::isInvolved((ViewNode**)m_ppBlocklist[2]->getShortcutsList(),pObj,m_ppBlocklist[2]->getShortcutsNum()))
	{
		return RIGHT;
	}
//	m_pBlocklist[m_currentID]
	return NON;
}

gkScene* 
LauncherScene::getScene()
{
	return m_pScene;
}

LauncherScene*
LauncherScene::getInstance() 
{
	if(!m_this)
	{
		m_this = new LauncherScene(0);
	}
	return m_this;
}

bool 
LauncherScene::isFocusOnAllAppButton()
{
	_ASSERT_(m_pTitleBlock);
	return m_FocusOnTitle?m_pTitleBlock->isFocusOnAllAppButton():false;
}

AppUnit* 
LauncherScene::getCurrentApp()
{
	return getBlockByID(getCurrentBlockID())->getCurrentFocus()->getApp();
}

AppUnit* 
LauncherScene::getHitApp(Ogre::RaySceneQueryResult& objArray)
{
	AppUnitShortcut* pShortcut = (AppUnitShortcut*)isHitGameObj(objArray);
	return pShortcut->getApp();
}

void 
LauncherScene::setFocusVisible(bool vsb)
{
	Block::setFocusVisible(vsb);
}

bool 
LauncherScene::getFocusVisible()
{
	return Block::getFocusVisible();
}

void 
LauncherScene::loadHomeApps()
{
#define __MAX_APPPOS_	12
	if (!m_pDataBase)
	{
		gkPrintf("NULL POINT!!!!");
		_PRINT_CODE_POS_;
		return;
	}
	vector<AppUnit*>* pVector = m_pDataBase->getAppsVector();
	int folderID = 0;
	int posindex = 255;

	unsigned int index = 0;
	int size = pVector->size();
	while (index < size)
	{
		AppUnit* pApp = pVector->at(index);
		folderID = pApp->getPlateName();

		posindex = folderID&255;
		folderID = folderID>>_LAUNCHER_HOMEAPP_POS_BITNUM_;
		if(folderID>0 && folderID < __MAX_BLOCK_NUM && posindex <__MAX_APPPOS_)
		{
			m_ppBlocklist[folderID-1]->setAppByIndex(posindex,pApp);
		}
		index++;
		
	}
	return;
}

void 
LauncherScene::finishBlockWholeTranslation()
{
	m_pBldAnm->finishAnm();
	m_pBgAnm->finishAnm();
}

int* 
LauncherScene::getBgColors()
{
	return g_BGColor;
}

void 
LauncherScene::setAllLauncherSceneVisible(bool visible)
{
	for (int i = 0;i<__MAX_BLOCK_NUM;i++)
	{
		m_ppBlocklist[i]->setAllVisible(visible);
	}
}