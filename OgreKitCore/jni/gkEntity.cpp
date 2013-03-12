/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

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
#include "OgreSceneManager.h"
#include "OgreEntity.h"
#include "gkEntity.h"
#include "gkScene.h"
#include "gkEngine.h"
#include "gkUserDefs.h"
#include "gkSkeleton.h"
#include "gkMesh.h"



gkEntity::gkEntity(gkInstancedManager* creator, const gkResourceName& name, const gkResourceHandle& handle)
	:    gkGameObject(creator, name, handle, GK_ENTITY),
	     m_entityProps(new gkEntityProperties()),
	     m_entity(0),
	     m_skeleton(0)
{
	
}




gkEntity::~gkEntity()
{
	delete m_entityProps;
}



void gkEntity::createInstanceImpl(void)
{
	//FUNCTION_PROFILE;

	gkGameObject::createInstanceImpl();

	GK_ASSERT(!m_entity);

 	if (!m_entityProps->m_mesh)
 		return;
 
 	if (m_skeleton)
 		m_skeleton->createInstance();
 
 	Ogre::SceneManager* manager = m_scene->getManager();
 	m_entity = manager->createEntity(m_name.getName(), m_entityProps->m_mesh->getResourceName().getName(), 
 		m_name.getGroup().empty() ? Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME : m_name.getGroup());
 
 	m_entity->setCastShadows(m_entityProps->m_casts);
 	m_node->attachObject(m_entity);
 
	if (m_entity)
	{
		addGpuParameter(m_entity);
	}

 	if (m_skeleton)
 		m_skeleton->updateFromController();
 

 	if (!m_entityProps->m_startPose.empty())
 		_resetPose();
	

 	if (m_baseProps.isInvisible())
 		m_node->setVisible(false, false);

	gkMesh * temp =getMesh();
	gkMesh::SubMeshIterator iter = temp->getSubMeshIterator();
	int i =0;
	while (iter.hasMoreElements())
	{
		gkSubMesh* sme = iter.getNext();
		if (sme)
		{
			m_entity->getSubEntity(i)->setMaterialIndex(sme->getMaterialIndex());
			m_entity->getSubEntity(i)->setRenderPriority(sme->getMaterialIndex()*10);
		}
		++i;
	}
}




void gkEntity::destroyInstanceImpl(void)
{
	if (m_entity)
	{

		Ogre::SceneManager* manager = m_scene->getManager();

		if (!m_entityProps->m_startPose.empty())
			_resetPose();

		if (!m_scene->isBeingDestroyed())
		{
			if (m_node)
				m_node->detachObject(m_entity);

			manager->destroyEntity(m_entity);
		}
	}

	m_entity = 0;


	gkGameObject::destroyInstanceImpl();
}


void gkEntity::setSkeleton(gkSkeleton* skel)
{
	if (m_skeleton == 0)
	{
		m_skeleton = skel;
		if (m_skeleton)
			m_skeleton->setController(this);
	}
}



void gkEntity::_destroyAsStaticGeometry(void)
{
	if (m_entity != 0)
	{
		Ogre::SceneManager* manager = m_scene->getManager();

		if (!m_entityProps->m_startPose.empty())
			_resetPose();

		if (m_node)
			m_node->detachObject(m_entity);

		manager->destroyEntity(m_entity);

		m_entity = 0;
	}
}


gkGameObject* gkEntity::clone(const gkString& name)
{
	gkEntity* cl = new gkEntity(getInstanceCreator(), name, -1);

	*cl->m_entityProps = *m_entityProps;

	gkGameObject::cloneImpl(cl);
	return cl;
}




void gkEntity::_resetPose(void)
{
	if (m_skeleton)
	{
		if (!m_entityProps->m_startPose.empty())
		{
			gkAnimationPlayer* act = getAnimationPlayer(m_entityProps->m_startPose);
			
			if(!act)
				act = addAnimation(m_entityProps->m_startPose);
			
			if (act)
			{
				act->setTimePosition(0);
				act->evaluate(0.0f);
			}
		}
	}
}



