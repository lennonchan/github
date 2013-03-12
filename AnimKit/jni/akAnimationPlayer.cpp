/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Xavier T.

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

#include "akAnimationPlayer.h"
#include "akAnimationSequence.h"


akAnimationPlayer::akAnimationPlayer()
	:	m_action(0),
	    m_evalTime(0.f),
		m_blenderFps(24.0f),
		m_animFps(24.0f),
	     m_weight(1.0),
	     m_enabled(true),
		 m_finished(false),
	     m_mode(AK_ACT_LOOP),
	     m_speedfactor(1.0f),
		 m_finishedCallback(NULL),
		 m_invalid(false)
{
}

akAnimationPlayer::akAnimationPlayer(akAnimation* resource)
	:	m_action(resource),
	    m_evalTime(0.f),
		m_blenderFps(24.0f),
		m_animFps(24.0f),
	     m_weight(1.0),
	     m_enabled(true),
		  m_finished(false),
	     m_mode(AK_ACT_LOOP),
	     m_speedfactor(1.0f),
		 m_finishedCallback(NULL)
{
}

void akAnimationPlayer::setTimePosition(akScalar v)
{
	if (m_action)
	{
		FOOT_LOG;
		m_evalTime = v/m_blenderFps;
	}
}

void akAnimationPlayer::setTimeEndPosition(akScalar v)
{
	if (m_action)
	{
		m_evalEndTime = v/m_blenderFps;
		if(m_evalEndTime > m_action->getEndFrame()/m_blenderFps)
		{
			m_evalEndTime = m_action->getEndFrame()/m_blenderFps;
		}
		if(m_evalEndTime < m_action->getStartFrame()/m_blenderFps)
		{
			m_invalid = true;
		}
	}
}

void akAnimationPlayer::setTimeStartPosition(akScalar v)
{
	if (m_action)
	{
		m_invalid = false;
		//float animFps =  gkEngine::getSingleton().getUserDefs().animFps;
		m_evalStartTime = v/m_blenderFps;
		m_evalTime = m_evalStartTime;
		if(m_evalStartTime > m_action->getEndFrame()/m_blenderFps)
		{
			m_invalid = true;
		}
	}
}

void akAnimationPlayer::setAnimationFps(akScalar fps)
{
	m_animFps = fps;
	m_speedfactor = m_animFps/m_blenderFps;
}


void akAnimationPlayer::setWeight(akScalar w)
{
	if (m_enabled)
	{
		m_weight = akClampf(w, 0, 1);
	}
}



bool akAnimationPlayer::evaluate(akScalar tick)
{
	if (!m_enabled || !m_action || m_invalid||m_finished)
	{
		m_invalid = true;
// 		if(!m_finished)
// 			setFinished();
		return false;
	}

	akScalar end = m_action->getLength();
	akScalar dt = m_speedfactor * tick;
	akScalar aniStartTime = m_action->getStartFrame()/m_blenderFps;

	m_evalTime += dt;
	
	akScalar curRunTime = m_evalTime - aniStartTime;
	akScalar curRunEndTime = m_evalEndTime - aniStartTime;
	
	if (m_mode & AK_ACT_LOOP)
	{
		if (curRunTime <= 0.f)
			curRunTime = 0.f;
		if (curRunTime >= end)
			curRunTime = 0.f;
	}
	else
	{
		if (curRunTime < 0.f)
			curRunTime = 0.f;

		if (curRunTime > curRunEndTime)
			curRunTime = curRunEndTime;
	}

	if(curRunEndTime < 0)
		return false;

	if (m_mode & AK_ACT_INVERSE)
		curRunTime = end - m_evalTime;

	if(curRunTime >= 0)
		evaluateImpl(curRunTime);
	else
		return true;

	if(curRunTime >= curRunEndTime)
	{
		return false;
	}

	return true;	
}

void akAnimationPlayer::setFinished(void)
{
	if(m_finished || m_invalid)
		return;
	m_evalTime = m_evalEndTime;	
	akScalar runEndTime = m_evalEndTime - m_action->getStartFrame()/m_blenderFps;
	evaluateImpl(runEndTime);
	if(m_finishedCallback)
		m_finishedCallback->Execute();
	m_finished = true;
}

void akAnimationPlayer::setAnimationFinishedCallback(akCallback * callback)
{
	m_finishedCallback = callback;
}

void akAnimationPlayer::reset(void)
{
	m_evalTime = m_evalStartTime;
	m_finished = false;
//	m_weight = 1.f;
//	m_enabled = false;
}
