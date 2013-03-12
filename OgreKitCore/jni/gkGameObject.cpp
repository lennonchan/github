/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): Nestor Silveira.
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
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreException.h"
#include "OgreEntity.h"
#include "OgreStringConverter.h"
#include "OgreMaterial.h"
#include "OgreSubEntity.h"

#include "gkSceneManager.h"
#include "gkScene.h"
#include "gkGameObject.h"
#include "gkCamera.h"
#include "gkLight.h"
#include "gkEntity.h"

#include "gkEngine.h"
#include "gkLogger.h"

#include "gkLogicManager.h"
#include "gkLogicLink.h"
#include "gkLogicTree.h"
#include "gkConstraintManager.h"
#include "gkGameObjectGroup.h"
#ifdef OGREKIT_USE_PHYSICS
#include "gkRigidBody.h"
#include "gkCharacter.h"
#include "gkDynamicsWorld.h"
#endif
#include "gkMesh.h"
#include "gkVariable.h"

#include "gkAnimationManager.h"
#include "gkWindowSystem.h"

#include "OgreMatrix4.h"
#include "OgreVector3.h"

using namespace Ogre;

gkGameObject::gkGameObject(gkInstancedManager* creator, const gkResourceName& name, const gkResourceHandle& handle, gkGameObjectTypes type)
	:    gkInstancedObject(creator, name, handle),
	     m_type(type), m_baseProps(), m_parent(0), m_scene(0),
	     m_node(0), m_logic(0), m_bricks(0),
		 #ifdef OGREKIT_USE_PHYSICS
	     m_rigidBody(0), m_character(0),m_ghost(0),
		 #endif
	     m_groupID(0), m_group(0),
	     m_state(0), m_activeLayer(true),
	     m_layer(0xFFFFFFFF),
	     m_isClone(false),
	     m_flags(0),
	     m_actionBlender(0),
		 m_rayQuery(NULL)
{
	m_life.tick = 0;
	m_life.timeToLive = 0;
}


gkGameObject::~gkGameObject()
{
	if(m_isClone)
	{
		Ogre::SceneNode::ObjectIterator iter = this->m_node->getAttachedObjectIterator();
		while(iter.hasMoreElements())
		{
			Ogre::MovableObject * node = iter.getNext();
			Ogre::Entity* cloneEntity = static_cast<Ogre::Entity *>(node);
			if (cloneEntity)
			{
				//for (unsigned int i = 0; i <cloneEntity->getNumSubEntities(); ++i)
				for (int i = (int)cloneEntity->getNumSubEntities()-1; i >=0; --i)
				{
					Ogre::SubEntity* subEntity = cloneEntity->getSubEntity(i);
					if (subEntity)
					{
						if (!subEntity->getMaterial().isNull())
						{
							for (int j = 0; j<subEntity->getSubTextureMap().size();j++)
							{
								if(subEntity->getSubTextureMap()[j])
									OGRE_DELETE subEntity->getSubTextureMap()[j];
							}
						}
					}
				}
			}
		}
	}

	clearVariables();

	if (m_bricks)
	{
		m_bricks->getLogicManager()->destroy(m_bricks);
		m_bricks = 0;
	}

	if(m_actionBlender)
		delete m_actionBlender;

	Animations::Iterator it = m_actions.iterator();
	while (it.hasMoreElements())
		delete it.getNext().second;
}


#ifdef OGREKIT_USE_NNODE
void gkGameObject::attachLogic(gkLogicTree* tree)
{
	if (!m_logic)
	{
		m_logic = tree;
		m_logic->attachObject(this);
	}
}
#endif

void gkGameObject::attachLogic(gkLogicLink* bricks)
{
	UT_ASSERT(!m_bricks);
	m_bricks = bricks;
}



gkGameObject* gkGameObject::clone(const gkString& name)
{
	gkGameObject* ob = new gkGameObject(getInstanceCreator(), name, m_type);
	cloneImpl(ob);
	return ob;
}




void gkGameObject::cloneImpl(gkGameObject* clob)
{
	clob->m_activeLayer = m_activeLayer;
	clob->m_baseProps = m_baseProps;
	clob->m_isClone = true;
	clob->m_scene = m_scene;

	// clone variables
	utHashTableIterator<VariableMap> iter(m_variables);
	while (iter.hasMoreElements())
	{
		gkVariable* ovar = iter.getNext().second;
		gkVariable* nvar = ovar->clone();

		// no debug
		nvar->setDebug(false);
		clob->m_variables.insert(nvar->getName(), nvar);
	}



	if (m_scene)
	{
		gkConstraintManager* mgr = m_scene->getConstraintManager();
		mgr->notifyObjectCloned(this, clob);
	}


	// clone logic nodes



	// clone logic bricks
	if (m_bricks != 0)
		clob->m_bricks = m_bricks->clone(clob);
}




void gkGameObject::createInstanceImpl(void)
{
	Ogre::SceneManager* manager = m_scene->getManager();
	Ogre::SceneNode* parentNode = 0;
	gkGameObject* parentGameObject = 0;

	if (!m_scene->isBeingCreated())
	{
		// Scene is not currently loading, meaning
		// a specific object is being loaded. (maintain previous parent)

		//add by zy: parent setting
		const gkHashedString pname = this->getProperties().m_parent;
		if (!pname.str().empty())
			parentGameObject = m_scene->getObject(pname.str());
		m_parent = parentGameObject;

		if (m_parent)
		{
			parentGameObject->getChildren().push_back(this);
			if (!m_parent->isInstanced())
				m_parent->createInstance();

			parentNode = m_parent->m_node;
			GK_ASSERT(parentNode);
		}
	}
	
	m_node = parentNode ? parentNode->createChildSceneNode(m_name.getName())
						: manager->getRootSceneNode()->createChildSceneNode(m_name.getName());

    
	//make matrix change enable  zy
	m_baseProps.m_transform.loc_enable = true;
	m_baseProps.m_transform.rot_enable = true;
	m_baseProps.m_transform.scl_enable = true;

	if(m_baseProps.m_transform.rot.isNaN())
	{
		m_baseProps.m_transform.rot = gkQuaternion(1,0,0,0);
	}

	//add by zy
		//m_parent->addChild(this);
	applyTransformState(m_baseProps.m_transform,1.0,true);


	if (!m_scene->isBeingCreated())
	{
		// Reattach children (ogre) nodes
		gkGameObjectArray::Iterator iter = m_children.iterator();
		while (iter.hasMoreElements())
		{
			gkGameObject* pChild = iter.getNext();

			if (pChild->m_node)
			{
				Ogre::SceneNode* pParentNode = pChild->m_node->getParentSceneNode();
				if (pParentNode)
				{
					Ogre::Node* pChildNode = pParentNode->removeChild(pChild->m_node);
					m_node->addChild(pChildNode);
				}
				else
					m_node->addChild(pChild->m_node);
			}
		}
	}

	//m_node->setInitialState();	/* 2012-11-8 marked by zhangying*/
}

