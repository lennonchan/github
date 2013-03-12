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

#ifndef AKANIMATIONPLAYER_H
#define AKANIMATIONPLAYER_H

#include "akAnimation.h"
#include "akMathUtils.h"

class akAnimationPlayer
{
protected:
	akAnimation*         m_action;
	akScalar             m_evalTime, m_weight;
	akScalar				m_evalEndTime;
	akScalar				m_evalStartTime;
	akScalar			m_blenderFps;
	akScalar			m_animFps;
	bool                 m_enabled;
	bool				m_invalid;
	bool					m_finished;
	int                  m_mode;
	akScalar             m_speedfactor;
	akCallback*				m_finishedCallback;

public:
	akAnimationPlayer();
	akAnimationPlayer(akAnimation* resource);
	~akAnimationPlayer() {}

	UT_INLINE akScalar         getTimePosition(void) const { return m_evalTime; }
	UT_INLINE akScalar         getTimeEndPosition(void) const { return m_evalEndTime; }
	UT_INLINE akScalar         getTimeStartPosition(void) const { return m_evalStartTime; }
	UT_INLINE akScalar         getWeight(void) const       { return m_weight; }
	UT_INLINE int              getMode(void) const         { return m_mode; }
	UT_INLINE akScalar         getSpeedFactor(void) const  { return m_speedfactor; }
	UT_INLINE akScalar         getLength(void) const       { return m_action? m_action->getLength() : 0;}

	UT_INLINE void             setMode(int v)              { m_mode = v; }
	UT_INLINE void             setAnimation(akAnimation* v){ m_action = v; }
	UT_INLINE void             setSpeedFactor(akScalar v)  { m_speedfactor = v; }

	UT_INLINE void             enable(bool v)              { m_enabled = v; }
	UT_INLINE bool             isEnabled(void) const       { return m_enabled; }
	UT_INLINE bool             isDone(void) const          { return !m_enabled || m_evalTime >= getLength(); }

	bool isInvalid(){return m_invalid;};
	bool isFinished(){return m_finished;};

	void setBlendFrames(akScalar v);
	void setTimePosition(akScalar v);
	void setTimeEndPosition(akScalar v);
	void setTimeStartPosition(akScalar v);
	void setAnimationFps(akScalar v);
	void setWeight(akScalar w);
	void setFinished();

	void setAnimationFinishedCallback(akCallback * callback);

	bool evaluate(akScalar tick);
	void reset(void);
	
private:
	virtual void evaluateImpl(akScalar time) = 0;

};



#endif // AKANIMATIONPLAYER_H
