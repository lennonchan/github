 #include "EditBlockMoveLogic.h"
#include "StateEditLogic.h"

 EditBlockMoveLogic::EditBlockMoveLogic(gkLogicTree* parent, size_t id): EditBaseLogic(parent, id)
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
 
 bool EditBlockMoveLogic::evaluate(gkScalar tick)
 {
 	if (GET_SOCKET_VALUE(CURRENT_EDIT_STATE) == ESS_BLOCK_MOVE)
 	{
 		editBlockMove();
 	} 
	else if (GET_SOCKET_VALUE(CURRENT_EDIT_STATE) == ESS_DELETE_BLOCK)
	{
		deleteBlock();
	}
	else if (GET_SOCKET_VALUE(CURRENT_EDIT_STATE) == ESS_ADD_BLOCK)
	{
		addBlock();
	}
 	return false;
 }
 
 void EditBlockMoveLogic::editBlockMove()
 {
 	if (GET_SOCKET_VALUE(LEFT_KEY))
 	{
  		mLauncherScene->switchBlockIndex_EM(LEFT);
 
 	}
 	else if (GET_SOCKET_VALUE(RIGHT_KEY))
 	{
		mLauncherScene->switchBlockIndex_EM(RIGHT);
 	}
 	else if(GET_SOCKET_VALUE(UP_KEY))
 	{
 
 	}
 	else if (GET_SOCKET_VALUE(DOWN_KEY))
 	{
 	}
 }


 void EditBlockMoveLogic::deleteBlock()
 {
	mLauncherScene->deleteBlock_EM();
	mStateEditLogic->setCurrentEditState(ESS_FOCUS_MOVE);
 }

 void EditBlockMoveLogic::addBlock()
 {
	mLauncherScene->addBlock_EM();
	mStateEditLogic->setCurrentEditState(ESS_FOCUS_MOVE);
 }


 
