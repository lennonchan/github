#ifndef __AaUNIALLAPP__
#define __AaUNIALLAPP__

#include "AaBaseLogic.h"

class AaUniAllApp : public AaBaseLogic
{
public:
	enum{
		ENTER_AaUNIALLAPP,
		QUIT_AaUNIALLAPP,

		QUIT_TO_ALLAPP
	};
	DECLARE_SOCKET_TYPE(ENTER_AaUNIALLAPP, bool);
	DECLARE_SOCKET_TYPE(QUIT_AaUNIALLAPP, bool);
	DECLARE_SOCKET_TYPE(QUIT_TO_ALLAPP, bool);

	AaUniAllApp(gkLogicTree* parent, UTsize handle);
	bool evaluate(gkScalar tick);
protected:
private:
};
#endif