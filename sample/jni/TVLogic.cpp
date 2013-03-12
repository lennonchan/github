#include "TVLogic.h"
#include "StateMachineLogic.h"

TVLogic::TVLogic(gkLogicTree* parent, UTsize handle): BaseLogic(parent, handle), isTVopen(false)
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

	ADD_ISOCK(ENABLE, NORMAL);

	mFrom = "TVwindowLogic";
	mTo = "Java";
	mSubject = "SetTV";
	mBody = "Enter";
}

bool TVLogic::evaluate(gkScalar tick)
{
	openTVInAa();
	openTVInNormal();
	closeTV();
	return false;
}

void TVLogic::openTVInAa()
{
	if (GET_SOCKET_VALUE(ENABLE) == ALLAPP)
	{
		if ( GET_SOCKET_VALUE(MOUSE_HIT) )
		{
			Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
			if (mAabridge->isHitTvButton(gameObjectArray))
			{
				sendOpenTVMessage();
				//MYLOGI("mouse open tv\n");
			}
		}
		else if (mAabridge->isFocusOnTvButton() && GET_SOCKET_VALUE(OK_KEY))
		{
			sendOpenTVMessage();
			//MYLOGI("key open tv\n");
		}
	}
}

void TVLogic::openTVInNormal()
{
	if (GET_SOCKET_VALUE(ENABLE) == NORMAL)
	{
		
	}
}

void TVLogic::closeTV()
{
	if (isTVopen)
	{
		isTVopen = false;
	}
}

void TVLogic::sendOpenTVMessage()
{
	if (!isTVopen)
	{
		if (gkMessageManager::getSingletonPtr())
		{
			gkMessageManager::getSingletonPtr()->sendMessage(mFrom, mTo, mSubject, mBody);
		}
		isTVopen = true;
	}
}