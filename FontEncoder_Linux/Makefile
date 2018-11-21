$(info ************ libfreetype6-dev must be installed ************)
$(info ************ Use this command: apt-get install libfreetype6-dev ************)

CXXFLAGS = -O2 -Wall -Werror -Wno-unused-function -Wno-sign-compare -std=c++0x
CXXFLAGS += -ggdb

ifneq ($(shell uname -s),Darwin)
	LDFLAGS += -pthread
endif

# Libfreetype
CXXFLAGS += $(shell freetype-config --cflags)
LDFLAGS += $(shell freetype-config --libs)

# Class to represent font data internally
OBJS = datafile.o

# Utility functions
OBJS += importtools.o exporttools.o

# Import formats
OBJS += bdf_import.o freetype_import.o

# rlefont export format
OBJS += encode_rlefont.o optimize_rlefont.o export_rlefont.o

# bwfont export format
OBJS += export_bwfont.o

all: mcufont

clean:
	rm -f mcufont $(OBJS) main.o

mcufont: main.o $(OBJS)
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cc *.hh
	g++ $(CXXFLAGS) -c $<
