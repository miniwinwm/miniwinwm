# To build this project you need OpenCV development package installed
# sudo apt install libopencv-dev

PROJECT = MiniWinCamera

BINARY = $(PROJECT)
SRCS := $(wildcard src/*.c) \
	$(wildcard ../../../$(PROJECT)_Common/*.c) \
	$(wildcard ../../../MiniWin/*.c) \
	$(wildcard ../../../MiniWin/bitmaps/*.c) \
	$(wildcard ../../../MiniWin/hal/*.c) \
	$(wildcard ../../../MiniWin/hal/RaspberryPiZeroW/*.c) \
	$(wildcard ../../../MiniWin/ui/*.c) \
	$(wildcard ../../../MiniWin/dialogs/*.c) \
	$(wildcard ../../../MiniWin/gl/*.c) \
	$(wildcard ../../../MiniWin/gl/fonts/bitmapped/*.c) \
	$(wildcard ../../../MiniWin/gl/fonts/truetype/*.c) \
	$(wildcard ../../../MiniWin/gl/fonts/truetype/mcufont/*.c)
CPPSRCS := src/camlib_opencv.cpp
CC = gcc
CPP = g++
CFLAGS = -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont -Isrc -I../../../$(PROJECT)_Common -g -Wall -Os -DRASPBERRY_PI_ZERO_W -std=c99
CPPFLAGS = -I/usr/include/opencv4 -Os -g
OBJS := $(SRCS:.c=.o)
CPPOBJS := $(CPPSRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)
CPPDEPS := $(CPPOBJS:.o=.d)
LIBS = -lm -lpthread -lopencv_core -lopencv_videoio -lopencv_imgproc

all: $(BINARY)

$(BINARY) : $(OBJS) $(CPPOBJS)
	$(CPP) $^ $(LIBS) -o $@
	
-include $(DEPS) $(CPPDEPS)

%.o : %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@
	
%.o : %.cpp
	$(CPP) $(CPPFLAGS) -MMD -c $< -o $@	

clean:
	rm $(OBJS)
	rm $(CPPOBJS)
	rm $(DEPS)
	rm $(CPPDEPS)	
	rm $(BINARY)
