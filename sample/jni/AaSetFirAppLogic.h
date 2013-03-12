#ifndef __AaSETFIRAPPLOGIC__
#define  __AaSETFIRAPPLOGIC__

#include "AaBaseLogic.h"

class AaSetFirAppLogic : public AaBaseLogic
{
public:
	enum{
		ENTER_AaSETFIRAPP,
		QUIT_AaSETFIRAPP,

		QUIT_TO_ALLAPP
	};
	DECLARE_SOCKET_TYPE(ENTER_AaSETFIRAPP, bool);
	DECLARE_SOCKET_TYPE(QUIT_AaSETFIRAPP, bool);

	DECLARE_SOCKET_TYPE(QUIT_TO_ALLAPP, bool);

	AaSetFirAppLogic(gkLogicTree* parent, UTsize handle);
	bool evaluate(gkScalar tick);

protected:

private:
};

#endif