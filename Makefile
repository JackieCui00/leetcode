CXX := g++

CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -pedantic-errors -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wswitch-default -Wfloat-equal -Wshadow -Wsuggest-override -Wcast-qual -Wextra-semi -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -g -O0 -lgtest -ldl 

ifeq ($(shell uname -s), Darwin)
    CXXFLAGS += -I/opt/homebrew/include -D_GNU_SOURCE -L/opt/homebrew/lib/
    CXX := clang++
endif

BINDIR:=bin

bins:=$(patsubst %.cpp, ${BINDIR}/%, $(wildcard *.cpp))

$(debug ${bins})

all : ${bins}

${BINDIR}/% : %.cpp leetcode.h
	mkdir -p ${BINDIR}
	-${CXX} ${CXXFLAGS} -o $@ $(patsubst ${BINDIR}/%, %.cpp, $@)

clean:
	-rm -f ${bins}

compiledb:
	-compiledb make -B -n
