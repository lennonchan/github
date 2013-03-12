//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : GameObjMaker.cpp
//  @ Date : 2012-11-20
//  @ Author : 
//
//

#include "GameObjMaker.h"
 #include "gkGameObjectManager.h"
// #include "gkGameObject.h"
 #include "gkEntity.h"
#include "LauncherScene.h"
#include "Util.h"

using namespace std;

gkString i2string(int n)
{
	char tmp[5];
	memset(tmp,0,5);
	sprintf(tmp,"%d",n);
	gkString s;
	s = tmp;
	return s;
}

gkGameObject* 
GameObjMaker::makeGameObjByAppUnit(AppUnit* pApp,int name,gkGameObject* pObjTemplate)
{
	gkGameObject* pObj = NULL;
	if(pObjTemplate)
		pObj = pObjTemplate->cloneGameObject(i2string(name));
	else
		pObj = gkGameObjectManager::getSingleton().createObject(i2string(name));
	return pObj;
}

gkVector3	
GameObjMaker::getPosByIndex(int index)
{
	gkVector3 temp(0,0,0);
	temp.x += (index%_APP_COLNUM_)*_COL_SPACE_;
	temp.y -= (index/_APP_COLNUM_)*_ROW_SPACE_;

	return temp;
}

void
GameObjMaker::adjustGameObjPos(const vector<AppUnit*>* const pVector,gkGameObject* parent)
{
	unsigned int size = pVector->size();
	gkGameObject* pGameObject;
	for (unsigned int i = 0,j = 0;i<size;i++)
	{
		pGameObject = (*pVector)[i]->getGameObj();
		if(!pGameObject)
		{
			(*pVector)[i]->setGameObj(makeGameObjByAppUnit((*pVector)[i],i,parent));
			pGameObject = (*pVector)[i]->getGameObj();
			pGameObject->setParent(parent);
			pGameObject->getEntity()->setGLTextureID(_APP_BACKGROUND_INDEX_,0,LauncherScene::getBgColors()[i%_GLOBLE_BG_COLORNUM_]);
			pGameObject->setSubEntityVisible(_APP_CROSS_INDEX_,false);
			pGameObject->setSubEntityVisible(_APP_X_INDEX_,false);
			pGameObject->setSubEntityVisible(_APP_HEART_INDEX_,false);
			pGameObject->setObjectClipEnable(true);
			pGameObject->setVisible(false);
		}
		if (pGameObject&&pGameObject->getVisible())
		{
			pGameObject->setPosition(getPosByIndex(j++));
			pGameObject->setOrientation(gkQuaternion(1,0,0,0));
			pGameObject->setScale(gkVector3(1,1,1));
		}
	}
}