gkVector2  gkGameObject::Convert3DPositionToScreenPosition(gkVector3 scenePosition)
{
	gkVector3 returnValue = _internal_Convert_Position_3D_2D(scenePosition,false);
	return  gkVector2(returnValue.x,returnValue.y);
}
gkVector3  gkGameObject::ConvertScreenPositionTo3DPosition(gkVector2 screenPosition)
{
	gkVector3 returnValue(screenPosition.x,screenPosition.y,0);
	return _internal_Convert_Position_3D_2D(returnValue);
}


gkVector3 gkGameObject::_internal_Convert_Position_3D_2D(gkVector3 value,bool to3D)
{
	gkVector3 ReslutPosition;
	if (m_scene)
	{
		Ogre::SceneManager* manager = m_scene->getManager();
		if (manager)
		{
			Ogre::Viewport* mainViewPort = manager->getCurrentViewport();
			if (mainViewPort)
			{
				Ogre::Camera * mCamera = mainViewPort->getCamera();
				Ogre::Matrix4 viewMat = mCamera->getViewMatrix(true); 
				Ogre::Matrix4 projMat = mCamera->getProjectionMatrix(); 
				if (to3D)
				{
					Matrix4 inverseVP = (projMat * viewMat).inverse();
					Real nx = (2.0f * value.x) - 1.0f;
					Real ny = 1.0f - (2.0f * value.y);
					Vector3 nearPoint(nx, ny, -1.f);
					ReslutPosition = inverseVP * nearPoint;
				}
				else
				{
					Ogre::Vector3 screenPos = projMat * viewMat * value; 
					ReslutPosition.x = (screenPos.x + 1.0f)/ 2.0f; 
					ReslutPosition.y = -1*(screenPos.y - 1.0f) / 2.0f; 
				}
			}
		}
	}
	return ReslutPosition;

}

