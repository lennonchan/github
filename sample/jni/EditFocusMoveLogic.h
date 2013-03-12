#ifndef __EDITFOCUSMOVELOGIC__
#define __EDITFOCUSMOVELOGIC__

#include "EditBaseLogic.h"

class EditFocusMoveLogic: public EditBaseLogic 
{
public:
	enum{
		CURRENT_EDIT_STATE= 10,
	};
	DECLARE_SOCKET_TYPE(CURRENT_EDIT_STATE, EditStateSet);
	EditFocusMoveLogic(gkLogicTree* parent, size_t id);

	bool evaluate(gkScalar tick);
private:
	void editFocusMove();
};

#endif