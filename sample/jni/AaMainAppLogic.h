#ifndef __MAINAPPLOGIC__
#define __MAINAPPLOGIC__

#include "BaseLogic.h"

class AaMainAppLogic : public BaseLogic
{
public:
	enum{
		ENABLE = 10,
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	AaMainAppLogic(gkLogicTree* parent, UTsize handle);

	bool evaluate(gkScalar tick);

protected:

private:
	void focusMove();
	void mouseHitAa();
	void focusHitApp();
	void enterAaVisable();
	void quitAaVisable();
};
#endif