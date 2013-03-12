//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : AppUnit.cpp
//  @ Date : 2012-11-20
//  @ Author : 
//
//


#include "AppUnit.h"
#include "Aabridge.h"
#include "OgreTextureUnitState.h"
#include "gkEntity.h"

AppUnit::AppUnit(AppDataInfo& info):
	ViewNode(Aabridge::getScene(),info.AppName)
{
	m_AppInfo = info;
	m_isDataChanged = false;
}

AppUnit::AppUnit(gkScene*pScene,const gkHashedString& str):
	ViewNode(pScene,str)
{
	m_AppInfo = AppDataInfo();
	m_isDataChanged = false;
}

AppUnit::~AppUnit()
{
}

void 
AppUnit::setAppDataInfo(AppDataInfo& info)
{
	m_isDataChanged = true;
	m_AppInfo = info;
}

const char* 
AppUnit::getChar()
{
	return m_AppInfo.appenglishname.c_str();
}

int 
AppUnit::getID()
{
	return m_AppInfo.AppID;
}

int 
AppUnit::getPlateName()
{
	return m_AppInfo.iconPositon;
}

void 
AppUnit::setPlateName(int pn)
{
	m_isDataChanged = true;
	m_AppInfo.iconPositon = pn;
}

void 
AppUnit::setHeartVisible(bool v)
{
	getGameObj()->setSubEntityVisible(_APP_HEART_INDEX_,v);
}

gkString 
AppUnit::getAppName()
{
	return m_AppInfo.AppName;
}

gkString 
AppUnit::getPackageName()
{
	return m_AppInfo.PackageName;
}

gkString 
AppUnit::getActivityName()
{
	return m_AppInfo.activityname;
}

void 
AppUnit::setPackageName(const gkString& str)
{
	m_isDataChanged = true;
	m_AppInfo.PackageName = str;
}

void 
AppUnit::setActivityName(const gkString& str)
{
	m_isDataChanged = true;
	m_AppInfo.activityname = str;
}

AppDataInfo 
AppUnit::getAppInfo()
{
	return m_AppInfo;
}

int 
AppUnit::getUseFrequence()
{
	return m_AppInfo.appStartCount;
}

void 
AppUnit::plusUseNumber()
{
	m_AppInfo.appStartCount++;
}

void 
AppUnit::setTextureID(int arr[])
{
	m_isDataChanged = true;
	m_AppInfo.IconTextureID = arr[0];
	//m_ArrayTextureID[1] = arr[1];
}

void 
AppUnit::setAppIconTID(int id)
{
	m_isDataChanged = true;
	m_AppInfo.IconTextureID = id;
}

void 
AppUnit::setAppNameTID(int id)
{
	m_isDataChanged = true;
	m_AppInfo.appNameTextureID = id;
	//m_ArrayTextureID[1] = id;
}

//int 
//AppUnit::getTextureID()
//{
//	return m_AppInfo.IconTextureID;
//}

int 
AppUnit::getAppIconTID()
{
	return m_AppInfo.IconTextureID;
}

int 
AppUnit::getAppNameTID()
{
	return m_AppInfo.appNameTextureID;
}

bool 
AppUnit::getDataChangeFlag()
{
	return m_isDataChanged;
}

AppUnit::AppTextureUnit::AppTextureUnit()
{
	MessageTag = "ALLAPP";
	m_pAppUnit = NULL;
	gkMessageManager::getSingleton().addListener(this);
}

void 
AppUnit::AppTextureUnit::showTexture(AppUnit* pApp)
{
#define _SEND_SUBJECT_0_	"getTextureID"
#define _SEND_SUBJECT_1_	"getAppNameTextrue"
	gkString to = "Java";
	char buffer[100];
	gkString sPack = pApp->getPackageName();
	const char* package = sPack.c_str();
	gkString sAct = pApp->getActivityName();
	const char* activity = sAct.c_str();

	sprintf(buffer,"%s\n%s",package,activity);
	m_pAppUnit = pApp;
	gkString sbody(buffer);
	gkPrintf("appunit sendMessage,from = %s,to = %s,subject = %s,body = %s\n",MessageTag.c_str(),to.c_str(),_SEND_SUBJECT_0_,sbody.c_str());
	gkMessageManager::getSingletonPtr()->sendMessage(MessageTag,to,_SEND_SUBJECT_0_,sbody);
	gkMessageManager::getSingletonPtr()->sendMessage(MessageTag,to,_SEND_SUBJECT_1_,pApp->getAppName());
	static bool test = true;
	if(test)
	{
	char buffer1[50];
	int b = 4<<4;
	b |= 1<<3;
	b |= 1<<2;
	b |= 1<<1;
	b |= 1;
	sprintf(buffer1,"%d",b);

	gkMessageManager::getSingletonPtr()->sendMessage(MessageTag,"StateBar","setState",buffer1);
	}
	test  = false;
}

void 
AppUnit::AppTextureUnit::handleMessage(gkMessageManager::Message* message)
{
#define _HANDLE_SUBJECT_0_	"setTextureID"
#define _HANDLE_SUBJECT_1_	"setAppNameTexture"
 	if(MessageTag != message->m_to)
  		return;
	gkPrintf("appunit getMessage,from = %s,to = %s,subject = %s,body = %s\n",message->m_from.c_str(),message->m_to.c_str(),message->m_subject.c_str(),message->m_body.c_str());
	if(message->m_subject == _HANDLE_SUBJECT_0_ && m_pAppUnit)
	{
		int textureid;
		const char* buffer = message->m_body.c_str(); 
		sscanf(buffer,"%d",&textureid);

		m_pAppUnit->setAppIconTID(textureid);
		//if(m_pAppUnit->getGameObj()&&m_pAppUnit->getGameObj()->getEntity())
		setEntityTextureID(_APP_ICON_INDEX_,textureid);
	}
	else if(_HANDLE_SUBJECT_1_ == message->m_subject && m_pAppUnit)
	{
		int textureid;
		float rotate;
		const char* buffer = message->m_body.c_str(); 
		sscanf(buffer,"%d\n%f",&textureid,&rotate);
		gkPrintf("appunit setAppNameTexture textureID  = %d,rotate = %f",textureid,rotate);
		
		m_pAppUnit->setAppNameTID(textureid);
		//if(m_pAppUnit->getGameObj()&&m_pAppUnit->getGameObj()->getEntity())
		setEntityTextureID(_APP_NAME_INDEX_,textureid);
	}
}

void 
AppUnit::AppTextureUnit::setEntityTextureID(int entityIndex,int textureID)
{
	if (textureID <= 0)
	{
		gkPrintf("appunit setEntityTextureID error! textureID  = %d",textureID);
		return;
	}
	gkGameObject* pObj = m_pAppUnit->getGameObj();
	if(!pObj)
	{
		gkPrintf("appunit setEntityTextureID error! gameObj == NULL");
		return;
	}
	((gkEntity*)pObj)->setGLTextureID(entityIndex,0,textureID);
}