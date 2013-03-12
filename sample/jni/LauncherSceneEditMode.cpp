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
#include "FocusMovePath.h"
#include "Title_Block.h"
#include "My_Block.h"

// edit Mode functions,�༭ģʽ�²��ܺ��зǱ༭ģʽ�ĺ���

#define _LAUNCHER_EDIT_ENTER_START_	520
#define _LAUNCHER_EDIT_ENTER_END_	550
#define _LAUNCHER_EDIT_EXIT_START_	550
#define _LAUNCHER_EDIT_EXIT_END_	570
#define _LAUNCHER_EDIT_ROOTEXIT_START_	610
#define _LAUNCHER_EDIT_ROOTEXIT_END_	630

#define _FOCUSIN_OFFSET_EM_	 gkVector3(0,-10,0)
#define _FOCUSOUT_OFFSET_EM_ gkVector3(0,10,0)

bool 
LauncherScene::setTimePosition(int start,int end)
{
	m_pBldAnm->setFrameScope(start,end);
	m_pEditPageAnm->setFrameScope(start,end);
	m_pExitEMAnm->setFrameScope(start,end);
	for (int i = 0;i<__MAX_BLOCK_NUM;i++)
	{
		m_ppBlocklist[i]->setAnmFrameScope(start,end);		// ���ø���block�ĸ��ڵ㶯����Χ
	}
	return false;
}

void 
LauncherScene::setBlockMaskVisible(Block* pBlock,bool vsb)
{
	if(pBlock)
	{
		pBlock->setMaskVisible(vsb);
	}
}

void 
LauncherScene::rememberBlocksRawPos_EM()
{
	for (int i = 0;i<__MAX_BLOCK_NUM;i++)
	{
		m_ppBlocklist[i]->writeDownRawData();				// ��¼Block��ԭʼλ��
	}
}
void 
LauncherScene::setTvBlockEnable(bool enable)
{
	((TVBlock*)m_ppBlocklist[0])->setTVBlockEnable(enable);
}

bool 
LauncherScene::isInEditMode()
{
	return m_isEditMode;
}

void 
LauncherScene::setEditMode(bool b)
{

	if (m_isEditMode == b)
	{
		return;
	}
	m_isEditMode = b;
	m_isEditMode?enterEditMode():exitEditMode();
}

void 
LauncherScene::setFocusInAnm_EM(gkGameObject* pObj,const gkVector3 pos)
{
	_ASSERT_(m_ppEditBkFocusAnm[0]);
	m_ppEditBkFocusAnm[0]->setGameObject(pObj);
	m_ppEditBkFocusAnm[0]->To(pos+_FOCUSIN_OFFSET_EM_,pObj->getScale(),false);
	m_ppEditBkFocusAnm[0]->From(pos,pObj->getScale());
}

void 
LauncherScene::setFocusOutAnm_EM(gkGameObject* pObj,const gkVector3& pos)
{
	_ASSERT_(m_ppEditBkFocusAnm[1]);
	m_ppEditBkFocusAnm[1]->setGameObject(pObj);
	m_ppEditBkFocusAnm[1]->To(pos,pObj->getScale(),false);
	m_ppEditBkFocusAnm[1]->From(pos+_FOCUSIN_OFFSET_EM_,pObj->getScale());
}

void 
LauncherScene::playBlockFocusAnm_EM()
{
	_ASSERT_(m_ppEditBkFocusAnm[0]&&m_ppEditBkFocusAnm[1]);
	m_ppEditBkFocusAnm[0]->Fly();
	m_ppEditBkFocusAnm[1]->Fly();
}

bool 
LauncherScene::enterEditMode()
{
	Block::setFocusVisible(false);
	rememberBlocksRawPos_EM();
#if _LAUNCHER_EDITMENU_OLDSTYLE_
	showEditMenu_Four();
#endif //_LAUNCHER_EDITMENU_OLDSTYLE_
	for (int i = 0;i<__MAX_BLOCK_NUM;i++)
	{
		m_ppBlocklist[i]->setMaskVisible(true);
	}
	setTimePosition(_LAUNCHER_EDIT_ENTER_START_,_LAUNCHER_EDIT_ENTER_END_);
	m_pBldAnm->play();
	m_pEditPageAnm->play();
	m_pExitEMAnm->play();

	for (int i = 0;i<__MAX_BLOCK_NUM;i++)
	{
		m_ppBlocklist[i]->playAnimation();
	}
	setTvBlockEnable(false);

	nextEditBlockBldAni = Enter_Ani;

	initEditBlock();

	return true;
}

