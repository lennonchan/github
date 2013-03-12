#include "AaMainAppLogic.h"
#include "Aabridge.h"
#include "AppUnit.h"
#include "StateMachineLogic.h"

AaMainAppLogic::AaMainAppLogic(gkLogicTree* parent, UTsize handle):BaseLogic(parent, handle)
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

}

bool AaMainAppLogic::evaluate(gkScalar tick)
{
	if ( GET_SOCKET_VALUE(ENABLE) == ALLAPP || GET_SOCKET_VALUE(ENABLE) == SORT_IN_ALLAPP)
	{
		enterAaVisable();
		focusMove();
		mouseHitAa();
		quitAaVisable();	
	}
	else if ( GET_SOCKET_VALUE(ENABLE) == NORMAL )
	{
		//quitAaVisable();	
	}
	else
	{
		//播放进入别的模式的动画 TV, App market
	}
	return false;
}

void AaMainAppLogic::focusMove()
{
	if (GET_SOCKET_VALUE(LEFT_KEY))
	{

		mAabridge->moveFocus(LEFT);
	}
	if(GET_SOCKET_VALUE(RIGHT_KEY))
	{

		mAabridge->moveFocus(RIGHT);
	}
	if (GET_SOCKET_VALUE(UP_KEY))
	{

		mAabridge->moveFocus(UP);
	}
	if(GET_SOCKET_VALUE(DOWN_KEY))
	{

		mAabridge->moveFocus(DOWN);
	}
}


void AaMainAppLogic::enterAaVisable()
{
	if ( !mAabridge->isInAaMode() )
	{
		mLauncherScene->setAllLauncherSceneVisible(false);
		mLauncherScene->setFocusVisible(false);
		mAabridge->enterAaMode();
	}

}


void AaMainAppLogic::quitAaVisable()
{

	if (GET_SOCKET_VALUE(QUIT_KEY) && GET_SOCKET_VALUE(ENABLE) == ALLAPP)
	{
		if ( mAabridge->isInAaMode() )
		{
			mAabridge->exitAaMode();
			mLauncherScene->setFocusVisible(true);
			mLauncherScene->setAllLauncherSceneVisible(true);
			//mStateMachineLogic->fromAaToNormal();
			mStateMachineLogic->setCurrentState(NORMAL);
		}
	}
}

void AaMainAppLogic::mouseHitAa()
{
	
	if ( GET_SOCKET_VALUE(MOUSE_HIT) )
	{
		Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
		ViewNode * hitNode = mAabridge->getHitViewNode(gameObjectArray);
		if ( hitNode != NULL )
		{
				mAabridge->setViewNodeFocus(hitNode);
		}
	}
}