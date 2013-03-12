#include "BaseLogic.h"
#include "gkScene.h"

//不要试图在头文件中定义(初始化)静态数据成员。
//在大多数的情况下，这样做会引起重复定义这样的错误。
//即使加上#ifndef #define #endif或者#pragma once也不行。
//静态数据成员实际上是类域中的全局变量。所以，静态数据成员的定义(初始化)不应该被放在头文件中。 
//其定义方式与全局变量相同

gkScene * BaseLogic::mGkScene = NULL;
LauncherScene * BaseLogic::mLauncherScene = NULL;
Aabridge * BaseLogic::mAabridge = NULL;
HaSettingsViewImpl * BaseLogic::mHaSettings = NULL;
StateMachineLogic * BaseLogic::mStateMachineLogic = NULL;
StateEditLoigc * BaseLogic::mStateEditLogic = NULL;

BaseLogic::BaseLogic(gkLogicTree* parent, UTsize handle):UtilKeyNode(parent, handle)
{
	
}


 void BaseLogic::setGkScene(gkScene * pGkScene)
 {
 	mGkScene = pGkScene;
 }
 
 gkScene * BaseLogic::getGkScene()
 {
 	_ASSERT_(mGkScene != NULL);
 	return mGkScene;
 }

void BaseLogic::setLauncherScene(LauncherScene * pLauncherScene)
{
	mLauncherScene = pLauncherScene;
}

LauncherScene * BaseLogic::getLauncherScene( )
{
	_ASSERT_(mLauncherScene != NULL);
	return mLauncherScene;
}

void BaseLogic::setAabridge(Aabridge * pAabridge)
{
	mAabridge = pAabridge;
}

void 
BaseLogic::setHaSettins(HaSettingsViewImpl* pHaSettings)
{
	mHaSettings = pHaSettings;
}

Aabridge * BaseLogic::getAabridge()
{
	_ASSERT_(mAabridge != NULL);
	return mAabridge;
}

void BaseLogic::setStateMachineLogic(StateMachineLogic * pLogic)
{
	mStateMachineLogic = pLogic;
}

StateMachineLogic * BaseLogic::getStateMachineLogic()
{
	_ASSERT_(mStateMachineLogic!= NULL);
	return mStateMachineLogic;
}

void BaseLogic::setStateEditLogic(StateEditLoigc * pLogic)
{
	mStateEditLogic = pLogic;
}

StateEditLoigc * BaseLogic::getStateEditLogic()
{
	_ASSERT_(mStateEditLogic != NULL);
	return mStateEditLogic;
}