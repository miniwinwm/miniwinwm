BINARY = MiniWinCamera

SRCS := $(wildcard src/*.c) \
	$(wildcard ../../../MiniWinCamera_Common/*.c) \
	$(wildcard ../../../MiniWin/*.c) \
	$(wildcard ../../../MiniWin/bitmaps/*.c) \
	$(wildcard ../../../MiniWin/hal/*.c) \
	$(wildcard ../../../MiniWin/hal/linux/*.c) \
	$(wildcard ../../../MiniWin/ui/*.c) \
	$(wildcard ../../../MiniWin/dialogs/*.c) \
	$(wildcard ../../../MiniWin/gl/*.c) \
	$(wildcard ../../../MiniWin/gl/fonts/bitmapped/*.c) \
	$(wildcard ../../../MiniWin/gl/fonts/truetype/*.c) \
	$(wildcard ../../../MiniWin/gl/fonts/truetype/mcufont/*.c) 

CPP = g++
CFLAGS = -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont -Isrc -I../../../MiniWinCamera_Common -g -Wall
OBJECTS := $(SRCS:.c=.o)
LIBS = -lX11 -lm -lpthread -lopencv_core -lopencv_videoio -lopencv_imgproc

all: camlib_opencv.o ${OBJECTS}
	${CPP} $(CFLAGS) camlib_opencv.o ${OBJECTS} ${LIBS} -o ${BINARY}
	
clean:
	rm $(OBJECTS)
	rm ${BINARY} 

