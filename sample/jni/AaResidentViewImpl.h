//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : AaResidentViewImpl.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_AARESIDENTVIEWIMPL_H)
#define _AARESIDENTVIEWIMPL_H

#include "Aabridge.h"
#include "RootViewImpl.h"
#include "Block.h"

class AaResidentView;
class SortordViewImpl;
class AaResidentViewImpl :public RootViewImpl
{
public:
	AaResidentViewImpl(SortordViewImpl* pSortImpl);
	~AaResidentViewImpl();
	void setThumbBlock(Block * pBlock);
	bool isHitTvButton(Ogre::RaySceneQueryResult& objArray);
	bool isHitAppMarketButton(Ogre::RaySceneQueryResult& objArray);
	bool isHitSortButton(Ogre::RaySceneQueryResult& objArray);
	bool isFocusOnTvButton();
	bool isFocusOnMarket();
	bool isFocusOnSortButton();
	bool onClickTvButton();
	bool onClickAppMarketButton();
	bool onClickSortButton();

	bool moveFocus(eFlyDirection direct);	// 移动focus
	bool MoveViewFocus(RootViewImpl* pPreImpl,eFlyDirection direction);
	bool setViewNodeFocus(ViewNode*);		// 设置viewNode* 为当前focus
	ViewNode* getCurrentViewNode();			
	void onClickViewNode(ViewNode*);
	void onLoseFocus();
	void onHitCurrentNode();
private:
	AaResidentView* m_pResidentView;
	SortordViewImpl* m_pSortImpl;
	Block* m_pThumbBlock;
};

#endif  //_AARESIDENTVIEWIMPL_H
