#ifndef __STATESBARLOGIC__
#define __STATESBARLOGIC__

#include "gkMessageManager.h"
#include "BaseLogic.h"

class StateBarLogic : public BaseLogic, public gkMessageManager::GenericMessageListener
{
public:
	enum{
		ENABLE = 10
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	StateBarLogic(gkLogicTree* parent, UTsize handle);
	bool evaluate(gkScalar tick);

private:
	void getMessage();
};

#endif