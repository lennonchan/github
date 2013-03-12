@ECHO OFF  
@echo 当前目录 %cd%  
  
@ECHO 批编译所有项目
  
SET abi=armeabi

FOR %%F IN (
AnimKit bfBlend bullet 
fbtFile FreeImage GameKitUtils 
lua OgreKitCore OgreMainStatic
OgreRTShaderSystemStatic OIS Plugin_ParticleFXStatic
RenderSystem_GLES2Static ZLib sample
) DO (
cd %%F
copy "%NDK%sources\cxx-stl\gnu-libstdc++\libs\%abi%\libgnustl_static.a" ".\obj\local\%abi%\libgnustl_static.a"
%NDK%/ndk-build.cmd
IF(%%F != sample)
	copy ".\obj\local\%abi%\lib%%F.a" "..\sample\jni\libs\lib%%F.a"
cd ..
)  
  
pause