#include "EditFocusMoveLogic.h"

EditFocusMoveLogic::EditFocusMoveLogic(gkLogicTree* parent, size_t id): EditBaseLogic(parent, id)
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

	ADD_ISOCK(CURRENT_EDIT_STATE, ESS_NONE);
	
}

bool EditFocusMoveLogic::evaluate(gkScalar tick)
{	
	if (GET_SOCKET_VALUE(CURRENT_EDIT_STATE) == ESS_FOCUS_MOVE)
	{
		editFocusMove();
	}
	else
	{
		SET_SOCKET_VALUE(CURRENT_EDIT_STATE, ESS_NONE);
	}
	return false;
}

void EditFocusMoveLogic::editFocusMove()
{
	if (GET_SOCKET_VALUE(LEFT_KEY))
	{
		mLauncherScene->flyMenuFocus_EM(LEFT);
	}

	else if (GET_SOCKET_VALUE(RIGHT_KEY))
	{
		mLauncherScene->flyMenuFocus_EM(RIGHT);
	}
	else if(GET_SOCKET_VALUE(UP_KEY))
	{
		mLauncherScene->flyMenuFocus_EM(UP);
	}
	else if (GET_SOCKET_VALUE(DOWN_KEY))
	{
		mLauncherScene->flyMenuFocus_EM(DOWN);
	}
}

