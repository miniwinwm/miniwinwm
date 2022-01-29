SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

# choose your compiler
# CPP = clang++
CPP = g++
LDFLAGS = 
CPPFLAGS = -std=c++11 -g

%.o : %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

CodeGen: $(OBJ)
	$(CPP) -o $@ $^ $(LDFLAGS)
	rm $(OBJ)

.PHONY: clean
clean:
	rm -f $(OBJ) CodeGen
