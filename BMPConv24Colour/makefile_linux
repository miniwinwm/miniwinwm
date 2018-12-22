SRC := main.cpp ../EasyBMP/EasyBMP.cpp
OBJ = $(SRC:.cpp=.o)

LDFLAGS = 
CXXFLAGS = -g -I../EasyBMP

BMPConv24Colour: ${OBJ}
	${CXX} -o $@ $^ $(LDFLAGS)
	rm $(OBJ)
	
.PHONY: clean
clean:
	rm BMPConv24Colour