bool gkGameObject::getObjectClipEnable()
{
	if (this->m_node)
	{
		Ogre::Entity * mainEntity = static_cast<Ogre::Entity *>(this->m_node->getAttachedObject(0));
		if (mainEntity)
		{
			Ogre::SubEntity * fristSubEntity = mainEntity->getSubEntity(0);
			if (fristSubEntity)
			{
				Ogre::MaterialPtr subMaterial = fristSubEntity->getMaterial();
				if(!subMaterial.isNull())
				{
					if (subMaterial->getTechnique(0) && subMaterial->getTechnique(0)->getPass(0)
						&& subMaterial->getTechnique(0)->getPass(0)->getManualCullingMode() == MANUAL_CULL_CLIP_RECT)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

void  gkGameObject::setAlpha(float alphaValue)
{
	gkString AlphaGPUName = "LastLayerColor";
	Ogre::Pass* CurrentPass = NULL;
	for (int i =0; i< getCurrentOgrePass().size(); ++i)
	{
		CurrentPass = getCurrentOgrePass()[i];
		Ogre::GpuProgramParametersSharedPtr vsParams = CurrentPass->getFragmentProgramParameters();
		if (!vsParams.isNull())
		{
			vsParams->setNamedConstant(AlphaGPUName,gkColor(1.0,1.0,1.0,alphaValue));
		}
	}

	gkEntity * caseEntity = dynamic_cast<gkEntity *>(this);
	if (caseEntity)
	{
		caseEntity->setAlpha(alphaValue);
	}

}

void gkGameObject::setGpuParameter(gkString gpuName,float * value, int valueSize)
{
	Ogre::Pass* CurrentPass = NULL;
	for (int i =0; i< getCurrentOgrePass().size(); ++i)
	{
		CurrentPass = getCurrentOgrePass()[i];
		Ogre::GpuProgramParametersSharedPtr vsParams = CurrentPass->getFragmentProgramParameters();
		if (!vsParams.isNull())
		{
			vsParams->setNamedConstant(gpuName,value,valueSize);
		}
	}

	gkEntity * childPointer = dynamic_cast<gkEntity*>(this);
	if (childPointer)
	{
		if (gpuName == "textureColorAdjust")
		{
			childPointer->setTextureColor(0,Vector4(value));
		}
	}
}

void gkGameObject::setObjectClipEnable(bool enable)
{
	if (this->m_node)
	{
		Ogre::Entity * mainEntity = static_cast<Ogre::Entity *>(this->m_node->getAttachedObject(0));
		if (mainEntity)
		{
			Ogre::SubEntity * fristSubEntity ;//= mainEntity->getSubEntity(0);
			int num = mainEntity->getNumSubEntities();
			for (int i = 0;i<num;i++)
			{
				fristSubEntity = mainEntity->getSubEntity(i);
				if (fristSubEntity)
				{
				//	Ogre::MaterialPtr subMaterial = fristSubEntity->getMaterial();
					//if(!subMaterial.isNull())
				//	{
						if (enable)
						{
							fristSubEntity->setManualCullingMode(MANUAL_CULL_CLIP_RECT);
						}
						else fristSubEntity->setManualCullingMode(MANUAL_CULL_NONE);
					//}
				}
			}
		}
	}
}


void gkGameObject::postCreateInstanceImpl(void)
{
	// tell scene
	m_scene->notifyInstanceCreated(this);

	sendNotification(Notifier::INSTANCE_CREATED);
}



void gkGameObject::postDestroyInstanceImpl(void)
{
	// tell logic
	if (m_bricks)
		m_bricks->destroyInstance();


	// tell scene
	m_scene->notifyInstanceDestroyed(this);

	if (m_scene->isBeingDestroyed())
	{
		m_parent = 0;
		m_children.clear();
	}

	sendNotification(Notifier::INSTANCE_DESTROYED);
}




void gkGameObject::destroyInstanceImpl(void)
{
	Ogre::SceneManager* manager = m_scene->getManager();


	if (!m_scene->isBeingDestroyed())
	{
		if (m_node)
		{
			// Destroy and detach from scene graph
			Ogre::SceneNode* pParentNode = m_node->getParentSceneNode();

			unsigned short n = m_node->numChildren();

			for (unsigned short i = 0; i < n; i++)
			{
				Ogre::Node* pChildNode = m_node->removeChild(i);

				pParentNode->addChild(pChildNode);

			}

			manager->destroySceneNode(m_node);
		}
	}

	m_node = 0;


	// Reset variables
	utHashTableIterator<VariableMap> iter(m_variables);
	while (iter.hasMoreElements())
	{
		gkVariable* cvar = iter.getNext().second;
		cvar->reset();
	}
}




bool gkGameObject::hasSensorMaterial(const gkString& name, bool onlyFirst)
{
	gkEntity* ent = getEntity();
	if (ent)
	{
		gkMesh* me = ent->getEntityProperties().m_mesh;
		if (me)
		{
			if (onlyFirst)
				return me->getFirstMaterial().m_name == name;
			else
			{
				gkMesh::SubMeshIterator iter = me->getSubMeshIterator();
				while (iter.hasMoreElements())
				{
					gkSubMesh* sme = iter.getNext();
					if (sme->getMaterialName() == name)
						return true;
				}
			}
		}
	}
	return false;
}



Ogre::MovableObject* gkGameObject::getMovable(void)
{
	if (!isInstanced())
		return 0;

	switch (m_type)
	{
	case GK_CAMERA:
		return getCamera()->getCamera();
	case GK_ENTITY:
		return getEntity()->getEntity();
	case GK_LIGHT:
		return getLight()->getLight();
	}
	return 0;
}



const gkTransformState& gkGameObject::getTransformState(void)
{
	static gkTransformState m_state;
	m_state.loc = getPosition();
	m_state.rot = getOrientation();
	m_state.scl = getScale();
	return m_state;
}



const gkMatrix4& gkGameObject::getTransform(void)
{
	static gkMatrix4 temp;
	if (m_node != 0)
	{
		getTransformState().toMatrix(temp);
		return temp;
	}
	return gkMatrix4::IDENTITY;
}



const gkVector3& gkGameObject::getPosition(void)
{
	if (m_node != 0)
		return m_node->getPosition();
	return m_baseProps.m_transform.loc;
}


const gkVector3& gkGameObject::getScale(void)
{
	if (m_node != 0)
		return m_node->getScale();
	return m_baseProps.m_transform.scl;
}



const gkQuaternion& gkGameObject::getOrientation(void)
{
	if (m_node != 0)
		return m_node->getOrientation();
	return m_baseProps.m_transform.rot;
}



gkEuler gkGameObject::getRotation(void)
{
	return gkEuler(getOrientation());
}


const gkTransformState& gkGameObject::getWorldTransformState(void)
{
	static gkTransformState m_state;
	m_state.loc = getWorldPosition();
	m_state.rot = getWorldOrientation();
	m_state.scl = getWorldScale();
	return m_state;
}


const gkMatrix4& gkGameObject::getWorldTransform(void)
{
	if (m_node != 0)
		return m_node->_getFullTransform();
	return gkMatrix4::IDENTITY;
}



const gkVector3& gkGameObject::getWorldPosition(void)
{
	if (m_node != 0)
		return m_node->_getDerivedPosition();
	return m_baseProps.m_transform.loc;
}


const gkVector3& gkGameObject::getWorldScale(void)
{
	if (m_node != 0)
		return m_node->_getDerivedScale();
	return m_baseProps.m_transform.scl;
}



const gkQuaternion& gkGameObject::getWorldOrientation(void)
{
	if (m_node != 0)
		return m_node->_getDerivedOrientation();
	return m_baseProps.m_transform.rot;
}



gkEuler gkGameObject::getWorldRotation(void)
{
	return gkEuler(getWorldOrientation());
}



void gkGameObject::notifyUpdate(void)
{
	if (m_scene)
		m_scene->notifyObjectUpdate(this);

	sendNotification(Notifier::UPDATED);
}

Ogre::Pass* gkGameObject::getCurrentOgrePass(int entityIndex)
{
	Ogre::SceneNode::ObjectIterator iter = this->m_node->getAttachedObjectIterator();
	while(iter.hasMoreElements())
	{
		Ogre::MovableObject * node = iter.getNext();
		Ogre::Entity* entity = static_cast<Ogre::Entity *>(node);
		if(entity->getNumSubEntities() <= entityIndex) return NULL;
		Ogre::SubEntity* subentity = entity->getSubEntity(entityIndex);
		if (subentity)
		{
			if (!subentity->getMaterial().isNull())
			{
				if(subentity->getTechnique())
					return subentity->getTechnique()->getPass(0);
			}
		}
	}
	return NULL;
}

// utility method    zy
utArray<Ogre::Pass*> gkGameObject::getCurrentOgrePass()
{
	utArray<Ogre::Pass*> returnPass;
	Ogre::SceneNode::ObjectIterator iter = this->m_node->getAttachedObjectIterator();
	while(iter.hasMoreElements())
	{
		Ogre::MovableObject * node = iter.getNext();
		Ogre::Entity* entity = static_cast<Ogre::Entity *>(node);
		for (unsigned int i = 0; i < entity->getNumSubEntities(); ++i)
		{
			Ogre::SubEntity* subentity = entity->getSubEntity(i);
			if (subentity)
			{
				if (!subentity->getMaterial().isNull())
				{
					if(subentity->getTechnique())
						returnPass.push_back(subentity->getTechnique()->getPass(0));
				}
			}
			
		}
		
	}
	return returnPass;
}

gkRay gkGameObject::CameraToViewportRay()
{
	Ogre::Camera * oc = ActiveOgreCamera();
	gkVector2 OgreMousePosition = GetMousePosition();

	//printf("Mouse Position x = %f y =%f \n",OgreMousePosition.x,OgreMousePosition.y);

	Ogre::Ray dest;
	if(oc) oc->getCameraToViewportRay(OgreMousePosition.x, OgreMousePosition.y, &dest);
	return dest;
}

Ogre::Camera * gkGameObject::ActiveOgreCamera()
{
	gkCamera* cam = getOwner()->getMainCamera();
	return cam->getCamera();
}

bool gkGameObject::TestRayHitMe(gkRay& ray)
{
	if (m_rayQuery == 0)
	{
		Ogre::SceneManager* mgr = getOwner()->getManager();
		m_rayQuery = mgr->createRayQuery(ray);
	}
	else m_rayQuery->setRay(ray);

	// do the test
	Ogre::RaySceneQueryResult& res = m_rayQuery->execute();

	bool result = false;
	for (Ogre::RaySceneQueryResult::iterator it = res.begin(); it != res.end(); ++it)
	{
		Ogre::RaySceneQueryResultEntry ent = (*it);

		//gkPrintf("hit Name %s \n",ent.movable->getName().c_str());

		if (ent.movable == ActiveOgreCamera())
			continue;
		if (ent.movable)
		{
			void * movable = static_cast<void*>(getMovable());

			if (ent.movable == m_node->getAttachedObject(0))
			{
				result = true;
				break;
			}
		}
	}
	return result;

}

bool gkGameObject::IsOnHit(bool hover,gkMouse::Buttons button,Ogre::Viewport* subViewPort)
{
	
	gkMouse* mse = gkWindowSystem::getSingleton().getMouse();

	if (!hover)
	{
		if (!mse->isButtonDown(button)) return false;
	}

	Ogre::Ray dest;

	if (subViewPort)
	{
		dest = getRayFromSubViewPort(subViewPort);
	}
	else dest = CameraToViewportRay();
	
	return TestRayHitMe(dest);
}

bool gkGameObject::isMouseHoverNow(Ogre::Viewport* subViewPort)
{
	return IsOnHit(true,gkMouse::Left,subViewPort);
}
bool gkGameObject::isMouseClickNow(gkMouse::Buttons button,Ogre::Viewport* subViewPort)
{
	return IsOnHit(false,button,subViewPort);
}

void gkGameObject::setTexture(Ogre::TexturePtr iconTexture,int index)
{
	if (isInstanced() && !iconTexture.isNull())
	{
		Ogre::Pass* currentPass = getCurrentOgrePass()[0];
		if (currentPass)
		{
			Ogre::TextureUnitState* indexUnit = currentPass->getTextureUnitState(index);
			if (indexUnit)
			{
				indexUnit->setTexture(iconTexture);
			}
		}
	}
}
void gkGameObject::setTexture(gkResourceName textureName,int index)
{
	Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName(textureName.getName(),textureName.getGroup());
	if (!texture.isNull())
	{
		setTexture(texture,index);
	}
}


void gkGameObject::setObjectRenderPriority(int priority)
{
	if (m_node)
	{
		if(m_node->getAttachedObject(0))
		{
			m_node->getAttachedObject(0)->setRenderQueueGroup(priority);
		}
	}
}


gkGameObject * gkGameObject::cloneGameObject(gkString newObjectName)
{
	gkGameObject* newObject = clone(newObjectName);
	Ogre::Texture* pTexture = NULL;
	Ogre::Texture* pStencilTexture = NULL;
	if (!newObject) return NULL; 
	newObject->m_node = m_node->getParentSceneNode()->createChildSceneNode(newObjectName);
	newObject->m_parent = getParent();

	newObject->m_node->setPosition(m_node->getPosition());
	newObject->m_node->setScale(m_node->getScale());
	newObject->m_node->setOrientation(m_node->getOrientation());


	if (newObject)
	{

		Ogre::SceneNode::ObjectIterator iter = this->m_node->getAttachedObjectIterator();
		while(iter.hasMoreElements())
		{
			Ogre::MovableObject * node = iter.getNext();
			Ogre::Entity* entity = static_cast<Ogre::Entity *>(node);
			if (entity)
			{
				Ogre::Entity* cloneEntity = entity->clone(newObjectName);
				newObject->getEntity()->setOgreEntity(cloneEntity);
				//for (unsigned int i = 0; i <entity->getNumSubEntities(); ++i)
				for (int i = (int)entity->getNumSubEntities()-1; i >=0; --i)
				{
					Ogre::SubEntity* subentity = entity->getSubEntity(i);
					if (subentity)
					{
						if (!subentity->getMaterial().isNull())
						{
#if 0
							gkString cloneMaterailName = subentity->getMaterialName();
							cloneMaterailName.append("_clone_");
							//cloneMaterailName.push_back(i);
							
							cloneMaterailName+=newObjectName;
							cloneMaterailName+=newObjectName;
							subentity->getMaterial()->clone(cloneMaterailName);
							cloneEntity->getSubEntity(i)->setMaterialName(cloneMaterailName);
#else
							Ogre::SubEntity* cloneSubentity = NULL;
							for (int j = 0; j<subentity->getSubTextureMap().size();j++)
							{
								pStencilTexture = subentity->getSubTextureMap()[j];
								cloneSubentity = cloneEntity->getSubEntity(i);
								if(cloneSubentity->getSubTextureMap().size() <= j)
								{
									if(pStencilTexture)
									{
										pTexture = pStencilTexture->getEmptyTexture(pStencilTexture->getName());
										pTexture->setGLID(pStencilTexture->getGLID());
										pTexture->setCloneFlag();
									}
									cloneSubentity->getSubTextureMap().insert(std::pair<int, Ogre::Texture *>(j,pTexture));
									cloneSubentity->setGLTextureID(j,subentity->getGLTextureID());
									cloneSubentity->setCustomParameter(subentity->getCustomParameter());
									cloneSubentity->setMaterialIndex(subentity->getMaterialIndex());
									cloneSubentity->setRenderPriority(subentity->getRenderPriority());
									pTexture = NULL;
								}
								else
									cloneSubentity->getSubTextureMap()[j]->setGLID(subentity->getSubTextureMap()[j]->getGLID());
							}
#endif
						}
					}
				}
				newObject->m_node->attachObject(cloneEntity);
			}
		}
	}
	newObject->m_instanceState = 2;
	return newObject;
}

gkTransformState gkGameObject::getLastTransformState()
{
	//setSubEntityVisible(0,true);
	return m_lastTransformState;
}

unsigned int gkGameObject::getSubEntitiesNum()
{
	Ogre::MovableObject * node =  m_node->getAttachedObjectIterator().getNext();
	Ogre::Entity* entity = static_cast<Ogre::Entity *>(node);

	return entity->getNumSubEntities();
}

void gkGameObject::setSubEntityVisible(unsigned int sEntityIndex,bool v)
{
	if(sEntityIndex >= getSubEntitiesNum())
	{ 
		return;
	}
	Ogre::MovableObject * node =  m_node->getAttachedObjectIterator().getNext();
	Ogre::Entity* entity = static_cast<Ogre::Entity *>(node);

	Ogre::SubEntity* pSubEntity = entity->getSubEntity(sEntityIndex);
	pSubEntity->setVisible(v);
}

gkMatrix4 gkGameObject::getParentInvTransform(gkTransformState& state)
{
	gkMatrix4& invmat = m_baseProps.m_transform.invMatrix;
	gkMatrix4 ori;
	gkVector3 loc = m_node->getPosition();
	gkVector3 scl = m_node->getScale();
	gkQuaternion rot = m_node->getOrientation();
	if(state.loc_enable)
		loc = state.loc;
	if(state.rot_enable)
		rot = state.rot;
	if(state.scl_enable)
		scl = state.scl;
	ori.makeTransform(loc,scl,rot);
	gkMatrix4 transed = invmat * ori;
	return transed;


}
void gkGameObject::applyTransformState(const gkTransformState& newstate, const gkScalar& weight,bool fromAnimationChannel)
{
	if (isImmovable())
		return;

	if (m_node)
	{
		m_lastTransformState = newstate;
		gkTransformState state = newstate;
		
		if (weight < 1.f)
		{
			const gkTransformState& cur = getTransformState();
	
			// blend poses
			state.loc = gkMathUtils::interp(newstate.loc, cur.loc, weight);
			state.rot = gkMathUtils::interp(newstate.rot, cur.rot, weight);
			state.rot.normalise();
			state.scl = gkMathUtils::interp(newstate.scl, cur.scl, weight);
	
		}
		if(fromAnimationChannel && hasParent())
		{
			gkMatrix4 transed = getParentInvTransform(state);
			gkMathUtils::extractTransform(transed,state.loc,state.rot,state.scl);
		}

		
		//set value when enabled    zy
		if(state.loc_enable)
			m_node->setPosition(state.loc);
		if(state.rot_enable)
			m_node->setOrientation(state.rot);
		if(state.scl_enable)
			m_node->setScale(state.scl);

		Ogre::Pass* pass = this->getCurrentOgrePass().size() >0 ?this->getCurrentOgrePass()[0]:NULL ;
		Ogre::TextureUnitState* otus;

		static int frame = 0;
		if(state.image_frame_enable && frame == 0)
		{
			frame = state.image_frame;
			
			if(pass)
			{
				int texNum = pass->getNumTextureUnitStates();
				if(texNum >=1)
				{
					otus = pass->getTextureUnitState(0);
					Ogre::String* anime = new Ogre::String[frame];
					anime[0] = otus->getFrameTextureName(0);
					int pos = anime[0].find('1');

					for(int i = 0; i< frame; i++)
					{
						char str[5];
						//itoa( i + 1, str, 10 );
						sprintf(str, "%d", i+1);
						anime[ i ] = anime[ 0 ]. replace(pos,1,1,str[0]);
					}
					otus->setAnimatedTextureName(anime, frame, frame*0.2);
					delete[] anime;
				}			
			}
		}
		if(!state.image_frame_enable)
		{
			if(frame)
			{
				otus = pass->getTextureUnitState(0);
				otus->setAnimatedTextureName(NULL,0,0);
			}
			frame = 0;
		}

		if(state.texture0_offset_enable)
		{
			if(pass)
			{
				int texNum = pass->getNumTextureUnitStates();
				if(texNum >=1)
				{
					otus = pass->getTextureUnitState(0);
					otus->setTextureScroll(state.texture0_offset.x, state.texture0_offset.y);
				}

				if (gkEntity * tempThis = dynamic_cast<gkEntity*>(this))
				{
					Vector4 tempValue(1.0,1.0,state.texture0_offset.x, state.texture0_offset.y);

					tempThis->setTextureMatrix(0,tempValue);
				}

			}
		}

		if(state.texture1_offset_enable)
		{
			if(pass)
			{
				int texNum = pass->getNumTextureUnitStates();
				if(texNum >=1)
				{
					otus = pass->getTextureUnitState(1);
					otus->setTextureScroll(state.texture1_offset.x+0.33, state.texture1_offset.y);
				}

				if (gkEntity * tempThis = dynamic_cast<gkEntity*>(this))
				{
					Vector4 tempValue(0.0,0.0,state.texture1_offset.x, state.texture1_offset.y);
					tempThis->setTextureMatrix(1,tempValue,2);
					tempThis->setTextureMatrix(1,tempValue,3);
				}
			}
		}

		if(state.texture0_alphaFactor_enable)
		{
			//float c[] = {1,1,1,state.texture0_alphaFactor};
			//setGpuParameter("textureColorAdjust",c,1);
			float factor = state.texture0_alphaFactor;
			
			//float c[] = {factor,factor,factor,1.0};
			//setGpuParameter("textureColorAdjust",c,1);
			if (gkEntity * tempThis = dynamic_cast<gkEntity*>(this))
			{
				Vector4 tempValue(1.0,1.0,1.0,factor);
				tempThis->setTextureDiffuseColor(0,tempValue);
			}
		}



		if(state.texture1_alphaFactor_enable)
		{

		}

		if(state.texture0_diffuseColorFactor_enable)
		{
			float factor = state.texture0_diffuseColorFactor;
			float c[] = {factor,factor,factor,1.0};
			setGpuParameter("textureColorAdjust",c,1);
			/*if (gkEntity * tempThis = dynamic_cast<gkEntity*>(this))
			{
				Vector4 tempValue(factor,factor,factor,1.0);
				tempThis->setTextureDiffuseColor(0,tempValue);
			}*/

		}

		if(state.texture1_diffuseColorFactor_enable)
		{
			float factor = state.texture1_diffuseColorFactor;
			float c[] = {factor,factor,factor,state.texture0_alphaFactor};
			setGpuParameter("textureColorAdjust1",c,1);
		}

		//set alpha  & diffuse color          zy
		if(state.diffuse_color_enable)
		{

			this->getEntity()->getMesh()->getFirstMaterial().m_diffuse.r = state.diffuse_color.x;
			this->getEntity()->getMesh()->getFirstMaterial().m_diffuse.g = state.diffuse_color.y;
			this->getEntity()->getMesh()->getFirstMaterial().m_diffuse.b = state.diffuse_color.z;
			this->getEntity()->getMesh()->getFirstMaterial().m_diffuse.a = 0;
			if(pass)

			{
				pass->setDiffuse(this->getEntity()->getMesh()->getFirstMaterial().m_diffuse);
			}
		}

		if(state.alpha_enable)
		{
			if(this->getEntity())
			{
				this->getEntity()->getMesh()->getFirstMaterial().m_alpha = state.alpha;
				this->getEntity()->getMesh()->getFirstMaterial().m_mode |= gkMaterialProperties::MA_ALPHABLEND;
				
			}
			if(pass)
			{
				pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
				pass->setAlphaRejectSettings(Ogre::CMPF_GREATER_EQUAL, 0);
				pass->setDepthWriteEnabled(false);
				int texNum = pass->getNumTextureUnitStates();
				if(texNum >=1)
				{
					otus = pass->getTextureUnitState(texNum-1);
					otus->setAlphaOperation(Ogre::LBX_MODULATE,Ogre::LBS_MANUAL,Ogre::LBS_TEXTURE,state.alpha);
					if(this->getName() == "Rectangle4")
						printf("alpha = %f\n",state.alpha);
				}			
			}		
		}


	//	m_node->needUpdate(true);
#ifdef OGREKIT_USE_PHYSICS
		if (m_rigidBody)
		{
			m_rigidBody->setTransformState(state);
		}
		else if (m_character)
		{
			m_character->setTransformState(state);
		}
		else if (m_ghost){
			m_ghost->setTransformState(state);
		}
#endif
	}
}



void gkGameObject::setTransform(const gkMatrix4& v)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		gkTransformState st;
		gkMathUtils::extractTransform(v, st.loc, st.rot, st.scl);
		st.loc_enable = true;
		st.rot_enable = true;
		st.scl_enable = true;
		applyTransformState(st);
		notifyUpdate();
	}
}



void gkGameObject::setTransform(const gkTransformState& v)
{
	if (isImmovable())
		return;

	gkTransformState st  = v;
	st.loc_enable = true;
	st.rot_enable = true;
	st.scl_enable = true;
	applyTransformState(st);
	notifyUpdate();
}




void gkGameObject::setPosition(const gkVector3& v)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		m_node->setPosition(v);
		notifyUpdate();
#ifdef OGREKIT_USE_PHYSICS
		// update the rigid body state
		if (m_rigidBody != 0)
		{
			m_rigidBody->updateTransform();
		}
		else if (m_character)
		{
			m_character->updateTransform();
		}
		else if (m_ghost) {
			m_ghost->updateTransform();
		}
#endif
	}
}



void gkGameObject::setScale(const gkVector3& v)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		m_node->setScale(v);
		notifyUpdate();
	}
}




