#ifndef __APPMARKETLOGIC__
#define __APPMARKETLOGIC__

#include "gkMessageManager.h"
#include "BaseLogic.h"

class AppMarketLogic: public BaseLogic, public gkMessageManager::GenericMessageListener
{
public:
	enum{
		ENABLE = 10,
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	AppMarketLogic(gkLogicTree* parent, UTsize handle);

	bool evaluate(gkScalar tick);

private:
	void openAppMarketNormal();
	void openAppMarketAa();
	void sendMessage();

private:

};

#endif