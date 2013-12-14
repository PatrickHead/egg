SHELL = /bin/sh

.SUFFIXES:

CC = gcc
ifeq ($(DEBUG),on)
  COPTS = -g -Wall -O0 -I include -I parser/include -L lib
else
  COPTS = -O3 -I include -I parser/include -L lib
endif

#all: embryo tests git docs
all: embryo tests git 

_parser: libegg-common
	@EGG_LIBRARY_PATH=../lib \
		EGG_INCLUDE_PATH=../include \
		make --no-print-directory -C parser

tests: test-stdin test-file test-buffer test-callback

embryo: _parser libegg-common bin/embryo

bin/embryo: obj/embryo.o \
		obj/generator.o \
		obj/map.o
	$(CC) $(COPTS) -o bin/embryo \
		obj/embryo.o \
		obj/generator.o \
		obj/map.o \
		parser/obj/egg-parser.o \
		parser/obj/egg-token.o \
		parser/obj/egg-token-util.o \
		-legg-common

obj/embryo.o: src/embryo.c \
		parser/include/egg-parser.h \
		parser/include/egg-token.h \
		parser/include/egg-token-util.h \
		include/generator.h \
		include/mkdir_p.h
	$(CC) $(COPTS) -o obj/embryo.o -c src/embryo.c

obj/egg-parser.o: src/egg-parser.c \
		include/egg-parser.h \
		include/token.h
	$(CC) $(COPTS) -o obj/egg-parser.o -c src/egg-parser.c

obj/token.o: src/token.c \
		include/token.h \
		include/token-type.h
	$(CC) $(COPTS) -o obj/token.o -c src/token.c

obj/token-util.o: src/token-util.c \
		include/token.h \
		include/token-type.h \
		include/token-util.h
	$(CC) $(COPTS) -o obj/token-util.o -c src/token-util.c

obj/input.o: src/input.c \
		include/input.h \
		include/common.h
	$(CC) $(COPTS) -fPIC -o obj/input.o -c src/input.c

obj/generator.o: src/generator.c \
		parser/include/egg-token.h \
		parser/include/egg-token-util.h \
		include/strapp.h \
		include/map.h \
		include/generator.h
	$(CC) $(COPTS) -o obj/generator.o -c src/generator.c

obj/map.o: src/map.c \
		parser/include/egg-token.h \
		parser/include/egg-token-util.h \
		include/map.h
	$(CC) $(COPTS) -o obj/map.o -c src/map.c

obj/strapp.o: src/strapp.c \
		include/strapp.h
	$(CC) $(COPTS) -fPIC -o obj/strapp.o -c src/strapp.c
                  
obj/mkdir_p.o: src/mkdir_p.c
	$(CC) $(COPTS) -fPIC -o obj/mkdir_p.o -c src/mkdir_p.c
                  
obj/callback.o: src/callback.c \
		include/callback.h
	$(CC) $(COPTS) -fPIC -o obj/callback.o -c src/callback.c

libegg-common: lib/libegg-common.a lib/libegg-common.so.1.0

lib/libegg-common.so.1.0: obj/callback.o \
		obj/input.o \
		obj/strapp.o \
		obj/mkdir_p.o
	$(CC) $(COPTS) --shared -Wl,-soname,libegg-common.so.1 \
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
                  
test-callback: test/callback/callback

test/callback/callback: test/callback/callback.o \
		obj/callback.o
	$(CC) $(COPTS) -o test/callback/callback \
    				test/callback/callback.o \
    				obj/callback.o

test/callback/callback.o: test/callback/callback.c \
		include/callback.h
	$(CC) $(COPTS) -o test/callback/callback.o -c test/callback/callback.c

test-stdin: test/input/stdin

test/input/stdin: test/input/stdin.o \
		obj/input.o
	$(CC) $(COPTS) -o test/input/stdin \
    				test/input/stdin.o \
    				obj/input.o

test/input/stdin.o: test/input/stdin.c \
		include/input.h \
		include/common.h
	$(CC) $(COPTS) -o test/input/stdin.o -c test/input/stdin.c

test-file: test/input/file

test/input/file: test/input/file.o \
		obj/input.o
	$(CC) $(COPTS) -o test/input/file \
		test/input/file.o \
		obj/input.o

test/input/file.o: test/input/file.c \
		include/input.h \
		include/common.h
	$(CC) $(COPTS) -o test/input/file.o -c test/input/file.c

test-buffer: test/input/buffer

test/input/buffer: test/input/buffer.o \
		obj/input.o
	$(CC) $(COPTS) -o test/input/buffer \
		test/input/buffer.o \
		obj/input.o

test/input/buffer.o: test/input/buffer.c \
		include/input.h \
		include/common.h
	$(CC) $(COPTS) -o test/input/buffer.o -c test/input/buffer.c

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
		parser/include/*.h \
		parser/src/*.c \
    doc/reference-manual/.regen
	@echo Making Reference Manual
	@doxygen doc/reference-manual/doxygen.cfg > /dev/null
	@(cd doc/reference-manual/latex; make) > /dev/null
	@(cd doc/reference-manual/html; scp -r * root@phs1:/var/www/htdocs) > /dev/null

doc/reference-manual/.regen:
	@touch doc/reference-manual/.regen

code-stats:
	@wc -l include/*.h src/*.c parser/include/*.h parser/src/*.c test/*/*.c doc/[A-Z]* doc/.egg misc/* Makefile parser/Makefile

clean:
	@rm -f bin/embryo
	@rm -f obj/*.o
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
	@make --no-print-directory -C parser clean

version:
	@misc/auto-version.sh
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
	@git add include/
	@git add src/
	@git add examples/
	@git add misc/
	@git add test/input/*.c
	@git add test/callback/*.c
	@git add parser/Makefile
	@git add parser/src
	@git add parser/include

commit: version
	git commit -a

push:
	git push backup master
	git push brawndo master
