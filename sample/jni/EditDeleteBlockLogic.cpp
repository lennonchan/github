#include "EditDeleteBlockLogic.h"


EditDeleteBlockLogic::EditDeleteBlockLogic(gkLogicTree* parent, size_t id):EditBaseLogic(parent, id)
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

bool EditDeleteBlockLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(CURRENT_EDIT_STATE) == ESS_EDIT_BLOCK)
	{
		//enterEditBlock();
	}
	return false;
}

void EditDeleteBlockLogic::enterEditBlock()
{

}