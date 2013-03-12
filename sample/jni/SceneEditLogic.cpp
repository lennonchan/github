#include "SceneEditLogic.h"
#include "StateMachineLogic.h"


SceneEditLogic::SceneEditLogic(gkLogicTree* parent, size_t id): BaseLogic(parent, id), sceneIsVisable(false), switchable(false), curSwitching(1),curFocus(1)
{
	ADD_ISOCK(ENABLE, NONE);
	ADD_ISOCK(STATE_IN_EDIT, ESS_FOCUS_MOVE);
	ADD_ISOCK(EDIT_BLOCK_LEFT, false);
	ADD_ISOCK(EDIT_BLOCK_RIGHT, false);
}

bool SceneEditLogic::evaluate(gkScalar tick)
{
	if ( GET_SOCKET_VALUE(ENABLE) == EDIT)
	{
		sceneEditVisable();
		focusMove();
		blockMove();
		quitEdit();
	}
	else
	{
		curFocus = 1;
		curSwitching = 1;
		sceneIsVisable = false;
	}
	return false;
}


void SceneEditLogic::sceneEditVisable()
{
	if(!sceneIsVisable)
	{
		mLauncherScene->setEditMode(true);
		sceneIsVisable = true;
	}
}


void SceneEditLogic::focusMove()
{
	//curFocus = mLauncherScene->getCurrentFocusIndex_EM();
	if (GET_SOCKET_VALUE(STATE_IN_EDIT) == ESS_FOCUS_MOVE)
	{
		if (GET_SOCKET_VALUE(EDIT_BLOCK_LEFT))
		{
			if ( curFocus > 1)
			{
				curFocus--;
				mLauncherScene->setBlockFocus_EM(curFocus);
			}
		}
		if (GET_SOCKET_VALUE(EDIT_BLOCK_RIGHT))
		{
			if ( curFocus < 4 )
			{
				curFocus++;
				mLauncherScene->setBlockFocus_EM(curFocus);
			}
		}
	}
	

}
void SceneEditLogic::blockMove()
{
	if (GET_SOCKET_VALUE(STATE_IN_EDIT) == ESS_BLOCK_MOVE)
	{
		curSwitching = curFocus;
		if (GET_SOCKET_VALUE(EDIT_BLOCK_LEFT))
		{
			if (curSwitching > 1)
			{						 		
				//MYLOGI("left %d \n", curSwitching);
				mLauncherScene->switchBlockIndex_EM(curSwitching-1, curSwitching);
				curSwitching--;
							
			}					 			
		}
		if (GET_SOCKET_VALUE(EDIT_BLOCK_RIGHT))
		{
			if ( curSwitching < 4)
			{
				//MYLOGI("right %d \n", curSwitching);
				mLauncherScene->switchBlockIndex_EM(curSwitching, curSwitching+1);
				curSwitching++;
			}	 			
		}
		curFocus = curSwitching;	
	}
}


void SceneEditLogic::quitEdit()
{
	Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
	if ( mLauncherScene->isHitExitNode_EM(gameObjectArray) )
	{
		mLauncherScene->setEditMode(false);
		sceneIsVisable = false;
		mStateMachineLogic->fromEditToNormal();
	}
}