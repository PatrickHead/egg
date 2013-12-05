CC = gcc
COPTS = -g -Wall -Wno-unused-but-set-variable -O0 -I include

all: egg-walker

egg-walker: bin/egg-walker

bin/egg-walker: obj/egg-walker.o \
		obj/egg-parser.o \
		obj/egg-token.o \
		obj/egg-token-util.o
	$(CC) $(COPTS) -o bin/egg-walker \
		obj/egg-walker.o \
		obj/egg-parser.o \
		obj/egg-token.o \
		obj/egg-token-util.o \
		obj/strapp.o \
		obj/callback.o \
		obj/input.o

obj/egg-walker.o: src/egg-walker.c \
		include/egg-token.h \
		include/egg-token-type.h \
		include/egg-token-util.h \
		include/egg-parser.h
	$(CC) $(COPTS) -o obj/egg-walker.o -c src/egg-walker.c

obj/egg-parser.o: src/egg-parser.c \
		include/egg-parser.h \
		include/egg-token.h \
		include/egg-token-type.h
	$(CC) $(COPTS) -o obj/egg-parser.o -c src/egg-parser.c

obj/egg-token.o: src/egg-token.c \
		include/egg-token.h \
		include/egg-token-type.h \
		include/egg-token-util.h
	$(CC) $(COPTS) -o obj/egg-token.o -c src/egg-token.c

obj/egg-token-util.o: src/egg-token-util.c \
		include/egg-token.h \
		include/egg-token-type.h \
		include/egg-token-util.h
	$(CC) $(COPTS) -o obj/egg-token-util.o -c src/egg-token-util.c

clean:
	@rm -f obj/*.o
	@rm -f bin/egg-walker

