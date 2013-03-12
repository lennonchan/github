/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): Nestor Silveira.
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
#ifndef _gkGameObject_h_
#define _gkGameObject_h_

#include "gkInstancedObject.h"
#include "gkMathUtils.h"
#include "gkTransformState.h"
#include "gkSerialize.h"
#include "gkInput.h"
#include "Animation/gkAnimation.h"
#ifdef OGREKIT_USE_PHYSICS
#include "Physics/gkGhost.h"
#endif
#include <OgreSceneNode.h>
#include <OgreMovableObject.h>
#include <OgrePass.h>

class gkGameObject : public gkInstancedObject
{
public:
	typedef utHashTable<gkHashedString, gkVariable*>   VariableMap;

	// Life counter of a cloned object
	struct LifeSpan
	{
		int tick;
		int timeToLive;
	};

	class Notifier
	{
	public:

		enum Event
		{
			UPDATED,
			INSTANCE_CREATED,
			INSTANCE_DESTROYED,
			DESTROYING,
		};

	public:

		virtual ~Notifier() {}

		virtual void notifyGameObjectEvent(gkGameObject* gobj, const Event& id) = 0;
	};


	typedef utArray<Notifier*> Notifications;

	typedef utHashTable<gkHashedString, gkAnimationPlayer*>  Animations;

public:

	gkGameObject(gkInstancedManager* creator, const gkResourceName& name, const gkResourceHandle& handle, gkGameObjectTypes type = GK_OBJECT);
	virtual ~gkGameObject();


	GK_INLINE void                      setOwner(gkScene* scene) {m_scene = scene;}
	GK_INLINE gkScene*                  getOwner(void)           {return m_scene;}

	GK_INLINE Ogre::SceneNode*          getNode(void)        {return m_node;}
	GK_INLINE gkGameObjectTypes         getType(void)        {return m_type;}
	GK_INLINE gkGameObjectProperties&   getProperties(void)  {return m_baseProps;}
	GK_INLINE bool                      isClone(void)        {return m_isClone;}


	bool hasSensorMaterial(const gkString& name, bool onlyFirst = true);

	// subtype access
	GK_INLINE gkEntity*         getEntity(void)         {return m_type == GK_ENTITY    ? (gkEntity*)this : 0; }
	GK_INLINE gkCamera*         getCamera(void)         {return m_type == GK_CAMERA    ? (gkCamera*)this : 0; }
	GK_INLINE gkLight*          getLight(void)          {return m_type == GK_LIGHT     ? (gkLight*)this : 0; }
	GK_INLINE gkSkeleton*       getSkeleton(void)       {return m_type == GK_SKELETON  ? (gkSkeleton*)this : 0; }
	GK_INLINE gkParticleObject* getParticleObject(void) {return m_type == GK_PARTICLES ? (gkParticleObject*)this : 0; }

	// Parent / Child access.
	GK_INLINE bool                      hasParent(void)         {return m_parent != 0;}
	gkGameObject*             getParent(void);
	GK_INLINE gkGameObjectArray&        getChildren(void)       {return m_children;}

	void setParent(gkGameObject* par);
	void setParentInPlace(gkGameObject* par);
	void clearParent(void);
	void clearParentInPlace(void);
	void addChild(gkGameObject* ob);
	void removeChild(gkGameObject* ob);
	bool hasChild(gkGameObject* ob);


	// Tells the parent scene this object has been updated
	// This allows extra update event processing per game object.
	void notifyUpdate(void);


	GK_INLINE LifeSpan& getLifeSpan(void)               {return m_life;}
	GK_INLINE void      setLifeSpan(const LifeSpan& v)  {m_life = v;}


	// layers
	GK_INLINE void setActiveLayer(bool v)   {m_activeLayer = v; }
	GK_INLINE bool isInActiveLayer(void)    {return m_activeLayer; }
	GK_INLINE void     setLayer(UTuint32 v) {m_layer = v; }
	GK_INLINE UTuint32 getLayer(void)       {return m_layer;}


	virtual gkGameObject* clone(const gkString& name);



