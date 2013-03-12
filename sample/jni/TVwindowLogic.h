#ifndef __TVWINDOW__
#define __TVWINDOW__

#include "BaseLogic.h"
#include "gkMessageManager.h"


class TVwindowLogic: public BaseLogic,  public gkMessageManager::GenericMessageListener
{
public:
	enum{
		ENABLE = 10
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);
	TVwindowLogic(gkLogicTree* parent, UTsize handle);
	bool evaluate(gkScalar tick);
private:
	void openTVwindow();
	void closeTVwindow();

private:
	
	gkString mBody_show;
	gkString mBody_hide;

private:
	bool mIsTVwindowOpen;
};

#endif