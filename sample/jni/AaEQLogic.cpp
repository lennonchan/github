#include "AaEQLogic.h"
#include "StateMachineLogic.h"

AaEQLogic::AaEQLogic(gkLogicTree* parent, UTsize handle): BaseLogic(parent, handle)
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

	ADD_ISOCK(ENABLE, NORMAL);//保证初始化完成后能够直接进入Aa

}

bool AaEQLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == NORMAL
		  && mLauncherScene->isFocusOnAllAppButton() 
		  && GET_SOCKET_VALUE(OK_KEY))
	{
		//mStateMachineLogic->fromNormalToAa();
		mStateMachineLogic->setCurrentState(ALLAPP);
	}
	else if (GET_SOCKET_VALUE(ENABLE) == ALLAPP && GET_SOCKET_VALUE(QUIT_KEY))
	{
		//mStateMachineLogic->fromAaToNormal();
	}
	return false;
}