	// physics
#ifdef OGREKIT_USE_PHYSICS
	GK_INLINE void           attachRigidBody(gkRigidBody* body)          {m_rigidBody = body;}
	GK_INLINE gkRigidBody*   getAttachedBody(void)                      {return m_rigidBody;}
	GK_INLINE void           attachCharacter(gkCharacter* character)     {m_character = character;}
	GK_INLINE gkCharacter*   getAttachedCharacter(void)                 {return m_character;}

	GK_INLINE void           attachGhost(gkGhost* ghost)     {m_ghost = ghost;}
	GK_INLINE gkGhost*       getAttachedGhost(void)                 {return m_ghost;}

	gkPhysicsController*     getPhysicsController(void);

	btCollisionObject*       getCollisionObject(void);
#endif

	// variables

	gkVariable* createVariable(const gkString& name, bool debug);
	gkVariable* getVariable(const gkString& name);
	bool        hasVariable(const gkString& name);
	void        removeVariable(const gkString& name);
	void        clearVariables(void);



	const gkTransformState&  getTransformState(void);
	const gkMatrix4&         getTransform(void);
	const gkVector3&         getPosition(void);
	const gkQuaternion&      getOrientation(void);
	const gkVector3&         getScale(void);
	gkEuler                  getRotation(void);

	const gkTransformState&  getWorldTransformState(void);
	const gkMatrix4&         getWorldTransform(void);
	const gkVector3&         getWorldPosition(void);
	const gkVector3&         getWorldScale(void);
	const gkQuaternion&      getWorldOrientation(void);
	gkEuler                  getWorldRotation(void);

	// add by dabao 2012-11-6 set icon texture or name texture
	void setTexture(Ogre::TexturePtr iconTexture,int index =0);
	void setTexture(gkResourceName textureName,int index =0);


	// add by dabao 2012-11-28
	gkGameObject * cloneGameObject(gkString newObjectName);

	// add by dabao 2012-11-30 check mouse hover or mouse click by subViewPort or MainViewPort
	bool isMouseHoverNow(Ogre::Viewport * hitViewPort = NULL);
	bool isMouseClickNow(gkMouse::Buttons button = gkMouse::Left,Ogre::Viewport * hitViewPort = NULL);


	// add by dabao 2012-12-07  convert 3D postion to 2D screen  or 2D screen to 3D position
	gkVector2  Convert3DPositionToScreenPosition(gkVector3 scenePosition);
	gkVector3  ConvertScreenPositionTo3DPosition(gkVector2 screenPosition);

	// add by dabao 2012-12-12  set or get clip sign (default no clip)
	bool getObjectClipEnable();
	void setObjectClipEnable(bool enable);

	// add by dabao 2012-12-14 set or get Node Alpha Value
	void  setAlpha(float alphaValue);

	// add by dabao 2012-12-14  set GPU update parameter
	void setGpuParameter(gkString gpuName,float * value, int valueSize);

	// add by dabao 2012-12-14 set object render priority 
	// eg: 
	/*  RENDER_QUEUE_BACKGROUND = 0,  First queue (after backgrounds), used for skyboxes if rendered first
	    RENDER_QUEUE_SKIES_EARLY = 5,
		RENDER_QUEUE_1 = 10,
		RENDER_QUEUE_2 = 20,
		RENDER_QUEUE_WORLD_GEOMETRY_1 = 25,
		RENDER_QUEUE_3 = 30,
		RENDER_QUEUE_4 = 40,
		RENDER_QUEUE_MAIN = 50,  /// The default render queue
		RENDER_QUEUE_6 = 60,
		RENDER_QUEUE_7 = 70,
		RENDER_QUEUE_WORLD_GEOMETRY_2 = 75,
		RENDER_QUEUE_8 = 80,
		RENDER_QUEUE_9 = 90,
		/// Penultimate queue(before overlays), used for skyboxes if rendered last
		RENDER_QUEUE_SKIES_LATE = 95,
		/// Use this queue for objects which must be rendered last e.g. overlays
		RENDER_QUEUE_OVERLAY = 100, */

	void setObjectRenderPriority(int priority);

	// add by dabao 2013-01-21 for use only one pass to save space
	virtual void addGpuParameter(Ogre::Entity * objectEntity){ }

	void applyTransformState(const gkTransformState& newstate, const gkScalar& weight=1.f,bool fromAnimationChannel = false);

	//add by zy 2012-12-13
	gkTransformState getLastTransformState();
	gkMatrix4 getParentInvTransform(gkTransformState& state);

