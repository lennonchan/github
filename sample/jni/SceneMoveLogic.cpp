#include "SceneMoveLogic.h"


SceneMoveLogic::SceneMoveLogic(gkLogicTree* parent, size_t id):BaseLogic(parent, id),isDrag(true)
{
	
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

	ADD_ISOCK(ENABLE, NORMAL);
}

bool SceneMoveLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == NORMAL)
	{
		return true;
	} 
	else
	{
		return false;
	}
			
}

void SceneMoveLogic::update(gkScalar tick)
{
	mouseDragSceneMove();
	mouseHitFocusSceneMove();
	keyFocusSceneMove();
}


void SceneMoveLogic::mouseHitFocusSceneMove()
{

	if ( GET_SOCKET_VALUE(MOUSE_HIT) )
	{
		Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
		ViewNode* hitObject = mLauncherScene->isHitGameObj(gameObjectArray);	
		if ( hitObject != NULL)
		{
			eFlyDirection temp = mLauncherScene->setCurrentFocus(hitObject);
			if ( temp == LEFT )
			{
				mLauncherScene->blockWholeTranslation(LEFT);
				mLauncherScene->setCurrentFocus(0);
			} 
			else if( temp == RIGHT )
			{
				mLauncherScene->blockWholeTranslation(RIGHT);
				mLauncherScene->setCurrentFocus(0);
			}
		}
	}
}



void SceneMoveLogic::keyFocusSceneMove()
{
	if (GET_SOCKET_VALUE(LEFT_KEY))
	{
		//返回 true代表要focus移动到下一屏幕，则翻屏
		//MYLOGI("key left\n");
		if (mLauncherScene->blockFocusTranslation(LEFT))  
		{
			mLauncherScene->blockWholeTranslation(LEFT);
		}
	}
	if(GET_SOCKET_VALUE(RIGHT_KEY))
	{
		//MYLOGI("key right\n");
		if (mLauncherScene->blockFocusTranslation(RIGHT))
		{
			mLauncherScene->blockWholeTranslation(RIGHT);
		}
	}

	if(GET_SOCKET_VALUE(UP_KEY))
	{
		//MYLOGI("key up\n");
		mLauncherScene->blockFocusTranslation(UP);
	}

	if(GET_SOCKET_VALUE(DOWN_KEY))
	{
		//MYLOGI("key down\n");
		mLauncherScene->blockFocusTranslation(DOWN);
	}
}

void SceneMoveLogic::mouseDragSceneMove()
{

	if (GET_SOCKET_VALUE(IS_MOUSE_DRAG).m_DargState == DragEvent::DragMove)
	{
		MYLOGI("x %f\n", GET_SOCKET_VALUE(IS_MOUSE_DRAG).m_DargDistance.x );
		if ( GET_SOCKET_VALUE(IS_MOUSE_DRAG).m_DargDistance.x < -300)
		{
			if (isDrag)
			{
				mLauncherScene->blockWholeTranslation(RIGHT);
				isDrag = false;
			}
			
		}
		if (GET_SOCKET_VALUE(IS_MOUSE_DRAG).m_DargDistance.x > 300)
		{
			if (isDrag)
			{
				mLauncherScene->blockWholeTranslation(LEFT);
				isDrag = false;
			}
		}
	}
	else isDrag = true;

}