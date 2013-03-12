#ifndef __EDITDELETEAPPLOGIC__
#define __EDITDELETEAPPLOGIC__

#include "EditBaseLogic.h"

class EditDeleteAppLogic: public EditBaseLogic
{
public: 
	enum{
		CURRENT_EDIT_STATE = 10,
	};
	DECLARE_SOCKET_TYPE(CURRENT_EDIT_STATE, EditStateSet);
	EditDeleteAppLogic(gkLogicTree* parent, size_t id);
	bool evaluate(gkScalar tick);

private:
	void editDeleteApp();
};

#endif