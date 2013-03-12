/***********************************************************************************************************************
/* 版权所有：
/* 功能描述：创建subMesh 
/* 编 写 者：dabao
/* 编写日期：2012/07/10
/* 修改日期：2012/07/10
/* 其    他：无
/**********************************************************************************************************************/
#ifndef _Db_TCL_DbCreateSubMesh_H__ 
#define _Db_TCL_DbCreateSubMesh_H__ 
//*********************************************************************************************************************/
//定义引用库文件
#include "OgreKit.h"
#include "OgreSceneManager.h"
#include "gkMesh.h"
#include "OgreCommon.h"

//*********************************************************************************************************************/
//定义类
namespace tcl
{
	enum MeshType
	{
		Plane,
		Cube
	};

	class DbCreateSubMesh
	{
	public:
		DbCreateSubMesh(gkScene * scene,gkString name,MeshType type):m_Mesh(NULL),m_Parent(NULL),
			m_Scene(scene),m_Name(name),m_MeshType(type)
		{}
	
		void BindEntity(gkEntity * parent)
		{
			if (!m_Mesh)
			{
				m_Mesh = m_Scene->createMesh(m_Name);
				m_SubMesh = CreateSubMesh(GetMeshType());
				gkMaterialProperties & proprMater = m_SubMesh->getMaterial();
				proprMater.m_name = m_Name+"_Materal";
				proprMater.m_mode = gkMaterialProperties::MA_DEPTHWRITE|gkMaterialProperties::MA_TWOSIDE;
				proprMater.m_rblend = GK_BT_MIXTURE;
				m_Mesh->addSubMesh(m_SubMesh);
			}
			if (!m_Parent && parent && m_Mesh)
			{
				if(parent->isInstanced()) return;
				else 
				{
					gkEntityProperties& EntityProperties = parent->getEntityProperties();
					EntityProperties.m_mesh = m_Mesh;
				}	
				m_Parent = parent;
			}
		}

		gkTextureProperties & AddTexture(gkString imageName,bool alphaManal = false)
		{
			gkMaterialProperties & propMateral = m_SubMesh->getMaterial();
			propMateral.m_textures[propMateral.m_totaltex].m_name = imageName;
			propMateral.m_textures[propMateral.m_totaltex].m_image = imageName;
			if (alphaManal)propMateral.m_textures[propMateral.m_totaltex].m_blend = GK_BT_APLHA_MANUAL;		
			++propMateral.m_totaltex;
			m_SubMesh->setTotalLayers(propMateral.m_totaltex);
			return propMateral.m_textures[propMateral.m_totaltex-1];
		}

		void SetTransparent(bool transparent)
		{
			if (transparent)
			{
				gkMaterialProperties & proprMater = m_SubMesh->getMaterial();
				proprMater.m_mode |= gkMaterialProperties::MA_ALPHABLEND;
			}
		}

		void SetTransparent(float alph)
		{
			Ogre::String name = m_SubMesh->getMaterialName().c_str();
			Ogre::ResourcePtr Matarl = Ogre::MaterialManager::getSingletonPtr()->getByName(name,m_Scene->getGroupName().c_str());
			if (!Matarl.isNull())
			{
				Ogre::MaterialPtr Matarel1 = Matarl;
				if (!Matarel1.isNull())
				{
					Ogre::LayerBlendModeEx refMode = Matarel1->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getAlphaBlendMode();
					if (refMode.operation == Ogre::LBX_MODULATE )
					{
						Matarel1->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE,Ogre::LBS_MANUAL,Ogre::LBS_TEXTURE,alph);
					}
				}
			}
		}

		gkEntity * GetParent(){ return m_Parent;}

		MeshType GetMeshType(){ return m_MeshType ;}

	private:
		virtual gkSubMesh *CreateSubMesh(MeshType type) = 0;
		gkSubMesh * m_SubMesh;
		gkMesh * m_Mesh;
		gkScene * m_Scene;
		gkEntity * m_Parent;
		gkString m_Name;
		MeshType m_MeshType;
	};

	class DbCubeMesh : public DbCreateSubMesh
	{
	public:
		DbCubeMesh(gkScene * scene,gkString name):DbCreateSubMesh(scene,name,Cube)
		{}
	private:
		virtual gkSubMesh *CreateSubMesh(MeshType type);
	};

	class DbPlaneMesh : public DbCreateSubMesh
	{
	public:
		DbPlaneMesh(gkScene * scene,gkString name):DbCreateSubMesh(scene,name,Plane)
		{}
	private:
		virtual gkSubMesh *CreateSubMesh(MeshType type);
	};
}
#endif