	// add by lennon 2013-1-9
	unsigned int getSubEntitiesNum();
	void setSubEntityVisible(unsigned int sEntityIndex,bool v);
	//utility method    zy
	Ogre::Pass* getCurrentOgrePass(int entityIndex);
	utArray<Ogre::Pass*> getCurrentOgrePass();
	void setTransform(const gkMatrix4& v);
	void setTransform(const gkTransformState& v);
	void setPosition(const gkVector3& v);
	void setScale(const gkVector3& v);

	void setOrientation(const gkQuaternion& q);
	void setOrientation(const gkEuler& v);

	void rotate(const gkEuler& drot, int tspace = TRANSFORM_PARENT);
	void rotate(const gkQuaternion& q, int tspace = TRANSFORM_PARENT);
	void translate(const gkVector3& dloc, int tspace = TRANSFORM_PARENT);
	void scale(const gkVector3& dscale);

	void yaw(const gkRadian& v, int  tspace = TRANSFORM_PARENT);
	void pitch(const gkRadian& v, int  tspace = TRANSFORM_PARENT);
	void roll(const gkRadian& v, int  tspace = TRANSFORM_PARENT);


	int getActAnimationNum(){return m_actionBlender->getActAnimationNum();};
	void removeAnmPlayer(gkAnimationPlayer* pPlayer);
	// rigid body methods

	void        applyTorque(const gkVector3& t, int tspace = TRANSFORM_PARENT);
	void        applyForce(const gkVector3& f, int tspace = TRANSFORM_PARENT);
	void        setLinearVelocity(const gkVector3& linv, int tspace = TRANSFORM_PARENT);
	void        setAngularVelocity(const gkVector3& angv, int tspace = TRANSFORM_PARENT);
	gkVector3   getLinearVelocity(void);
	gkVector3   getAngularVelocity(void);

#ifdef OGREKIT_USE_NNODE
	void attachLogic(gkLogicTree* tree);
#endif

	void attachLogic(gkLogicLink* bricks);
	GK_INLINE gkLogicLink* getLogicBricks() {return m_bricks;}

	// Ogre base class for movables
	Ogre::MovableObject* getMovable(void);

	virtual Ogre::AxisAlignedBox getAabb() const;

	struct NavMeshData
	{
		int triangleBaseIndex;
		int nIndex;
		float hmin;
		float hmax;

		NavMeshData() : triangleBaseIndex(-1), nIndex(0), hmin(0), hmax(0) {}
		NavMeshData(int i, int n, float hMin, float hMax) : triangleBaseIndex(i), nIndex(n), hmin(hMin), hmax(hMax) {}
		bool isEmpty() const { return !nIndex; }
	};

	GK_INLINE const NavMeshData& getNavData() const { return m_navMeshData; }

	GK_INLINE void setNavData(const NavMeshData& data) { m_navMeshData = data; }

	GK_INLINE void resetNavData() { m_navMeshData = NavMeshData(); }

	void GK_INLINE recalcNavData(int i, int n)
	{
		if (m_navMeshData.triangleBaseIndex > i)
		{
			m_navMeshData.triangleBaseIndex -= n;
		}
	}

	gkGameObject* getChildEntity();

	GK_INLINE void  setState(int v)     {m_state = v;}
	GK_INLINE int   getState(void)      {return m_state;}

	void changeState(int v);

	// See gkGameObjectMode

	GK_INLINE void setFlags(int flag)   {m_flags = flag;}
	GK_INLINE int  getFlags(void)       {return m_flags;}



	GK_INLINE bool   isStaticGeometry(void)   {return (m_flags & GK_STATIC_GEOM) != 0;}
	GK_INLINE bool   isImmovable(void)        {return (m_flags & GK_IMMOVABLE) != 0;}
	
	GK_INLINE void setVisible(bool v)          { if(isInstanced())getNode()->setVisible(v, false);}
	GK_INLINE void setVisibleRecursive(bool v) { if(isInstanced())getNode()->setVisible(v, true);}
	GK_INLINE bool getVisible()                {return getNode()->getAttachedObject(0)->getVisible();}


	// Grouping