void gkGameObject::setOrientation(const gkQuaternion& q)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		m_node->setOrientation(q);
		notifyUpdate();
#ifdef OGREKIT_USE_PHYSICS
		// update the rigid body state
		if (m_rigidBody != 0)
		{
			m_rigidBody->updateTransform();
		}
		else if (m_character)
		{
			m_character->updateTransform();
		} else if (m_ghost) {
			m_ghost->updateTransform();
		}
#endif
	}
}



void gkGameObject::setOrientation(const gkEuler& v)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		gkQuaternion q = v.toQuaternion();
		m_node->setOrientation(q);
		notifyUpdate();
#ifdef OGREKIT_USE_PHYSICS
		// update the rigid body state
		if (m_rigidBody != 0)
		{
			m_rigidBody->updateTransform();
		}
		else if (m_character)
		{
			m_character->updateTransform();
		}
		else if (m_ghost)
		{
			m_ghost->updateTransform();
		}
#endif
	}
}



void gkGameObject::rotate(const gkEuler& drot, int tspace)
{
	if (isImmovable())
		return;

	// convert to quaternion and rotate normally
	rotate(drot.toQuaternion(), tspace);
}



void gkGameObject::rotate(const gkQuaternion& dq, int tspace)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		m_node->rotate(dq, (Ogre::Node::TransformSpace)tspace);
		notifyUpdate();