bool 
LauncherScene::exitEditMode()
{
	Block::setFocusVisible(true);
	setTimePosition(_LAUNCHER_EDIT_EXIT_START_,_LAUNCHER_EDIT_EXIT_END_);
	m_pBldAnm->setFrameScope(_LAUNCHER_EDIT_ROOTEXIT_START_,_LAUNCHER_EDIT_ROOTEXIT_END_);
	setTvBlockEnable(true);
#if _LAUNCHER_EDITMENU_OLDSTYLE_
	hideEditMenu_Four();
#else
	for (int i = 0;i<__MAX_BLOCK_NUM;i++)
	{
		m_ppBlocklist[i]->setMaskVisible(false);
	}
	//getBlockByID(getCurrentBlockID())->hideMenu();
#endif //_LAUNCHER_EDITMENU_OLDSTYLE_
	
	m_pBldAnm->play();
	m_pEditPageAnm->play();
	m_pExitEMAnm->play();
	for (int i = 0;i<__MAX_BLOCK_NUM;i++)
	{
		m_ppBlocklist[i]->playAnimation();
	}
	
	//�˳�edit�󣬰�focus�ŵ���ʼλ��
	exitEditFocus();

	nextEditBlockBldAni= Quit_Ani;

	m_pTitleBlock->setTitleBlockVisable(true);

	for (int i = 0; i < __MAX_BLOCK_NUM; i++)
	{
		if (m_ppBlocklist[i]->getAddBlockSymbol())
		{
			m_ppBlocklist[i]->getAddBlockSymbol()->setVisible(true);
			break;
		}
	}
	hasEnterEditAniFinished = false;
	hasFinishEditSBA = true;
	return true;
}

void 
LauncherScene::initEditBlock()
{
	//����eidt�󣬹ص�title
	m_pTitleBlock->setTitleBlockVisable(false);

	//��ʼ������block�ƶ��ı�־λ
	m_curEditBlockIdxPerScreen.min_idx = 0;
	m_curEditBlockIdxPerScreen.max_idx = 4;
	m_editblockLeftTranNum = 0;
	m_editblockRightTranNum = getTotalBlockNum() - _MAX_BLOCKS_EDIT_PER_SCREEN;

	for (int i = 0; i < __MAX_BLOCK_NUM; i++)
	{
		if (m_ppBlocklist[i]->getAddBlockSymbol())
		{
			if (m_ppBlocklist[i]->isDelete())
			{
				m_ppBlocklist[i]->getAddBlockSymbol()->setVisible(true);
				break;
			}
		}
	}

}


void 
LauncherScene::initEditFocus()
{
	gkGameObject ** tmpMenuListInfirstBlock = m_ppBlocklist[1]->getMenuObjList();
	gkVector3 desPos = tmpMenuListInfirstBlock[0]->getWorldPosition();
	gkVector3 desSca = tmpMenuListInfirstBlock[0]->getWorldScale();
	Block::getEditFocus()->setPosition(desPos);
	Block::getEditFocus()->setScale(desSca);	
	Block::getEditFocus()->setVisible(true);

	Block::getFocusEditAnm()->To(desPos, desSca);
	Block::getFocusEditAnm()->From(desPos, desSca);

	Block::getEditFocus()->setPosition(desPos);
	Block::getEditFocus()->setScale(desSca);
	Block::getFocusEditAnm()->To(desPos, desSca);
	Block::getMenuFocusAnm()->setFrameScope(856, 876);
	Block::getMenuFocusAnm()->play();

	Block::getFocusEditAnm()->setAnmListener(this);
}

 void 
 LauncherScene::exitEditFocus()
 {
	Block::getEditFocus()->setVisible(false);
	setCurrentFocusIndex_EM(1);
 }

