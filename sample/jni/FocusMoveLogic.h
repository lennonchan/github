#ifndef  __FOCUSMOVENODE 
#define  __FOCUSMOVENODE


#include "BaseLogic.h"

class FocusMoveLogic :public BaseLogic
{
public:
	enum
	{
		ENABLE,

		FOCUS_FLY_LEFT,
		FOCUS_FLY_RIGHT,
		FOCUS_FLY_UP,
		FOCUS_FLY_DOWN,

		SCENE_MOVE_LEFT,
		SCENE_MOVE_RIGHT
	};
	DECLARE_SOCKET_TYPE(ENABLE, bool);
	DECLARE_SOCKET_TYPE(FOCUS_FLY_LEFT, bool);
	DECLARE_SOCKET_TYPE(FOCUS_FLY_RIGHT, bool);
	DECLARE_SOCKET_TYPE(FOCUS_FLY_UP, bool);
	DECLARE_SOCKET_TYPE(FOCUS_FLY_DOWN, bool);

	DECLARE_SOCKET_TYPE(SCENE_MOVE_LEFT, bool);
	DECLARE_SOCKET_TYPE(SCENE_MOVE_RIGHT, bool);

	FocusMoveLogic(gkLogicTree* parent, size_t id):BaseLogic(parent, id)
	{	
		ADD_ISOCK(ENABLE,true);
		ADD_ISOCK(FOCUS_FLY_LEFT, false);
		ADD_ISOCK(FOCUS_FLY_RIGHT, false);
		ADD_ISOCK(FOCUS_FLY_UP, false);
		ADD_ISOCK(FOCUS_FLY_DOWN, false);

		ADD_OSOCK(SCENE_MOVE_LEFT, false);
		ADD_OSOCK(SCENE_MOVE_RIGHT, false);
	}

	bool evaluate(gkScalar tick);

protected:
	


};

#endif