#ifdef OGREKIT_USE_PHYSICS
		// update the rigid body state
		if (m_rigidBody != 0)
		{
			m_rigidBody->updateTransform();
		}
		else if (m_character)
		{
			m_character->updateTransform();
		}
		else if (m_ghost)
		{
			m_ghost->updateTransform();
		}
#endif
	}
}



void gkGameObject::yaw(const gkRadian& v, int tspace)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		m_node->yaw(v, (Ogre::Node::TransformSpace)tspace);
		notifyUpdate();
#ifdef OGREKIT_USE_PHYSICS
		// update the rigid body state
		if (m_rigidBody != 0)
		{
			m_rigidBody->updateTransform();
		}
		else if (m_character)
		{
			m_character->updateTransform();
		}
		else if (m_ghost)
		{
			m_ghost->updateTransform();
		}
#endif
	}
}



void gkGameObject::pitch(const gkRadian& v, int tspace )
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		m_node->pitch(v, (Ogre::Node::TransformSpace)tspace);
		notifyUpdate();
#ifdef OGREKIT_USE_PHYSICS
		// update the rigid body state
		if (m_rigidBody != 0)
		{
			m_rigidBody->updateTransform();
		}
		else if (m_character)
		{
			m_character->updateTransform();
		}
		else if (m_ghost)
		{
			m_ghost->updateTransform();
		}
