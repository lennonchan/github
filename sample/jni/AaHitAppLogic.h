#ifndef __HITICONLOGIC__
#define __HITICONLOGIC__

#include "BaseLogic.h"
#include "gkMessageManager.h"

class AppUnit;

class AaHitAppLogic : public BaseLogic, public gkMessageManager::GenericMessageListener
{
public:
	enum{
		ENABLE = 10
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	AaHitAppLogic(gkLogicTree* parent, size_t id);

	bool evaluate(gkScalar tick);

private:
	void mouseHitIcon();
	void keyPressIcon();
	void sendAppMessage();
private:
	AppUnit * mAppUnit;
};

#endif