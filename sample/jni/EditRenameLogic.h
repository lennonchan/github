#ifndef __EDITRENAMELOGIC__
#define __EDITRENAMELOGIC__

#include "EditBaseLogic.h"


class EditRenameLogic: public EditBaseLogic
{
public:
	enum{
		CURRENT_EDIT_STATE,
		
	};
	DECLARE_SOCKET_TYPE(CURRENT_EDIT_STATE, EditStateSet);

	EditRenameLogic(gkLogicTree* parent, size_t id);
	bool evaluate(gkScalar tick);
	
};

#endif