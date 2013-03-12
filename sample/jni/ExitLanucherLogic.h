#ifndef __EXITLAUNCHERLOGIC__
#define __EXITLAUNCHERLOGIC__

#include "BaseLogic.h"
class gkEngine;
class ExitLauncherLogic : public BaseLogic
{
public:
	enum{
		ENABLE = 10,
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	ExitLauncherLogic(gkLogicTree* parent, UTsize handle);

	bool evaluate(gkScalar tick);

	void setEngine(gkEngine * pEngine);
	gkEngine * getEngine();

private:
	gkEngine * mEngine;
};

#endif