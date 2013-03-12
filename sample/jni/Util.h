#ifndef __UTIL_H__
#define __UTIL_H__

#include "gkLogger.h"
#include "OgreSceneQuery.h"
#include "OgreMovableObject.h"
#include "gkGameObject.h"


// 裁剪区域 大小
#define _CLIP_TOP_X_		0.05
#define _CLIP_TOP_Y_		50
//#define _CLIP_BOTTOM_X_		1500/2
//#define _CLIP_BOTTOM_Y_		730/2

// all app 的属性
#define _APP_COLNUM_	4		// 一列app的数目
#define _ROW_SPACE_		2.25158	// 行之间的距离 1.73198 - 0.39963
#define _COL_SPACE_		2.18914	// 列之间的距离	1.53012+0.65902
#define _FIRST_X_		0		// 第一个app的位置
#define _FIRST_Y_		0
#define _FIRST_Z_		0

enum eFlyDirection 
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	RR,		// 有时候需要翻两屏
	NON,
};

enum ePlateName
{
	PN_NON		= 0,
	PN_MOVIE	= 1,
	PN_FAVORITE	= 2,
	PN_MYPLATE	= 4,
};

enum eSortord
{
	ST_DEFAULT,
	ST_FREQUENCE,
	ST_NAME
};

enum eAaViews
{
	AA_ScrollBar,
	AA_Letter,
	AA_Menu,
	AA_AllApp,
	AA_AaRsd,
	AA_HaSet,
	AA_HaRsd,
	AA_Sort,
	AA_NON,
};

enum BlockAniFilpInEdit
{
	None,
	Enter_Ani,
	Quit_Ani,
	Left_Ani,
	Right_Ani,
};

enum BlockEnum
{
	TV_Block,
	Recommend_Block,
	Movie_Block,
	Video_Block,
	Favorite_Block,
	My_Block,
	Title_Block
};

typedef struct sEditBlockIdx
{
	int min_idx;
	int max_idx;

	sEditBlockIdx(int minIdx = 0, int maxIdx = 0)
	{
		min_idx = minIdx;
		max_idx = maxIdx;
	}

}EditBlockIdx;

typedef struct sScrollData
{
	float TotalSize;
	float ScreenSize;
	float Position;

	sScrollData(float tts = 0.0f,float ss = 0.0f,float pos = 0.0f)
	{
		TotalSize = tts;
		ScreenSize = ss;
		Position = pos;
	}
}tScrollData;

#define _PRINT_CODE_POS_	gkPrintf("FILE = %s ,LINE = %d",__FILE__,__LINE__)

#ifdef OGREKIT_BUILD_ANDROID
#define _ASSERT_( _CONDITION_ )  if (!(_CONDITION_)) {gkPrintf("ASSERT  FAILED %s %d",__FILE__,__LINE__);}
#else
#define _ASSERT_( _CONDITION_ ) if (!(_CONDITION_)) {gkPrintf("ASSERT  FAILED %s %d",__FILE__,__LINE__); _asm int 3}
#endif

#define ui_delete(__p) if(__p){delete __p;__p=NULL;}

#define ui_deleteArray(__pp,__num)				\
	if(__pp)									\
	{											\
		for (int __i_ = 0;__i_<__num;__i_++)	\
		{										\
			ui_delete(__pp[__i_]);				\
		}										\
		delete[] __pp;							\
		__pp = NULL;							\
	}							

#define __print_t__(){ \
	time_t t = time(0);	\
	char cchar[64];		\
	strftime( cchar, sizeof(cchar), "%X",localtime(&t) ); \
	gkPrintf(cchar);	\
}	

#define _Printf_T_  __print_t__()

inline bool 
isObjInArray( Ogre::RaySceneQueryResult& res,gkGameObject* pObj)
{
	for (Ogre::RaySceneQueryResult::iterator it = res.begin(); it != res.end(); ++it)
	{
		Ogre::RaySceneQueryResultEntry ent = (*it);

		if (ent.movable)
		{
			if (ent.movable == pObj->getNode()->getAttachedObject(0))
			{
				return true;
			}
		}
	}

	/*gkGameObjectArray::Iterator iter = hitList.iterator();
	while (iter.hasMoreElements())
	{
		gkGameObject* pChild = iter.getNext();
		if (pChild == pObj)
		{
			return true;
		}
	}*/

	return false;
}

#endif