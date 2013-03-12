#ifndef __TVLOGIC__
#define  __TVLOGIC__

#include "BaseLogic.h"
#include "gkMessageManager.h"

class TVLogic : public BaseLogic, public gkMessageManager::GenericMessageListener
{
public:
	enum{
		ENABLE = 10,
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	TVLogic(gkLogicTree* parent, UTsize handle);

	bool evaluate(gkScalar tick);

private:
	void openTVInAa();
	void openTVInNormal();
	void closeTV();
	void sendOpenTVMessage();

private:
	bool isTVopen;
};

#endif