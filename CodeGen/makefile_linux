SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

LDFLAGS = 
CXXFLAGS = -std=c++11 -g

CodeGen: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)
	rm $(OBJ)

.PHONY: clean
clean:
	rm -f CodeGen
