#ifndef __STATEMACHINELOGIC__
#define __STATEMACHINELOGIC__

#include "BaseLogic.h"

class StateMachineLogic : public gkLogicNode
{
public:
	enum{
		CURRENT_STATE
	};

	DECLARE_SOCKET_TYPE(CURRENT_STATE, StateSet);

	StateMachineLogic(gkLogicTree* parent, UTsize handle);

	StateSet getCurrentState();
	void setCurrentState(StateSet s);

	bool evaluate(gkScalar tick);
	void update(gkScalar tick);

private:
	StateSet mCurrentstate;
};

#endif