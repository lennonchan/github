#include "AaScrollBarLogic.h"
#include "gkWindow.h"

AaScrollBarLogic::AaScrollBarLogic(gkLogicTree* parent, UTsize handle): BaseLogic(parent, handle)
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

	ADD_ISOCK(ENABLE, NONE);

}

bool AaScrollBarLogic::evaluate(gkScalar tick)
{
	if (GET_SOCKET_VALUE(ENABLE) == ALLAPP)
	{
		if (GET_SOCKET_VALUE(MOUSE_HIT))
		{
			Ogre::RaySceneQueryResult gameObjectArray= getGkScene()->getOgreRayTest();
			scrollBarDrag(gameObjectArray);
			scrollBarTrack(gameObjectArray);
		}
	} 	
	return true;
}

void AaScrollBarLogic::scrollBarDrag(Ogre::RaySceneQueryResult& gameObjectArray)
{
	
	if (mAabridge->isHitScrollBar(gameObjectArray))
	{
		if (GET_SOCKET_VALUE(IS_MOUSE_DRAG).m_DargState == DragEvent::DragMove)
		{
			float x = GET_SOCKET_VALUE(IS_MOUSE_DRAG).m_DargDistance.x;
 			float y = GET_SOCKET_VALUE(IS_MOUSE_DRAG).m_DargDistance.y;
 			

// 			float windowWidth = Aabridge::getScene()->getDisplayWindow()->getRequestedWidth();
// 			float windowHeight = Aabridge::getScene()->getDisplayWindow()->getRequestedHeight();
// 
// 			MYLOGI("%f,  %f\n", x,  y);
// 			MYLOGI("%f,  %f\n", windowWidth,  windowHeight);
// 			MYLOGI("%f,  %f\n", x/windowWidth,  y/windowHeight);
		}
	}
	
}

void AaScrollBarLogic::scrollBarTrack(Ogre::RaySceneQueryResult& gameObjectArray)
{
	if (mAabridge->isHitScrollBarTrack(gameObjectArray))
	{
		gkVector3 gk3 = mAabridge->getScrollBarPos();
	}
}