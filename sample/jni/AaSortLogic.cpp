#include "AaSortLogic.h"
#include "StateMachineLogic.h"

AaSortLogic::AaSortLogic(gkLogicTree* parent, UTsize handle):BaseLogic(parent, handle), mSortVisable(false)
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

bool AaSortLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == ALLAPP || GET_SOCKET_VALUE(ENABLE) == SORT_IN_ALLAPP)
	{
		if (  mAabridge->isFocusOnSortButton() && GET_SOCKET_VALUE(OK_KEY)  )
		{
			mSortVisable = !mSortVisable;
		}
		
		if ( GET_SOCKET_VALUE(MOUSE_HIT) )
		{
			Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
			if (mAabridge->isHitSortButton(gameObjectArray))
			{
				mSortVisable = !mSortVisable;
			}
		}
		
		return true;
	}
	else
	{
		mSortVisable = false;
		mAabridge->setSortordVisible(mSortVisable);
		return false;
	}
}

void AaSortLogic::update(gkScalar tick)
{
	sortMenu();
	quitSort();
}

void AaSortLogic::sortMenu()
{
	if (mSortVisable)
	{
		mAabridge->setSortordVisible(true);
		mStateMachineLogic->setCurrentState(SORT_IN_ALLAPP);

		if ( !mouseHit() && !keyHit() )
		{
			if (mAabridge->getCurrentViewType() != AA_Sort)
			{
				mAabridge->setFocusView(AA_Sort);
			}
		}
	} 
	else
	{
		mAabridge->setSortordVisible(false);
	}
}

bool AaSortLogic::mouseHit()
{
	if (GET_SOCKET_VALUE(MOUSE_HIT))
	{
		Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
		if ( mAabridge->isHitStDefault(gameObjectArray))
		{
			MYLOGI("hit default\n");
			mAabridge->onHitStDefault();
			mSortVisable = false;
			mAabridge->setFocusView(AA_AaRsd);
			return true;
		}
		else if ( mAabridge->isHitStFrequence(gameObjectArray))
		{
			MYLOGI("hit frequence\n");
			mAabridge->onHitStFrequence();
			mSortVisable = false;
			mAabridge->setFocusView(AA_AaRsd);
			return true;
		}
		else if ( mAabridge->isHitStLetter(gameObjectArray))
		{
			MYLOGI("hit letter\n");
			mAabridge->onHitStLetter();
			mSortVisable = false;
			mAabridge->setFocusView(AA_AaRsd);
			return true;
		}
	}
	
	return false;
}

bool AaSortLogic::keyHit()
{
	if (mAabridge->isFocusOnStDefault()  && GET_SOCKET_VALUE(OK_KEY))
	{
		mAabridge->onHitStDefault();
		mSortVisable = false;
		mAabridge->setFocusView(AA_AaRsd);
		return true;
	}
	else if (mAabridge->isFocusOnStFrequence() && GET_SOCKET_VALUE(OK_KEY))
	{
		mAabridge->onHitStFrequence();
		mSortVisable = false;
		mAabridge->setFocusView(AA_AaRsd);
		return true;
	}
	else if (mAabridge->isFocusOnHitStLetter() && GET_SOCKET_VALUE(OK_KEY) )
	{
		mAabridge->onHitStLetter();
		mSortVisable = false;
		mAabridge->setFocusView(AA_AaRsd);
		return true;
	}
	return false;
}

void AaSortLogic::quitSort()
{
	if (GET_SOCKET_VALUE(QUIT_KEY) && mStateMachineLogic->getCurrentState() == SORT_IN_ALLAPP)
	{
		mStateMachineLogic->setCurrentState(ALLAPP);
		mSortVisable = false;
		mAabridge->setLetterVisable(false);
		mAabridge->setFocusView(AA_AaRsd);
	}
}