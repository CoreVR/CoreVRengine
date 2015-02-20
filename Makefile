COMPILER= g++

SRC_FILES=$(wildcard src/*.cpp)
INCLUDE_FILES=$(wildcard include/*.h)

INCLUDE_FLAGS=-I/home/swagman/Desktop/GameEngine/include

LINKER_FLAGS=-lglfw3 -lGLEW -lX11 -lXrandr -lXi -lXxf86vm -lGL -lpthread -lXinerama -lXcursor
LINK_FLAGS1=$(shell pkg-config --cflags glfw3) 
LINK_FLAGS2=-lGLEW $(shell pkg-config --static --libs glfw3)
COMPILER_SETTINGS=-std=c++11

#nopck:
#	$(COMPILER) -o Core $(SRC_FILES) $(INCLUDE_FLAGS) $(LINKER_FLAGS) $(COMPILER_SETTINGS)

VR:
	$(COMPILER) -DVR $(INCLUDE_FLAGS) $(LINK_FLAGS1) -o Core $(SRC_FILES) $(LINK_FLAGS2) $(COMPILER_SETTINGS)

monitor:
	$(COMPILER) -DNOVR $(INCLUDE_FLAGS) $(LINK_FLAGS1) -o Core $(SRC_FILES) $(LINK_FLAGS2) $(COMPILER_SETTINGS)

debug:
	$(COMPILER) -DNOVR -g $(INCLUDE_FLAGS) $(LINK_FLAGS1) -o Core $(SRC_FILES) $(LINK_FLAGS2) $(COMPILER_SETTINGS)
