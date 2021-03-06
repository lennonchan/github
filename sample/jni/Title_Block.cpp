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


#include "Title_Block.h"
#include "FocusMovePath.h"
#include "RootView.h"
#include "gkEntity.h"

#define	_TT_BLOCK_PLANE0_	"Plane_x02x"	

#define	_TT_BLOCK_WORD_	"Plane_ba01"	// 畅游应用

#define	_TT_BLOCK_CIRCLE1_	"Plane_ba02"	// 应用商店
#define	_TT_BLOCK_CIRCLE2_	"Plane_ba03"	// 所有应用
#define	_TT_BLOCK_CIRCLE3_	"Plane_ba04"	// TV icon


#define _TT_BLOCK_NUM_	6

#define	_TT_BLOCK_PLANE1B_	"Plane_ba02b"	// 应用商店
#define	_TT_BLOCK_PLANE2B_	"Plane_ba03b"	// 所有应用
#define	_TT_BLOCK_PLANE3B_	"Plane_ba04b"	// TV icon

#define	_TT_BLOCK_ANM0_	"Plane_ba02Action.002"
#define _TT_BLOCK_ANM9_	"Plane_ba02Action"
#define	_TT_BLOCK_ANM1_	"Plane_ba02bAction"
#define	_TT_BLOCK_ANM2_	"Plane_ba03Action.002"
#define	_TT_BLOCK_ANM3_	"Plane_ba03Action.001"
#define	_TT_BLOCK_ANM4_	"Plane_ba03bAction"
#define	_TT_BLOCK_ANM5_	"Plane_ba04Action.002"
#define	_TT_BLOCK_ANM6_	"Plane_ba04Action.001"
#define	_TT_BLOCK_ANM7_	"Plane_ba04bAction"
#define	_TT_BLOCK_ANM8_	"Plane_x02xAction"

#define _TT_BLOCK_ANMNUM_	10

TitleBlock::TitleBlock(gkScene* pscene):Block(pscene),m_ppBldAnmArray(NULL)
{
	if (m_pScene)
	{
		pTitleWord = m_pScene->getObject(_TT_BLOCK_WORD_);
		m_AnmList = BlenderAnmList();
		m_ppShortcutList = new AppUnitShortcut*[_TT_BLOCK_NUM_];
		m_ppShortcutList[0] = (new AppUnitShortcut(m_pScene,_TT_BLOCK_CIRCLE1_))->setIndex(-6,-6);
		m_ppShortcutList[1] = (new AppUnitShortcut(m_pScene,_TT_BLOCK_CIRCLE2_))->setIndex(-5,-5);
		m_ppShortcutList[2] = (new AppUnitShortcut(m_pScene,_TT_BLOCK_CIRCLE3_))->setIndex(-4,-4);
		m_ppShortcutList[3] = (new AppUnitShortcut(m_pScene, _TT_BLOCK_PLANE1B_));
		m_ppShortcutList[4] = (new AppUnitShortcut(m_pScene, _TT_BLOCK_PLANE2B_));
		m_ppShortcutList[5] = (new AppUnitShortcut(m_pScene, _TT_BLOCK_PLANE3B_));

		m_ShortCutNum = _TT_BLOCK_NUM_;
		m_BlockParentPlane = m_pScene->getObject(_TT_BLOCK_PLANE0_);

		m_ppBldAnmArray = new BlenderAnimation*[_TT_BLOCK_ANMNUM_];

		m_ppBldAnmArray[0] = new BlenderAnimation(m_pScene,m_BlockParentPlane,_TT_BLOCK_ANM8_);
		m_ppBldAnmArray[1] = new BlenderAnimation(m_pScene,m_ppShortcutList[0]->getGameObj(),_TT_BLOCK_ANM0_);
		m_ppBldAnmArray[2] = new BlenderAnimation(m_pScene,m_ppShortcutList[1]->getGameObj(),_TT_BLOCK_ANM2_);
		m_ppBldAnmArray[3] = new BlenderAnimation(m_pScene,m_ppShortcutList[2]->getGameObj(),_TT_BLOCK_ANM5_);
		m_ppBldAnmArray[9] = new BlenderAnimation(m_pScene,m_ppShortcutList[0]->getGameObj(),_TT_BLOCK_ANM9_);
		m_ppBldAnmArray[4] = new BlenderAnimation(m_pScene,m_pScene->getObject(_TT_BLOCK_PLANE1B_),_TT_BLOCK_ANM1_);
		m_ppBldAnmArray[5] = new BlenderAnimation(m_pScene,m_ppShortcutList[1]->getGameObj(),_TT_BLOCK_ANM3_);
		m_ppBldAnmArray[6] = new BlenderAnimation(m_pScene,m_pScene->getObject(_TT_BLOCK_PLANE2B_),_TT_BLOCK_ANM4_);
		m_ppBldAnmArray[7] = new BlenderAnimation(m_pScene,m_ppShortcutList[2]->getGameObj(),_TT_BLOCK_ANM6_);
		m_ppBldAnmArray[8] = new BlenderAnimation(m_pScene,m_pScene->getObject(_TT_BLOCK_PLANE3B_),_TT_BLOCK_ANM7_);
		/*m_pScene->getObject(_TT_BLOCK_PLANE1B_)->setVisible(false);
		m_pScene->getObject(_TT_BLOCK_PLANE2B_)->setVisible(false);
		m_pScene->getObject(_TT_BLOCK_PLANE3B_)->setVisible(false);*/
		

		for (int i = 0;i<_TT_BLOCK_ANMNUM_;i++)
		{
			m_ppBldAnmArray[i]->setAnmInterface(this);
		}
		//m_BlockParentPlane = m_pScene->getObject(_FT_BLOCK_PARENT_);
		//m_BlockParentPlane->setVisible(false);
		//m_pBldAnm = new BlenderAnimation(m_pScene,m_BlockParentPlane,_FT_BLOCK_ANM_NAME_);
		m_pAllApp = new AppUnit(m_pScene,_TCL_ALLAPP_);
		m_pAllApp->setPackageName(_TCL_ALLAPP_);
		//m_pAllApp->setPackageName(_TCL_ALLAPP_);
		m_ppShortcutList[1]->setApp(m_pAllApp);
	}
}

