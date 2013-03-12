#include "UtilKeyLogic.h"

UtilKeyNode::UtilKeyNode(gkLogicTree* parent, size_t id): gkLogicNode(parent, id)
{
	mFrom = "";
	mTo = "Java";
	mSubject = "";
	mBody = "";
}

void UtilKeyNode::linkKey(gkKeyNode*leftKey = NULL,gkKeyNode*rightKey = NULL, gkKeyNode*upKey = NULL,
							gkKeyNode*downKey = NULL, gkKeyNode * okKey = NULL, gkKeyNode * returnKey = NULL)
{
	if (leftKey && rightKey && upKey && downKey && okKey && returnKey)
	{
		leftKey->getIS_DOWN()->link(getLEFT_KEY());
		rightKey->getIS_DOWN()->link(getRIGHT_KEY());
		upKey->getIS_DOWN()->link(getUP_KEY());
		downKey->getIS_DOWN()->link(getDOWN_KEY());
		okKey->getPRESS()->link(getOK_KEY());
		returnKey->getPRESS()->link(getQUIT_KEY());
	}
}

void UtilKeyNode::linkMouse(gkMouseNode * mouse = NULL, gkMouseButtonNode * mouseButton = NULL)
{
	if (mouse && mouseButton)
	{
		mouse->getMOTION()->link(getIS_MOUSE_DOWN());
		mouse->getDRAG_EVENT()->link(getIS_MOUSE_DRAG());
		mouseButton->getPRESS()->link(getMOUSE_HIT());
	}
}


//void UtilKeyNode::InitKeyAndMouse()
//{
//	ADD_ISOCK(LEFT_KEY, false);
//	ADD_ISOCK(RIGHT_KEY, false);
//	ADD_ISOCK(UP_KEY, false);
//	ADD_ISOCK(DOWN_KEY, false);
//	ADD_ISOCK(OK_KEY, false);
//	ADD_ISOCK(QUIT_KEY, false);
//
//	ADD_ISOCK(IS_MOUSE_DOWN,false);
//	ADD_ISOCK(IS_MOUSE_UP,false);
//	ADD_ISOCK(IS_MOUSE_DRAG,DragEvent());
//
//	ADD_ISOCK(MOUSE_HIT, false);
//}