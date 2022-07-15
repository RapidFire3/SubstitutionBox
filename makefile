CXX 	= g++
CFLAG 	= -std=c++17
EXE 	= bin/sBox_demo
INCLUDE = -Iinclude

SOURCES = src/sbox_demo.cpp 			\
	src/MultiplicativeInverse.cpp 	\
	src/SubstitutionBox.cpp

all: build

build : $(SOURCES)
	$(CXX) -o $(EXE) $(INCLUDE) $(CFLAG) $(SOURCES)

clean: 
	rm $(EXE)
