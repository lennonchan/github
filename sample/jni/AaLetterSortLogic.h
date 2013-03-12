#ifndef __AaLETTERSORTLOGIC__
#define __AaLETTERSORTLOGIC__

#include "BaseLogic.h"

class AaLetterSortLogic : public BaseLogic
{
public:
	enum{
		ENABLE = 10,
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	AaLetterSortLogic(gkLogicTree* parent, UTsize handle);

	bool evaluate(gkScalar tick);


private:
	void sortByLetter();
	void quitSortLetter();
};

#endif