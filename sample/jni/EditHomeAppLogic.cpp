#include "EditHomeAppLogic.h"
#include "StateMachineLogic.h"
#include "HaSettingsViewImpl.h"
#include "StateEditLogic.h"

EditHomeAppLogic::EditHomeAppLogic(gkLogicTree* parent, UTsize handle):BaseLogic(parent, handle)
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
	ADD_ISOCK(ENABLE_FROM_EDIT, ESS_NONE)
}


bool EditHomeAppLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == EDIT_HOME_APP || GET_SOCKET_VALUE(ENABLE_FROM_EDIT) ==ESS_EDIT_BLOCK)
	{
		openSetPage();
		closeSetPage();
		moveFocus();
	}
	return false;
}

void EditHomeAppLogic::openSetPage()
{
	if(!mAabridge->isInHomeAppMode())
	{
		mLauncherScene->setAllLauncherSceneVisible(false);
		mAabridge->enterHomeAppSettings(mLauncherScene->getBlockByID(mLauncherScene->getCurrentBlockID()));
	}
}

void EditHomeAppLogic::closeSetPage()
{
	if (GET_SOCKET_VALUE(QUIT_KEY) && GET_SOCKET_VALUE(ENABLE) == EDIT_HOME_APP)
	{
		if(mAabridge->isInHomeAppMode())
		{
			mLauncherScene->setAllLauncherSceneVisible(true);
			mAabridge->exitHomeAppSettings();
			mStateMachineLogic->setCurrentState(NORMAL);
		}
	}
}

void EditHomeAppLogic::moveFocus()
{
	if (GET_SOCKET_VALUE(LEFT_KEY))
	{
		mHaSettings->moveFocus(LEFT);
	} 
	else if (GET_SOCKET_VALUE(RIGHT_KEY))
	{
		mHaSettings->moveFocus(RIGHT);
	}
	else if (GET_SOCKET_VALUE(UP_KEY))
	{
		mHaSettings->moveFocus(UP);
	}
	else if (GET_SOCKET_VALUE(DOWN_KEY))
	{
		mHaSettings->moveFocus(DOWN);
	}
	else if (GET_SOCKET_VALUE(OK_KEY))
	{
		mHaSettings->setHomeAppTag((AppUnit *)mHaSettings->getCurrentViewNode());
	}
}