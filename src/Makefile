.default: all

all: qwirkle

clean:
	rm -rf qwirkle  *.dSYM

qwirkle: *.cpp
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

