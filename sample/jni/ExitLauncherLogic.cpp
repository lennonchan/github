#include "ExitLanucherLogic.h"
#include "gkEngine.h"

ExitLauncherLogic::ExitLauncherLogic(gkLogicTree* parent, UTsize handle):BaseLogic(parent, handle)
{
	mEngine = NULL;

	ADD_ISOCK(LEFT_KEY, false);
	ADD_ISOCK(RIGHT_KEY, false);
	ADD_ISOCK(UP_KEY, false);
	ADD_ISOCK(DOWN_KEY, false);
	ADD_ISOCK(OK_KEY, false);
	ADD_ISOCK(QUIT_KEY, false);

	ADD_ISOCK(IS_MOUSE_DOWN,false);
	ADD_ISOCK(IS_MOUSE_UP,false);
	ADD_ISOCK(IS_MOUSE_DRAG,DragEvent());

	ADD_ISOCK(MOUSE_HIT, false);

	ADD_ISOCK(ENABLE, NORMAL);

}

bool ExitLauncherLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == NORMAL && GET_SOCKET_VALUE(QUIT_KEY))
	{
		mEngine->requestExit();
	}
	return false;
}

void ExitLauncherLogic::setEngine(gkEngine * pEngine)
{
	mEngine = pEngine;
}

gkEngine * ExitLauncherLogic::getEngine()
{
	_ASSERT_(mEngine != NULL)
	return mEngine;
}