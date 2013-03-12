#include "EQEditHomeAppLogic.h"
#include "StateMachineLogic.h"
#include "StateEditLogic.h"
EQEditHomeAppLogic::EQEditHomeAppLogic(gkLogicTree* parent, UTsize handle): BaseLogic(parent, handle)
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

	ADD_ISOCK(ENABLE_EDIT_HOME_APP, NORMAL);

	ADD_ISOCK(ENTER_KEY, false);
}

bool EQEditHomeAppLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_REF_VALUE(ENABLE_EDIT_HOME_APP) == NORMAL && GET_SOCKET_REF_VALUE(ENTER_KEY))
	{
		mStateMachineLogic->setCurrentState(EDIT_HOME_APP);
	}
	else if (GET_SOCKET_REF_VALUE(ENABLE_EDIT_HOME_APP) == EDIT)
	{
		
	}
	return false;
}

