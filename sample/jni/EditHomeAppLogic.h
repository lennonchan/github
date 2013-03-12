#ifndef __EDITHOMEAPPLOGIC__
#define __EDITHOMEAPPLOGIC__

#include "BaseLogic.h"

class EditHomeAppLogic: public BaseLogic
{
public:
	enum{
		ENABLE = 10,              //��normal�½���༭Ӧ��
		ENABLE_FROM_EDIT  //��EDIT�½���	
	};
	DECLARE_SOCKET_TYPE(ENABLE, StateSet);
	DECLARE_SOCKET_TYPE(ENABLE_FROM_EDIT, EditStateSet);

	EditHomeAppLogic(gkLogicTree* parent, UTsize handle);
	bool evaluate(gkScalar tick);

private:
	void openSetPage();
	void closeSetPage();
	void moveFocus();

	
};


#endif