PROJECT = MiniWinCamera

BINARY = $(PROJECT).exe
RM = cmd \/C del
SRCS := $(wildcard src/*.c) \
	$(wildcard ../../../$(PROJECT)_Common/*.c) \
	$(wildcard ../../../MiniWin/*.c) \
	$(wildcard ../../../MiniWin/bitmaps/*.c) \
	$(wildcard ../../../MiniWin/hal/*.c) \
	$(wildcard ../../../MiniWin/hal/windows/*.c) \
	$(wildcard ../../../MiniWin/ui/*.c) \
	$(wildcard ../../../MiniWin/dialogs/*.c) \
	$(wildcard ../../../MiniWin/gl/*.c) \
	$(wildcard ../../../MiniWin/gl/fonts/bitmapped/*.c) \
	$(wildcard ../../../MiniWin/gl/fonts/truetype/*.c) \
	$(wildcard ../../../MiniWin/gl/fonts/truetype/mcufont/*.c)
CPPSRCS := src/camlib/camlib_opencv.cpp

CC = gcc
CPP = g++

CFLAGS = -D_WIN32 -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont -Isrc -I../../../$(PROJECT)_Common -g -Wall -std=c99
CPPFLAGS = -IC:/msys64/mingw64/include/opencv4
OBJS := $(SRCS:.c=.o)
CPPOBJS := $(CPPSRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)
CPPDEPS := $(CPPOBJS:.o=.d)

LIBS = -lopencv_core.dll -lopencv_imgproc.dll -lopencv_videoio.dll -lgdi32 

all : $(BINARY)

$(BINARY) : $(OBJS) $(CPPOBJS)
	$(CPP) -LC:/msys64/mingw64/lib $^ $(LIBS) -o $@ 
	
-include $(DEPS) $(CPPDEPS)

%.o : %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

%.o : %.cpp
	$(CPP) $(CPPFLAGS) -MMD -c $< -o $@

clean:
	$(RM) $(subst /,\,$(OBJS))
	$(RM) $(subst /,\,$(CPPOBJS))
	$(RM) $(subst /,\,$(DEPS))
	$(RM) $(subst /,\,$(CPPDEPS))
	$(RM) $(BINARY)
	