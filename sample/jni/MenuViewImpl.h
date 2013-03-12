//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : MenuViewImpl.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_MENUVIEWIMPL_H)
#define _MENUVIEWIMPL_H

#include "RootViewImpl.h"

class MenuView;
class MenuViewImpl :public RootViewImpl
{
public:
	MenuViewImpl();
	~MenuViewImpl();

	void setMenuVisible(bool v);
	bool getMenuVisible();
	bool isHitSetHomeApps();
	bool isHitUninstallApps();
	void onHitSetHomeApps();
	void onHitUninstallApps();

	bool moveFocus(eFlyDirection direct);	// 移动focus
	bool MoveViewFocus(RootViewImpl* pPreImpl,eFlyDirection direction);
	bool setViewNodeFocus(ViewNode* pNode);		// 设置viewNode* 为当前focus
	ViewNode* getCurrentViewNode();			
	void onClickViewNode(ViewNode* pNode);
	void onLoseFocus();
	void onHitCurrentNode();
private:
	MenuView* m_pMenuView;
};

#endif  //_MENUVIEWIMPL_H
