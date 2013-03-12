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
#include "gkInstancedManager.h"
#include "gkInstancedObject.h"


gkInstancedManager::gkInstancedManager(const gkString& type, const gkString& rtype)
	:    gkResourceManager(type, rtype)
{
}

gkInstancedManager::~gkInstancedManager()
{
	GK_ASSERT(m_instances.empty() && "Instances not cleared in derived class");
}


void gkInstancedManager::notifyDestroyAllInstancesImpl(void)
{
	destroyAllInstances();
	m_instanceQueue.clear();
}

void gkInstancedManager::destroyGroupInstances(const gkString& group)
{
	Instances::Iterator it = getInstanceIterator();
	while (it.hasMoreElements())
	{
		gkInstancedObject* obj = it.getNext();
		if (obj->getGroupName() == group)
			obj->destroyInstance();
	}
}

void gkInstancedManager::destroyAllInstances(void)
{
	Instances::Iterator it = getInstanceIterator();
	while (it.hasMoreElements())
		it.getNext()->destroyInstance();
}


void gkInstancedManager::addCreateInstanceQueue(gkInstancedObject* iobj)
{
	if (iobj && !iobj->isInstanced())
	{
		InstanceParam p = {iobj, InstanceParam::CREATE};
		if (m_instanceQueue.find(p))
			m_instanceQueue.push_back(p);
	}


}



void gkInstancedManager::addDestroyInstanceQueue(gkInstancedObject* iobj)
{
	if (iobj && iobj->isInstanced())
	{
		InstanceParam p = {iobj, InstanceParam::DESTROY};
		if (m_instanceQueue.find(p))
			m_instanceQueue.push_back(p);
	}
}

void gkInstancedManager::addReInstanceQueue(gkInstancedObject* iobj)
{
	if (iobj && iobj->isInstanced())
	{
		InstanceParam p = {iobj, InstanceParam::REINSTANCE};
		if (m_instanceQueue.find(p))
			m_instanceQueue.push_back(p);
	}
}

static bool cmp(const gkInstancedManager::InstanceParam& a,const gkInstancedManager::InstanceParam& b)
{
	return a.first->getName() < b.first->getName();
}


void gkInstancedManager::postProcessQueue(void)
{
#if 0
	InstanceParams::Iterator it = m_instanceQueue.iterator();

	while (it.hasMoreElements())
	{
		InstanceParam& iq = it.getNext();

		switch (iq.second)
		{
		case InstanceParam::CREATE:
			iq.first->createInstance();
			break;
		case InstanceParam::DESTROY:
			iq.first->destroyInstance();
			break;
		case InstanceParam::REINSTANCE:
			iq.first->reinstance();
			break;
		}
	}

	m_instanceQueue.clear(true);
#else

	InstanceParams::Iterator it = m_instanceQueue.iterator();
	static bool sorted = false;

	//add by zy, only sort once
	if(!sorted)
	{
		m_instanceQueue.sort(cmp);
		sorted = true;
	}

	while (it.hasMoreElements())
	{
		InstanceParam& iq = it.getNext(); 
		static int LoadNum = 0;

		switch (iq.second)
		{
		case InstanceParam::CREATE:
			iq.first->createInstance();
			m_instanceQueue.erase(iq);
			LoadNum++;
			break;
		case InstanceParam::DESTROY:
			iq.first->destroyInstance();
			break;
		case InstanceParam::REINSTANCE:
			iq.first->reinstance();
			break;
		}

		//Test: load 30 inst/frame, then load all
		if (LoadNum < 30)
		{		
			break;
		}
	}

	if (m_instanceQueue.size() == 0)
	{
		UTsize i;
		for (i = 0; i < m_instanceListeners.size(); ++i)
		{
			m_instanceListeners[i]->notifyInstanceQueueCreated();
			m_instanceListeners.erase(i);
		}
	}

#endif
}



void gkInstancedManager::notifyInstanceCreated(gkInstancedObject* iobj)
{
	if (iobj)
	{
		bool result = m_instances.insert(iobj);
		GK_ASSERT(result);


		notifyInstanceCreatedImpl(iobj);

		UTsize i;
		for (i = 0; i < m_instanceListeners.size(); ++i)
			m_instanceListeners[i]->notifyInstanceCreated(iobj);
	}


}

void gkInstancedManager::notifyInstanceDestroyed(gkInstancedObject* iobj)
{
	if (iobj)
	{
		UTsize i;
		for (i = 0; i < m_instanceListeners.size(); ++i)
			m_instanceListeners[i]->notifyInstanceDestroyed(iobj);

		notifyInstanceDestroyedImpl(iobj);

		m_instances.erase(iobj);
	}
}

void gkInstancedManager::addInstanceListener(gkInstancedManager::InstancedListener* li)
{
	if (m_instanceListeners.find(li) == UT_NPOS)
		m_instanceListeners.push_back(li);

}

void gkInstancedManager::removeInstanceListener(gkInstancedManager::InstancedListener* li)
{
	if (m_instanceListeners.find(li) != UT_NPOS)
		m_instanceListeners.erase(li);
}
