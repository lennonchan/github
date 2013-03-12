
#ifndef _gkMouseNode_h_
#define _gkMouseNode_h_

#include "gkLogicNode.h"
#include "gkInput.h"

typedef struct DragEvent
{
	enum DragType
	{
		DragMove,
		DragNone
	};
	DragEvent():m_DargState(DragNone),m_DargDistance(0,0)
	{}
	DragType m_DargState;
    gkVector2 m_DargDistance;
} DragEvent;


class gkMouseNode : public gkLogicNode
{
public:

	enum
	{
		SCALE_X,
		SCALE_Y,
		MOTION,
		REL_X,
		REL_Y,
		ABS_X,
		ABS_Y,
		WHEEL,
		WHEEL_MOTION,
		DRAG_LEFT,
		DRAG_RIGHT,
		DRAG_EVENT
	};

	DECLARE_SOCKET_TYPE(SCALE_X, gkScalar);
	DECLARE_SOCKET_TYPE(SCALE_Y, gkScalar);
	DECLARE_SOCKET_TYPE(MOTION, bool);
	DECLARE_SOCKET_TYPE(REL_X, gkScalar);
	DECLARE_SOCKET_TYPE(REL_Y, gkScalar);
	DECLARE_SOCKET_TYPE(ABS_X, gkScalar);
	DECLARE_SOCKET_TYPE(ABS_Y, gkScalar);
	DECLARE_SOCKET_TYPE(WHEEL, gkScalar);
	DECLARE_SOCKET_TYPE(WHEEL_MOTION, bool);
	DECLARE_SOCKET_TYPE(DRAG_LEFT, bool);
	DECLARE_SOCKET_TYPE(DRAG_RIGHT, bool);
	DECLARE_SOCKET_TYPE(DRAG_EVENT,DragEvent);

	gkMouseNode(gkLogicTree* parent, size_t id);

	virtual ~gkMouseNode() {}

	bool evaluate(gkScalar tick);


};

#endif//_gkMouseNode_h_
