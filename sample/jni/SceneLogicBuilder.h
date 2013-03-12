#ifndef __SCENELOGIC__
#define __SCENELOGIC__

#include "Ogrekit.h"

class LauncherScene;
class Menu;
class gkLogicNode;
class SceneMoveLogic;
class gkEngine;

class StateMachineLogic;
class MenuLogic;
class gkMouseButtonNode;
class StateEditLoigc;
class gkMouseNode;
class TVLogic;
class TVwindowLogic;
class AppMarketLogic;
class ExitLauncherLogic;
class EditFocusMoveLogic;
class EditBlockMoveLogic;
class EditHomeAppLogic;
class EQEditHomeAppLogic;
class SetBackgroundLogic;

class SceneLogicBuilder
{
public:
	SceneLogicBuilder(gkScene * pScene, gkLogicTree * pTree, gkEngine * pEngine);
	
	~SceneLogicBuilder();


private:

	void createNode();
	void buildMode();

//normal
	void buildEditMenu();

//Edit
	void buildEditMode();

//TV
	void buildTV();
	void buildTVwindow();

//app market
	void buildAppMarket();

//exit luncher
	void buildExit();

//set home app
	void buildHomeApp();

private:
	gkScene* mScene;
	Menu * mMenu;
	gkLogicTree* mTree;
	gkEngine * mEngine;

	gkKeyNode * leftKeyNode;
	gkKeyNode * rightKeyNode;
	gkKeyNode * upKeyNode;
	gkKeyNode * downKeyNode;

// ok & return key
	gkKeyNode * mOKNode;
	gkKeyNode * mReturnNode;
	
//***************************************
	SceneMoveLogic * sceneMoveNode;
	gkMouseNode * mouseMovingNode;
	gkMouseButtonNode * mouseButtonNode;

//menu
	gkKeyNode * openMenuNode;
	MenuLogic * menuLoigcNode;

//edit
	StateEditLoigc * stateEditNode;
//focus move in edit
	EditFocusMoveLogic * mEditFocusMoveNode;
//block move in edit
	EditBlockMoveLogic * mEditBlockMoveNode;

//stateMachine
	StateMachineLogic * stateMachineNode;

//TV 
	TVLogic * mTVNode;

//TV window
	TVwindowLogic * mTVwindowNode;

//App market
	AppMarketLogic * mAppMarketNode;

//Exit luncher
	ExitLauncherLogic *mExitLauncherNode;

//Edit home app
	EQEditHomeAppLogic * mEQEditHomeAppNode;
	EditHomeAppLogic * mEditHomeAppNode;

//set Background
	SetBackgroundLogic * mSetBackgroundNode;
};

#endif


