#ifndef __STATEEDITLOGIC__
#define __STATEEDITLOGIC__

#include "EditBaseLogic.h"
#include "BlenderAnmInterface.h"


class StateEditLoigc : public EditBaseLogic,public BlenderAnmInterface
{
public:
	enum{
		ENABLE = 10,
		EDIT_STATE,
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);
	DECLARE_SOCKET_TYPE(EDIT_STATE, EditStateSet);

	StateEditLoigc(gkLogicTree* parent, size_t id);

	bool evaluate(gkScalar tick);
	virtual void onBlenderAnmFinish(BlenderAnimation* p,int s,int e);

	void setCurrentEditState(EditStateSet editState);
	EditStateSet getCurrentEditState();

private:
	void changeToNextState();

	// edit mode change call eg: enter edit or exit edit mode
	void editModeChange(bool isEdit);

	//quit edit
	void quitEdit();

	//dispatch states
	void dispatchStateInEdit();

private:
	bool m_InitEditMode;
	EditStateSet m_currentStateInEdit;
};

#endif