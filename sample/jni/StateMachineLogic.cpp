#include "StateMachineLogic.h"
/*#include "Util.h"*/
#include "Logic/gkNodeManager.h"

StateMachineLogic::StateMachineLogic(gkLogicTree* parent, UTsize handle):gkLogicNode(parent, handle), mCurrentstate(NORMAL)
{
	ADD_OSOCK(CURRENT_STATE, NORMAL);
}

StateSet StateMachineLogic::getCurrentState()
{
	return mCurrentstate;
}

void StateMachineLogic::setCurrentState(StateSet s)
{
	mCurrentstate = s;
	gkNodeManager::getSingleton().notifyUpdate();
}

bool StateMachineLogic::evaluate(gkScalar tick)
{
	switch (mCurrentstate)
	{
	case NORMAL:
			SET_SOCKET_VALUE(CURRENT_STATE, NORMAL);
			//MYLOGI("current normal\n");
		    break;
	case EDIT:
			SET_SOCKET_VALUE(CURRENT_STATE, EDIT);
			//MYLOGI("current edit\n");
		break;
	case ALLAPP:
			  SET_SOCKET_VALUE(CURRENT_STATE, ALLAPP);
			  MYLOGI("current allapp\n");
		break;
	case SORT_IN_ALLAPP:
			 SET_SOCKET_VALUE(CURRENT_STATE, SORT_IN_ALLAPP);
			  MYLOGI("sort allapp\n");
		break;
	case MENU:
			SET_SOCKET_VALUE(CURRENT_STATE, MENU);
		break;
	case SET_BACKGROUND:
			  SET_SOCKET_VALUE(CURRENT_STATE, SET_BACKGROUND);
		break;
	case TV:
			SET_SOCKET_VALUE(CURRENT_STATE, TV);
			MYLOGI("current tv\n");
			break;
	case EDIT_HOME_APP:
			SET_SOCKET_VALUE(CURRENT_STATE, EDIT_HOME_APP);
			MYLOGI("current edit home app\n");
			break;
	default:
		_ASSERT_(0);
	}

	return false;
}

void StateMachineLogic::update(gkScalar tick)
{
	
}
