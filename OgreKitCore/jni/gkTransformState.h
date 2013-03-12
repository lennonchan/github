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
#ifndef _gkTransformState_h_
#define _gkTransformState_h_

#include "gkCommon.h"
#include "gkMathUtils.h"



class gkTransformState
{
public:


	gkTransformState(const gkMatrix4& mat)
	{
		invMatrix = gkMatrix4::IDENTITY;
		disableAllChannel();
		gkMathUtils::extractTransform(mat, loc, rot, scl);
		alpha = 1;
		diffuse_color = gkVector3(-1,-1,-1);
	}

	gkTransformState(const gkVector3&    oloc = gkVector3::ZERO,
	                 const gkQuaternion& orot = gkQuaternion::IDENTITY,
	                 const gkVector3&    oscl = gkVector3::UNIT_SCALE)
	{
		invMatrix = gkMatrix4::IDENTITY;
		disableAllChannel();
		rot.w = orot.w;
		rot.x = orot.x; rot.y = orot.y; rot.z = orot.z;
		loc.x = oloc.x; loc.y = oloc.y; loc.z = oloc.z;
		scl.x = oscl.x; scl.y = oscl.y; scl.z = oscl.z;
		alpha = -1;
		diffuse_color = gkVector3(-1,-1,-1);
	}

	void disableAllChannel()
	{
		loc_enable = false; rot_enable = false; scl_enable = false;
		alpha_enable = false; diffuse_color_enable = false; texture0_offset_enable = false;texture1_offset_enable = false;
		image_frame_enable = false;texture0_alphaFactor_enable = false; texture1_alphaFactor_enable = false;
		texture0_diffuseColorFactor_enable = false; texture1_diffuseColorFactor_enable = false;
	}

	GK_INLINE const gkTransformState& operator= (const gkTransformState& o)
	{
		rot.w = o.rot.w;
		rot.x = o.rot.x; rot.y = o.rot.y; rot.z = o.rot.z;
		loc.x = o.loc.x; loc.y = o.loc.y; loc.z = o.loc.z;
		scl.x = o.scl.x; scl.y = o.scl.y; scl.z = o.scl.z;
		return *this;
	}


	GK_INLINE bool operator != (const gkTransformState& o) const
	{
		return ((rot.w != o.rot.w) ||
		        (rot.x != o.rot.x) ||
		        (rot.y != o.rot.y) ||
		        (rot.z != o.rot.z) ||
		        (loc.x != o.loc.x) ||
		        (loc.y != o.loc.y) ||
		        (loc.z != o.loc.z) ||
		        (scl.x != o.scl.x) ||
		        (scl.y != o.scl.y) ||
		        (scl.z != o.scl.z)
		       );
	}

	void set(const gkVector3& oloc, const gkQuaternion& orot, const gkVector3& oscl)
	{
		rot.w = orot.w;
		rot.x = orot.x; rot.y = orot.y; rot.z = orot.z;
		loc.x = oloc.x; loc.y = oloc.y; loc.z = oloc.z;
		scl.x = oscl.x; scl.y = oscl.y; scl.z = oscl.z;
	}

	GK_INLINE void setIdentity(void)
	{
		rot.w = gkScalar(1.0);
		rot.x = gkScalar(0.0); rot.y = gkScalar(0.0); rot.z = gkScalar(0.0);
		loc.x = gkScalar(0.0); loc.y = gkScalar(0.0); loc.z = gkScalar(0.0);
		scl.x = gkScalar(1.0); scl.y = gkScalar(1.0); scl.z = gkScalar(1.0);
	}

	GK_INLINE void      toMatrix(gkMatrix4& m) const    { m.makeTransform(loc, scl, rot); }
	GK_INLINE gkMatrix4 toMatrix(void) const            { gkMatrix4 m; m.makeTransform(loc, scl, rot); return m;}


	GK_INLINE btQuaternion  toRotation(void)        const { return btQuaternion(rot.x, rot.y, rot.z, rot.w);}
	GK_INLINE btVector3     toOrigin(void)          const { return btVector3(loc.x, loc.y, loc.z); }
	GK_INLINE btVector3     toLocalScaling(void)    const { return btVector3(scl.x, scl.y, scl.z); }
	GK_INLINE btTransform   toTransform(void)       const { btTransform t; toTransform(t); return t; }

	GK_INLINE void toTransform(btTransform& trans)  const
	{
		trans.setIdentity();
		trans.setOrigin(toOrigin());
		trans.setRotation(toRotation());
	}


	//add Key & enable
	gkMatrix4 invMatrix;
	gkQuaternion        rot;	bool                      rot_enable; 
	gkVector3           loc; 	bool                    loc_enable;
	gkVector3           scl; 	bool                    scl_enable;
	gkScalar             alpha;	bool                    alpha_enable;
	gkVector3           diffuse_color; 	bool                     diffuse_color_enable;
	gkVector3				texture0_offset; bool		texture0_offset_enable;
	gkVector3				texture1_offset; bool		texture1_offset_enable;
	gkScalar			texture0_alphaFactor; bool texture0_alphaFactor_enable;
	gkScalar			texture1_alphaFactor; bool texture1_alphaFactor_enable;
	gkScalar			texture0_diffuseColorFactor; bool texture0_diffuseColorFactor_enable;
	gkScalar			texture1_diffuseColorFactor; bool texture1_diffuseColorFactor_enable;
	gkScalar				image_frame; bool image_frame_enable;
};


#endif//_gkTransformState_h_
