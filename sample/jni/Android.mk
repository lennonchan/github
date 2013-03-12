LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ZLIB = zlib/adler32.c zlib/compress.c	zlib/crc32.c	zlib/deflate.c zlib/gzio.c zlib/infback.c	zlib/inffast.c zlib/inflate.c zlib/inftrees.c	zlib/trees.c	zlib/uncompr.c zlib/zutil.c
SQLite = sqliteUI5.0/CUI50DBService.cpp sqliteUI5.0/CSqlite3DUI.cpp
HomeSrc = Block.cpp BlenderAnimation.cpp Favorite_Block.cpp  TranslationAnm.cpp  FocusMovePath.cpp  LauncherScene.cpp LauncherSceneEditMode.cpp	LauncherSceneEditMenu.cpp        Recommend_Block.cpp        Movieinfo_Block.cpp        TV_Block.cpp        Videoaudio_Block.cpp	My_Block.cpp	Title_Block.cpp	ViewNode.cpp	Menu.cpp	WallpaperView.cpp	WallpaperViewImpl.cpp	StateBarView.cpp	StateBarViewImpl.cpp
AllAppSrc = AaAppsView.cpp	AaAppsViewImpl.cpp	AaResidentView.cpp	Aaview.cpp	AaViewImpl.cpp	AaViewport.cpp	AppUnit.cpp	AppUnitShortcut.cpp	AppsViewUtil.cpp	DataBaseImpl.cpp	GameObjMaker.cpp	HaResidentView.cpp	HaSettingsView.cpp	HaSettingsViewImpl.cpp	LetterView.cpp	LetterViewImpl.cpp	MenuView.cpp	MenuViewImpl.cpp	RootView.cpp	ScrollbarView.cpp	ScrollViewImpl.cpp	SortordView.cpp	SortordViewImpl.cpp	Sort.cpp	Aabridge.cpp	AaResidentViewImpl.cpp	HaResidentViewImpl.cpp	RootViewImpl.cpp
AaLogicNode = AaEQLogic.cpp   AaMainAppLogic.cpp   AaSortLogic.cpp   AaScrollBarLogic.cpp   AaLetterSortLogic.cpp   AaHitAppLogic.cpp
Builder = AaLogicBuilder.cpp  SceneLogicBuilder.cpp
HomeLogicNode = AppMarketLogic.cpp   BaseLogic.cpp   MenuLogic.cpp   SceneMoveLogic.cpp   StateMachineLogic.cpp   TVLogic.cpp   TVwindowLogic.cpp   ExitLauncherLogic.cpp   UtilKeyLogic.cpp   EditHomeAppLogic.cpp   EQEditHomeAppLogic.cpp   SetBackgroundLogic.cpp
EditLogicNode = EditBaseLogic.cpp	EditBlockMoveLogic.cpp	EditFocusMoveLogic.cpp	EditDeleteAppLogic.cpp	EditDeleteBlockLogic.cpp	EditRenameLogic.cpp	StateEditLogic.cpp
SHARED = Shared/Main.cpp Shared/AndroidLogListener.cpp
LOCAL_MODULE := ogrekit

LOCAL_ARM_MODE   := arm
LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES := $(SQLite) $(HomeSrc) $(AllAppSrc) $(AaLogicNode) $(Builder) $(HomeLogicNode) $(EditLogicNode) $(SHARED)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../OgreKitCore/jni
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../OgreMainStatic/jni/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../bullet/jni
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../OIS/jni/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/tclap
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../GameKitUtils/jni
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../AnimKit/jni

#-lLinearMath -lBulletCollision -lBulletDynamics -lPlugin_ParticleFXStatic -lfreetype 
LOCAL_LDLIBS += -L$(LOCAL_PATH)/libs -lGLESv2 -lOgreKitCore -lbullet -lOgreMainStatic -lFreeImage -OIS -lgnustl_static -lzziplib -lbfBlend -lGameKitUtils  -lRenderSystem_GLES2Static -lOIS -lfbtFile -lAnimKit -lsqlite -lZLib
LOCAL_LDLIBS += -ldl -llog -lgcc

include $(BUILD_SHARED_LIBRARY)
