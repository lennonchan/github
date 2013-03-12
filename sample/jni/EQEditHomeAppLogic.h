#ifndef __EQEDITHOMEAPPLOGIC__
#define __EQEDITHOMEAPPLOGIC__

#include "BaseLogic.h"
 //从normal下进入编辑页面
class EQEditHomeAppLogic: public BaseLogic
{
public:
	enum{
		ENABLE_EDIT_HOME_APP = 10,
		ENTER_KEY,

	};
	DECLARE_SOCKET_TYPE(ENABLE_EDIT_HOME_APP, StateSet); 
	DECLARE_SOCKET_TYPE(ENTER_KEY, bool);

	EQEditHomeAppLogic(gkLogicTree* parent, UTsize handle);
	bool evaluate(gkScalar tick);

private:

};


#endif