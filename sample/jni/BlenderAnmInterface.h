#ifndef __BLENDERANMINTERFACE_H__
#define __BLENDERANMINTERFACE_H__

#include "BlenderAnimation.h"

class BlenderAnmInterface
{
public:
	virtual void onBlenderAnmFinish(BlenderAnimation* p,int s,int e) = 0;
};


#endif //__BLENDERANMINTERFACE_H__