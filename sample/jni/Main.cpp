
#include "tclap/CmdLine.h"
#include "OgreKit.h"
#include "LauncherScene.H"
#include "SceneLogicBuilder.h"
#include "Logic/gkMotionNode.h"
#include "LauncherScene.h"
#include "BaseLogic.h"
#include "AaLogicBuilder.h"
#include "Aabridge.h"
#include "HaSettingsViewImpl.h"

const gkString gkDefaultConfig  = "OgreKitStartup.cfg";
const gkString gkDefaultBlend   = "ui5.0_a20_e.blend";


class OgreKit : public gkCoreApplication, public gkWindowSystem::Listener,public gkMessageManager::GenericMessageListener , public gkInstancedManager::InstancedListener
{
public:
	gkString    m_blend;
	gkScene*    m_scene;

private:
	SceneLogicBuilder * m_sceneLogicBuilder;
 	LauncherScene * m_LauncherScene;
	
	AaLogicBuilder * m_AaLogicBuilder;
	Aabridge * m_Aabridge;
	HaSettingsViewImpl* m_HaSettings;


	
public:
	OgreKit();
	virtual ~OgreKit() 
	{ 
		ui_delete (m_LauncherScene);
		ui_delete (m_sceneLogicBuilder);
		ui_delete (m_Aabridge);
		ui_delete (m_AaLogicBuilder);
	}

	int setup(int argc, char** argv);

	void tick(gkScalar rate)
	{
		if (m_LauncherScene)
		{
			m_LauncherScene->tick(rate);
		}

		if(m_Aabridge)
		{
			m_Aabridge->tick(rate);
		}
	}

	void keyReleased(const gkKeyboard& key, const gkScanCode& sc);
	void keyPressed(const gkKeyboard& key, const gkScanCode& sc);
	void handleMessage(gkMessageManager::Message* message);
	void mousePressed(const gkMouse& mouse);
	void mouseReleased(const gkMouse& mouse);

	// add by dabao 2012-12-06
	virtual void notifyInstanceQueueCreated()
	{		
		return ;   
		if(m_scene)
		{
			//no need parent setting
			//m_scene->_applyBuiltinParents(m_scene->getInstancedObjects());	

			gkLogicTree * mTree =gkNodeManager::getSingleton().createLogicTree(m_scene->getGroupName());
 			
 			Aabridge::setScene(m_scene);
			m_LauncherScene = new LauncherScene(m_scene);
 			m_Aabridge = new Aabridge();
 			
 			m_sceneLogicBuilder = new SceneLogicBuilder(m_scene, mTree, m_engine);
 
 			
 			m_AaLogicBuilder = new AaLogicBuilder(m_scene, mTree);
 
 			BaseLogic::setAabridge(m_Aabridge);
			BaseLogic::setHaSettins(HaSettingsViewImpl::getInstance());
 			BaseLogic::setLauncherScene(m_LauncherScene);
 			BaseLogic::setGkScene(m_scene);
 
 			mTree->solveOrder(true);

//testing , release resources after scene Loading
			gkTextManager::getSingleton().destroyAll();
			gkMeshManager::getSingleton().destroyAll();
			gkSkeletonManager::getSingleton().destroyAll();
			delete gkBlendLoader::getSingletonPtr();
			gkHUDManager::getSingleton().destroyAll();
#ifdef OGREKIT_USE_PARTICLE
			gkParticleManager::getSingleton().destroyAll();
#endif

#ifdef OGREKIT_OPENAL_SOUND
			gkSoundManager::getSingleton().destroyAll();
#endif

#ifdef OGREKIT_USE_LUA
			gkLuaManager::getSingleton().destroyAll();
#endif
		}
	}

private:

	bool setup(void);
};


void OgreKit::handleMessage(gkMessageManager::Message* message)
{
	if(message->m_to.size()>0)
	{
	
	}
}

OgreKit::OgreKit()
	:   m_blend(gkDefaultBlend), m_scene(NULL),m_LauncherScene(NULL), m_sceneLogicBuilder(NULL),m_AaLogicBuilder(NULL),m_Aabridge(NULL)
{
#ifdef WIN32
	char buffer[1024] ={0};
	GetCurrentDirectory( 1024,buffer);
	strcat(buffer,"\\data\\data.so");
	m_ResZipPath = buffer;
#else
	m_ResZipPath = "data/data/com.tcl.UIEngine/lib/libdata.so";
#endif
}


