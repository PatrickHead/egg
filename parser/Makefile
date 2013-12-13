CC = gcc
CFLAGS = -g -Wall -Wno-unused-but-set-variable -O0 \
		-I include \
		-I /usr/local/include/egg \
		-I /usr/include/egg \
		-L /usr/local/lib/egg \
		-L ./lib

CFLAGS_ALL = $(CFLAGS)

ifdef EGG_LIBRARY_PATH
	CFLAGS_ALL += -L $(EGG_LIBRARY_PATH)
endif

ifdef EGG_INCLUDE_PATH
	CFLAGS_ALL += -I $(EGG_INCLUDE_PATH)
endif

all: egg-walker

egg-walker: bin/egg-walker

bin/egg-walker: obj/egg-walker.o \
		lib/libegg-parser.so.1.0
	$(CC) $(CFLAGS_ALL) \
		-o bin/egg-walker \
		obj/egg-walker.o \
		-legg-common \
		-legg-parser

libegg-parser: lib/libegg-parser.a lib/libegg-parser.so.1.0

lib/libegg-parser.so.1.0: obj/egg-parser.o \
		obj/egg-token.o \
		obj/egg-token-util.o
	$(CC) $(COPTS) --shared -Wl,-soname,libegg-parser.so.1 \
		-o lib/libegg-parser.so.1.0 \
		obj/egg-parser.o \
		obj/egg-token.o \
		obj/egg-token-util.o
	@(cd lib; ln -sf libegg-parser.so.1.0 libegg-parser.so.1)
	@(cd lib; ln -sf libegg-parser.so.1 libegg-parser.so)

lib/libegg-parser.a: obj/egg-parser.o \
		obj/egg-token.o \
		obj/egg-token-util.o
	ar crD lib/libegg-parser.a \
		obj/egg-parser.o \
		obj/egg-token.o \
		obj/egg-token-util.o

obj/egg-walker.o: src/egg-walker.c \
		include/egg-token.h \
		include/egg-token-type.h \
		include/egg-token-util.h \
		include/egg-parser.h
	$(CC) $(CFLAGS_ALL) \
		-o obj/egg-walker.o \
		-c src/egg-walker.c

obj/egg-parser.o: src/egg-parser.c \
		include/egg-parser.h \
		include/egg-token.h \
		include/egg-token-type.h
	$(CC) $(CFLAGS_ALL) -fPIC\
		-o obj/egg-parser.o \
		-c src/egg-parser.c

obj/egg-token.o: src/egg-token.c \
		include/egg-token.h \
		include/egg-token-type.h \
		include/egg-token-util.h
	$(CC) $(CFLAGS_ALL) -fPIC\
		-o obj/egg-token.o \
		-c src/egg-token.c

obj/egg-token-util.o: src/egg-token-util.c \
		include/egg-token.h \
		include/egg-token-type.h \
		include/egg-token-util.h
	$(CC) $(CFLAGS_ALL) -fPIC\
		-o obj/egg-token-util.o \
		-c src/egg-token-util.c

clean:
	@rm -f obj/*.o
	@rm -f bin/egg-walker