void 
LauncherScene::switchBlckBldAnm_EM(int i1,int i2)
{
	BlenderAnimation* pAnm1 = m_ppBlocklist[i1]->getBlenderAnm();
	BlenderAnimation* pAnm2 = m_ppBlocklist[i2]->getBlenderAnm();
	pAnm1->setGameObj(m_ppBlocklist[i2]->getBlockParentPlane());
	pAnm2->setGameObj(m_ppBlocklist[i1]->getBlockParentPlane());
	m_ppBlocklist[i1]->setBlenderAnm(pAnm2);
	m_ppBlocklist[i2]->setBlenderAnm(pAnm1);

}

void 
LauncherScene::setBlockOgreAnm_EM(TranslationAnm* pAnm,gkGameObject* pObj,gkGameObject* pDest,gkVector3 destPos)
{
	pAnm->setGameObject(pObj);
	//pAnm->From(pObj->getPosition(),pObj->getScale());
	pAnm->To(destPos,pDest->getScale(),false);
	pAnm->From(pObj->getPosition(),pObj->getScale());
}

bool
LauncherScene::flyMenuFocusImpl_EM(eFlyDirection e)
{
	if (e == UP)
	{
		m_ppBlocklist[getCurrentFocusIndex_EM()]->flyfocusInEditMenu(e);

		return true;
	}
	else if (e == DOWN)
	{
		m_ppBlocklist[getCurrentFocusIndex_EM()]->flyfocusInEditMenu(e);
		return true;
	}
	else if (e == LEFT)
	{

		if (getCurrentFocusIndex_EM() > 1)
		{
			//MYLOGI("left cur idx %d \n", m_editBlockFocusID);
			if (getCurrentFocusIndex_EM() - 1 > m_curEditBlockIdxPerScreen.min_idx)
			{
				gkGameObject ** pDesMenuList = m_ppBlocklist[getCurrentFocusIndex_EM() - 1]->getMenuObjList();
				m_ppBlocklist[getCurrentFocusIndex_EM()]->flyfocusInEditMenu(e, pDesMenuList[0]);
				Block::getEditFocus()->setVisible(true);
			}
			else
			{
				if (m_editblockRightTranNum < getTotalBlockNum() -  _MAX_BLOCKS_EDIT_PER_SCREEN)
				{
					transformEditBlockAnm_EM(RIGHT);
					if (m_curEditBlockIdxPerScreen.min_idx >= 1)
					{
						m_curEditBlockIdxPerScreen.min_idx--;
						m_curEditBlockIdxPerScreen.max_idx--;
						nextEditBlockBldAni = Right_Ani;
						m_editblockLeftTranNum--;
						m_editblockRightTranNum++;
					}
				}
			}

			setBlockFocus_EM(LEFT);
			setCurrentFocusIndex_EM(getCurrentFocusIndex_EM() - 1);
			return true;
		}	
	}
	else if (e == RIGHT)
	{

		if (getCurrentFocusIndex_EM() < getTotalBlockNum() - 1)
		{
			//MYLOGI("right cur idx %d \n", m_editBlockFocusID);
			if (getCurrentFocusIndex_EM() + 1 <= m_curEditBlockIdxPerScreen.max_idx 
				&& !m_ppBlocklist[getCurrentFocusIndex_EM() + 1]->isDelete())
			{
				gkGameObject ** pDesMenuList = m_ppBlocklist[getCurrentFocusIndex_EM() + 1]->getMenuObjList();
				m_ppBlocklist[getCurrentFocusIndex_EM()]->flyfocusInEditMenu(e, pDesMenuList[0]);
			}
			else
			{
				if (m_editblockLeftTranNum < getTotalBlockNum() - _MAX_BLOCKS_EDIT_PER_SCREEN)
				{
					transformEditBlockAnm_EM(LEFT);
					if (m_curEditBlockIdxPerScreen.max_idx < getTotalBlockNum() - 1)
					{
						m_curEditBlockIdxPerScreen.min_idx++;
						m_curEditBlockIdxPerScreen.max_idx++;
					}
					nextEditBlockBldAni = Left_Ani;
					m_editblockLeftTranNum++;
					m_editblockRightTranNum--;
				}	
			}

			setBlockFocus_EM(RIGHT);
			setCurrentFocusIndex_EM(getCurrentFocusIndex_EM() + 1);
		}

		return true;
	}	
	return false;
}

