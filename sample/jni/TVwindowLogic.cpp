#include "TVwindowLogic.h"
#include "StateMachineLogic.h"


TVwindowLogic::TVwindowLogic(gkLogicTree* parent, UTsize handle):BaseLogic(parent, handle), mIsTVwindowOpen(true)
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
	mSubject = "setTV";

	mBody_show = "Show";
	mBody_hide = "Hide";
}


bool TVwindowLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == NORMAL || GET_SOCKET_VALUE(ENABLE) == MENU)
	{
		if(mLauncherScene->getCurrentBlockID() == 0 || mLauncherScene->getCurrentBlockID() == 1)
		{
			openTVwindow();
		}
		else
		{
			closeTVwindow();
		}
	}
	else
	{
		closeTVwindow();
	}
	return false;
}

void TVwindowLogic::openTVwindow()
{
	if (mIsTVwindowOpen == false)
	{
		if (gkMessageManager::getSingletonPtr())
		{
			gkMessageManager::getSingletonPtr()->sendMessage(mFrom, mTo, mSubject, mBody_show);
		}
		MYLOGI("open tv winodw\n");
		mIsTVwindowOpen = true;
	}
	
}

void TVwindowLogic::closeTVwindow()
{
	if (mIsTVwindowOpen == true)
	{
		if (gkMessageManager::getSingletonPtr())
		{
			gkMessageManager::getSingletonPtr()->sendMessage(mFrom, mTo, mSubject, mBody_hide);
		}
		MYLOGI("close tv window\n");
		mIsTVwindowOpen = false;
	}
	
}
