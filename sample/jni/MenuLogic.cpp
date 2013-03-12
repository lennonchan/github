#include "MenuLogic.h"
#include "Menu.h"
#include "StateMachineLogic.h"

MenuLogic::MenuLogic(gkLogicTree* parent, size_t id): BaseLogic(parent, id),menuIsOpen(false)
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

	ADD_ISOCK(ENABLE_MENU,NORMAL);
 	ADD_ISOCK(OPEN_MENU, false);
}


bool MenuLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE_MENU) == MENU || GET_SOCKET_VALUE(ENABLE_MENU) == NORMAL)
	{
		if (GET_SOCKET_VALUE(OPEN_MENU))
		{
			menuIsOpen = !menuIsOpen;
		}
		return true;
	}
 	else
 	{
		menuIsOpen = false;
 		mMenu->setMenuVisible(menuIsOpen);
		return false;
 	}
	
}

void MenuLogic::update(gkScalar tick)
{
	if (menuIsOpen)
	{
		mMenu->setMenuVisible(true);
        mStateMachineLogic->setCurrentState(MENU);

		if (GET_SOCKET_VALUE(MOUSE_HIT))
		{
			Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
			if( mMenu->isHitHomeEdit(gameObjectArray) )
			{
				fromMenuToState(EDIT);
				//mStateMachineLogic->setCurrentState(EDIT);
			}
			else if ( mMenu->isHitWallpaperSetting(gameObjectArray))
			{
				fromMenuToState(SET_BACKGROUND);
				//mStateMachineLogic->setCurrentState(SET_BACKGROUND);
			}	 	
		}
		else if ( GET_SOCKET_VALUE(QUIT_KEY) )
 		{
			fromMenuToState(NORMAL);
			//mStateMachineLogic->setCurrentState(NORMAL);
 		}
		else if (GET_SOCKET_VALUE(OK_KEY))
		{
			if (mMenu->isFocusOnHomeEdit())
			{
				fromMenuToState(EDIT);
			} 
			else if (mMenu->isFocusOnWallpaper())
			{
				fromMenuToState(SET_BACKGROUND);
			}
		}
		else if (GET_SOCKET_VALUE(LEFT_KEY))
		{
			//mStateMachineLogic->setCurrentState(EDIT);
			mMenu->MoveFocus(LEFT);
		}
		else if (GET_SOCKET_VALUE(RIGHT_KEY))
		{
			//mStateMachineLogic->setCurrentState(SET_BACKGROUND);
			mMenu->MoveFocus(RIGHT);
		}
		
	}
	else
	{
		fromMenuToState(NORMAL);
	}
}

void MenuLogic::fromMenuToState(StateSet mSet)
{
	if (mStateMachineLogic->getCurrentState() == MENU)
	{
		mStateMachineLogic->setCurrentState(mSet);
	}
	menuIsOpen = false;
	mMenu->setMenuVisible(menuIsOpen);
}