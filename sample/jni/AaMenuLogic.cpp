#include "AaMenuLogic.h"
#include "Aabridge.h"
#include "StateMachineLogic.h"

AaMenuLoigc::AaMenuLoigc(gkLogicTree* parent, UTsize handle): BaseLogic(parent, handle), mAaMenuIsOpen(false)
{
	ADD_ISOCK(ENABLE_AaMENU,NONE);
	ADD_ISOCK(OPEN_AaMENU, false);

	ADD_OSOCK(IS_HIT_SET_APP, false);
	ADD_OSOCK(IS_HIT_UNINS_APP,false);
}

bool AaMenuLoigc::evaluate(gkScalar tick)
{

	if (GET_SOCKET_VALUE(ENABLE_AaMENU) == ALLAPP)
	{
		if ( GET_SOCKET_VALUE(OPEN_AaMENU) )
		{
			mAaMenuIsOpen = !mAaMenuIsOpen;
		} 
		return true;
	}
 	else
 	{
 	//	mAabridge->setMenuVisible(false);
		mAaMenuIsOpen = false;
		return false;
 	}
}

void AaMenuLoigc::update(gkScalar tick)
{
	if (mAaMenuIsOpen)
	{
		/*mAabridge->setMenuVisible(true);
		if ( mAabridge->isHitSetHomeApps() )
		{
			mStateMachineLogic->fromAaToSetFirApp();
			mAaMenuIsOpen = false;
		}
		if ( mAabridge->isHitUninstallApps() )
		{
			mStateMachineLogic->fromAaToUntApp();
			mAaMenuIsOpen= false;
		}	*/
	}
	else
	{
		//mAabridge->setMenuVisible(false);
	}
}