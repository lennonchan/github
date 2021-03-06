//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : SortordViewImpl.cpp
//  @ Date : 2012-11-10
//  @ Author : 
//
//


#include "SortordViewImpl.h"
#include "SortordView.h"
#include "FocusMovePath.h"
#include "LetterViewImpl.h"

#define  _AASORTORD_COLNUM_ 1
SortordViewImpl::SortordViewImpl(AaAppsViewImpl* pBgImpl):
			m_pSortView(NULL),m_pBgImpl(pBgImpl)
{
	m_pSortView = new SortordView();
	setRootView(m_pSortView);
}

SortordViewImpl::~SortordViewImpl()
{
	ui_delete(m_pSortView);
	m_pBgImpl = NULL;
}

void 
SortordViewImpl::setSortordVisible(bool flag)
{
	m_pSortView->setSortordVisible(flag);
}

bool 
SortordViewImpl::getSortordVisible()
{
	return m_pSortView->getSortordVisible();
}

bool 
SortordViewImpl::isHitStDefault(Ogre::RaySceneQueryResult& objArray)
{
	return m_pSortView->isHitStDefault(objArray);
}

bool 
SortordViewImpl::isHitStFrequence(Ogre::RaySceneQueryResult& objArray)
{
	return m_pSortView->isHitStFrequence(objArray);
}

bool 
SortordViewImpl::isHitStLetter(Ogre::RaySceneQueryResult& objArray)
{
	return m_pSortView->isHitStLetter(objArray);
}

bool 
SortordViewImpl::isFocusOnStDefault()
{
	return m_pSortView->isFocusOnStDefault();
}

bool 
SortordViewImpl::isFocusOnStFrequence()
{
	return m_pSortView->isFocusOnStFrequence();
}

bool 
SortordViewImpl::isFocusOnHitStLetter()
{
	return m_pSortView->isFocusOnHitStLetter();
}

void 
SortordViewImpl::enterAaMode()
{
	m_pSortView->enterAaMode();
}

void 
SortordViewImpl::exitAaMode()
{
	m_pSortView->exitAaMode();
}

void 
SortordViewImpl::onHitStDefault()
{
	if(m_pBgImpl->appSort(ST_DEFAULT))
	{
		m_pBgImpl->update();
		m_pBgImpl->setRightViewImpl(NULL);
	}
}

void 
SortordViewImpl::onHitStFrequence()
{
	if(m_pBgImpl->appSort(ST_FREQUENCE))
	{
		m_pBgImpl->update();
		m_pBgImpl->setRightViewImpl(NULL);
	}
}

void 
SortordViewImpl::onHitStLetter()
{
	if(m_pBgImpl->appSort(ST_NAME))
	{
		m_pBgImpl->update();
		m_pBgImpl->setRightViewImpl(LetterViewImpl::getSingletonPtr());
	}
}

RootView* 
SortordViewImpl::getRootView()
{
	return m_pSortView;
}

bool 
SortordViewImpl::moveFocus(eFlyDirection direct)	// 移动focus
{
	ViewNode* pResult = FocusMovePath::getNextFocusNode_AA(m_pSortView->getViewNodeList(),
		m_pSortView->getViewNodeNum(),m_pSortView->getFocus()->getMinIndex(),direct,_AASORTORD_COLNUM_);
	if(pResult)
	{
		m_pSortView->setFocus(pResult);
		return true;
	}
	return false;
}

bool 
SortordViewImpl::MoveViewFocus(RootViewImpl* pPreImpl,eFlyDirection direction)
{
	return true;
}

bool 
SortordViewImpl::setViewNodeFocus(ViewNode* pNode)		// 设置viewNode* 为当前focus
{
	if(!pNode)
		return false;

	return m_pSortView->setFocus(pNode);
}

ViewNode* 
SortordViewImpl::getCurrentViewNode()
{
	return m_pSortView->getFocus();
}

void 
SortordViewImpl::onClickViewNode(ViewNode* pNode)
{

}

void 
SortordViewImpl::onLoseFocus()
{

}

void 
SortordViewImpl::onHitCurrentNode()
{

}