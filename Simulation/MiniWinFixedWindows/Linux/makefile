PROJECT = MiniWinFixedWindows

BINARY = $(PROJECT)
SRCS := $(wildcard src/*.c) \
	$(wildcard ../../../$(PROJECT)_Common/*.c) \
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
CC = gcc
CFLAGS = -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont -Isrc -I../../../$(PROJECT)_Common -g -Wall
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)
LIBS = -lX11 -lm -lpthread

all: $(BINARY)

$(BINARY) : $(OBJS)
	$(CC) $^ $(LIBS) -o $@
	
-include $(DEPS)

%.o : %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm $(OBJS)
	rm $(DEPS)
	rm $(BINARY)