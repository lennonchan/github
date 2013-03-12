#ifndef __EDITDELETEBLOCKLOGIC__
#define __EDITDELETEBLOCKLOGIC__

#include "EditBaseLogic.h"


class EditDeleteBlockLogic: public EditBaseLogic
{
public:
	enum{
		CURRENT_EDIT_STATE,

	};
	DECLARE_SOCKET_TYPE(CURRENT_EDIT_STATE, EditStateSet);
	EditDeleteBlockLogic(gkLogicTree* parent, size_t id);
	bool evaluate(gkScalar tick);

private:
	void enterEditBlock();
};

#endif