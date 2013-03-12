#ifndef __SCENEMOVE
#define __SCENEMOVE

#include "BaseLogic.h"
#include "Logic/gkMouseNode.h"


class SceneMoveLogic : public BaseLogic
{
public:
	enum{
		ENABLE = 10,
	};

	DECLARE_SOCKET_TYPE(ENABLE, StateSet);

	SceneMoveLogic(gkLogicTree* parent, size_t id);

	~SceneMoveLogic(){ }

	bool evaluate(gkScalar tick);
	void update(gkScalar tick);
protected:

private:
	void mouseDragSceneMove();
	void mouseHitFocusSceneMove();
	void keyFocusSceneMove();

private:
 	bool isDrag;
	
};

#endif


