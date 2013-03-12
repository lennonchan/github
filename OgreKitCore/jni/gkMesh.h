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
#ifndef _gkMesh_h_
#define _gkMesh_h_

#define GK_UV_MAX 8

#include "gkMathUtils.h"
#include "gkSerialize.h"
#include "gkResource.h"
class btTriangleMesh;
class gkMeshLoader;


class gkDeformVertex
{
public:
	int         group;
	gkScalar    weight;
	int         vertexId;
};



class gkVertex
{
public:
	gkVertex();
	gkVertex(const gkVertex& o);
	gkVertex& operator = (const gkVertex& o);

	gkVector3       co;                 // vertex coordinates
	gkVector3       no;                 // normals
	unsigned int    vcol;               // vertex color
	gkVector2       uv[GK_UV_MAX];      // texture coordinates < GK_UV_MAX
	int             vba;                // Vertex bone assignment
};



struct gkTriangle
{
	enum TriFlag
	{
		TRI_INVISIBLE    = (1 << 0),
		TRI_COLLIDER     = (1 << 1),
	};

	unsigned int i0, i1, i2;
	int flag;
};

struct gkTriFace
{
	gkVector3 p[3];
	unsigned int i[3];

	gkTriFace() { i[0] = i[1] = i[2] = 0; }

	GK_INLINE gkVector3 normal()
	{
		return (p[1]-p[0]).crossProduct(p[2]-p[1]).normalisedCopy();
	}
};


class gkSubMeshIndexer;


class gkSubMesh
{
public:
	typedef utArray<gkTriangle>         Triangles;
	typedef utArray<gkVertex>           Verticies;
	typedef utArray<gkDeformVertex>     DeformVerts;

private:

	Triangles           m_tris;
	Verticies           m_verts;
	int                 m_uvlayers;
	gkBoundingBox       m_bounds;
	bool                m_boundsInit;

	DeformVerts         m_defverts;
	bool                m_hasVertexColors;

	friend class gkSubMeshIndexer;
	gkSubMeshIndexer* m_sort;

	gkMaterialProperties*    m_material;

	//add 
	int m_priority;
	int m_MaterialIndex;

public:

	gkSubMesh();
	~gkSubMesh();

	void setPriority(int Priority){m_priority = Priority;};
	int getPriority(){return m_priority;};
	void setMaterialIndex(int index){m_MaterialIndex = index;};
	int getMaterialIndex(){return m_MaterialIndex;};
	Verticies&          getVertexBuffer(void)               {return m_verts;}
	Triangles&          getIndexBuffer(void)                {return m_tris;}
	DeformVerts&        getDeformVertexBuffer(void)         {return m_defverts;}
	gkString            getMaterialName(void)               {return m_material->m_name.c_str();}
	void                setMaterialName(const gkString& v)  {m_material->m_name = v.c_str();}
	void                setTotalLayers(int v)               {m_uvlayers = v;}
	int                 getUvLayerCount(void)               {return m_uvlayers;}
	void                setVertexColors(bool v)             {m_hasVertexColors = v;}
	bool                hasVertexColors(void)               {return m_hasVertexColors; }


	gkBoundingBox&       getBoundingBox(void);

	gkMaterialProperties& getMaterial(void)                 {return *m_material;}


	gkSubMesh* clone(void);
	void       addTriangle(const gkVertex& v0,
	                       unsigned int i0,
	                       const gkVertex& v1,
	                       unsigned int i1,
	                       const gkVertex& v2,
	                       unsigned int i2, int flag);

	void        addDeformVert(const gkDeformVertex& dv);
};





class gkVertexGroup
{
public:

	gkVertexGroup(const gkString& name, int index) : m_name(name), m_index(index) {}

	const int       getIndex(void)              { return m_index; }
	const gkString& getName(void)               { return m_name; }

private:
	gkString    m_name;
	int         m_index;
};


class gkMesh : public gkResource
{
public:

	typedef utArray<gkSubMesh*>             SubMeshArray;
	typedef utArrayIterator<SubMeshArray>   SubMeshIterator;
	typedef utArray<gkVertexGroup*>         VertexGroups;

private:

