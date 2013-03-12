/***********************************************************************************************************************
/* 版权所有：
/* 功能描述：创建subMesh 
/* 编 写 者：dabao
/* 编写日期：2012/07/10
/* 修改日期：2012/07/10
/* 其    他：无
/**********************************************************************************************************************/
#include "DbCreateSubMesh.h"

namespace tcl
{
	gkSubMesh * DbCubeMesh::CreateSubMesh(MeshType type)
	{
		//***********************************************************************
		// create cube mesh
		gkSubMesh * subCubeMesh = new gkSubMesh();
		gkSubMesh::Verticies& subCubeVer = subCubeMesh->getVertexBuffer();
		gkSubMesh::Triangles& indexSubCube = subCubeMesh->getIndexBuffer();
		gkVector3 CubeVertexControls[8] = {gkVector3(0.5,0.5,0.5),gkVector3(-0.5,0.5,0.5),gkVector3(-0.5,-0.5,0.5),
			gkVector3(0.5,-0.5,0.5),gkVector3(0.5,0.5,-0.5),gkVector3(-0.5,0.5,-0.5),gkVector3(-0.5,-0.5,-0.5),
			gkVector3(0.5,-0.5,-0.5)};
		gkVector2 CubeTextrueControls[4] ={gkVector2(1,1),gkVector2(0,1),gkVector2(0,0),gkVector2(1,0)};
		int sixPlane[6][4] ={{0,1,2,3},{5,4,7,6},
		                    {4,5,1,0},{3,2,6,7},
		                    {0,4,7,3},{1,5,6,2}};
		gkVertex CubeVertex;
		CubeVertex.co = gkVector3(0.5,0.5,0);
		CubeVertex.uv[0] = gkVector2(1,1);
		CubeVertex.vba =0;
		CubeVertex.no = gkVector3::UNIT_Z;
		gkTriangle indexCube;
		indexCube.i0 =0;
		indexCube.i1 = 1;
		indexCube.i2 = 2;
		indexCube.flag =2;
		for (int i =0; i< 6; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				CubeVertex.co = CubeVertexControls[sixPlane[i][j]];
				CubeVertex.uv[0] = CubeTextrueControls[j];
				subCubeVer.push_back(CubeVertex);
			}
			for (int index =0; index < 2; ++index)
			{
				indexCube.i0 = (i*4+0+ (index *2)) % ((i+1)*4);
				indexCube.i1 = (i*4+1+ (index *2)) % ((i+1)*4);
				indexCube.i2 = (i*4+2+ (index *2)) % ((i+1)*4);
				if (index) indexCube.i2 = i*4;
				indexSubCube.push_back(indexCube);
			}
		}
		return subCubeMesh;
	}

	gkSubMesh * DbPlaneMesh::CreateSubMesh(MeshType tyep)
	{
		//***********************************************************************
		// create plane mesh
		gkSubMesh * subMesh = new gkSubMesh();
		gkSubMesh::Verticies& subVer = subMesh->getVertexBuffer();
		gkSubMesh::Triangles& indexSub = subMesh->getIndexBuffer();
		gkTriangle indexTriangle ;
		indexTriangle.i0 =0;
		indexTriangle.i1 = 1;
		indexTriangle.i2 = 2;
		indexTriangle.flag =2;		
		indexSub.push_back(indexTriangle);
		indexTriangle.i0 =2;
		indexTriangle.i1 = 3;
		indexTriangle.i2 = 0;
		indexTriangle.flag =2;
		indexSub.push_back(indexTriangle);
		gkVertex temp;
		temp.co = gkVector3(1,1,0);
		temp.uv[0] = gkVector2(1,1);
		temp.vba =0;
		temp.no = gkVector3::UNIT_Z;
		subVer.push_back(temp);
		temp.co = gkVector3(-1,1,0);
		temp.uv[0] = gkVector2(0,1);
		temp.vba =3;
		subVer.push_back(temp);
		temp.co = gkVector3(-1,-1,0);
		temp.uv[0] = gkVector2(0,0);
		temp.vba =2;
		subVer.push_back(temp);
		temp.co = gkVector3(1,-1,0);
		temp.uv[0] = gkVector2(1,0);
		temp.vba =1;
		subVer.push_back(temp);
		return subMesh;
	}
}
