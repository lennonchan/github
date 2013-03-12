#include "SceneLogicBuilder.h"
#include "SceneMoveLogic.h"

#include "StateMachineLogic.h"
#include "Menu.h"
#include "MenuLogic.h"
#include "StateEditLogic.h"
#include "TVLogic.h"
#include "TVwindowLogic.h"
#include "AppMarketLogic.h"
#include "ExitLanucherLogic.h"
#include "EditFocusMoveLogic.h"
#include "EditBlockMoveLogic.h"
#include "logic/gkButtonNode.h"
#include "EditHomeAppLogic.h"
#include "EQEditHomeAppLogic.h"
#include "SetBackgroundLogic.h"

SceneLogicBuilder::SceneLogicBuilder(gkScene * pScene, gkLogicTree * pLogicTree, gkEngine * pEngine): mScene(pScene),mTree(pLogicTree), mEngine(pEngine)
{
	mMenu = new Menu(mScene);

	createNode();
	buildMode();
	
	buildEditMenu();

	buildEditMode();

	buildTV();
	buildTVwindow();

	buildAppMarket();

	buildExit();

	buildHomeApp();
}

SceneLogicBuilder::~SceneLogicBuilder()
{
	ui_delete (mMenu);
	mMenu = NULL;
}


void SceneLogicBuilder::createNode()
{
	stateMachineNode = mTree->createNode<StateMachineLogic>();
	BaseLogic::setStateMachineLogic(stateMachineNode);

	leftKeyNode = mTree->createNode<gkKeyNode>();
	leftKeyNode->setKey(KC_LEFTARROWKEY);

	rightKeyNode = mTree->createNode<gkKeyNode>();
	rightKeyNode->setKey(KC_RIGHTARROWKEY);

	upKeyNode = mTree->createNode<gkKeyNode>();
	upKeyNode->setKey(KC_UPARROWKEY);

	downKeyNode = mTree->createNode<gkKeyNode>();
	downKeyNode->setKey(KC_DOWNARROWKEY);

	mOKNode = mTree->createNode<gkKeyNode>();
	mOKNode->setKey(KC_RETKEY);

	mReturnNode = mTree->createNode<gkKeyNode>();
	mReturnNode->setKey(KC_ESCKEY);

	mouseMovingNode = mTree->createNode<gkMouseNode>();
	mouseButtonNode = mTree->createNode<gkMouseButtonNode>();

//普通模式下场景移动
	sceneMoveNode = mTree->createNode<SceneMoveLogic>();
	sceneMoveNode->setPriority(THIRD_PRIORITY);
	sceneMoveNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	sceneMoveNode->linkMouse(mouseMovingNode, mouseButtonNode);
  
//进入eidt的menu
	openMenuNode = mTree->createNode<gkKeyNode>();
	openMenuNode->setKey(KC_LEFTALTKEY);
	
	menuLoigcNode = mTree->createNode<MenuLogic>();
	menuLoigcNode->setMenu(mMenu);
	menuLoigcNode->setPriority(FIRST_PRIORITY);
	menuLoigcNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	menuLoigcNode->linkMouse(mouseMovingNode, mouseButtonNode);

//EDIT
	stateEditNode = mTree->createNode<StateEditLoigc>();
	stateEditNode->setPriority(FIRST_PRIORITY);
	stateEditNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	stateEditNode->linkMouse(mouseMovingNode, mouseButtonNode);
	
	BaseLogic::setStateEditLogic(stateEditNode);

//Edit Focus Move
	mEditFocusMoveNode = mTree->createNode<EditFocusMoveLogic>();
	mEditFocusMoveNode->setPriority(THIRD_PRIORITY);
	mEditFocusMoveNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	mEditFocusMoveNode->linkMouse(mouseMovingNode, mouseButtonNode);

//Edit block move
 	mEditBlockMoveNode = mTree->createNode<EditBlockMoveLogic>();
 	mEditBlockMoveNode->setPriority(THIRD_PRIORITY);
 	mEditBlockMoveNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	mEditBlockMoveNode->linkMouse(mouseMovingNode, mouseButtonNode);

	//TV
	mTVNode = mTree->createNode<TVLogic>();
	mTVNode->setPriority(THIRD_PRIORITY);
	mTVNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	mTVNode->linkMouse(mouseMovingNode, mouseButtonNode);

//TV window
	mTVwindowNode = mTree->createNode<TVwindowLogic>();
	mTVwindowNode->setPriority(THIRD_PRIORITY);
	mTVwindowNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	mTVwindowNode->linkMouse(mouseMovingNode, mouseButtonNode);


//App market
 	mAppMarketNode = mTree->createNode<AppMarketLogic>();
 	mAppMarketNode->setPriority(THIRD_PRIORITY);
 	mAppMarketNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
 	mAppMarketNode->linkMouse(mouseMovingNode, mouseButtonNode);

	//Exit launcher
	mExitLauncherNode = mTree->createNode<ExitLauncherLogic>();
	mExitLauncherNode->setEngine(mEngine);
	mExitLauncherNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	mExitLauncherNode->linkMouse(mouseMovingNode, mouseButtonNode);

	//
	mEQEditHomeAppNode = mTree->createNode<EQEditHomeAppLogic>();
	mEQEditHomeAppNode->setPriority(FIRST_PRIORITY);
	mEQEditHomeAppNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	mEQEditHomeAppNode->linkMouse(mouseMovingNode, mouseButtonNode);


	mEditHomeAppNode = mTree->createNode<EditHomeAppLogic>();
	mEditHomeAppNode->setPriority(THIRD_PRIORITY);
	mEditHomeAppNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	mEditHomeAppNode->linkMouse(mouseMovingNode, mouseButtonNode);

//setBackground
	mSetBackgroundNode = mTree->createNode<SetBackgroundLogic>();
	mSetBackgroundNode->setPriority(THIRD_PRIORITY);
	mSetBackgroundNode->linkKey(leftKeyNode, rightKeyNode, upKeyNode, downKeyNode, mOKNode, mReturnNode);
	mSetBackgroundNode->linkMouse(mouseMovingNode, mouseButtonNode);
}


