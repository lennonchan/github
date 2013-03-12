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
#include "gkCoreApplication.h"
#include "gkLogger.h"
#include "OgreResourceGroupManager.h"

gkCoreApplication::gkCoreApplication()
:       m_engine(0), m_prefs(),m_AppResName("")
{
	
}


gkCoreApplication::~gkCoreApplication()
{
	delete m_engine;
	m_engine = 0;
}


void gkCoreApplication::run(void)
{
	if (!initialize())
		return;

	if (m_engine)
		m_engine->run();
}


// Internal startup
bool gkCoreApplication::initialize(void)
{
	m_engine = new gkEngine(&m_prefs);
	m_engine->initialize();
	if (m_ResZipPath.size() > 0) addZipDataPath(m_ResZipPath,m_AppResName);
	m_engine->updateMaterial();
	if (!m_engine->isInitialized())
		return false;

	// Setup scene information
	if (!setup())
	{
		m_engine->finalize();
		delete m_engine;
		m_engine = 0;
		return false;
	}

	// add update
	m_engine->addListener(this);
	return true;
}
void gkCoreApplication::addResourceDataPath(gkString resPath)
{
#ifdef WIN32
		char *p=0;
		char fpath[1024];
#if defined(WCHAR_CODE)
		p = _wfullpath(fpath, filename.c_str(), 1024);
#else
		p = _fullpath(fpath, "..\\..\\", 1024);
		std::string new_location(fpath);
		new_location.append("\\Material\\");
#endif

#else
	    std::string new_location = "./data/data/Material";
#endif
       if(resPath.size() > 0) new_location = resPath.c_str();
	   Ogre::ResourceGroupManager::getSingleton().addResourceLocation(new_location.c_str(),"FileSystem","", true);
}
void gkCoreApplication::addZipDataPath(gkString zipPath,gkResourceName resoureName)
{
	addResourceDataPath("");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(zipPath, "Zip", resoureName.getName());
	
}