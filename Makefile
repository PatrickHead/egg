SHELL = /bin/sh

.SUFFIXES:

CC = gcc
ifeq ($(DEBUG),on)
  CFLAGS = -g -Wall -O0 -I include -L lib
else
  CFLAGS = -O3 -I include -L lib
endif

CFLAGS_ALL = $(CFLAGS)

#all: embryo tests git docs
all: embryo egg-walker tests git 

tests: test-stdin test-file test-buffer test-callback

embryo: libegg-common libegg-parser bin/embryo

egg-walker: libegg-common libegg-parser bin/egg-walker

bin/embryo: obj/embryo.o \
		obj/generator.o \
		obj/map.o
	$(CC) $(CFLAGS) -o bin/embryo \
		obj/embryo.o \
		obj/generator.o \
		obj/map.o \
		-legg-parser \
		-legg-common

obj/embryo.o: src/embryo.c \
		include/egg-parser.h \
		include/egg-token.h \
		include/egg-token-util.h \
		include/generator.h \
		include/mkdir_p.h
	$(CC) $(CFLAGS) -o obj/embryo.o -c src/embryo.c

bin/egg-walker: obj/egg-walker.o
	$(CC) $(CFLAGS) -o bin/egg-walker \
		obj/egg-walker.o \
		-legg-parser \
		-legg-common

obj/input.o: src/input.c \
		include/input.h \
		include/common.h
	$(CC) $(CFLAGS) -fPIC -o obj/input.o -c src/input.c

obj/generator.o: src/generator.c \
		include/egg-token.h \
		include/egg-token-util.h \
		include/strapp.h \
		include/map.h \
		include/generator.h
	$(CC) $(CFLAGS) -o obj/generator.o -c src/generator.c

obj/map.o: src/map.c \
		include/egg-token.h \
		include/egg-token-util.h \
		include/map.h
	$(CC) $(CFLAGS) -o obj/map.o -c src/map.c

obj/strapp.o: src/strapp.c \
		include/strapp.h
	$(CC) $(CFLAGS) -fPIC -o obj/strapp.o -c src/strapp.c
                  
obj/mkdir_p.o: src/mkdir_p.c
	$(CC) $(CFLAGS) -fPIC -o obj/mkdir_p.o -c src/mkdir_p.c
                  
obj/callback.o: src/callback.c \
		include/callback.h
	$(CC) $(CFLAGS) -fPIC -o obj/callback.o -c src/callback.c

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
	$(CC) $(CFLAGS_ALL) -fPIC \
		-o obj/egg-parser.o \
		-c src/egg-parser.c

obj/egg-token.o: src/egg-token.c \
		include/egg-token.h \
		include/egg-token-type.h \
		include/egg-token-util.h
	$(CC) $(CFLAGS_ALL) -fPIC \
		-o obj/egg-token.o \
		-c src/egg-token.c

obj/egg-token-util.o: src/egg-token-util.c \
		include/egg-token.h \
		include/egg-token-type.h \
		include/egg-token-util.h
	$(CC) $(CFLAGS_ALL) -fPIC\
		-o obj/egg-token-util.o \
		-c src/egg-token-util.c

libegg-common: lib/libegg-common.a lib/libegg-common.so.1.0

lib/libegg-common.so.1.0: obj/callback.o \
		obj/input.o \
		obj/strapp.o \
		obj/mkdir_p.o
	$(CC) $(CFLAGS) --shared -Wl,-soname,libegg-common.so.1 \
		-o lib/libegg-common.so.1.0 \
		obj/callback.o \
		obj/input.o \
		obj/strapp.o \
		obj/mkdir_p.o
	@(cd lib; ln -sf libegg-common.so.1.0 libegg-common.so.1)
	@(cd lib; ln -sf libegg-common.so.1 libegg-common.so)

lib/libegg-common.a: obj/callback.o \
		obj/input.o \
		obj/strapp.o \
		obj/mkdir_p.o
	ar crD lib/libegg-common.a \
		obj/callback.o \
		obj/input.o \
		obj/strapp.o \
		obj/mkdir_p.o
                  
libegg-parser: lib/libegg-parser.a lib/libegg-parser.so.1.0

lib/libegg-parser.so.1.0: obj/egg-parser.o \
		obj/egg-token.o \
		obj/egg-token-util.o
	$(CC) $(CFLAGS) --shared -Wl,-soname,libegg-parser.so.1 \
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

test-callback: test/callback/callback