	GK_INLINE gkGameObjectGroup*    getGroup(void)           { return m_group;}
	GK_INLINE gkGameObjectInstance* getGroupInstance(void)   { return m_groupID; }
	GK_INLINE bool                  isGroupInstance(void)    { return m_groupID != 0;}
	GK_INLINE bool                  isInGroup(void)          { return m_group != 0;}

	GK_INLINE void                  _makeGroupInstance(gkGameObjectInstance* id)  { m_groupID = id; }
	GK_INLINE void                  _makeGroup(gkGameObjectGroup* id)             { m_group = id; }


	// events
	void addEventListener(Notifier* evt);
	void removeEventListener(Notifier* evt);


	// animation
	gkAnimationPlayer*     addAnimation(const gkHashedString& name);
	gkAnimationPlayer*     addAnimation(gkAnimation* action, const gkHashedString& playername);
	gkAnimationPlayer*     getAnimationPlayer(const gkHashedString& name);
	void                   playAnimation(const gkString& act, gkScalar blend, int mode = AK_ACT_END, int priority = 0);
	void                   playAnimation(gkAnimationPlayer* act, gkScalar blend, int mode = AK_ACT_END, int priority = 0);
	void                   updateAnimationBlender(const gkScalar tick);
	gkAnimationBlender&    getAnimationBlender(void);
	GK_INLINE bool         hasAnimationBlender(void) { return m_actionBlender != 0; }
	
	void                   stopAnimation(const gkString& act);
	void                   stopAnimation(gkAnimationPlayer* act);

	void                   pauseAnimations(void);
	void                   resumeAnimations(void);

	GK_INLINE const Animations& getAnimations(void) { return m_actions; }
	void getAnimationNames(utArray<gkHashedString>& names);



protected:

	// add by dabao 2012-11-8 check node is hit
	bool IsOnHit(bool hover =false , gkMouse::Buttons button = gkMouse::Left, Ogre::Viewport* subViewPort = NULL);

	// add by dabao 2012-12-10 gkVector3 3D Position or 2D Screen Position convert

	gkVector3 _internal_Convert_Position_3D_2D(gkVector3 value , bool to3D = true);

	// add by dabao 2012-11-30 check subViewPort is hit
	gkVector2 getSubViewPortMousePosition(Ogre::Viewport* subViewPort);
	gkRay getRayFromSubViewPort(Ogre::Viewport* subViewPort);

private:
	// internal fuction not for outside class call
    gkVector2 GetMousePosition();
	gkRay CameraToViewportRay();
	bool TestRayHitMe(gkRay& ray);

	Ogre::Camera * ActiveOgreCamera();

protected:

	bool canCreateInstance(void) {return m_scene != 0;}


	Ogre::RaySceneQuery* m_rayQuery;


	void cloneImpl(gkGameObject* clob);

	gkGameObjectTypes           m_type;


	// Properties specific to the GameObject class
	gkGameObjectProperties      m_baseProps;

	// Parent object
	gkGameObject*               m_parent;
	gkGameObjectArray           m_children;


	// Access to the owing scene
	gkScene*                    m_scene;

	// Ogre scenegraph node
	Ogre::SceneNode*            m_node;

	// Attached nodelogic trees
	gkLogicTree*                m_logic;

	// Attached logic bricks
	gkLogicLink*                m_bricks;

#ifdef OGREKIT_USE_PHYSICS
	// Physics body instances
	gkRigidBody*                m_rigidBody;
	gkCharacter*                m_character;
	gkGhost*                    m_ghost;
#endif


	VariableMap                 m_variables;
	gkGameObjectInstance*       m_groupID;
	gkGameObjectGroup*          m_group;

	Notifications               m_events;


	int                         m_state;
	bool                        m_activeLayer;
	int                         m_layer;
	bool                        m_isClone;
	int                         m_flags;
	LifeSpan                    m_life;


	gkAnimationBlender*         m_actionBlender;
	Animations                  m_actions;
	gkTransformState            m_lastTransformState;


	virtual void createInstanceImpl(void);
	virtual void destroyInstanceImpl(void);
	virtual void postCreateInstanceImpl(void);
	virtual void postDestroyInstanceImpl(void);
	virtual void notifyResourceDestroying(void);



	void sendNotification(const Notifier::Event& e);

private:

	NavMeshData m_navMeshData;
};

#endif//_gkGameObject_h_
