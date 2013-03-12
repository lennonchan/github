#include "AaHitAppLogic.h"
#include "AppUnit.h"

AaHitAppLogic::AaHitAppLogic(gkLogicTree* parent, size_t id): BaseLogic(parent, id), mAppUnit(NULL)
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

	mFrom = "AaHitAppLogic";
	mSubject = "StartActivity";
}


bool AaHitAppLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == ALLAPP)
	{
		mouseHitIcon();
		keyPressIcon();
	}

	return false;
}

void AaHitAppLogic::mouseHitIcon()
{
	if (GET_SOCKET_VALUE(MOUSE_HIT))
	{
		Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
		mAppUnit = mAabridge->isHitApp_AA(gameObjectArray);
		sendAppMessage();
	}
		
}

void AaHitAppLogic::keyPressIcon()
{
	if (GET_SOCKET_VALUE(OK_KEY))
	{
		mAppUnit = mAabridge->getCurrentApp();
		sendAppMessage();
	}
}


void AaHitAppLogic::sendAppMessage()
{
	if (mAppUnit)
	{
		mBody = mAppUnit->getPackageName() +"\n" +mAppUnit->getActivityName();

		_ASSERT_(gkMessageManager::getSingletonPtr());
		if (gkMessageManager::getSingletonPtr())
		{
			gkMessageManager::getSingletonPtr()->sendMessage(mFrom, mTo, mSubject, mBody);
		}	
		
	}

}