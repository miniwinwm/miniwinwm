PROJECT = MiniWinFreeRTOS

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
	$(wildcard ../../../MiniWin/gl/fonts/truetype/mcufont/*.c) \
	$(wildcard BSP/*.c)
CC = gcc
CFLAGS = -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont -Isrc -I../../../$(PROJECT)_Common -IBSP -g -Wall -Os -DRASPBERRY_PI_ZERO_W
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)
LIBS = -lm -lpthread

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