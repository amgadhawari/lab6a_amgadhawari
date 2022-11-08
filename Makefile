CXX=clang++

CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

BINARIES=test

all: ${BINARIES}

test: tddFuncs.o test.o WordCount.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o