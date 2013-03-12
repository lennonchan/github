#include "StateEditLogic.h"
#include "StateMachineLogic.h"

 StateEditLoigc:: StateEditLoigc(gkLogicTree* parent, size_t id): EditBaseLogic(parent, id)
	 ,m_InitEditMode(false), m_currentStateInEdit(ESS_FOCUS_MOVE)
{

	// 基类的socket必须在派生类中add
	ADD_ISOCK(LEFT_KEY, false);
	ADD_ISOCK(RIGHT_KEY, false);
	ADD_ISOCK(UP_KEY, false);
	ADD_ISOCK(DOWN_KEY, false);
	ADD_ISOCK(OK_KEY, false);
	ADD_ISOCK(QUIT_KEY, false);

	ADD_ISOCK(IS_MOUSE_DOWN,false);
	ADD_ISOCK(IS_MOUSE_UP,false);
	ADD_ISOCK(IS_MOUSE_DRAG,DragEvent());
	
	ADD_ISOCK(MOUSE_HIT, false);

	//派生类的socket必须在基类的socket后add
	ADD_ISOCK(ENABLE, NONE);
	ADD_OSOCK(EDIT_STATE, ESS_FOCUS_MOVE);	

}

void StateEditLoigc::setCurrentEditState(EditStateSet editState)
{
	m_currentStateInEdit = editState;
}

EditStateSet StateEditLoigc::getCurrentEditState()
{
	return m_currentStateInEdit;
}

bool  StateEditLoigc::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == EDIT)
	{
		editModeChange(true);
		changeToNextState();
		quitEdit();
		dispatchStateInEdit();
	}
	else
	{
		editModeChange(false);
	}
	return false;
}




void StateEditLoigc::editModeChange(bool isEdit)
{
	if (m_InitEditMode != isEdit)
	{
		m_InitEditMode = isEdit;
		if (!m_InitEditMode)
		{
			m_EditBlockIndex = 1;
 			m_EditFocusIndex = 1;
		}
#if _LAUNCHER_EDITMENU_OLDSTYLE_
		mLauncherScene->setEditMode(m_InitEditMode);
#else
		m_InitEditMode?mLauncherScene->setEditMode(m_InitEditMode):
			mLauncherScene->hideEditMenu(this);	
#endif
		//初始化edit下的状态
		if (isEdit)
		{
			//SET_SOCKET_VALUE(EDIT_STATE, ESS_FOCUS_MOVE);
			m_currentStateInEdit = ESS_FOCUS_MOVE;
			dispatchStateInEdit();
		}
	}
}


static bool isDelete = false;
void StateEditLoigc::changeToNextState()
{
	//EditStateSet nextstate = ESS_FOCUS_MOVE;
	bool isChange = false;
	int currentIndex = -1;
	if (mLauncherScene)
	{
		if (  GET_SOCKET_VALUE(IS_MOUSE_DOWN)	 )
		{
			//MYLOGI("Mouse down\n");
			Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
			isChange = mLauncherScene->onContextMenu_EM(currentIndex, gameObjectArray);
		}	
		else if (GET_SOCKET_VALUE(OK_KEY))
		{
			isChange = true;
			currentIndex = mLauncherScene->getMenuFocus_EM();
		}
		
		if (isChange)
		{
			//MYLOGI("Hit Index %d \n", currentIndex);
			switch(currentIndex)
			{
			case 0:
				m_currentStateInEdit = ESS_BLOCK_MOVE;
				break;
			case 1:
				m_currentStateInEdit = ESS_EDIT_BLOCK;
				break;
			case 2:
				m_currentStateInEdit = ESS_DELETE_BLOCK;
				//isDelete = true;
				break;
			case 3:
				m_currentStateInEdit = ESS_DELETE_APP;
				break;
			case 4:
				m_currentStateInEdit = ESS_ADD_BLOCK;
				break;	
			default:
				MYLOGI("Edit menu stats error \n");
				_ASSERT_(0);
				break;
			}
			isChange = false;
		}
	}
}


void StateEditLoigc::quitEdit()
{


	if ( GET_SOCKET_VALUE(QUIT_KEY) )
	{
		if (GET_SOCKET_VALUE(EDIT_STATE) == ESS_FOCUS_MOVE)
		{
			editModeChange(false);
			mStateMachineLogic->setCurrentState(NORMAL);
			m_currentStateInEdit = ESS_NONE;	
		}
		else if (GET_SOCKET_VALUE(EDIT_STATE) == ESS_EDIT_BLOCK)
		{
			mAabridge->exitHomeAppSettings();
			mLauncherScene->setMenuFocus_EM(0);
			m_currentStateInEdit = ESS_FOCUS_MOVE;
		}
		else if(GET_SOCKET_VALUE(EDIT_STATE) == ESS_BLOCK_MOVE)
		{
			m_currentStateInEdit = ESS_FOCUS_MOVE;
		}
	
	}
	else if (GET_SOCKET_VALUE(MOUSE_HIT))
	{
		Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
		if (mLauncherScene->isHitExitNode_EM(gameObjectArray))
		{
			editModeChange(false);
			mStateMachineLogic->setCurrentState(NORMAL);
		}
		//SET_SOCKET_VALUE(EDIT_STATE, ESS_NONE);
		m_currentStateInEdit = ESS_NONE;
	}
}

void StateEditLoigc::onBlenderAnmFinish(BlenderAnimation* p,int s,int )
{
	mLauncherScene->setEditMode(m_InitEditMode);
}

void StateEditLoigc::dispatchStateInEdit()
{
	SET_SOCKET_VALUE(EDIT_STATE, m_currentStateInEdit);
	if (m_currentStateInEdit == ESS_EDIT_BLOCK)
	{
		MYLOGI("current ess edit block\n");
	}
}

