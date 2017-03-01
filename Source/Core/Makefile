include ../../ThirdParty/PSCommon/BuildSystem/CommonDefs.mak

BIN_DIR = ../../Bin

INC_DIRS = \
	../../Include \
	../../ThirdParty/PSCommon/XnLib/Include \
	../Drivers/OniFile/Formats \
	../../ThirdParty/LibJPEG

SRC_FILES = \
	*.cpp \
	../Drivers/OniFile/Formats/XnCodec.cpp \
	../Drivers/OniFile/Formats/XnStreamCompression.cpp \
	../../ThirdParty/LibJPEG/*.c \

ifeq ("$(OSTYPE)","Darwin")
	INC_DIRS += /opt/local/include
	LIB_DIRS += /opt/local/lib
	LDFLAGS += -framework CoreFoundation -framework IOKit
endif

LIB_NAME = OpenNI2

LIB_DIRS = ../../ThirdParty/PSCommon/XnLib/Bin/$(PLATFORM)-$(CFG)
LIB_DIRS += /usr/lib/x86_64-linux-gnu
LIB_DIRS += /lib/x86_64-linux-gnu
USED_LIBS = XnLib dl pthread udev usb-1.0
ifneq ("$(OSTYPE)","Darwin")
        USED_LIBS += rt  
endif

DEFINES += OPENNI2_EXPORT

CFLAGS += -Wall

LDFLAGS +=  \
	../../Bin/x64-Release/OpenNI2/Drivers/libPS1080.a \
	../../Bin/x64-Release/OpenNI2/Drivers/libDummyDevice.a \
	../../Bin/x64-Release/OpenNI2/Drivers/libOniFile.a \
	../../Bin/x64-Release/OpenNI2/Drivers/libPSLink.a \
	../../Bin/x64-Release/libDepthUtils.a

include ../../ThirdParty/PSCommon/BuildSystem/CommonCppMakefile