test/callback/callback: test/callback/callback.o \
		obj/callback.o
	$(CC) $(CFLAGS) -o test/callback/callback \
    				test/callback/callback.o \
    				obj/callback.o

test/callback/callback.o: test/callback/callback.c \
		include/callback.h
	$(CC) $(CFLAGS) -o test/callback/callback.o -c test/callback/callback.c

test-stdin: test/input/stdin

test/input/stdin: test/input/stdin.o \
		obj/input.o
	$(CC) $(CFLAGS) -o test/input/stdin \
    				test/input/stdin.o \
    				obj/input.o

test/input/stdin.o: test/input/stdin.c \
		include/input.h \
		include/common.h
	$(CC) $(CFLAGS) -o test/input/stdin.o -c test/input/stdin.c

test-file: test/input/file

test/input/file: test/input/file.o \
		obj/input.o
	$(CC) $(CFLAGS) -o test/input/file \
		test/input/file.o \
		obj/input.o

test/input/file.o: test/input/file.c \
		include/input.h \
		include/common.h
	$(CC) $(CFLAGS) -o test/input/file.o -c test/input/file.c

test-buffer: test/input/buffer

test/input/buffer: test/input/buffer.o \
		obj/input.o
	$(CC) $(CFLAGS) -o test/input/buffer \
		test/input/buffer.o \
		obj/input.o

test/input/buffer.o: test/input/buffer.c \
		include/input.h \
		include/common.h
	$(CC) $(CFLAGS) -o test/input/buffer.o -c test/input/buffer.c

parser-code:
	bin/embryo -p egg -g hs -d . doc/.egg \
		--email=patrickhead@gmail.com \
		--author "Patrick Head" \
		--use-doxygen=true

docs: printable-egg egg-pdf reference-manual

egg-pdf: doc/egg.pdf

doc/egg.pdf: doc/printable.egg
	@echo Creating doc/egg.pdf
	@enscript -q -t egg.pdf -B -sPAPERSIZE=letter -o - doc/printable.egg | \
		ps2pdf -q - doc/egg.pdf

printable-egg: doc/printable.egg

doc/printable.egg: doc/.egg
	@echo Creating doc/printable.egg
	@pr -F -W 70 -o 10 -h "EGG Grammar Definition" \
		-D "$$(date -r doc/.egg +'rev. %Y%m%d')" doc/.egg > doc/printable.egg

reference-manual: doc/reference-manual/latex/refman.tex

doc/reference-manual/latex/refman.tex: doc/reference-manual/doxygen.cfg \
    doc/reference-manual/DoxygenLayout.xml \
		include/*.h \
		src/*.c \
    doc/reference-manual/.regen
	@echo Making Reference Manual
	@doxygen doc/reference-manual/doxygen.cfg > /dev/null
	@(cd doc/reference-manual/latex; make) > /dev/null
	@(cd doc/reference-manual/html; scp -r * root@phs1:/var/www/htdocs) > /dev/null

doc/reference-manual/.regen:
	@touch doc/reference-manual/.regen

code-stats:
	@wc -l include/*.h src/*.c test/*/*.c doc/[A-Z]* doc/.egg misc/* Makefile

clean:
	@rm -f bin/embryo
	@rm -f bin/egg-walker
	@rm -f obj/*.o
	@rm -f lib/*
	@rm -f test/input/stdin
	@rm -f test/input/buffer
	@rm -f test/input/file
	@rm -f test/input/*.o
	@rm -f test/token/token
	@rm -f test/token/*.o
	@rm -f doc/printable.egg
	@rm -f doc/egg.pdf
	@rm -rf doc/reference-manual/html
	@rm -rf doc/reference-manual/latex
	@rm -rf doc/reference-manual/man
	@rm -rf doc/reference-manual/xml

timestamp:
	@tools/auto-timestamp.sh
	@touch doc/reference-manual/.regen

git: .git

.git:
	@git init
	@git add Makefile
	@git add README
	@git add doc/.egg
	@git add doc/INSTALL
	@git add doc/LICENSE
	@git add doc/PROJECT
	@git add doc/README
	@git add doc/TODOS
	@git add doc/VERSION
	@git add doc/reference-document/doxygen.cfg
	@git add doc/reference-document/DoxygenLayout.xml
	@git add include/*
	@git add src/*
	@git add examples/*
	@git add misc/*
	@git add tools/*
	@git add test/input/*.c
	@git add test/callback/*.c

commit: timestamp
	git commit -a

push:
	git push backup master
	git push brawndo master