TitleBlock::~TitleBlock() 
{
	ui_delete(m_pAllApp);
}

BlockEnum
TitleBlock::getBlockEnum()
{
	return Title_Block;
}

bool 
TitleBlock::isFocusOnAllAppButton()
{
	return m_ppShortcutList[1] == m_pCurrentFocus;
}

bool 
TitleBlock::flyfocus(ViewNode* pDestFocusNode)
{
	finishAllAnm();
	for (int i = 0;i<_TT_BLOCK_NUM_;i++)
	{
		if(m_pCurrentFocus == m_ppShortcutList[i])
		{
			m_AnmList.push_back((i+1)*2);
		}
	}

	if(!Block::flyfocus(pDestFocusNode))
	{
		if(pDestFocusNode != m_pCurrentFocus)
			playAllAnmAsync();
		m_AnmList.clear();
		return false;
	}


	for (int i = 0;i<_TT_BLOCK_NUM_;i++)
	{
		if(m_pCurrentFocus == m_ppShortcutList[i])
		{
			m_AnmList.push_back((i+1)*2-1);
		}
	}
	playAllAnmAsync();
	return true;
}

bool 
TitleBlock::flyfocus(eFlyDirection e,ViewNode* pFocusNode)
{
	finishAllAnm();
	for (int i = 0;i<_TT_BLOCK_NUM_;i++)
	{
		if(m_pCurrentFocus == m_ppShortcutList[i])
		{
			m_AnmList.push_back((i+1)*2);
			break;
		}
	}

	if(!playFocusAnm(e,pFocusNode))
	{
		/*if(e == DOWN)
			playAllAnmAsync();
		m_AnmList.clear();*/
		return false;
	}

	for (int i = 0;i<_TT_BLOCK_NUM_;i++)
	{
		if(m_pCurrentFocus == m_ppShortcutList[i])
		{
			m_AnmList.push_back((i+1)*2-1);
			break;
		}
	}
	playAllAnmAsync();
	return true;
}

bool 
TitleBlock::playFocusAnm(eFlyDirection e,ViewNode* pFocusNode)
{
	ViewNode* pShortcup = FocusMovePath::getNextFocusNode_HomeBlock((ViewNode**)m_ppShortcutList,pFocusNode?pFocusNode:m_pCurrentFocus,e,this->getShortcutsNum());
	if(!pShortcup)
		return false;
	static bool bFinish = false;
	if(bFinish)
		pFocus->finishAnimation();
	bFinish = true;
	((gkEntity*)m_pFocus)->setGLTextureID(0,0,RootView::getCircleTextureID());
	pFocus->To(pShortcup->getPosition()-m_pScene->getObject("Plane_x00")->getPosition(),pShortcup->getScale()*1.05f);
	pFocus->Fly();
	this->m_pCurrentFocus = (AppUnitShortcut*)pShortcup;

	return true;
}