bool 
LauncherScene::flyMenuFocus_EM(eFlyDirection e)
{
	if (hasEnterEditAniFinished)
	{
		return flyMenuFocusImpl_EM(e);
	}
	return false;
}


bool 
LauncherScene::flyMenuFocus_EM()
{
	//m_MenuItemFocus = 0;
	gkGameObject ** pDesMenuList = m_ppBlocklist[getCurrentFocusIndex_EM()]->getMenuObjList();
	m_ppBlocklist[getCurrentFocusIndex_EM()]->flyfocusInEditMenu(LEFT, pDesMenuList[0]);
	Block::getEditFocus()->setVisible(true);
	return true;
}

void 
LauncherScene::transformEditBlockAnm_EM(eFlyDirection e)
{
	
	if ( e == RIGHT)
	{
		Block::getEditFocus()->setVisible(false);
		m_pBldAnm->setFrameScope(580, 610);
		m_pBldAnm->play();	
	}else if (e == LEFT)
	{
		Block::getEditFocus()->setVisible(false);
		m_pBldAnm->setFrameScope(550, 580);
		m_pBldAnm->play();
	}
}


bool 
LauncherScene::switchBlockIndex_EM(int i0,int i1)	// �������Ĵ���
{
	if(i1 < 1 || i1 >= __MAX_BLOCK_NUM||
		i0 < 1 || i0 >= __MAX_BLOCK_NUM ||
		i0 == i1)	// ��0��̶�
		return false;

	if(!m_ppEditBkSwitchAnm[0])
	{
		m_ppEditBkSwitchAnm[0] = new TranslationAnm(m_pScene,m_ppBlocklist[i0]->getBlockParentPlane(),"blockAnm0",gkVector3(0,0,0));
	//	m_ppEditBkSwitchAnm[0]->setAnmListener(this);
	}
	if(!m_ppEditBkSwitchAnm[1])
	{
		m_ppEditBkSwitchAnm[1] = new TranslationAnm(m_pScene,m_ppBlocklist[i1]->getBlockParentPlane(),"blockAnm1",gkVector3(0,0,0));
	//	m_ppEditBkSwitchAnm[0]->setAnmListener(this);
	}

	m_ppEditBkSwitchAnm[0]->finishAnimation();
	m_ppEditBkSwitchAnm[1]->finishAnimation();
	setBlockOgreAnm_EM(m_ppEditBkSwitchAnm[0],m_ppBlocklist[i0]->getBlockParentPlane(),m_ppBlocklist[i1]->getBlockParentPlane(),m_ppBlocklist[i1]->getRawData());
	setBlockOgreAnm_EM(m_ppEditBkSwitchAnm[1],m_ppBlocklist[i1]->getBlockParentPlane(),m_ppBlocklist[i0]->getBlockParentPlane(),m_ppBlocklist[i0]->getRawData());
	
	gkVector3 tempPos = m_ppBlocklist[i0]->getRawData();
	m_ppBlocklist[i0]->setRawData(m_ppBlocklist[i1]->getRawData());
	m_ppBlocklist[i1]->setRawData(tempPos);

	m_ppEditBkSwitchAnm[0]->Fly();
	m_ppEditBkSwitchAnm[1]->Fly();

	switchBlckBldAnm_EM(i0,i1);

	Block* pTemp = m_ppBlocklist[i0];
	m_ppBlocklist[i0] = m_ppBlocklist[i1];
	m_ppBlocklist[i1] = pTemp;

	return true;
}

