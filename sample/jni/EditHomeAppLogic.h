#ifndef __EDITHOMEAPPLOGIC__
#define __EDITHOMEAPPLOGIC__

#include "BaseLogic.h"

class EditHomeAppLogic: public BaseLogic
{
public:
	enum{
		ENABLE = 10,              //从normal下进入编辑应用
		ENABLE_FROM_EDIT  //从EDIT下进入	
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