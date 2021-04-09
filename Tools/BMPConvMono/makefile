SRC := main.cpp ../EasyBMP/EasyBMP.cpp
OBJ = $(SRC:.cpp=.o)

# choose your compiler
# CPP = clang++
CPP = g++
LDFLAGS = 
CPPFLAGS = -g -I../EasyBMP

%.o : %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

BMPConvMono: ${OBJ}
	${CPP} -o $@ $^ $(LDFLAGS)
	rm $(OBJ)
	
.PHONY: clean
clean:
	rm BMPConvMono
