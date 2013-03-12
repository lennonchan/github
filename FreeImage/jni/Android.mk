LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= FreeImage
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/
LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API
FreeImage = FreeImage/WuQuantizer.cpp FreeImage/BitmapAccess.cpp FreeImage/CacheFile.cpp FreeImage/ColorLookup.cpp FreeImage/Conversion.cpp FreeImage/Conversion16_555.cpp FreeImage/Conversion16_565.cpp FreeImage/Conversion24.cpp FreeImage/Conversion32.cpp FreeImage/Conversion4.cpp FreeImage/Conversion8.cpp FreeImage/ConversionRGBF.cpp \
	FreeImage/ConversionType.cpp FreeImage/FreeImage.cpp FreeImage/FreeImageIO.cpp FreeImage/GetType.cpp FreeImage/Halftoning.cpp FreeImage/J2KHelper.cpp FreeImage/MemoryIO.cpp FreeImage/MultiPage.cpp FreeImage/NNQuantizer.cpp FreeImage/PixelAccess.cpp FreeImage/Plugin.cpp FreeImage/PluginJPEG.cpp FreeImage/PluginPNG.cpp FreeImage/PluginTARGA.cpp FreeImage/ZLibInterface.cpp

LibJPEG = LibJPEG/jaricom.c LibJPEG/jcapimin.c LibJPEG/jcapistd.c LibJPEG/jcarith.c LibJPEG/jccoefct.c LibJPEG/jccolor.c LibJPEG/jcdctmgr.c LibJPEG/jchuff.c LibJPEG/jcinit.c LibJPEG/jcmainct.c LibJPEG/jcmarker.c LibJPEG/jcmaster.c LibJPEG/jcomapi.c LibJPEG/jcparam.c LibJPEG/jcphuff.c LibJPEG/jcprepct.c LibJPEG/jcsample.c LibJPEG/jctrans.c LibJPEG/jdapimin.c LibJPEG/jdapistd.c \
	LibJPEG/jdarith.c LibJPEG/jdatadst.c LibJPEG/jdatasrc.c LibJPEG/jdcoefct.c LibJPEG/jdcolor.c LibJPEG/jddctmgr.c LibJPEG/jdhuff.c LibJPEG/jdinput.c LibJPEG/jdmainct.c LibJPEG/jdmarker.c LibJPEG/jdmaster.c LibJPEG/jdmerge.c LibJPEG/jdphuff.c LibJPEG/jdpostct.c LibJPEG/jdsample.c LibJPEG/jdtrans.c LibJPEG/jerror.c \
	LibJPEG/jfdctflt.c LibJPEG/jfdctfst.c LibJPEG/jfdctint.c LibJPEG/jidctflt.c LibJPEG/jidctfst.c LibJPEG/jidctint.c LibJPEG/jmemansi.c LibJPEG/jmemmgr.c LibJPEG/jquant1.c LibJPEG/jquant2.c LibJPEG/jutils.c LibJPEG/rdbmp.c LibJPEG/rdcolmap.c LibJPEG/rdgif.c LibJPEG/rdppm.c LibJPEG/rdrle.c LibJPEG/rdswitch.c LibJPEG/rdtarga.c \
	LibJPEG/transupp.c LibJPEG/wrbmp.c LibJPEG/wrgif.c LibJPEG/wrppm.c LibJPEG/wrrle.c LibJPEG/wrtarga.c 
LibOpenJPEG = LibOpenJPEG/bio.c LibOpenJPEG/cio.c LibOpenJPEG/dwt.c LibOpenJPEG/event.c LibOpenJPEG/image.c LibOpenJPEG/j2k.c LibOpenJPEG/j2k_lib.c LibOpenJPEG/jp2.c LibOpenJPEG/jpt.c LibOpenJPEG/mct.c LibOpenJPEG/mqc.c LibOpenJPEG/openjpeg.c LibOpenJPEG/pi.c LibOpenJPEG/raw.c LibOpenJPEG/t1.c LibOpenJPEG/t2.c LibOpenJPEG/tcd.c LibOpenJPEG/tgt.c
LibPNG = LibPNG/png.c LibPNG/pngerror.c LibPNG/pnggccrd.c LibPNG/pngget.c LibPNG/pngmem.c LibPNG/pngpread.c LibPNG/pngread.c LibPNG/pngrio.c LibPNG/pngrtran.c LibPNG/pngrutil.c LibPNG/pngset.c LibPNG/pngtrans.c LibPNG/pngvcrd.c LibPNG/pngwio.c LibPNG/pngwrite.c LibPNG/pngwtran.c LibPNG/pngwutil.c
Metadata = Metadata/Exif.cpp Metadata/FIRational.cpp Metadata/FreeImageTag.cpp Metadata/IPTC.cpp Metadata/TagConversion.cpp Metadata/TagLib.cpp Metadata/XTIFF.cpp 
FreeImageToolkit = FreeImageToolkit/BSplineRotate.cpp FreeImageToolkit/Background.cpp FreeImageToolkit/Channels.cpp FreeImageToolkit/ClassicRotate.cpp FreeImageToolkit/Colors.cpp FreeImageToolkit/CopyPaste.cpp FreeImageToolkit/Display.cpp FreeImageToolkit/Flip.cpp FreeImageToolkit/JPEGTransform.cpp FreeImageToolkit/MultigridPoissonSolver.cpp FreeImageToolkit/Rescale.cpp FreeImageToolkit/Resize.cpp

LOCAL_SRC_FILES		:= 	$(FreeImage) $(LibJPEG) $(LibOpenJPEG) $(LibPNG) $(Metadata) $(FreeImageToolkit)

 LOCAL_LDLIBS := -L$(LOCAL_PATH)/../lib -lzlib
 LOCAL_LDLIBS += -ldl -llog -lgcc
include $(BUILD_STATIC_LIBRARY)
