//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : AaAppsView.h
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#if !defined(_AABACKGROUNDVIEW_H)
#define _AABACKGROUNDVIEW_H

#include <gkGameObject.h>
#include "Rootview.h"
#include "AaViewport.h"
#include "DataBaseImpl.h"
#include "TranslationAnmInterface.h"


class AaAppsView:public RootView,public TranslationAnmInterface 
{
public:
	AaAppsView(const gkString& str,bool visible = true);
	~AaAppsView();
	DataBaseImpl* getDataBase();
	ViewNode* getParentNode();
	void setMoveVector(gkVector3 gVector,bool anm = false);		// ����AA���ƶ�����
	void onTranslationAnmFinish(TranslationAnm* pAnm);
	void upDateAnm(gkScalar time);
	
	virtual ViewNode* isHitViewNode(Ogre::RaySceneQueryResult& objArray);
	void setStickFocus(ViewNode* pNode);
	ViewNode* getStickFocus();
	virtual bool setFocus(ViewNode* node);
	virtual bool setFocus(int vindex);
	virtual void loseViewFocus() = 0;
protected:
	virtual void showView();
	virtual void hideView();
private:
	ViewNode* m_pParentNode;
	ViewNode* m_pPreFocusNode;	// ��¼�����������FocusӦ������Node
	TranslationAnm* m_pTransAnm;//ogre����
	static AaViewport* m_pAaViewPort;
protected:
	static DataBaseImpl* m_pDataBase;
};

#endif  //_AABACKGROUNDVIEW_H