bool
LauncherScene::switchBlockIndexImpl_EM(eFlyDirection e)
{

	if ( e == LEFT )
	{
		if ( getCurrentFocusIndex_EM() >  (m_curEditBlockIdxPerScreen.min_idx ?  m_curEditBlockIdxPerScreen.min_idx: 1) )
		{
			Block * curBlock = m_ppBlocklist[getCurrentFocusIndex_EM()];
			gkGameObject ** curMenuList = curBlock->getMenuObjList();

			Block * desBlock = m_ppBlocklist[getCurrentFocusIndex_EM() - 1];
			gkGameObject ** desMenuList = desBlock->getMenuObjList();

			//�����һ��menu��λ��Z����ƫ���ֵ
			if (curMenuList[0]->getWorldPosition().z - desMenuList[0]->getWorldPosition().z > 0.1
				|| curMenuList[0]->getWorldPosition().z - desMenuList[0]->getWorldPosition().z < -0.1)
			{
				gkVector3 desPos(desMenuList[0]->getWorldPosition().x,
					desMenuList[0]->getWorldPosition().y, curMenuList[0]->getWorldPosition().z);
				desBlock->flyfocusImp(desMenuList[0], desPos, desMenuList[0]->getWorldScale());
			}
			else
			{
				desBlock->flyfocusImp(desMenuList[0]);
			}

			switchBlockIndex_EM(getCurrentFocusIndex_EM() - 1, getCurrentFocusIndex_EM());

			setBlockFocus_EM(getCurrentFocusIndex_EM() - 1);
			setCurrentFocusIndex_EM(getCurrentFocusIndex_EM() - 1);

			return true;
		}
	} 
	else if( e == RIGHT)
	{
		if ( getCurrentFocusIndex_EM() < m_curEditBlockIdxPerScreen.max_idx )
		{
			Block * curBlock = m_ppBlocklist[getCurrentFocusIndex_EM()];
			gkGameObject ** curMenuList = curBlock->getMenuObjList();

			Block * desBlock = m_ppBlocklist[getCurrentFocusIndex_EM() + 1];
			gkGameObject ** desMenuList = desBlock->getMenuObjList();

			//�����һ��menu��λ��Z����ƫ���ֵ
			if (curMenuList[0]->getWorldPosition().z - desMenuList[0]->getWorldPosition().z > 0.1
				|| curMenuList[0]->getWorldPosition().z - desMenuList[0]->getWorldPosition().z < -0.1)
			{
				gkVector3 desPos(desMenuList[0]->getWorldPosition().x,
					desMenuList[0]->getWorldPosition().y, curMenuList[0]->getWorldPosition().z);
				desBlock->flyfocusImp(desMenuList[0], desPos, desMenuList[0]->getWorldScale());
			}
			else
			{
				desBlock->flyfocusImp(desMenuList[0]);
			}


			switchBlockIndex_EM(getCurrentFocusIndex_EM(), getCurrentFocusIndex_EM()+1);

			setBlockFocus_EM(getCurrentFocusIndex_EM() + 1);
			setCurrentFocusIndex_EM(getCurrentFocusIndex_EM() + 1);
			return true;
		}
	}
	return false;
}

bool
LauncherScene::switchBlockIndex_EM(eFlyDirection e)
{
	//�������ƶ�blockʱ���䶯���ܿ���û�в���
	//�����ڻص��������hasFinishEditSBAû�б���Ϊtrue
	//�Ӷ�����deadlock
	//��������һ����־λ����hasFinishEditSBA����5��Ϊfalse����������Ϊture����break deadlock
	static int count = 5;
 	hasFinishEditSBA?MYLOGI("true\n"):MYLOGI("false\n");
 	if (hasFinishEditSBA)
 	{
 		hasFinishEditSBA = false;
		count = 5;
 		return switchBlockIndexImpl_EM(e);
 	}
	else
	{
		count--;
		if (count == 0)
		{
			hasFinishEditSBA = true;
		}
	}

	return false;
}

bool 
LauncherScene::setDeleteShortCutMode_EM(bool b)
{
	return false;
}