	SubMeshArray         m_submeshes;
	gkBoundingBox        m_bounds;
	bool                 m_boundsInit;
	VertexGroups         m_groups;
	#ifdef OGREKIT_USE_BULLET
	btTriangleMesh*      m_triMesh;
	#endif
	gkSkeletonResource*  m_skeleton;
	gkMeshLoader*        m_meshLoader;

	UTsize               m_vertexCount;
	UTsize               m_triFaceCount;

public:

	gkMesh(gkResourceManager* creator, const gkResourceName& name, const gkResourceHandle& handle);
	virtual ~gkMesh();

	void addSubMesh(gkSubMesh* me);
	void _setSkeleton(gkSkeletonResource* res) {m_skeleton = res;}
	gkSkeletonResource* getSkeleton(void)      {return m_skeleton;}


	gkBoundingBox& getBoundingBox(void);

	btTriangleMesh*          getTriMesh(void);
	gkMaterialProperties&    getFirstMaterial(void);

	gkVertexGroup*   createVertexGroup(const gkString& name);
	VertexGroups&    getGroups(void) {return m_groups;}
	gkVertexGroup*   findVertexGroup(const gkString& name);
	gkVertexGroup*   findVertexGroup(int i);

	SubMeshIterator getSubMeshIterator(void) {return SubMeshIterator(m_submeshes);}


	gkMeshLoader* getLoader(void) {return m_meshLoader;}

	UTsize getMeshVertexCount(void);
	const gkVertex& getMeshVertex(UTsize n);

	UTsize getMeshTriFaceCount(void);
	gkTriFace getMeshTriFace(UTsize n);
	
	void reload();
};



// add by dabao 2012.08.06 ---------------------------------------------------------------

#define  TCL_ASSERT(exp) assert(exp)

#define  TCL_CHECK(mode,sign) ( mode.m_mode & sign )  

class gkBlendFileTemplate
{
public:
	gkBlendFileTemplate(gkMaterialProperties * MaterialProp):m_MaterialProp(MaterialProp)
	{}
	virtual ~gkBlendFileTemplate(){}
	virtual const gkMaterialProperties& GetMaterialDescription()  =0;	
protected:
	gkMaterialProperties * m_MaterialProp;
};

class gkBlendFileTemplateImpl : public gkBlendFileTemplate
{
public:
	gkBlendFileTemplateImpl(gkMaterialProperties * MaterialProp):gkBlendFileTemplate(MaterialProp)
	{}
	virtual ~gkBlendFileTemplateImpl(){}
	const gkMaterialProperties& GetMaterialDescription() 
	{
		return *m_MaterialProp;
	}
};

class gkBlendFile2Ogre
{
public:

	static gkBlendFile2Ogre* OgreMaterai;

	gkBlendFile2Ogre(){}
	virtual ~gkBlendFile2Ogre(){}	
	virtual bool ParseFile(gkBlendFileTemplate* BlendTree)
	{
		TCL_ASSERT(BlendTree);
		if (BlendTree)
		{
			ParseBlendMaterail(BlendTree);
			ParseBlendTexuture(BlendTree);
			return true;
		}
		return false;
		
	}
private:	
	virtual void ParseBlendMaterail( gkBlendFileTemplate* BlendTree) = 0;
	virtual void ParseBlendTexuture( gkBlendFileTemplate* BlendTree) = 0;
	// virtual void ParseBlendParticle() = 0;
	// virtual void ParseBlendPhysics() =0;
};

class gkBlendFile2OgreImpl :public gkBlendFile2Ogre
{
public:
	enum SourceFrom
	{
		GK_BT_Current = 0x0, 
		GK_BT_Texture,
		GK_BT_Vertex,
		GK_BT_MANUAL = 0x2, 
		GK_BT_Contant =0x4,
	};

