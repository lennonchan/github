#include "SetBackgroundLogic.h"
#include "StateMachineLogic.h"
#include "WallpaperViewImpl.h"

SetBackgroundLogic::SetBackgroundLogic(gkLogicTree* parent, size_t id):BaseLogic(parent, id), isSetBackground(false)
{
	mWallpaperView = new WallpaperViewImpl();
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

SetBackgroundLogic::~SetBackgroundLogic()
{
	ui_delete(mWallpaperView);
}

bool SetBackgroundLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == SET_BACKGROUND)
	{
		enterSetBackground();
		quitSetBackground();
		focusMove();
		changeBackground();
	}
	return false;
}

void SetBackgroundLogic::enterSetBackground()
{
	if (isSetBackground == false)
	{
		mWallpaperView->setViewVisible(true);
		isSetBackground = true;
	}
}

void SetBackgroundLogic::quitSetBackground()
{
	if (GET_SOCKET_VALUE(QUIT_KEY))
	{
		if (isSetBackground)
		{
			mWallpaperView->setViewVisible(false);
			mStateMachineLogic->setCurrentState(NORMAL);
		}
		isSetBackground = false;
	}	
}


void SetBackgroundLogic::focusMove()
{
	if (GET_SOCKET_VALUE(LEFT_KEY))
	{
		mWallpaperView->moveFocus(LEFT);
	}
	else if (GET_SOCKET_VALUE(RIGHT_KEY))
	{
		mWallpaperView->moveFocus(RIGHT);
	}
	else if (GET_SOCKET_VALUE(UP_KEY))
	{
		mWallpaperView->moveFocus(UP);
	}
	else if (GET_SOCKET_VALUE(DOWN_KEY))
	{
		mWallpaperView->moveFocus(DOWN);
	}
	else if (GET_SOCKET_VALUE(OK_KEY))
	{
		if(mWallpaperView->isFocusOnWpSetButton())
			mWallpaperView->setWallpaper(mWallpaperView->getWallPaperThumbIndex());
	}
}

void SetBackgroundLogic::changeBackground()
{
	if (GET_SOCKET_VALUE(OK_KEY))
	{
		mWallpaperView->setWallpaper(mWallpaperView->getWallPaperThumbIndex());
	}
}