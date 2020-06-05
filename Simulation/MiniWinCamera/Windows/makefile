BINARY = MiniWinCamera.exe
RM=cmd \/C del

SRCS := $(wildcard src/*.c) \
	$(wildcard ../../../MiniWinCamera_Common/*.c) \
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

CPP = g++
CFLAGS = -D_WIN32 -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont -Isrc -I../../../MiniWinCamera_Common -g -Wall
OBJECTS := $(SRCS:.c=.o)
LIBS = -L. -lopencv_core.dll -lopencv_imgproc.dll -lopencv_videoio.dll -lgdi32

all: gcc_camlib.o ${OBJECTS} 
	$(CPP) $(CFLAGS) gcc_camlib.o ${OBJECTS} ${LIBS} -o ${BINARY}

clean:
	$(RM) $(subst /,\,$(OBJECTS))
	$(RM) ${BINARY}