bool 
LauncherScene::setBlockFocus_EM(int index)
{
	if(index == -1)
	{
		m_ppEditBkFocusAnm[1]->finishAnimation();
		m_ppEditBkFocusAnm[1]->Fly();
		return true;
	}
	
#if _LAUNCHER_EDITMENU_OLDSTYLE_
	setEditMenuPos(m_ppBlocklist[index]->getMenuPos(index));
	setEditMenuFlag(m_ppBlocklist[index]->getMenuFlag());
#else
	if(getCurrentFocusIndex_EM() != index)
	{
		getBlockByID(getCurrentFocusIndex_EM())->hideMenu();
		getBlockByID(getCurrentFocusIndex_EM())->setMaskVisible(true);
		//MYLOGI("hide %d \n", getCurrentFocusIndex_EM());
	}
	getBlockByID(index)->showMenu();
	getBlockByID(index)->setMaskVisible(false); 
	//MYLOGI("show %d \n\n", index);
#endif // _LAUNCHER_EDITMENU_OLDSTYLE_

	return true;
}

bool 
LauncherScene::setBlockFocus_EM(eFlyDirection e)
{
	if (e == LEFT)
	{
		if (getCurrentFocusIndex_EM() > 1)
		{
			if (getBlockByID(getCurrentFocusIndex_EM())->isDelete())
			{
				getBlockByID(getCurrentFocusIndex_EM())->setMyBlockFocusVisible(false);

				getBlockByID(getCurrentFocusIndex_EM() - 1)->showMenu();
				getBlockByID(getCurrentFocusIndex_EM() - 1)->setMaskVisible(false);
			}
			else
			{
				setBlockFocus_EM(getCurrentFocusIndex_EM() - 1);
			}
			return true;
		}
	}
	else if (e == RIGHT)
	{
		if (getCurrentFocusIndex_EM() < getTotalBlockNum() - 1)
		{
			if (getBlockByID(getCurrentFocusIndex_EM() + 1)->isDelete())
			{
				getBlockByID(getCurrentFocusIndex_EM() + 1)->setMyBlockFocusVisible(true);
				getBlockByID(getCurrentFocusIndex_EM())->hideMenu();
				getBlockByID(getCurrentFocusIndex_EM())->setMaskVisible(true);
				Block::getEditFocus()->setVisible(false);
			}
			else
			{
				setBlockFocus_EM(getCurrentFocusIndex_EM() + 1);
			}
		   return true;
		}
	}
	return false;
}

bool
LauncherScene::addBlock_EM()
{
	deletedBlockNum--;
	if ( getCurrentFocusIndex_EM() <  getTotalBlockNum())
	{
		//m_ppBlocklist[m_editBlockFocusID]->addMyBlock();
		getBlockByID(getCurrentFocusIndex_EM())->addMyBlock();
		getBlockByID(getCurrentFocusIndex_EM())->showMenu();
		return true;
	}
	return false;
}

bool 
LauncherScene::deleteBlock_EM()
{
	deletedBlockNum++;
	m_ppBlocklist[m_editBlockFocusID]->deleteMyBlock();
	if (m_editblockRightTranNum < getTotalBlockNum() -  _MAX_BLOCKS_EDIT_PER_SCREEN)
	{
		transformEditBlockAnm_EM(RIGHT);
		if (m_curEditBlockIdxPerScreen.min_idx >= 1)
		{
			m_curEditBlockIdxPerScreen.min_idx--;
			m_curEditBlockIdxPerScreen.max_idx--;
			nextEditBlockBldAni = Right_Ani;
			m_editblockLeftTranNum--;
			m_editblockRightTranNum++;
		}
	}

	if (getCurrentFocusIndex_EM() != 1)
	{
		setBlockFocus_EM(LEFT);
	}
	else
	{
		setBlockFocus_EM(RIGHT);
	}

	if (getCurrentFocusIndex_EM() != getTotalBlockNum() - 1)
	{
		for (int i = getCurrentFocusIndex_EM(); i < getTotalBlockNum() - 1; i++)
		{
			switchBlockIndex_EM(i, i + 1);
		}
	}

	if (getCurrentFocusIndex_EM() != 1)
	{
		setCurrentFocusIndex_EM(getCurrentFocusIndex_EM() - 1);
	} 
	
	return true;
}

