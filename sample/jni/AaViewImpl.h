//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : AaViewImpl.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_AAVIEWIMPL_H)
#define _AAVIEWIMPL_H

#include "AaAppsViewImpl.h"
#include "AaResidentView.h"
#include "Aaview.h"

class AppsViewUtil;
class AaViewImpl :public AaAppsViewImpl
{
public:
	AaViewImpl();
	~AaViewImpl();
	//virtual void onTick(gkScalar time);
	static AaViewImpl* getInstance();
	void setUninstallAppMode(bool flag = true);
	bool isUninstallAppMode();
	AppUnit* getCurrentApp();
	AppUnit* isHitApp_AA(Ogre::RaySceneQueryResult& objArray);
	
	//bool moveFocus(eFlyDirection direct);	// �ƶ�focus
	//bool MoveViewFocus(RootViewImpl* pPreImpl,eFlyDirection direction);		
	void onClickViewNode(ViewNode*);
	void onLoseFocus();
	void onHitCurrentNode();
private:
	bool m_isUninstallMode;
	Aaview* m_pAaView;
	AppsViewUtil*	m_pViewUtil;
	static AaViewImpl* mInstance;
};

#endif  //_AAVIEWIMPL_H
