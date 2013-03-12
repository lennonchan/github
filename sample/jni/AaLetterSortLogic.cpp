#include "AaLetterSortLogic.h"
#include "StateMachineLogic.h"

AaLetterSortLogic::AaLetterSortLogic(gkLogicTree* parent, UTsize handle): BaseLogic(parent, handle)
{
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

	ADD_ISOCK(ENABLE, NONE);
}

bool AaLetterSortLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == SORT_IN_ALLAPP)
	{
		 sortByLetter();
	}

	return false;
}

void AaLetterSortLogic::sortByLetter()
{
	
	if (GET_SOCKET_VALUE(MOUSE_HIT) )
	{
		Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
		char mCurrentLetter = mAabridge->getHitLetter(gameObjectArray);
		if (mCurrentLetter != NULL)
		{
			mAabridge->setCurrentLetter(mCurrentLetter);
		}
	}
	else if (GET_SOCKET_VALUE(OK_KEY))
	{
		char c = mAabridge->getCurrentLetter();
		mAabridge->setCurrentLetter(c);
	}
}