	enum OgreType
	{
		LBX_SOURCE1,
		LBX_SOURCE2,
		LBX_MODULATE,
		LBX_MODULATE_X2,
		LBX_MODULATE_X4,
		LBX_ADD,
		LBX_ADD_SIGNED,
		LBX_ADD_SMOOTH,
		LBX_SUBTRACT,
		LBX_BLEND_DIFFUSE_ALPHA,
		LBX_BLEND_TEXTURE_ALPHA,
		LBX_BLEND_CURRENT_ALPHA,
		LBX_BLEND_MANUAL,
		LBX_DOTPRODUCT,
		LBX_BLEND_DIFFUSE_COLOUR
	};

	struct TextureChannel
	{
		TextureChannel():BlendType(LBX_MODULATE),
			Source0(GK_BT_Current),Source1(GK_BT_Texture){}
		OgreType BlendType;
		SourceFrom Source0;
		SourceFrom Source1;
	};

	struct OgreTexture
	{
		OgreTexture():m_TextureMode(0){}
		gkString TextureName;
		TextureChannel ColorChannel;
		TextureChannel AlphaChannel;
		int m_TextureMode;
		gkColor ConstValue;
	};

	struct Material
	{
		Material():m_UseTexture(0)
		{
			LastLayer.ColorChannel.BlendType = LBX_SOURCE1;
			LastLayer.ColorChannel.Source0 = GK_BT_Current;
			LastLayer.ColorChannel.Source1 = GK_BT_Texture;
			LastLayer.AlphaChannel.BlendType = LBX_MODULATE;
			LastLayer.AlphaChannel.Source0 = GK_BT_Current;
			LastLayer.AlphaChannel.Source1 = GK_BT_Contant;
		}
		gkString m_MaterailName;
		gkColor m_Diffuse;
		gkColor m_Spection;
		gkColor m_Environment;
		gkColor m_Emission;
		//gkColor m_Mirror;
		gkScalar m_Alpha;
		gkScalar m_Hardness;
		int  m_MaterialMode;
		int  m_ShandowMode;
		OgreTexture Textures[5];
		OgreTexture LastLayer;
		int m_UseTexture;
	};

