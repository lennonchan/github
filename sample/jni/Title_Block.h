//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : Recommand Block.h
//  @ Date : 2012-11-6
//  @ Author : 
//
//


#if !defined(_TITLE_BLOCK_H)
#define _TITLE_BLOCK_H

#include "Block.h"

#define _TCL_ALLAPP_	"TCL.AllApp"
typedef utArray<int>		BlenderAnmList;

class TitleBlock :public Block 
{
public:
	TitleBlock(gkScene*);
	~TitleBlock();
	virtual BlockEnum getBlockEnum(); 
	bool isFocusOnAllAppButton();
	virtual bool flyfocus(ViewNode* pDestFocusNode); 
	virtual bool flyfocus(eFlyDirection e,ViewNode* pFocusNode = NULL);
	virtual void onLoseFocus();
	void setAnmTimeScope(int istart,int iend);
	void playPageAnm();
	void setTitleBlockVisable(bool isVisable);
	void finishAllAnm();
protected:
	void onBlenderAnmFinish(BlenderAnimation* p,int s,int e);
private:
	void playAllAnmAsync();
	bool playFocusAnm(eFlyDirection e,ViewNode* pFocusNode = NULL);
private:
	BlenderAnimation** m_ppBldAnmArray;
	BlenderAnmList m_AnmList;
	AppUnit* m_pAllApp;
	gkGameObject * pTitleWord;
};

#endif  //_TITLE_BLOCK_H