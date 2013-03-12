/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Nestor Silveira.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/

#include "gkCollisionNode.h"
#ifdef OGREKIT_USE_PHYSICS
#include "gkRigidBody.h"
#endif
#include "gkScene.h"
#ifdef OGREKIT_USE_PHYSICS
#include "gkDynamicsWorld.h"
#endif
#include "gkEngine.h"
#include "gkGameObject.h"
#ifdef OGREKIT_USE_PHYSICS
#include "gkCharacter.h"
#endif
#ifdef OGREKIT_USE_BULLET
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#endif

gkCollisionNode::gkCollisionNode(gkLogicTree* parent, size_t id)
	: gkLogicNode(parent, id),
	  m_object(0)
{
	ADD_ISOCK(ENABLE, false);
	ADD_ISOCK(TARGET, 0);
	ADD_ISOCK(COLLIDES_WITH, "");
	ADD_OSOCK(HAS_COLLIDED, false);
	ADD_OSOCK(NOT_HAS_COLLIDED, true);
	ADD_OSOCK(COLLIDED_OBJ, 0);
	ADD_OSOCK(CONTACT_POSITION, gkVector3::ZERO);
}

gkCollisionNode::~gkCollisionNode()
{
}

void gkCollisionNode::initialize()
{
	gkScene* pScene = gkEngine::getSingleton().getActiveScene();
#ifdef OGREKIT_USE_PHYSICS
	pScene->getDynamicsWorld()->EnableContacts(true);
#endif
}

bool gkCollisionNode::evaluate(gkScalar tick)
{
	gkGameObject* pObj = GET_SOCKET_VALUE(TARGET);

	m_object = 0;
#ifdef OGREKIT_USE_PHYSICS
	if (pObj && pObj->isInstanced())
	{
		m_object = pObj->getPhysicsController();
	}
#endif

	return m_object != 0;
}

void gkCollisionNode::update(gkScalar tick)
{
	SET_SOCKET_VALUE(HAS_COLLIDED, false);

	if (m_timer.getTimeMilliseconds() > 300)
	{
		SET_SOCKET_VALUE(NOT_HAS_COLLIDED, true);
		m_timer.reset();
	}


	if (GET_SOCKET_VALUE(ENABLE))
	{
#ifdef OGREKIT_USE_PHYSICS
		m_object->enableContactProcessing(true);

		gkContactInfo c;

		if (m_object->collidesWith(GET_SOCKET_VALUE(COLLIDES_WITH), &c))
		{
			SET_SOCKET_VALUE(CONTACT_POSITION, gkVector3(c.point.getPositionWorldOnA()));
			SET_SOCKET_VALUE(COLLIDED_OBJ, c.collider->getObject());
			SET_SOCKET_VALUE(HAS_COLLIDED, true);
			SET_SOCKET_VALUE(NOT_HAS_COLLIDED, false);
			m_timer.reset();
		}
#endif
	}
	else
	{
#ifdef OGREKIT_USE_PHYSICS
		m_object->enableContactProcessing(false);
#endif
	}
}
