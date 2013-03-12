/***********************************************************************************************************************
/* 版权所有：
/* 功能描述：动画控制接口类 
/* 编 写 者：dabao
/* 编写日期：2012/07/11
/* 修改日期：2012/07/11
/* 其    他：无
/**********************************************************************************************************************/
#ifndef _Db_tcl_DbIAnimation_H__ 
#define _Db_tcl_DbIAnimation_H__ 
//*********************************************************************************************************************/
//定义引用库文件
#include "gkCommon.h"
#include "OgreKit.h"
//*********************************************************************************************************************/
//定义类
namespace tcl
{
	enum AnimationType
	{
		PositionAnimation,
		RatetionAnimation,
		ScaleAnimation
	};

	class DbIAnimation : public gkResource
	{
	public:
		DbIAnimation(const gkResourceName& name,float length):
		  gkResource(&gkAnimationManager::getSingleton(),name,m_Handle),m_TimeLength(length)
		  {}
		AnimationType GetType() { return m_AnimationType;}
		float GetTimeLength() { return m_TimeLength;}
	private:
		int m_Handle;
		float m_TimeLength;
		AnimationType m_AnimationType;
	};

	class DbBezierAnimation : public DbIAnimation
	{
	public:
		DbBezierAnimation(const gkResourceName& name,float lengthTime,const gkVector3 & start,const gkVector3 & end,bool loop)
		  : DbIAnimation(name,lengthTime),m_Start(start),m_End(end),m_Loop(loop)
		{
		}
		void AddBezierMiddle(float index,gkVector3 middleValue)
		{
			if (index == 0 || index >=GetTimeLength()) return;
			else
			{
				m_BezierCurve.insert((int)index,middleValue);
			}
		}
		void AttachEntity(gkEntity * parent)
		{
			if (parent)
			{
				Create_gkKeyedAnimation_internal();
				parent->addAnimation(m_name.getName());
				parent->playAnimation(m_name.getName(),1);
			}
		}
	protected:
		gkVector3 m_Start;
		gkVector3 m_End;
		typedef utHashTable<utIntHashKey,gkVector3> BezierCurve; 
		BezierCurve m_BezierCurve;
		bool m_Loop;
		gkKeyedAnimation * m_Key;
	private:
		virtual gkKeyedAnimation * Create_gkKeyedAnimation_internal() = 0;
	};

	class DbPositionAnimation : public DbBezierAnimation
	{
	public:
		DbPositionAnimation(const gkResourceName& name,float lengthTime,const gkVector3 & start,const gkVector3 & end,bool loop)
		  :DbBezierAnimation(name,lengthTime,start,end,loop)
		{}
	private:
		virtual  gkKeyedAnimation *  Create_gkKeyedAnimation_internal();
	};

	class DbRotationAnimation: public DbBezierAnimation
	{
	public:
		DbRotationAnimation(const gkResourceName& name,float lengthTime,const gkVector3 & start,const gkVector3 & end,bool loop)
		  :DbBezierAnimation(name,lengthTime,start,end,loop)
		  {}
	private:
		virtual  gkKeyedAnimation *  Create_gkKeyedAnimation_internal();
	};

	class DbScaleAnimation: public DbBezierAnimation
	{
	public:
		DbScaleAnimation(const gkResourceName& name,float lengthTime,const gkVector3 & start,const gkVector3 & end,bool loop)
		  :DbBezierAnimation(name,lengthTime,start,end,loop)
		  {}
	private:
		virtual  gkKeyedAnimation *  Create_gkKeyedAnimation_internal();
	};
}
#endif
