CC:=g++
CPPFLAGS:=-std=c++20 -g -O0 -lgtest
BINDIR:=bin

bins:=$(patsubst %.cpp, ${BINDIR}/%, $(wildcard *.cpp))

$(debug ${bins})

all : ${bins}

${BINDIR}/% : %.cpp
	mkdir -p ${BINDIR}
	-${CC} ${CPPFLAGS} -o $@ $(patsubst ${BINDIR}/%, %.cpp, $@)

clean:
	-rm -f ${bins}

compiledb:
	-compiledb make -B -n
