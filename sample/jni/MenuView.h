//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : MenuView.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_MENUVIEW_H)
#define _MENUVIEW_H

#include "RootView.h"

class BlenderAnimation;
class MenuView :public RootView
{
public:
	MenuView();
	~MenuView();
	void setVisible(bool visible = true);
	bool getVisible();
	bool isHitSetHomeApps(Ogre::RaySceneQueryResult& objArray);
	bool isHitUninstallApps(Ogre::RaySceneQueryResult& objArray);
	int getSetHomeNodeIndex();
	int getUninstallNodeIndex();
	virtual void loseViewFocus();
private:
	inline void showMenu();
	inline void hideMenu();
	inline void setTimePosition(int start,int end);
private:
	ViewNode** m_ppNodeList;
	bool m_visible;
	gkScene* m_pScene;
	gkGameObject* m_pMenuNode;		// menu 根节点
	gkGameObject* m_pHomeApp;		// 首页编辑
	gkGameObject* m_pUninstall;		// 卸载应用
	BlenderAnimation* m_pBldAnm;
	BlenderAnimation* m_pBldAnm1;
};

#endif  //_MENUVIEW_H
