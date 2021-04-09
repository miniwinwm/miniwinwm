PROJECT = MiniWinFile

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
CC = gcc
CFLAGS = -D_WIN32 -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont -Isrc -I../../../$(PROJECT)_Common -g -Wall -std=c99
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)
LIBS = -lgdi32

all : $(BINARY)

$(BINARY) : $(OBJS)
	$(CC) $^ $(LIBS) -o $@
	
-include $(DEPS)

%.o : %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	$(RM) $(subst /,\,$(OBJS))
	$(RM) $(subst /,\,$(DEPS))
	$(RM) $(BINARY)
