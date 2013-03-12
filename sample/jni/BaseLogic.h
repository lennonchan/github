#ifndef __BASELOGIC__
#define __BASELOGIC__

#include "UtilKeyLogic.h"


class StateMachineLogic;
class StateEditLoigc;
class gkScene;

class BaseLogic: public UtilKeyNode
{
public:
	
	BaseLogic(gkLogicTree* parent, UTsize handle);
	
	static void setGkScene(gkScene * pGkScene);
	static gkScene * getGkScene();

	static void setLauncherScene(LauncherScene * pLauncherScene);
	static LauncherScene * getLauncherScene( );
	
	static void setAabridge(Aabridge * pAabridge);
	static void setHaSettins(HaSettingsViewImpl * pHaSettings);
	static Aabridge * getAabridge();
	
	static void setStateMachineLogic(StateMachineLogic * pLogic);
	static StateMachineLogic * getStateMachineLogic();

	static void setStateEditLogic(StateEditLoigc * pLogic);
	static StateEditLoigc * getStateEditLogic();

protected:
	static gkScene * mGkScene;
	static LauncherScene * mLauncherScene;
	static Aabridge * mAabridge;
	static HaSettingsViewImpl* mHaSettings;
	
	static StateMachineLogic * mStateMachineLogic;
	static StateEditLoigc * mStateEditLogic;
	
};

#endif


