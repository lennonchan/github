/***********************************************************************************************************************
/* ��Ȩ���У�
/* �����������������ƽӿ��� 
/* �� д �ߣ�dabao
/* ��д���ڣ�2012/07/11
/* �޸����ڣ�2012/07/11
/* ��    ������
/**********************************************************************************************************************/
#ifndef _Db_tcl_DbIAnimation_H__ 
#define _Db_tcl_DbIAnimation_H__ 
//*********************************************************************************************************************/
//�������ÿ��ļ�
#include "gkCommon.h"
#include "OgreKit.h"
//*********************************************************************************************************************/
//������
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
