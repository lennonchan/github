#ifndef __EDITBASELOGIC__
#define __EDITBASELOGIC__

#include "BaseLogic.h"
#include "Logic/gkButtonNode.h"
#include "Logic/gkMouseNode.h"


class EditBaseLogic: public BaseLogic
{
public:
// 	enum{
// 		//key event
// 		LEFT_KEY,
// 		RIGHT_KEY,
// 		UP_KEY,
// 		DOWN_KEY,
// 	
// 		OK_KEY,
// 		QUIT_KEY,
// 
// 		// mouse event 
// 		IS_MOUSE_DOWN,
// 		IS_MOUSE_UP,
// 		IS_MOUSE_DRAG,
// 
// 		//mouse hit
// 		MOUSE_HIT
// 	};
// 
// 	DECLARE_SOCKET_TYPE(LEFT_KEY, bool);
// 	DECLARE_SOCKET_TYPE(RIGHT_KEY, bool);
// 	DECLARE_SOCKET_TYPE(UP_KEY, bool);
// 	DECLARE_SOCKET_TYPE(DOWN_KEY, bool);
// 	DECLARE_SOCKET_TYPE(OK_KEY, bool);
// 	DECLARE_SOCKET_TYPE(QUIT_KEY, bool);
// 	
// 	// mouse event
// 	DECLARE_SOCKET_TYPE(IS_MOUSE_DOWN,bool);
// 	DECLARE_SOCKET_TYPE(IS_MOUSE_UP,bool);
// 	DECLARE_SOCKET_TYPE(IS_MOUSE_DRAG,DragEvent);
// 
// 	//mouse hit
// 	DECLARE_SOCKET_TYPE(MOUSE_HIT, bool);

	EditBaseLogic(gkLogicTree* parent, size_t id);
// 	void linkKey(gkKeyNode*leftKey,gkKeyNode*rightKey,gkKeyNode*upKey,
// 		gkKeyNode*downKey, gkKeyNode * okKey, gkKeyNode * returnKey);
// 	void linkMouse(gkMouseNode * mouse, gkMouseButtonNode * mouseButton);

protected:
	static int m_EditFocusIndex;
	static int m_EditBlockIndex;
};

#endif