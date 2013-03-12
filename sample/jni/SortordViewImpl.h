//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : SortordViewImpl.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_SORTORDVIEWIMPL_H)
#define _SORTORDVIEWIMPL_H

#include "RootViewImpl.h"
#include "AaAppsViewImpl.h"

class SortordView;

class SortordViewImpl :public RootViewImpl
{
	friend class Aabridge;
public:
	SortordViewImpl(AaAppsViewImpl* pBgImpl = NULL);
	~SortordViewImpl();

	void setSortordVisible(bool flag);
	bool getSortordVisible();
	bool isHitStDefault(Ogre::RaySceneQueryResult& objArray);
	bool isHitStFrequence(Ogre::RaySceneQueryResult& objArray);
	bool isHitStLetter(Ogre::RaySceneQueryResult& objArray);
	bool isFocusOnStDefault();
	bool isFocusOnStFrequence();
	bool isFocusOnHitStLetter();

	void onHitStDefault();
	void onHitStFrequence();
	void onHitStLetter();

	RootView* getRootView();
	bool moveFocus(eFlyDirection direct);	// �ƶ�focus
	bool MoveViewFocus(RootViewImpl* pPreImpl,eFlyDirection direction);
	bool setViewNodeFocus(ViewNode*);		// ����viewNode* Ϊ��ǰfocus
	ViewNode* getCurrentViewNode();			
	void onClickViewNode(ViewNode*);
	void onLoseFocus();
	void onHitCurrentNode();
protected:
	void enterAaMode();
	void exitAaMode();
private:
	SortordView* m_pSortView;
	AaAppsViewImpl* m_pBgImpl;
};

#endif  //_SORTORDVIEWIMPL_H