int OgreKit::setup(int argc, char** argv)
{

	float adjust = 1.4f;

	int winsize_x		= 800 *adjust;
	int winsize_y		= 450 *adjust;
	m_prefs.wintitle	= gkString("TCL UI Engine Demo (Press Escape to exit)[") + m_blend + gkString("]");


	gkString cfgfname;

	// Parse command line
	try
	{
		TCLAP::CmdLine cmdl("Ogrekit", ' ', "n/a");
		cmdl.setExceptionHandling(false);

		//cfg arguments

		TCLAP::ValueArg<std::string>	rendersystem_arg		("r", "rendersystem",			"Set rendering system. (gl, d3d9, d3d10, d3d11)", false, "", "string"); //default GL
		TCLAP::ValueArg<std::string>	viewportOrientation_arg	("",  "viewportorientation",	"Set viewport orientation.", false, m_prefs.viewportOrientation, "string"); 
		TCLAP::ValueArg<std::string>	log_arg					("",  "log",					"Set log file name.", false, m_prefs.log, "string"); 
		TCLAP::ValueArg<bool>			verbose_arg				("v", "verbose",				"Enable verbose log.", false, m_prefs.verbose, "bool");
		TCLAP::ValueArg<int>			winsize_x_arg			("",  "width",					"Set window width.", false, winsize_x, "int");
		TCLAP::ValueArg<int>			winsize_y_arg			("",  "height",					"Set window height.", false, winsize_y, "int");
		TCLAP::ValueArg<std::string>	wintitle_arg			("",  "wintitle",				"Set window title.", false, m_prefs.wintitle, "string"); 
		TCLAP::ValueArg<bool>			fullscreen_arg			("f", "fullscreen",				"Enable fullscreen mode.", false, m_prefs.fullscreen, "bool");
		TCLAP::ValueArg<std::string>	framingType_arg			("",  "framingtype",			"Set viewport framing type. (extend, crop, letterbox)", false, "", "string");
		TCLAP::ValueArg<std::string>	resources_arg			("",  "resources",				"Set resouces.", false, m_prefs.resources, "string");
		TCLAP::ValueArg<bool>			blendermat_arg			("",  "blendmat",				"Convert meshes using blender materials.", false, m_prefs.blendermat, "bool");
		TCLAP::ValueArg<bool>			matblending_arg			("",  "matblending",			"Enable material pass blending mode.", false, m_prefs.matblending, "bool");		
		TCLAP::ValueArg<bool>			grapInput_arg			("g", "grabinput",				"Grap mouse input.", false, m_prefs.grabInput, "bool");
		TCLAP::ValueArg<bool>			debugFps_arg			("d", "debugfps",				"Display debug fps.", false, m_prefs.debugFps, "bool");
		TCLAP::ValueArg<bool>			debugPhysics_arg		("p", "debugphysics",			"Display debug physics.", false, m_prefs.debugPhysics, "bool");
		TCLAP::ValueArg<bool>			debugPhysicsAabb_arg	("a", "debugphysicsaabb",		"Display debug physics aabb.", false, m_prefs.debugPhysicsAabb, "bool");
		TCLAP::ValueArg<bool>			buildStaticGeometry_arg	("",  "buildinstances",			"Build Static Geometry.", false, m_prefs.buildStaticGeometry, "bool");
		TCLAP::ValueArg<bool>			useBulletDbvt_arg		("",  "frustumculling",			"Enable view frustum culling by dbvt.", false, m_prefs.useBulletDbvt, "bool");
		TCLAP::ValueArg<bool>			showDebugProps_arg		("t", "showdebugprops",			"Show debug props.", false, m_prefs.showDebugProps, "bool");
		TCLAP::ValueArg<bool>			debugSounds_arg			("",  "debugsounds",			"Debug sounds.", false, m_prefs.debugSounds, "bool");
		TCLAP::ValueArg<bool>			disableSound_arg		("s", "disablesound",			"Disable sounds.", false, m_prefs.disableSound, "bool");
		TCLAP::ValueArg<bool>			fsaa_arg				("",  "fsaa",					"Enable fsaa.", false, m_prefs.fsaa, "bool");
		TCLAP::ValueArg<int>			fsaaSamples_arg			("",  "fsaasSamples",			"Set fsaa samples.", false, m_prefs.fsaaSamples, "int");
		TCLAP::ValueArg<bool>			enableshadows_arg		("",  "enableshadows",			"Enable Shadows.", false, m_prefs.enableshadows, "bool");
		TCLAP::ValueArg<int>			defaultMipMap_arg		("",  "defaultmipmap",			"Set default mipMap.", false, m_prefs.defaultMipMap, "int");
		TCLAP::ValueArg<std::string>	shadowtechnique_arg		("",  "shadowtechnique",		"Set shadow technique.", false, m_prefs.shadowtechnique, "string"); 
		TCLAP::ValueArg<std::string>	colourshadow_arg		("",  "colourshadow",			"Set shadow colour.", false, "", "string"); 
		TCLAP::ValueArg<float>			fardistanceshadow_arg	("",  "fardistanceshadow",		"Set far distance shadow.", false, m_prefs.fardistanceshadow, "float"); 
		TCLAP::ValueArg<std::string>	shaderCachePath_arg		("",  "shadercachepath",		"RTShaderSystem cache file path.", false, m_prefs.shaderCachePath, "string"); 
		

		cmdl.add(rendersystem_arg);
		cmdl.add(viewportOrientation_arg);
		cmdl.add(log_arg);
		cmdl.add(verbose_arg);
		cmdl.add(winsize_x_arg);
		cmdl.add(winsize_y_arg);
		cmdl.add(wintitle_arg);
		cmdl.add(fullscreen_arg);
		cmdl.add(framingType_arg);
		cmdl.add(resources_arg);
		cmdl.add(blendermat_arg);
		cmdl.add(matblending_arg);
		cmdl.add(grapInput_arg);
		cmdl.add(debugFps_arg);
		cmdl.add(debugPhysics_arg);	
		cmdl.add(debugPhysicsAabb_arg);	
		cmdl.add(buildStaticGeometry_arg);
		cmdl.add(useBulletDbvt_arg);
		cmdl.add(showDebugProps_arg);
		cmdl.add(debugSounds_arg);
		cmdl.add(disableSound_arg);
		cmdl.add(fsaa_arg);
		cmdl.add(fsaaSamples_arg);
		cmdl.add(enableshadows_arg);
		cmdl.add(defaultMipMap_arg);
		cmdl.add(shadowtechnique_arg);
		cmdl.add(colourshadow_arg);
		cmdl.add(fardistanceshadow_arg);
		cmdl.add(shaderCachePath_arg);

		//input file arguments
		
		TCLAP::ValueArg<std::string>			cfgfname_arg("c", "config-file", "Startup configuration file (.cfg) to use.", false, gkDefaultConfig, "string");
		TCLAP::UnlabeledValueArg<std::string>	bfname_arg("blender-file", "Blender file to launch as game.", false, gkDefaultBlend, "string");

		cmdl.add(cfgfname_arg);
		cmdl.add(bfname_arg);

		cmdl.parse( argc, argv );

		cfgfname						= cfgfname_arg.getValue();
		m_blend							= bfname_arg.getValue();

		m_prefs.rendersystem			= gkUserDefs::getOgreRenderSystem(rendersystem_arg.getValue());
		m_prefs.viewportOrientation		= viewportOrientation_arg.getValue();
		//m_prefs.sceneManager			= sceneManager_arg.getValue();
		m_prefs.log						= log_arg.getValue();
		m_prefs.verbose					= verbose_arg.getValue();

		m_prefs.winsize					= gkVector2(winsize_x_arg.getValue(), winsize_y_arg.getValue());
		m_prefs.wintitle				= wintitle_arg.getValue();

		m_prefs.fullscreen				= fullscreen_arg.getValue();
		m_prefs.framingType				= gkUserDefs::getViewportFramingType(framingType_arg.getValue());
		m_prefs.resources				= resources_arg.getValue();
		m_prefs.blendermat				= blendermat_arg.getValue();
		m_prefs.matblending				= matblending_arg.getValue();
		m_prefs.grabInput				= false/*grapInput_arg.getValue()*/;
		m_prefs.debugFps				= true ;//debugFps_arg.getValue();
		m_prefs.debugPhysics			= debugPhysics_arg.getValue();
		m_prefs.debugPhysicsAabb		= debugPhysicsAabb_arg.getValue();
		m_prefs.buildStaticGeometry		= buildStaticGeometry_arg.getValue();
		m_prefs.useBulletDbvt			= useBulletDbvt_arg.getValue();
		m_prefs.showDebugProps			= showDebugProps_arg.getValue();
		m_prefs.debugSounds				= debugSounds_arg.getValue();
		m_prefs.disableSound			= disableSound_arg.getValue();

		m_prefs.fsaa					= fsaa_arg.getValue();
		m_prefs.fsaaSamples				= fsaaSamples_arg.getValue();
		m_prefs.enableshadows			= enableshadows_arg.getValue();
		m_prefs.defaultMipMap			= defaultMipMap_arg.getValue();
		m_prefs.shadowtechnique			= shadowtechnique_arg.getValue();
		m_prefs.fardistanceshadow		= fardistanceshadow_arg.getValue();	
		m_prefs.shaderCachePath			= shaderCachePath_arg.getValue();

		if (colourshadow_arg.isSet())
			m_prefs.colourshadow		= Ogre::StringConverter::parseColourValue(colourshadow_arg.getValue());

#ifdef __APPLE__
		if (m_blend.find("-psn") != gkString::npos)
			m_blend = gkDefaultBlend;
#endif

	}
	catch (TCLAP::ArgException& e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		return -1;
	}
	catch (TCLAP::ExitException&)
	{
		// just return and exit app
		return -1;
	}
	catch (...)
	{
		std::cerr << "Unknown exception." << std::endl;
		return -1;
	}

	gkPath path = cfgfname;

	// overide settings if found
	if (path.isFile())
		m_prefs.load(path.getPath());

	return 0;
}


