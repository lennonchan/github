#include "AaSetFirAppLogic.h"

AaSetFirAppLogic::AaSetFirAppLogic(gkLogicTree* parent, UTsize handle): AaBaseLogic(parent, handle) 
{
	ADD_ISOCK(ENTER_AaSETFIRAPP, false);

	ADD_ISOCK(QUIT_AaSETFIRAPP, false);
	ADD_OSOCK(QUIT_TO_ALLAPP, false);
}

bool AaSetFirAppLogic::evaluate(gkScalar tick)
{
	return false;
}
