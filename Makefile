CC=gcc
CFLAGS= -Wall -Werror -std=c99

run: build
	./saferm.out



build:
	${CC} saferm.c ${CFLAGS} -o saferm.out


