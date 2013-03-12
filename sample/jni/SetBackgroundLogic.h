#ifndef __SETBACKGROUNDLOGIC__
#define __SETBACKGROUNDLOGIC__

#include "BaseLogic.h"

class WallpaperViewImpl;

class SetBackgroundLogic : public BaseLogic
{
public:
	enum{
		ENABLE = 10,
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);
	SetBackgroundLogic(gkLogicTree* parent, size_t id);
	~SetBackgroundLogic();
	bool  evaluate(gkScalar tick);

private:
	void enterSetBackground();
	void quitSetBackground();
	void focusMove();
	void changeBackground();

private:
	WallpaperViewImpl * mWallpaperView;
	bool isSetBackground;
};

#endif