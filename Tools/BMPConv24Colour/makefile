SRC := main.cpp ../EasyBMP/EasyBMP.cpp
OBJ = $(SRC:.cpp=.o)

# choose your compiler
# CPP = clang++
CPP = g++
LDFLAGS =
CPPFLAGS = -g -I../EasyBMP

%.o : %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

BMPConv24Colour: ${OBJ}
	${CPP} -o $@ $^ $(LDFLAGS)
	rm $(OBJ)

.PHONY: clean
clean:
	rm -f $(OBJ) BMPConv24Colour


