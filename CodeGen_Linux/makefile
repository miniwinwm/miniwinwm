src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = 
CXXFLAGS = -std=c++11 -g

CodeGen_Linux: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) CodeGen_Linux
