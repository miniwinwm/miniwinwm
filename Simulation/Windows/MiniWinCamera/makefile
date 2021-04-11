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

# choose your compiler

# CC = clang
# CPP = clang++
CC = gcc
CPP = g++

CFLAGS = -D_WIN32 -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont -Isrc -I../../../$(PROJECT)_Common -g -Wall -std=c99
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

# different camlib library needed for each compiler
ifeq ($(CPP), clang++)
	LIBS = lib/camlib_opencv_clang.o
else
	LIBS = lib/camlib_opencv.o
endif

LIBS += -Llib -lopencv_core.dll -lopencv_imgproc.dll -lopencv_videoio.dll -lgdi32 

all : $(BINARY)

$(BINARY) : $(OBJS)
	$(CPP) $^ $(LIBS) -o $@ 
	
-include $(DEPS)

%.o : %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	$(RM) $(subst /,\,$(OBJS))
	$(RM) $(subst /,\,$(DEPS))
	$(RM) $(BINARY)
	