CC:=g++
CPPFLAGS:=-std=c++20 -Wall -Wextra -Werror -pedantic-errors -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wswitch-default -Wfloat-equal -Wshadow -Wsuggest-override -Wcast-qual -Wextra-semi -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -g -O0 -lgtest -ldl
BINDIR:=bin

bins:=$(patsubst %.cpp, ${BINDIR}/%, $(wildcard *.cpp))

$(debug ${bins})

all : ${bins}

${BINDIR}/% : %.cpp leetcode.h
	mkdir -p ${BINDIR}
	-${CC} ${CPPFLAGS} -o $@ $(patsubst ${BINDIR}/%, %.cpp, $@)

clean:
	-rm -f ${bins}

compiledb:
	-compiledb make -B -n
