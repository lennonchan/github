#ifndef __AaSORTLOGIC__
#define __AaSORTLOGIC__

#include "BaseLogic.h"

class AaSortLogic: public BaseLogic
{
public:
	enum{
		ENABLE = 10,
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	AaSortLogic(gkLogicTree* parent, UTsize handle);

	bool evaluate(gkScalar tick);
	void update(gkScalar tick);
private:
	void sortMenu();
	bool mouseHit();
	bool keyHit();
	void quitSort();
	bool mSortVisable;
};


#endif