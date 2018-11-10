BINARY = MiniWinSimple

SRCS := $(wildcard src/*.c) \
	$(wildcard ../common/*.c) \
	$(wildcard ../../MiniWin/*.c) \
	$(wildcard ../../MiniWin/bitmaps/*.c) \
	$(wildcard ../../MiniWin/hal/*.c) \
	$(wildcard ../../MiniWin/hal/linux/*.c) \
	$(wildcard ../../MiniWin/ui/*.c) \
	$(wildcard ../../MiniWin/dialogs/*.c) \
	$(wildcard ../../MiniWin/gl/*.c) \
	$(wildcard ../../MiniWin/gl/fonts/*.c)

CC = gcc
CFLAGS = -I../../MiniWin -Isrc -I../common -g -Wall
OBJECTS := $(SRCS:.c=.o)
LIBS = -lX11 -lm -lpthread

all: ${OBJECTS}
	${CC} ${OBJECTS} ${LIBS} -o ${BINARY}
	
clean:
	rm ${BINARY} 
	rm $(OBJECTS)