#endif
	}
}



void gkGameObject::roll(const gkRadian& v, int tspace)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		m_node->roll(v, (Ogre::Node::TransformSpace)tspace);
		notifyUpdate();
#ifdef OGREKIT_USE_PHYSICS
		// update the rigid body state
		if (m_rigidBody != 0)
		{
			m_rigidBody->updateTransform();
		}
		else if (m_character)
		{
			m_character->updateTransform();
		}
		else if (m_ghost)
		{
			m_ghost->updateTransform();
		}
#endif
	}
}



void gkGameObject::translate(const gkVector3& dloc, int tspace)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		m_node->translate(dloc, (Ogre::Node::TransformSpace)tspace);
		notifyUpdate();
#ifdef OGREKIT_USE_PHYSICS
		// update the rigid body state
		if (m_rigidBody != 0)
		{
			m_rigidBody->updateTransform();
		}
		else if (m_character)
		{
			m_character->updateTransform();
		}
		else if (m_ghost)
		{
			m_ghost->updateTransform();
		}
#endif
	}
}



void gkGameObject::scale(const gkVector3& dscale)
{
	if (isImmovable())
		return;

	if (m_node != 0)
	{
		m_node->scale(dscale);
		notifyUpdate();
	}
}



void gkGameObject::setLinearVelocity(const gkVector3& v, int tspace)
{
	if (isImmovable())
		return;
#ifdef OGREKIT_USE_PHYSICS
	if (m_rigidBody != 0)
	{
		m_rigidBody->setLinearVelocity(v, tspace);
	}
	else if (m_character)
	{
		m_character->setVelocity(m_node->getOrientation() * v, gkEngine::getStepRate());

	}
#endif
//	else if (m_ghost)
//	{
//		m_ghost->updateTransform();
//	}
}



void gkGameObject::setAngularVelocity(const gkVector3& v, int tspace)
{
	if (isImmovable())
		return;
#ifdef OGREKIT_USE_PHYSICS
	if (m_rigidBody != 0)
		m_rigidBody->setAngularVelocity(v, tspace);
#endif
}



void gkGameObject::applyTorque(const gkVector3& v, int tspace)
{
	if (isImmovable())
		return;
#ifdef OGREKIT_USE_PHYSICS
	if (m_rigidBody != 0)
		m_rigidBody->applyTorque(v, tspace);
#endif
}



void gkGameObject::applyForce(const gkVector3& v, int tspace)
{
	if (isImmovable())
		return;
#ifdef OGREKIT_USE_PHYSICS
	if (m_rigidBody != 0)
		m_rigidBody->applyForce(v, tspace);
#endif
}



