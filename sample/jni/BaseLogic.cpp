#include "BaseLogic.h"
#include "gkScene.h"

//��Ҫ��ͼ��ͷ�ļ��ж���(��ʼ��)��̬���ݳ�Ա��
//�ڴ����������£��������������ظ����������Ĵ���
//��ʹ����#ifndef #define #endif����#pragma onceҲ���С�
//��̬���ݳ�Աʵ�����������е�ȫ�ֱ��������ԣ���̬���ݳ�Ա�Ķ���(��ʼ��)��Ӧ�ñ�����ͷ�ļ��С� 
//�䶨�巽ʽ��ȫ�ֱ�����ͬ

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