#include "AppMarketLogic.h"
#include "StateMachineLogic.h"
#include "gkScene.h"

AppMarketLogic::AppMarketLogic(gkLogicTree* parent, UTsize handle): BaseLogic(parent, handle)
{
	ADD_ISOCK(LEFT_KEY, false);
	ADD_ISOCK(RIGHT_KEY, false);
	ADD_ISOCK(UP_KEY, false);
	ADD_ISOCK(DOWN_KEY, false);
	ADD_ISOCK(OK_KEY, false);
	ADD_ISOCK(QUIT_KEY, false);

	ADD_ISOCK(IS_MOUSE_DOWN,false);
	ADD_ISOCK(IS_MOUSE_UP,false);
	ADD_ISOCK(IS_MOUSE_DRAG,DragEvent());

	ADD_ISOCK(MOUSE_HIT, false);

	ADD_ISOCK(ENABLE, NONE);

	gkString mAppMarketPackageName = "com.tcl.appmarket2";
	gkString mAppMarketActivityName = "com.tcl.appmarket2.AppMarket2";

	mFrom = "AppMarketLogic";
	mSubject = "StartActivity";
	mBody= mAppMarketPackageName + "\n" + mAppMarketActivityName;
}

bool AppMarketLogic::evaluate(gkScalar tick)
{
	openAppMarketNormal();
	openAppMarketAa();
	//closeAppMarket();
	return false;
}

void AppMarketLogic::openAppMarketNormal()
{
	if (GET_SOCKET_VALUE(ENABLE) == NORMAL)
	{
	
	}
}

void AppMarketLogic::openAppMarketAa()
{
	if (GET_SOCKET_VALUE(ENABLE) == ALLAPP)
	{
		if (GET_SOCKET_VALUE(MOUSE_HIT))
		{
			Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
			if (mAabridge->isHitAppMarketButton(gameObjectArray))
			{
				MYLOGI("key open app market\n");
				sendMessage();
			}
		}
		else if (mAabridge->isFocusOnMarket() && GET_SOCKET_VALUE(OK_KEY))
		{
			MYLOGI("key open app market\n");
			sendMessage();
		}
	}
}

void AppMarketLogic::sendMessage()
{
	if (gkMessageManager::getSingletonPtr())
	{
		gkMessageManager::getSingletonPtr()->sendMessage(mFrom, mTo, mSubject, mBody);
	}
}