void 
TitleBlock::onLoseFocus()
{
	playAllAnmAsync();
	m_pCurrentFocus = NULL;
}

void 
TitleBlock::playAllAnmAsync()
{
#define _TT_P0ANM_ENTER_START_	790
#define _TT_P0ANM_ENTER_END_	805
#define _TT_P0ANM_EXIT_START_	805
#define _TT_P0ANM_EXIT_END_		810
#define _TT_P1ANM_ENTER_START_	810
#define _TT_P1ANM_ENTER_END_	825
#define _TT_P1ANM_EXIT_START_	825
#define _TT_P1ANM_EXIT_END_		830
#define _TT_P2ANM_ENTER_START_	830
#define _TT_P2ANM_ENTER_END_	845
#define _TT_P2ANM_EXIT_START_	845
#define _TT_P2ANM_EXIT_END_		850

	int timeArray[] = {
		_TT_P0ANM_ENTER_START_	,
		_TT_P0ANM_ENTER_END_	,
		_TT_P0ANM_EXIT_START_	,
		_TT_P0ANM_EXIT_END_		,
		_TT_P1ANM_ENTER_START_	,
		_TT_P1ANM_ENTER_END_	,
		_TT_P1ANM_EXIT_START_	,
		_TT_P1ANM_EXIT_END_		,
		_TT_P2ANM_ENTER_START_	,
		_TT_P2ANM_ENTER_END_	,
		_TT_P2ANM_EXIT_START_	,
		_TT_P2ANM_EXIT_END_		,
	};

	if (m_AnmList.empty())
		return;
	if(m_AnmList.size()>=2 && m_AnmList.at(0)+1 == m_AnmList.at(1))
	{
		setAnmTimeScope(timeArray[m_AnmList.at(0)*2-2],timeArray[m_AnmList.at(1)*2-1]);
		m_AnmList.clear();
	}
	else
	{
		setAnmTimeScope(timeArray[m_AnmList.at(0)*2-2],timeArray[m_AnmList.at(0)*2-1]);
	}

	for (int i = 0;i<_TT_BLOCK_ANMNUM_;i++)
	{
		m_ppBldAnmArray[i]->play();
	}

}

void 
TitleBlock::playPageAnm()
{
	//finishAllAnm();
	for (int i = 0;i<=_TT_BLOCK_NUM_;i++)
	{
		m_ppBldAnmArray[i]->play();
	}
}

void 
TitleBlock::setAnmTimeScope(int istart,int iend)
{
	//gkPrintf("setAnmTimeScope start = %d,end = %d\n",istart,iend);
	for (int i = 0;i<_TT_BLOCK_ANMNUM_;i++)
	{
		m_ppBldAnmArray[i]->setFrameScope(istart,iend);
	}
}

//static int tttt = 0;
void 
TitleBlock::finishAllAnm()
{
	for (int i = 0;i<_TT_BLOCK_ANMNUM_;i++)
	{
		m_ppBldAnmArray[i]->finishAnm();
	}
	m_AnmList.clear();
	//tttt++;
}

void 
TitleBlock::onBlenderAnmFinish(BlenderAnimation* p,int s,int e)
{
	//if(p == m_ppBldAnmArray[1])
	//	gkPrintf("m_ppBldAnmArray[1] finish,s = %d,e = %d\n",s,e);
	for (int i = 0;i<_TT_BLOCK_ANMNUM_;i++)
	{
		if(m_ppBldAnmArray[i]->isPlaying())
			return;
	}

	if (!m_AnmList.empty())
	{
		m_AnmList.erase(m_AnmList.at(0));
	}

	if(!m_AnmList.empty())
		playAllAnmAsync();
}


void 
TitleBlock::setTitleBlockVisable(bool isVisable)
{
	m_BlockParentPlane->setVisible(isVisable);
	pTitleWord->setVisible(isVisable);
	for (int i = 0; i < _TT_BLOCK_NUM_; i++)
	{
		m_ppShortcutList[i]->getGameObj()->setVisible(isVisable);
	}
	
}