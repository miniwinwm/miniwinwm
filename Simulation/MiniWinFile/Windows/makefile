BINARY = MiniWinFile.exe
RM=cmd \/C del

SRCS := $(wildcard src/*.c) \
	$(wildcard ../../../MiniWinFile_Common/*.c) \
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
CFLAGS = -D_WIN32 -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont -Isrc -I../../../MiniWinFile_Common -g -Wall
OBJECTS := $(SRCS:.c=.o)
LIBS = -lgdi32

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(BINARY)

clean:
	$(RM) $(subst /,\,$(OBJECTS))
	$(RM) $(BINARY)
