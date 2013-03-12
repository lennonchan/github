#ifndef __EQAALOGIC__
#define __EQAALOGIC__

#include "BaseLogic.h"

// enter / quit All app 
class AaEQLogic : public BaseLogic
{
public:
	enum{
		ENABLE = 10
	};

	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	AaEQLogic(gkLogicTree* parent, UTsize handle);
	bool evaluate(gkScalar tick);

private:

};

#endif