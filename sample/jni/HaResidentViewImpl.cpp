//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : ScrollbarView.cpp
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#include "HaResidentViewImpl.h"
#include "HaResidentView.h"
#include "ViewNode.h"

HaResidentViewImpl::HaResidentViewImpl()
{
	m_pResidentView = new HaResidentView();
	setRootView(m_pResidentView);
}
HaResidentViewImpl::~HaResidentViewImpl()
{
	ui_delete(m_pResidentView);
}

bool 
HaResidentViewImpl::isHitMovieButton()
{
	return m_pResidentView->isHitMovieButton();
}

bool 
HaResidentViewImpl::isHitFavoriteButton()
{
	return m_pResidentView->isHitFavoriteButton();
}

bool 
HaResidentViewImpl::isHitExitButton()
{
	return m_pResidentView->isHitExitButton();
}

bool 
HaResidentViewImpl::moveFocus(eFlyDirection direct)	// �ƶ�focus
{
	return true;// m_pResidentView->moveFocus(direct);
}

bool 
HaResidentViewImpl::MoveViewFocus(RootViewImpl* pPreImpl,eFlyDirection direction)
{
	return false;
}
bool 
HaResidentViewImpl::setViewNodeFocus(ViewNode* pApp)		// ����viewNode* Ϊ��ǰfocus
{
	return m_pResidentView->setFocus(pApp->getMinIndex());
}

ViewNode* 
HaResidentViewImpl::getCurrentViewNode()
{
	return m_pResidentView->getFocus();
}

void 
HaResidentViewImpl::onClickViewNode(ViewNode* pNode)
{

}
void 
HaResidentViewImpl::onLoseFocus()
{

}

void
HaResidentViewImpl::onHitCurrentNode()
{

}