bool OgreKit::setup(void)
{
	//FUNCTION_PROFILE;
	gkBlendFile* blend = gkBlendLoader::getSingleton().loadFile(gkUtils::getFile(m_blend), gkBlendLoader::LO_ALL_SCENES);
	if (!blend)
	{
		gkPrintf("File loading failed.\n");
		return false;
	}

	m_scene = blend->getMainScene();
	if (!m_scene)
	{
		gkPrintf("No usable scenes found in blend.\n");
		return false;
	}

	m_scene->setUpdateFlags(m_scene->getUpdateFlags() & ~gkScene::UF_NODE_TREES);

	gkGameObjectManager::getSingleton().addInstanceListener(this);
	m_scene->createInstance();
	//gkEngine::getSingleton().registerActiveScene(m_scene);
	
	//m_scene->createInstance();

	
	// add input hooks
	gkWindowSystem::getSingleton().addListener(this);

#ifdef OGREKIT_USE_COMPOSITOR
	//gkCompositorManager::getSingleton().setCompositorChain(GK_COMPOSITOR_OP_ADD, GK_COMPOSITOR_BLOOM);
#endif

	gkMessageManager::getSingleton().addListener(this);
	if (gkMessageManager::getSingletonPtr()){
		gkMessageManager::getSingletonPtr()->sendMessage("OgreKit::setup","other","setup over","setup over");
	}

	return true;
}



void OgreKit::keyReleased(const gkKeyboard& key, const gkScanCode& sc)
{

	gkNodeManager::getSingleton().notifyUpdate();
	gkNodeManager::getSingleton().update(0);

}

void OgreKit::keyPressed(const gkKeyboard& key, const gkScanCode& sc)
{

	gkNodeManager::getSingleton().notifyUpdate();
	gkNodeManager::getSingleton().update(0);

}

void OgreKit::mousePressed(const gkMouse& mouse)
{
	gkNodeManager::getSingleton().notifyUpdate();
	gkNodeManager::getSingleton().update(1);

}

void OgreKit::mouseReleased(const gkMouse& mouse)
{
	gkNodeManager::getSingleton().notifyUpdate();
	gkNodeManager::getSingleton().update(1);
}

int main(int argc, char** argv)
{

	TestMemory;

	OgreKit okit;
	if (okit.setup(argc, argv) != 0)
	{
		// error
		return -1;
	}

	// Launch runtime
	okit.run();

	//PrintProfileResult();

	//system("pause");

	return 0;
}
