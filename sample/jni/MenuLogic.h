#ifndef __MENULOGIC__
#define __MENULOGIC__


#include "BaseLogic.h"

class Menu;
class MenuLogic: public BaseLogic
{
public:
	enum{
		ENABLE_MENU = 10,  //在normal模式下
 		OPEN_MENU,   

	};
	DECLARE_SOCKET_TYPE(ENABLE_MENU, StateSet);
 	DECLARE_SOCKET_TYPE(OPEN_MENU, bool);

	MenuLogic(gkLogicTree* parent, size_t id);

	void setMenu(Menu * pMenu)
	{
		mMenu = pMenu;
	}
	
	bool evaluate(gkScalar tick);
	void update(gkScalar tick);

private:
	void fromMenuToState(StateSet mSet);

	Menu * mMenu;
	bool menuIsOpen;
};

#endif