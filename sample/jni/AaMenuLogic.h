#ifndef __AaMENULOGIC__
#define __AaMENULOGIC__

#include "BaseLogic.h"

class AaMenuLoigc : public BaseLogic
{
public:
	enum{
		ENABLE_AaMENU,
		OPEN_AaMENU,

		IS_HIT_SET_APP,
		IS_HIT_UNINS_APP
	};
	DECLARE_SOCKET_TYPE(ENABLE_AaMENU, StateSet);
	DECLARE_SOCKET_TYPE(OPEN_AaMENU, bool);
	DECLARE_SOCKET_TYPE(IS_HIT_SET_APP, bool);
	DECLARE_SOCKET_TYPE(IS_HIT_UNINS_APP, bool)

	AaMenuLoigc(gkLogicTree* parent, UTsize handle);
	bool evaluate(gkScalar tick);
	void update(gkScalar tick);
protected:
	bool mAaMenuIsOpen;
};


#endif