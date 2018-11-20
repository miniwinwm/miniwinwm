BINARY = BMPConvMono_Linux

SRCS := $(wildcard src/*.cpp) \
	$(wildcard ../EasyBMP/*.cpp)

CXX = g++
CPPFLAGS = -I../EasyBMP -g -Wall
OBJECTS := $(SRCS:.cpp=.o)
LIBS = 

all: ${OBJECTS}
	${CXX} ${OBJECTS} $(CPPFLAGS) ${LIBS} -o ${BINARY}
	
clean:
	rm ${BINARY} 
	rm $(OBJECTS)