	static utHashTable<gkHashedString,Material> Materials;
	gkBlendFile2OgreImpl():gkBlendFile2Ogre()
	{}

private:
	virtual void ParseBlendMaterail( gkBlendFileTemplate* BlendTree)
	{
		TCL_ASSERT(BlendTree);
		gkBlendFileTemplate *temp = const_cast<gkBlendFileTemplate*>(BlendTree);
		const gkMaterialProperties& MaterailProp = temp->GetMaterialDescription();
		{
			Material SaveMaterail;
			SaveMaterail.m_MaterailName = MaterailProp.m_name;
			SaveMaterail.m_Alpha = MaterailProp.m_alpha;
			SaveMaterail.m_Diffuse = MaterailProp.m_diffuse *(MaterailProp.m_emissive + MaterailProp.m_refraction);
			SaveMaterail.m_Environment = MaterailProp.m_diffuse * MaterailProp.m_ambient;
			SaveMaterail.m_Hardness = MaterailProp.m_hardness;
			SaveMaterail.m_Spection = MaterailProp.m_specular * MaterailProp.m_spec;
			SaveMaterail.m_Emission = MaterailProp.m_diffuse * MaterailProp.m_emissive;
			SaveMaterail.m_MaterialMode = MaterailProp.m_mode;
			Materials.insert(SaveMaterail.m_MaterailName.c_str(),SaveMaterail);
		}
	}
	virtual void ParseBlendTexuture( gkBlendFileTemplate* BlendTree)
	{
		TCL_ASSERT(BlendTree);
		gkBlendFileTemplate *temp = const_cast<gkBlendFileTemplate*>(BlendTree);
		const gkMaterialProperties& MaterailProp = temp->GetMaterialDescription();
		int TextureCount = MaterailProp.m_totaltex;

		for (int i =0 ; i< TextureCount; ++i)
		{
			gkTextureProperties tempProper = MaterailProp.m_textures[i];
			OgreTexture TextureTemp;
			TextureTemp.TextureName = tempProper.m_name;
			if (i == 0)
			{
				TextureTemp.ColorChannel.Source0 = GK_BT_Vertex;
				TextureTemp.ColorChannel.Source1 = GK_BT_Texture;
				TextureTemp.ConstValue = tempProper.m_color;
				TextureTemp.ConstValue.r = TextureTemp.ConstValue.r;
				TextureTemp.ConstValue.g = TextureTemp.ConstValue.g;
				TextureTemp.ConstValue.b = TextureTemp.ConstValue.b;
				TextureTemp.AlphaChannel.Source0 = GK_BT_Vertex;
				TextureTemp.AlphaChannel.Source1 = GK_BT_Texture;
				if (TCL_CHECK(tempProper,gkTextureProperties::TM_COLOR_USE))
				{
					TextureTemp.ColorChannel.Source0 = GK_BT_Texture;
					TextureTemp.ColorChannel.Source1 = GK_BT_Contant;
					TextureTemp.ColorChannel.BlendType = LBX_MODULATE;
				}
				else
				{
					TextureTemp.ColorChannel.BlendType = LBX_SOURCE1;
				}

				if (TCL_CHECK(tempProper,gkTextureProperties::TM_ALPHA_USE))
				{
					TextureTemp.ColorChannel.Source0 = GK_BT_Texture;
					TextureTemp.ColorChannel.Source1 = GK_BT_Contant;
					TextureTemp.ColorChannel.BlendType = LBX_MODULATE;
				}
				else
				{
					TextureTemp.AlphaChannel.Source0 = GK_BT_Vertex;
					TextureTemp.AlphaChannel.BlendType = LBX_SOURCE1;
				}

				if (TCL_CHECK(tempProper,gkTextureProperties::TM_TEXTURE_ALPHA_USE))
				{
					TextureTemp.AlphaChannel.Source0 = GK_BT_Texture;
					TextureTemp.AlphaChannel.Source1 = GK_BT_Contant;
					TextureTemp.AlphaChannel.BlendType = LBX_MODULATE;
					
					TextureTemp.ConstValue.a = TextureTemp.ConstValue.a > 0 ?TextureTemp.ConstValue.a:-TextureTemp.ConstValue.a;
				}
			}
			else 
			{
				TextureTemp.ColorChannel.Source0 = GK_BT_Current;
				TextureTemp.ColorChannel.Source1 = GK_BT_Texture;
                TextureTemp.ConstValue = tempProper.m_color;
				TextureTemp.ConstValue.r = TextureTemp.ConstValue.r;
				TextureTemp.ConstValue.g = TextureTemp.ConstValue.g;
				TextureTemp.ConstValue.b = TextureTemp.ConstValue.b;
				if (TCL_CHECK(tempProper,gkTextureProperties::TM_COLOR_USE))
				{
					TextureTemp.ColorChannel.BlendType = LBX_BLEND_MANUAL;
					TextureTemp.ConstValue.r =1- TextureTemp.ConstValue.r;
				}
				else
				{
					TextureTemp.ColorChannel.BlendType = LBX_SOURCE1;
				}

				if (TCL_CHECK(tempProper, gkTextureProperties::TM_ALPHA_USE))
				{
					TextureTemp.AlphaChannel.BlendType = LBX_BLEND_MANUAL;
				}
				else
				{
					TextureTemp.AlphaChannel.Source0 = GK_BT_Current;
					TextureTemp.AlphaChannel.BlendType = LBX_SOURCE1;
				}

				if (TCL_CHECK(tempProper,gkTextureProperties::TM_TEXTURE_ALPHA_USE))
				{
					TextureTemp.AlphaChannel.Source0 = GK_BT_Texture;
					TextureTemp.AlphaChannel.Source1 = GK_BT_Contant;
					TextureTemp.AlphaChannel.BlendType = LBX_MODULATE;
				}
			}

			Material* AddMaterial = Materials.get(MaterailProp.m_name.c_str());
			if (AddMaterial)
			{
				AddMaterial->Textures[AddMaterial->m_UseTexture++] = TextureTemp;
			}
		}
	}
	public:

	 static gkBlendFile2OgreImpl::Material* GetMaterialByName(gkHashedString name)
	 {
		 return Materials.get(name);
	 }
};

#endif//_gkMesh_h_
