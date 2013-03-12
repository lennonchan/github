
#include "AaLogicBuilder.h"
#include "StateMachineLogic.h"
#include "BaseLogic.h"
#include "AaEQLogic.h"
#include "AaMainAppLogic.h"
#include "AaScrollBarLogic.h"
#include "AaSortLogic.h"
#include "Logic/gkMouseNode.h"
#include "Logic/gkButtonNode.h"
#include "AaLetterSortLogic.h"
#include "AaHitAppLogic.h"

AaLogicBuilder::AaLogicBuilder(gkScene * pScene, gkLogicTree * pTree):mScene(pScene), mTree(pTree)
{
	createNode();
	buildAaAppMode();
	buildAaSort();
	buildAaScrollBar();
}

AaLogicBuilder::~AaLogicBuilder()
{

}


void AaLogicBuilder::createNode()
{
	mStateMachineLoigc = BaseLogic::getStateMachineLogic();
	mStateMachineLoigc->	setPriority(FOUTH_PRIORITY);

	//Aa key
	mFocusMoveLeft = mTree->createNode<gkKeyNode>();
	mFocusMoveLeft->setKey(KC_LEFTARROWKEY);

	mFocusMoveRight = mTree->createNode<gkKeyNode>();
	mFocusMoveRight->setKey(KC_RIGHTARROWKEY);

	mFocusMoveUp = mTree->createNode<gkKeyNode>();
	mFocusMoveUp->setKey(KC_UPARROWKEY);

	mFocusMoveDown = mTree->createNode<gkKeyNode>();
	mFocusMoveDown->setKey(KC_DOWNARROWKEY);

	mReturnHomeNode = mTree->createNode<gkKeyNode>();
	mReturnHomeNode->setKey(KC_ESCKEY);

	mOKNode = mTree->createNode<gkKeyNode>();
	mOKNode->setKey(KC_RETKEY);

	//Aa mouse hit
	mMousePress = mTree->createNode<gkMouseButtonNode>();
    mMouseNode = mTree->createNode<gkMouseNode>();

	//	 Aa main
	mMainAppLogicNode = mTree->createNode<AaMainAppLogic>();
	mMainAppLogicNode->setPriority(THIRD_PRIORITY);
	mMainAppLogicNode->linkKey(mFocusMoveLeft, mFocusMoveRight, mFocusMoveUp, mFocusMoveDown, mOKNode, mReturnHomeNode);
	mMainAppLogicNode->linkMouse(mMouseNode, mMousePress);

	// Aa EQ
	mAaEQLogicNode = mTree->createNode<AaEQLogic>();
	mAaEQLogicNode->setPriority(FIRST_PRIORITY);
	mAaEQLogicNode->linkKey(mFocusMoveLeft, mFocusMoveRight, mFocusMoveUp, mFocusMoveDown, mOKNode, mReturnHomeNode);
	mAaEQLogicNode->linkMouse(mMouseNode, mMousePress);

	//Aa scroll bar
	mAaScrollBarNode = mTree->createNode<AaScrollBarLogic>();
	mAaScrollBarNode->setPriority(THIRD_PRIORITY);
	mAaScrollBarNode->linkKey(mFocusMoveLeft, mFocusMoveRight, mFocusMoveUp, mFocusMoveDown, mOKNode, mReturnHomeNode);
	mAaScrollBarNode->linkMouse(mMouseNode, mMousePress);
	
	//Aa sort
	mAaSortNode = mTree->createNode<AaSortLogic>();
	mAaSortNode->setPriority(THIRD_PRIORITY);
	mAaSortNode->linkKey(mFocusMoveLeft, mFocusMoveRight, mFocusMoveUp, mFocusMoveDown, mOKNode, mReturnHomeNode);
	mAaSortNode->linkMouse(mMouseNode, mMousePress);

  //Aa letter sort
	mAaLetterSortLogic = mTree->createNode<AaLetterSortLogic>();
	mAaLetterSortLogic->setPriority(THIRD_PRIORITY);
	mAaLetterSortLogic->linkKey(mFocusMoveLeft, mFocusMoveRight, mFocusMoveUp, mFocusMoveDown, mOKNode, mReturnHomeNode);
	mAaLetterSortLogic->linkMouse(mMouseNode, mMousePress);

	mAaHitAppNode = mTree->createNode<AaHitAppLogic>();
	mAaHitAppNode->setPriority(THIRD_PRIORITY);
	mAaHitAppNode->linkKey(mFocusMoveLeft, mFocusMoveRight, mFocusMoveUp, mFocusMoveDown, mOKNode, mReturnHomeNode);
	mAaHitAppNode->linkMouse(mMouseNode, mMousePress);
}

void AaLogicBuilder::buildAaAppMode()
{
	//½øÈëAa³¡¾°
	mStateMachineLoigc->getCURRENT_STATE()->link(mAaEQLogicNode->getENABLE());
	mStateMachineLoigc->getCURRENT_STATE()->link(mMainAppLogicNode->getENABLE());
}



void AaLogicBuilder::buildAaScrollBar()
{
	mStateMachineLoigc->getCURRENT_STATE()->link(mAaScrollBarNode->getENABLE());
}

void AaLogicBuilder::buildAaSort()
{
	mStateMachineLoigc->getCURRENT_STATE()->link(mAaSortNode->getENABLE());
	mStateMachineLoigc->getCURRENT_STATE()->link(mAaLetterSortLogic->getENABLE());


	mStateMachineLoigc->getCURRENT_STATE()->link(mAaHitAppNode->getENABLE());
}