gkBoundingBox gkEntity::getAabb() const
{
	return m_entityProps->m_mesh ? m_entityProps->m_mesh->getBoundingBox() : gkGameObject::getAabb();
}


void gkEntity::addGpuParameter(Ogre::Entity * objectEntity)
{
	Ogre::Vector4 val(1.0f,1.0f,1.0f,1.0f);	
	if (objectEntity)
	{
		for (int i =0 ; i< objectEntity->getNumSubEntities(); ++i)
		{
			Ogre::SubEntity *subEntity = objectEntity->getSubEntity(i);
			for (int j =1; j < SP_COUNT ; ++j)
			{
				subEntity->setCustomParameter(j,val);
			}
			gkSubMesh* gks = getSubMesh(i);
			int TextureCount = gks->getMaterial().m_totaltex;
			for (int index =0 ; index < TextureCount; ++index)
			{
				gkString texuture = gks->getMaterial().m_textures[index].m_image;
				Ogre::TexturePtr textureRes = Ogre::TextureManager::getSingleton().load(texuture,"");
				subEntity->getSubTextureMap().insert(std::pair<int, Ogre::Texture *>(index,textureRes.getPointer()));
				subEntity->setGLTextureID(index,textureRes.getPointer()->getGLID());
			}
		
			subEntity->setCustomParameter(SP_DIFFUSE,Ogre::Vector4(gks->getMaterial().m_diffuse.ptr()));
			subEntity->setCustomParameter(SP_TEXTURE_COUNT,val *TextureCount);
			Ogre::Vector3 scl = gks->getMaterial().m_textures[0].m_Transform.scl;
			Ogre::Vector3 loc = gks->getMaterial().m_textures[0].m_Transform.loc;
			subEntity->setCustomParameter(SP_TEXTURE_MATRIX0,Ogre::Vector4(scl.x,scl.y,0.5-scl.x/2+loc.x,loc.y));
			scl = gks->getMaterial().m_textures[1].m_Transform.scl;
			loc = gks->getMaterial().m_textures[1].m_Transform.loc;
			subEntity->setCustomParameter(SP_TEXTURE_MATRIX1,Ogre::Vector4(scl.x,scl.y,0.5-scl.x/2+loc.x,loc.y));

			subEntity->setCustomParameter(SP_ALPHA,Ogre::Vector4(gks->getMaterial().m_alpha));
			if(TextureCount)
			{
				float alpha = gks->getMaterial().m_textures[0].m_diffuseAlpahFactor;
				float red = gks->getMaterial().m_textures[0].m_color.r;
				float green = gks->getMaterial().m_textures[0].m_color.g;
				float blue = gks->getMaterial().m_textures[0].m_color.b;
				subEntity->setCustomParameter(SP_TEXTURE_COLOR,Ogre::Vector4(red,green,blue,alpha));
			}
		}
	}
}

gkSubMesh * gkEntity::getSubMesh(int index)
{
	gkMesh * entityMesh = getMesh();
	int indexCount = 0;
	gkSubMesh * returnMesh = NULL;
	if (entityMesh)
	{
		gkMesh::SubMeshIterator subMeshIer = entityMesh->getSubMeshIterator();
		while(subMeshIer.hasMoreElements())
		{
			gkSubMesh* subMesh =subMeshIer.getNext();
			if (subMesh && indexCount == index)
			{
				returnMesh = subMesh;
				break;
			}
			indexCount ++;
		}
	}
	return returnMesh;
}

//int gkEntity::getSEntityIndexByMatIndex(int materialIndex)
//{
//	return getEntity()->getSEntityIndexByMatIndex(materialIndex);
//}

void gkEntity::setAlpha(float alpha)
{
	Ogre::Entity * objectEntity = getEntity();
	for (int i =0 ; i< objectEntity->getNumSubEntities(); ++i)
	{
		Ogre::SubEntity *subEntity = objectEntity->getSubEntity(i);
		//for (int j =1; j < SP_COUNT ; ++j)
		//{
			subEntity->setCustomParameter(SP_LAST_LAYER_COLOR,Ogre::Vector4(alpha));
		//}
	}
}

