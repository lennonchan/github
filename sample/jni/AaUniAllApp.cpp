#include "AaUniAllApp.h"

AaUniAllApp::AaUniAllApp(gkLogicTree* parent, UTsize handle): AaBaseLogic(parent, handle)
{
	ADD_ISOCK(ENTER_AaUNIALLAPP, false);
	ADD_ISOCK(QUIT_AaUNIALLAPP, false);

	ADD_OSOCK(QUIT_TO_ALLAPP, false);
}

bool AaUniAllApp::evaluate(gkScalar tick)
{
	return false;
}