void SceneLogicBuilder::buildMode()
{	
	stateMachineNode->getCURRENT_STATE()->link(sceneMoveNode->getENABLE());
	stateMachineNode->getCURRENT_STATE()->link(menuLoigcNode->getENABLE_MENU());

	stateMachineNode->getCURRENT_STATE()->link(mSetBackgroundNode->getENABLE());
}


void SceneLogicBuilder::buildEditMenu()
{
	openMenuNode->getPRESS()->link(menuLoigcNode->getOPEN_MENU());
}

void SceneLogicBuilder::buildEditMode()
{
 	stateMachineNode->getCURRENT_STATE()->link(stateEditNode->getENABLE());
	stateEditNode->getEDIT_STATE()->link(mEditFocusMoveNode->getCURRENT_EDIT_STATE());
	stateEditNode->getEDIT_STATE()->link(mEditBlockMoveNode->getCURRENT_EDIT_STATE());
	stateEditNode->getEDIT_STATE()->link(mEditHomeAppNode->getENABLE_FROM_EDIT());
}



void SceneLogicBuilder::buildTV()
{
	stateMachineNode->getCURRENT_STATE()->link(mTVNode->getENABLE());
}

void SceneLogicBuilder::buildTVwindow()
{
	stateMachineNode->getCURRENT_STATE()->link(mTVwindowNode->getENABLE());
}

void SceneLogicBuilder::buildAppMarket()
{
	stateMachineNode->getCURRENT_STATE()->link(mAppMarketNode->getENABLE());
}

void SceneLogicBuilder::buildExit()
{
	stateMachineNode->getCURRENT_STATE()->link(mExitLauncherNode->getENABLE());
}

void SceneLogicBuilder::buildHomeApp()
{
	gkKeyNode * E_key = mTree->createNode<gkKeyNode>();
	E_key->setKey(KC_EKEY);
	E_key->getPRESS()->link(mEQEditHomeAppNode->getENTER_KEY());
	stateMachineNode->getCURRENT_STATE()->link(mEQEditHomeAppNode->getENABLE_EDIT_HOME_APP());
	stateMachineNode->getCURRENT_STATE()->link(mEditHomeAppNode->getENABLE());
}