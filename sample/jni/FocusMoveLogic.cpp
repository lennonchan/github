#include "FocusMoveLogic.h"
#include "LauncherScene.h"

bool FocusMoveLogic::evaluate(gkScalar tick)
{

	if (GET_SOCKET_VALUE(ENABLE))
	{
		if (GET_SOCKET_VALUE(FOCUS_FLY_LEFT))
		{
		
			if (mLauncherScene->blockFocusTranslation(LEFT))
			{
				SET_SOCKET_VALUE(SCENE_MOVE_LEFT, true);
			}
			else
			{
				SET_SOCKET_VALUE(SCENE_MOVE_LEFT, false);
			}
		}
		if(GET_SOCKET_VALUE(FOCUS_FLY_RIGHT))
		{
	
			if (mLauncherScene->blockFocusTranslation(RIGHT))
			{
				SET_SOCKET_VALUE(SCENE_MOVE_RIGHT, true);
			}
			else
			{
				SET_SOCKET_VALUE(SCENE_MOVE_RIGHT, false);
			}
		}

		if(GET_SOCKET_VALUE(FOCUS_FLY_UP))
		{
	
			mLauncherScene->blockFocusTranslation(UP);
		}

		if(GET_SOCKET_VALUE(FOCUS_FLY_DOWN))
		{
	
			mLauncherScene->blockFocusTranslation(DOWN);
		}
	}



	return false;
}