gkVector3 gkGameObject::getLinearVelocity(void)
{
	if (isImmovable())
		return gkVector3::ZERO;
#ifdef OGREKIT_USE_PHYSICS
	if (m_rigidBody != 0)
		return m_rigidBody->getLinearVelocity();
#endif
	return gkVector3::ZERO;
}




gkVector3 gkGameObject::getAngularVelocity()
{
	if (isImmovable())
		return gkVector3::ZERO;
#ifdef OGREKIT_USE_PHYSICS
	if (m_rigidBody != 0)
		return m_rigidBody->getAngularVelocity();
#endif
	return gkVector3::ZERO;
}




void gkGameObject::clearVariables(void)
{

	// Destroy all variables.
	gkEngine& eng = gkEngine::getSingleton();
	utHashTableIterator<VariableMap> iter(m_variables);


	while (iter.hasMoreElements())
	{
		gkVariable* v = iter.getNext().second;


		// remove from debug list
		if (v->isDebug())
			eng.removeDebugProperty(v);

		delete v;
	}

	m_variables.clear();
}




gkVariable* gkGameObject::createVariable(const gkString& name, bool debug)
{
	gkHashedString findName(name);


	UTsize pos = m_variables.find(findName);
	if (pos != UT_NPOS)
	{
		gkPrintf("Duplicate property found");
		return 0;
	}


	gkVariable* prop = new gkVariable(name, debug);
	m_variables.insert(findName, prop);


	// add to the debugging interface
	if (debug)
		gkEngine::getSingleton().addDebugProperty(prop);

	return prop;
}



gkVariable* gkGameObject::getVariable(const gkString& name)
{

	UTsize pos = m_variables.find(name);
	if (pos != UT_NPOS)
		return m_variables.at(pos);

	return 0;
}



bool gkGameObject::hasVariable(const gkString& name)
{
	return m_variables.find(name) != UT_NPOS;
}

void gkGameObject::removeVariable(const gkString& name)
{
       gkVariable* v;
       gkEngine& eng = gkEngine::getSingleton();
       UTsize pos = m_variables.find(name);
       if (pos != UT_NPOS) 
       {
            v = m_variables.at(pos);
            // remove from debug list
            if (v->isDebug())
                    eng.removeDebugProperty(v);
            m_variables.remove(name);
       }
}


gkGameObject* gkGameObject::getParent(void)         
{
	if(!m_parent) 
		return NULL;
	if(!m_parent->isInstanced()) 
		m_parent->createInstance(false);
	return m_parent;
}

void gkGameObject::setParent(gkGameObject* par)
{
	if (!isInstanced() || isBeingCreated() || (par && (!par->isInstanced() || par->isBeingCreated())))
		return;

	if (par && par != this)
	{
		GK_ASSERT(!m_parent && "Already has a parent");
		par->addChild(this);
	}
}


void gkGameObject::setParentInPlace(gkGameObject* par)
{
	if (par && par != this)
	{
		GK_ASSERT(!m_parent && "Already has a parent");

		gkMatrix4 trans =  par->getWorldTransform().inverse() * getWorldTransform();

		setParent(par);
		setTransform(trans);
	}
}



void gkGameObject::clearParent()
{
	if (!isInstanced() || isBeingCreated())
		return;

	if (m_parent)
	{
		m_parent->removeChild(this);
	}
}


void gkGameObject::clearParentInPlace()
{
	if (m_parent)
	{
		gkMatrix4 trans =  m_parent->getWorldTransform() * getTransform();

		clearParent();
		setTransform(trans);
	}
}


void gkGameObject::addChild(gkGameObject* gobj)
{
	if (!isInstanced() || isBeingCreated() || (gobj && (!gobj->isInstanced() || gobj->isBeingCreated())))
		return;

	if (gobj && gobj != this)
	{
		GK_ASSERT(!gobj->m_parent && "Already has a parent");
		GK_ASSERT(!hasChild(gobj)  && "Already has this child");

		m_children.push_back(gobj);
		gobj->m_parent = this;


		/*
		Ogre::Node * fatherNode = getNode();
		Ogre::Matrix4 fatherMatrix = fatherNode->_getFullTransform();
		Ogre::Node * childNode = gobj->getNode();
		Ogre::Matrix4 childMatrix = childNode->_getFullTransform();
		childMatrix = fatherMatrix.inverse() * childMatrix;
		childNode->setOrientation(childMatrix.extractQuaternion());
		childNode->setPosition(childMatrix.getTrans());	         
		Ogre::Vector3 ov3 = childNode->getPosition();
		gobj->setTransform(childMatrix);
		gkVector3 gkv = gobj->getPosition();
		*/
		



		if (!gobj->isInstanced())
			gobj->createInstance();
#ifdef OGREKIT_USE_PHYSICS
		// Suspend child updates.
		gkPhysicsController* cont = gobj->getPhysicsController();
		if (cont)
			cont->suspend(true);
#endif
		Ogre::SceneNode* node = gobj->getNode();
		if (node->getParentSceneNode())
			node->getParentSceneNode()->removeChild(node);

		m_node->addChild(gobj->getNode());
	}
}



void gkGameObject::removeChild(gkGameObject* gobj)
{
	if (!isInstanced() || isBeingCreated() || (gobj && (!gobj->isInstanced() || gobj->isBeingCreated())))
		return;

	if (gobj &&  gobj != this && hasChild(gobj))
	{
		GK_ASSERT(gobj->m_parent         && "Missing parent");
		GK_ASSERT(gobj->m_parent == this && "Parent mismatch");

		gobj->m_parent = 0;
		m_children.erase(gobj);


		// place in parent ogre node
		Ogre::SceneNode* node = gobj->getNode();
		GK_ASSERT(node->getParentSceneNode() == m_node && "Parent mismatch");

		m_node->removeChild(node);



		Ogre::SceneNode* pNode = m_node->getParentSceneNode();
		if (pNode)
			pNode->addChild(node);
		else
			m_scene->getManager()->getRootSceneNode()->addChild(node);

		// Re-enable physics
#ifdef OGREKIT_USE_PHYSICS
		gkPhysicsController* cont = gobj->getPhysicsController();
		if (cont)
		{
			cont->suspend(false);
			cont->updateTransform();
		}
#endif
	}
}



bool gkGameObject::hasChild(gkGameObject* gobj)
{
	return m_children.find(gobj) != UT_NPOS;
}



#ifdef OGREKIT_USE_PHYSICS
gkPhysicsController* gkGameObject::getPhysicsController()
{

	if (m_rigidBody)
		return m_rigidBody;
	else if (m_character)
		return m_character;
	else if (m_ghost)
		return m_ghost;
	else
		return 0;
}
#endif


