#ifndef __AaLOGICBUILDER__
#define __AaLOGICBUILDER__

#include "Ogrekit.h"

class StateMachineLogic;
class AaMainAppLogic;
class AaMenuLoigc;
class AaEQLogic;
class AaScrollBarLogic;
class gkMouseNode;
class AaSortLogic;
class AaLetterSortLogic;
class gkMouseButtonNode;
class AaHitAppLogic;


class AaLogicBuilder
{
public:
	AaLogicBuilder(gkScene * pScene, gkLogicTree * pTree);
	~AaLogicBuilder();

	void createNode();
	void buildAaAppMode();
	void buildAaSort();
	void buildAaScrollBar();
private:
	StateMachineLogic * mStateMachineLoigc;
	gkScene * mScene;
	gkLogicTree * mTree;
	
	gkMouseButtonNode * mMousePress;
	gkMouseNode * mMouseNode;
	gkKeyNode * mFocusMoveLeft;
	gkKeyNode * mFocusMoveRight;
	gkKeyNode * mFocusMoveUp;
	gkKeyNode * mFocusMoveDown;
	gkKeyNode * mOKNode;
	gkKeyNode * mReturnHomeNode;

	AaEQLogic * mAaEQLogicNode;
	AaMainAppLogic * mMainAppLogicNode;

	AaScrollBarLogic * mAaScrollBarNode;

	AaSortLogic * mAaSortNode;
	
	AaLetterSortLogic * mAaLetterSortLogic;

    AaHitAppLogic * mAaHitAppNode;

};



#endif