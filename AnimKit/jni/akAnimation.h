/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): Xavier T.
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
#ifndef _akAnimation_h_
#define _akAnimation_h_

#include "utCommon.h"
#include "utString.h"

#include "akCommon.h"
#include "akMathUtils.h"

class akCallback
{
public:
	virtual void Execute() = 0;
};

template   <typename   T,   void   (T::*F)(void)> 
class akAnimationCallback :public akCallback
{ 
public: 
	akAnimationCallback(T   *t) : m_Instance(t){} 
	void Execute(void) 
	{ 
		if(m_Instance)
			(m_Instance->*F)(); 
		return; 
	} 
private: 
	T*   m_Instance; 
}; 


class akAnimation
{
protected:
	akScalar m_length;
	akScalar m_startFrame;
	akScalar m_endFrame;
	
public:
	akAnimation() : m_length(0),m_startFrame(0),m_endFrame(0) {}
	virtual ~akAnimation() {}
	
	UT_INLINE akScalar         getLength(void) const       { return m_length; }
	UT_INLINE void             setLength(akScalar v)       { m_length = v; }
	UT_INLINE akScalar         getStartFrame(void) const       { return m_startFrame; }
	UT_INLINE void             setStartFrame(akScalar v)       { m_startFrame = v; }
	UT_INLINE akScalar         getEndFrame(void) const       { return m_endFrame; }
	UT_INLINE void             setEndFrame(akScalar v)       { m_endFrame = v; }
	
	virtual void evaluate(const akScalar& time, const akScalar& weight, void* object) const = 0;

};







#endif//_akAnimation_h_