bool 
LauncherScene::deleteShortCut_EM(ViewNode* pObj)
{
	return true;
}

int 
LauncherScene::getCurrentFocusIndex_EM()
{
	return m_editBlockFocusID;
}

void 
LauncherScene::setCurrentFocusIndex_EM(int idx)
{
	m_editBlockFocusID = idx;
}

bool 
LauncherScene::blockRename_EM(gkString rename)
{
	return true;
}

void 
LauncherScene::createEditBkFocusAnm_EM()
{
	if (!m_ppEditBkFocusAnm[0] && !m_ppEditBkFocusAnm[1])
	{
		m_ppEditBkFocusAnm[0] = new TranslationAnm(m_pScene,m_ppBlocklist[1]->getBlockParentPlane(),"focusIn");
		m_ppEditBkFocusAnm[1] = new TranslationAnm(m_pScene,m_ppBlocklist[1]->getBlockParentPlane(),"focusOut");
		m_ppEditBkFocusAnm[0]->setAnmListener(this);
		m_ppEditBkFocusAnm[1]->setAnmListener(this);

		m_ppEditBkFocusAnm[0]->To(m_ppBlocklist[1]->getBlockParentPlane()->getPosition()+_FOCUSIN_OFFSET_EM_,
			m_ppBlocklist[1]->getBlockParentPlane()->getScale(),false);
		m_ppEditBkFocusAnm[1]->To(m_ppBlocklist[1]->getBlockParentPlane()->getPosition(),
			m_ppBlocklist[1]->getBlockParentPlane()->getScale(),false);
		m_ppEditBkFocusAnm[1]->From(m_ppBlocklist[1]->getBlockParentPlane()->getPosition()+_FOCUSIN_OFFSET_EM_,
			m_ppBlocklist[1]->getBlockParentPlane()->getScale());
	}
	
}

bool
LauncherScene::isHitExitNode_EM(Ogre::RaySceneQueryResult& objArray)
{
	return m_pExitEditModeIcon?isObjInArray(objArray,m_pExitEditModeIcon):false;
}


int 
LauncherScene::getTotalBlockNum()
{
	return m_totalBlockNumEdit;
}

void
LauncherScene::setTotalBlockNum(int num)
{
	m_totalBlockNumEdit = num;
}

void 
LauncherScene::onBlenderAnmFinish(BlenderAnimation* p,int s,int e)
{
	if (isInEditMode()&&p == m_pBldAnm)
	{

		if (nextEditBlockBldAni == Enter_Ani)
		{
			setBlockFocus_EM(1);
			initEditFocus();
			nextEditBlockBldAni = Left_Ani;
			hasEnterEditAniFinished = true;
		}
		else if (nextEditBlockBldAni == Left_Ani)
		{
			flyMenuFocus_EM();
			nextEditBlockBldAni = None;
			if (getBlockByID(getCurrentFocusIndex_EM())->isDelete())
			{
				Block::getEditFocus()->setVisible(false);
			}
		}
		else if ( nextEditBlockBldAni == Right_Ani)
		{
			flyMenuFocus_EM();
			nextEditBlockBldAni = None;
			Block::getEditFocus()->setVisible(true);
		}
	}
	else if (!isInEditMode()&&p == m_pEditPageAnm)
	{
		blockWholeTranslation(1,m_currentID);
 	}
}

void 
LauncherScene::onTranslationAnmFinish(TranslationAnm* p)
{
	if ( !isInEditMode() && p == m_ppEditBkFocusAnm[1])
	{
		m_pBldAnm->play();
		m_pEditPageAnm->play();
		m_pExitEMAnm->play();
		for (int i = 0;i<__MAX_BLOCK_NUM;i++)
		{
			m_ppBlocklist[i]->playAnimation();
		}
	}
	else if (isInEditMode() && p == Block::getFocusEditAnm())
	{
		hasFinishEditSBA = true;
	}
}


void 
LauncherScene::hideEditMenu(BlenderAnmInterface* pInterface)
{
	getBlockByID(getCurrentFocusIndex_EM())->hideMenu(pInterface);
}

