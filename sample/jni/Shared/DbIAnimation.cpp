/***********************************************************************************************************************
/* 版权所有：
/* 功能描述：动画控制接口类 
/* 编 写 者：dabao
/* 编写日期：2012/07/11
/* 修改日期：2012/07/11
/* 其    他：无
/**********************************************************************************************************************/
#include "DbIAnimation.h"

namespace tcl
{
	gkKeyedAnimation *  DbPositionAnimation::Create_gkKeyedAnimation_internal()
	{
		gkKeyedAnimation* KeyedAnimation = gkAnimationManager::getSingleton().createKeyedAnimation(getResourceName());
		KeyedAnimation->setLength(GetTimeLength());
		gkObjectChannel* KeyChannel = new gkObjectChannel(m_name.getFullName()+"KeyChannel",KeyedAnimation);
		akBezierSpline * splineArrary[3]={0};
		splineArrary[0] = new akBezierSpline(gkTransformChannel::SC_LOC_X);
		splineArrary[1] = new akBezierSpline(gkTransformChannel::SC_LOC_Y);
		splineArrary[2] = new akBezierSpline(gkTransformChannel::SC_LOC_Z);
		akBezierVertex bezierVer;
		akBezierVertex bezierVer2;
		for (int i =0; i< 3; ++i)
		{
			bezierVer.h1[0] = bezierVer.cp[0] = 0;
			bezierVer.h1[1] = bezierVer.cp[1] = m_Start[i];
			bezierVer2.cp[0]= bezierVer2.h2[0] = GetTimeLength();
			bezierVer2.cp[1]= bezierVer2.h2[1] = m_End[i];
			if (m_BezierCurve.size() <=0)
			{
				bezierVer.h2[0] = bezierVer2.h1[0]= GetTimeLength()/2;
				bezierVer.h2[1] = bezierVer2.h1[1] = (m_End[i]- m_Start[i])/2;
			}
			else
			{
				gkVector3 middle = m_BezierCurve.at(0);
				float time = (float)(int)m_BezierCurve.keyAt(0).key();
				bezierVer.h2[0] = bezierVer2.h1[0]= time;
				bezierVer.h2[1] = bezierVer2.h1[1] = middle.x;
			}
			splineArrary[i]->addVertex(bezierVer);
			if (m_End[i] != m_Start[i]) splineArrary[i]->addVertex(bezierVer2);
			KeyChannel->addSpline(splineArrary[i]);
		}
		KeyedAnimation->addChannel(KeyChannel);
		return KeyedAnimation;
	}

	gkKeyedAnimation *  DbScaleAnimation::Create_gkKeyedAnimation_internal()
	{
		gkKeyedAnimation* KeyedAnimation = gkAnimationManager::getSingleton().createKeyedAnimation(getResourceName());
		KeyedAnimation->setLength(GetTimeLength());
		gkObjectChannel* KeyChannel = new gkObjectChannel(m_name.getFullName()+"KeyChannel",KeyedAnimation);
		akBezierSpline * splineArrary[3]={0};
		splineArrary[0] = new akBezierSpline(gkTransformChannel::SC_SCL_X);
		splineArrary[1] = new akBezierSpline(gkTransformChannel::SC_SCL_Y);
		splineArrary[2] = new akBezierSpline(gkTransformChannel::SC_SCL_Z);
		akBezierVertex bezierVer;
		akBezierVertex bezierVer2;
		for (int i =0; i< 3; ++i)
		{
			bezierVer.h1[0] = bezierVer.cp[0] = 0;
			bezierVer.h1[1] = bezierVer.cp[1] = m_Start[i];
			bezierVer2.cp[0]= bezierVer2.h2[0] = GetTimeLength();
			bezierVer2.cp[1]= bezierVer2.h2[1] = m_End[i];
			if (m_BezierCurve.size() <=0)
			{
				bezierVer.h2[0] = bezierVer2.h1[0]= GetTimeLength()/2;
				bezierVer.h2[1] = bezierVer2.h1[1] = (m_End[i]- m_Start[i])/2;
			}
			else
			{
				gkVector3 middle = m_BezierCurve.at(0);
				float time = (float)(int)m_BezierCurve.keyAt(0).key();
				bezierVer.h2[0] = bezierVer2.h1[0]= time;
				bezierVer.h2[1] = bezierVer2.h1[1] = middle.x;
			}
			splineArrary[i]->addVertex(bezierVer);
			splineArrary[i]->addVertex(bezierVer2);
			KeyChannel->addSpline(splineArrary[i]);
		}
		KeyedAnimation->addChannel(KeyChannel);
		return KeyedAnimation;

	}

	gkKeyedAnimation *  DbRotationAnimation::Create_gkKeyedAnimation_internal()
	{
		gkKeyedAnimation* KeyedAnimation = gkAnimationManager::getSingleton().createKeyedAnimation(getResourceName());
		KeyedAnimation->setLength(GetTimeLength());
		gkObjectChannel* KeyChannel = new gkObjectChannel(m_name.getFullName()+"KeyChannel",KeyedAnimation);
		KeyChannel->setEulerRotation(true);
		akBezierSpline * splineArrary[3]={0};
		splineArrary[0] = new akBezierSpline(gkTransformChannel::SC_ROT_EULER_X);
		splineArrary[1] = new akBezierSpline(gkTransformChannel::SC_ROT_EULER_Y);
		splineArrary[2] = new akBezierSpline(gkTransformChannel::SC_ROT_EULER_Z);
		akBezierVertex bezierVer;
		akBezierVertex bezierVer2;
		for (int i =0; i< 3; ++i)
		{
			bezierVer.h1[0] = bezierVer.cp[0] = 0;
			bezierVer.h1[1] = bezierVer.cp[1] = m_Start[i];
			bezierVer2.cp[0]= bezierVer2.h2[0] = GetTimeLength();
			bezierVer2.cp[1]= bezierVer2.h2[1] = m_End[i];
			if (m_BezierCurve.size() <=0)
			{
				bezierVer.h2[0] = bezierVer2.h1[0]= GetTimeLength()/2;
				bezierVer.h2[1] = bezierVer2.h1[1] = (m_End[i]- m_Start[i])/2;
			}
			else
			{
				gkVector3 middle = m_BezierCurve.at(0);
				float time = (float)(int)m_BezierCurve.keyAt(0).key();
				bezierVer.h2[0] = bezierVer2.h1[0]= time;
				bezierVer.h2[1] = bezierVer2.h1[1] = middle.x;
			}
			splineArrary[i]->addVertex(bezierVer);
			splineArrary[i]->addVertex(bezierVer2);
			KeyChannel->addSpline(splineArrary[i]);
		}
		KeyedAnimation->addChannel(KeyChannel);
		return KeyedAnimation;
	}
}