#ifdef OGREKIT_USE_PHYSICS
btCollisionObject* gkGameObject::getCollisionObject()
{

	if (m_rigidBody)
		return m_rigidBody->getCollisionObject();
	else if (m_character)
		return m_character->getCollisionObject();
	else if (m_ghost)
		return m_ghost->getCollisionObject();
	else
		return 0;
}
#endif


Ogre::AxisAlignedBox gkGameObject::getAabb() const
{
	return m_node->_getWorldAABB();
}




gkGameObject* gkGameObject::getChildEntity()
{
	gkGameObjectArray::Iterator iter = m_children.iterator();
	while (iter.hasMoreElements())
	{
		gkGameObject* pChild = iter.getNext();

		if (pChild->m_type == GK_ENTITY)
		{
			return pChild;
		}
		else if (pChild->m_type == GK_SKELETON)
		{
			return pChild->getChildEntity();
		}
	}

	return 0;
}


void gkGameObject::sendNotification(const Notifier::Event& e)
{
	if (!m_events.empty())
	{
		Notifications::Iterator it = m_events.iterator();
		while (it.hasMoreElements())
			it.getNext()->notifyGameObjectEvent(this, e);
	}
}

void gkGameObject::notifyResourceDestroying(void)
{
	sendNotification(Notifier::DESTROYING);
}


void gkGameObject::addEventListener(gkGameObject::Notifier* evt)
{
	GK_ASSERT(evt);
	if (evt) m_events.push_back(evt);
}

void gkGameObject::removeEventListener(gkGameObject::Notifier* evt)
{
	GK_ASSERT(evt);
	if (evt) m_events.erase(evt);
}

void gkGameObject::getAnimationNames(utArray<gkHashedString>& names)
{
	Animations::Iterator it = m_actions.iterator();
	while (it.hasMoreElements())
		names.push_back(it.getNext().first);
}


gkAnimationPlayer* gkGameObject::addAnimation(gkAnimation* action, const gkHashedString& name)
{
	if(!m_actionBlender)
		m_actionBlender = new gkAnimationBlender();
	
	gkAnimationPlayer* act;
	if (getAnimationPlayer(name))
		return 0; 

	act = new gkAnimationPlayer(action, this);

	m_actions.insert(name, act);
	return act;
}

gkAnimationPlayer* gkGameObject::addAnimation(const gkHashedString& name)
{
	gkAnimation* res = gkAnimationManager::getSingleton().getAnimation(gkResourceName(name, getGroupName()));
	
	if(!res)
		return 0;
	
	return addAnimation(res, name);
}


gkAnimationPlayer* gkGameObject::getAnimationPlayer(const gkHashedString& name)
{
	size_t pos;
	if ((pos = m_actions.find(name)) == GK_NPOS)
		return 0;

	return m_actions.at(pos);
}

gkAnimationBlender& gkGameObject::getAnimationBlender(void)
{
	GK_ASSERT(m_actionBlender);
	return *m_actionBlender;
}


void gkGameObject::playAnimation(const gkString& act, gkScalar blend, int mode, int priority)
{
	gkAnimationPlayer* gact = getAnimationPlayer(act);
	playAnimation(gact, blend, mode, priority);
}


void gkGameObject::playAnimation(gkAnimationPlayer* act, gkScalar blend, int mode, int priority)
{
	if (act)
	{
		getAnimationBlender().push(act, blend, mode, priority);
		m_scene->pushAnimationUpdate(this);
	}
}

void gkGameObject::stopAnimation(const gkString& act)
{
	gkAnimationPlayer* gact = getAnimationPlayer(act);
	stopAnimation(gact);
}

void gkGameObject::stopAnimation(gkAnimationPlayer* act)
{
	if (act)
	{
		act->setFinished();
		getAnimationBlender().remove(act);
	}
}

void gkGameObject::pauseAnimations(void)
{
	m_scene->removeAnimationUpdate(this);
}

void gkGameObject::resumeAnimations(void)
{
	if (!m_actions.empty())
		m_scene->pushAnimationUpdate(this);
}

///Called by the scene when object is animated
///tick is in second
void gkGameObject::updateAnimationBlender(const gkScalar tick)
{
	GK_ASSERT(hasAnimationBlender());

	getAnimationBlender().evaluate(tick);
}

void gkGameObject::changeState(int v)
{
	int old = getState();
	if (old == v) return;

	setState(v);
	if (m_bricks)
	{
		m_bricks->setState(v);

		m_bricks->notifyState();
		gkLogicManager::getSingleton().notifyState(v, m_bricks);
	}
}

gkVector2 gkGameObject::GetMousePosition()
{
	gkMouse* mse = gkWindowSystem::getSingleton().getMouse();
	//gkPrintf("press mouse x = %f y= %f \n",mse->position.x,mse->position.y );
	gkScalar ncx = mse->position.x / mse->winsize.x;
	gkScalar ncy = mse->position.y / mse->winsize.y;
	return gkVector2(ncx,ncy);
}

gkVector2 gkGameObject::getSubViewPortMousePosition(Ogre::Viewport* subViewPort)
{
	gkMouse* mse = gkWindowSystem::getSingleton().getMouse();
	//gkPrintf("press mouse x = %f y= %f \n",mse->position.x,mse->position.y );
	if (subViewPort)
	{
		int subViewPortTop = subViewPort->getActualTop();
		int subViewPortLeft = subViewPort->getActualLeft();

		gkScalar mousePostion_X = mse->position.x - subViewPortLeft >= 0 ?( mse->position.x - subViewPortLeft): 0;
		gkScalar mousePostion_Y = mse->position.y - subViewPortTop >= 0 ?( mse->position.x - subViewPortTop): 0;
		gkScalar ncx =  mousePostion_X / subViewPort->getActualHeight();
	    gkScalar ncy =	mousePostion_Y / subViewPort->getActualWidth();
		gkVector2(ncx,ncy);
	}
	return gkVector2(0,0); 
}

gkRay gkGameObject::getRayFromSubViewPort(Ogre::Viewport* subViewPort)
{
	if (subViewPort)
	{
		Ogre::Camera * oc = subViewPort->getCamera();
		gkVector2 OgreMousePosition = getSubViewPortMousePosition(subViewPort);

		//printf("Mouse Position x = %f y =%f \n",OgreMousePosition.x,OgreMousePosition.y);

		Ogre::Ray dest;
		if(oc) oc->getCameraToViewportRay(OgreMousePosition.x, OgreMousePosition.y, &dest);
		return dest;
	}
	return gkRay();
}

void gkGameObject::removeAnmPlayer(gkAnimationPlayer* pPlayer)
{
	getAnimationBlender().remove(pPlayer);
}