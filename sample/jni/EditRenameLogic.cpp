#include "EditRenameLogic.h"


EditRenameLogic::EditRenameLogic(gkLogicTree* parent, size_t id):EditBaseLogic(parent, id)
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

bool EditRenameLogic::evaluate(gkScalar tick)
{
	return false;
}