void gkEntity::setTextureMatrix(int index,Ogre::Vector4 textureMatrix,unsigned int texIndex)
{
	Ogre::Entity * objectEntity = getEntity();
	for (int i =0 ; i< objectEntity->getNumSubEntities(); ++i)
	{
		Ogre::SubEntity *subEntity = objectEntity->getSubEntity(i);
		if(texIndex == 2)
		{
			Ogre::Vector4 pre = subEntity->getCustomParameter(SP_TEXTURE_MATRIX0+index);
			textureMatrix.z = 0.5-pre.x/2+textureMatrix.z;
		}
		//for (int j =1; j < SP_COUNT ; ++j)
		//{
			switch(index)
			{
			case 0:
	            subEntity->setCustomParameter(SP_TEXTURE_MATRIX0,textureMatrix,texIndex);
				break;
			case 1:
				subEntity->setCustomParameter(SP_TEXTURE_MATRIX1,textureMatrix,texIndex);
				break;
			default:
				break;
			}
			
		//}
	}

}
void gkEntity::setTextureColor(int index,Ogre::Vector4 color)
{
	Ogre::Entity * objectEntity = getEntity();
	for (int i =0 ; i< objectEntity->getNumSubEntities(); ++i)
	{
		Ogre::SubEntity *subEntity = objectEntity->getSubEntity(i);
		//for (int j =1; j < SP_COUNT ; ++j)
		//{
			subEntity->setCustomParameter(SP_TEXTURE_COLOR,color);
		//}
	}
}

void gkEntity::setGLTextureID(int bufferID, int textureLayerID,int glID)
{
	Ogre::Entity * objectEntity = getEntity();
	if(!objectEntity)
		return;
	Ogre::SubEntity* subEntity = objectEntity->getSubEntity(bufferID);
	if(!subEntity || subEntity->getSubTextureMap().size() <= textureLayerID)
		return;	
	subEntity->getSubTextureMap()[textureLayerID]->setGLID(glID);
	subEntity->setGLTextureID(textureLayerID,glID);

}

int gkEntity::getGLTextureID(int bufferID, int textureLayerID)
{
	Ogre::Entity * objectEntity = getEntity();
	if(!objectEntity)
		return 0;
	Ogre::SubEntity* subEntity = objectEntity->getSubEntity(bufferID);
	if(!subEntity || subEntity->getSubTextureMap().size() <= textureLayerID)
		return 0;	
	return subEntity->getSubTextureMap()[textureLayerID]->getGLID();
}

void gkEntity::setGLTexture(int bufferID, int textureLayerID,Ogre::Texture* tex)
{
	Ogre::Entity * objectEntity = getEntity();
	if(!objectEntity)
		return;
	Ogre::SubEntity* subEntity = objectEntity->getSubEntity(bufferID);
	if(!subEntity || subEntity->getSubTextureMap().size() <= textureLayerID)
		return;	
	subEntity->getSubTextureMap()[textureLayerID] = tex;
}

void gkEntity::setTextureDiffuseColor(int textureLayer, Ogre::Vector4& diffColor,int bufferID)
{
	if(bufferID >= 0)
	{
		getEntity()->getSubEntity(bufferID)->setCustomParameter(SP_TEXTURE_COUNT,diffColor);
		return;
	}

	Ogre::Entity * objectEntity = getEntity();
	for (int i =0 ; i< objectEntity->getNumSubEntities(); ++i)
	{
		Ogre::SubEntity *subEntity = objectEntity->getSubEntity(i);
		subEntity->setCustomParameter(SP_TEXTURE_COLOR,diffColor);
	}
}

Ogre::Texture*  gkEntity::getGLTexture(int bufferID, int textureLayerID)
{
	Ogre::Entity * objectEntity = getEntity();
	if(!objectEntity)
		return 0;
	Ogre::SubEntity* subEntity = objectEntity->getSubEntity(bufferID);
	if(!subEntity || subEntity->getSubTextureMap().size() <= textureLayerID)
		return 0;	
	return subEntity->getSubTextureMap()[textureLayerID];
}