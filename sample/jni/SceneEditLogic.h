#ifndef __SCENEEDITLOGIC
#define __SCENEEDITLOGIC

#include "BaseLogic.h"

class SceneEditLogic : public BaseLogic
{
public:   
	enum{
		ENABLE,
		STATE_IN_EDIT,
		EDIT_BLOCK_LEFT,
		EDIT_BLOCK_RIGHT,
	};

	DECLARE_SOCKET_TYPE(ENABLE, StateSet);
	DECLARE_SOCKET_TYPE(STATE_IN_EDIT, EditStateSet);
	DECLARE_SOCKET_TYPE(EDIT_BLOCK_LEFT, bool);
	DECLARE_SOCKET_TYPE(EDIT_BLOCK_RIGHT, bool);

	SceneEditLogic(gkLogicTree* parent, size_t id);
	~SceneEditLogic(){ }
	
	
	bool evaluate(gkScalar tick);
	//void update(gkScalar tick);

private:
	void sceneEditVisable();
	void focusMove();
	void blockMove();
	void quitEdit();
private:
	bool sceneIsVisable;
	bool switchable;
	int curSwitching;
	int curFocus;
};



#endif