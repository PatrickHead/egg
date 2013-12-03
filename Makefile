CC = gcc
COPTS = -g -Wall -O0 -I include -I parser/include

all: embryo tests printable-egg egg-pdf git

_parser: obj/input.o \
		obj/strapp.o
	@(cd parser/include; ln -fs ../../include/common.h)
	@(cd parser/include; ln -fs ../../include/input.h)
	@(cd parser/include; ln -fs ../../include/strapp.h)
	@(cd parser/obj; ln -fs ../../obj/input.o)
	@(cd parser/obj; ln -fs ../../obj/strapp.o)
	@make --no-print-directory -C parser

tests: test-stdin test-file test-buffer

embryo: _parser bin/embryo

bin/embryo: obj/embryo.o \
		obj/generator.o \
		obj/map.o \
		obj/mkdir_p.o
	$(CC) $(COPTS) -o bin/embryo \
		obj/embryo.o \
		obj/generator.o \
		obj/map.o \
		obj/mkdir_p.o \
		parser/obj/egg-parser.o \
		parser/obj/egg-token.o \
		parser/obj/egg-token-util.o \
		obj/input.o \
		obj/strapp.o

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
	$(CC) $(COPTS) -o obj/input.o -c src/input.c

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
	$(CC) $(COPTS) -o obj/strapp.o -c src/strapp.c
                  
obj/mkdir_p.o: src/mkdir_p.c
	$(CC) $(COPTS) -o obj/mkdir_p.o -c src/mkdir_p.c
                  
obj/callback.o: src/callback.c \
		include/callback.h
	$(CC) $(COPTS) -o obj/callback.o -c src/callback.c
                  
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

lcp: list-checkpoints

list-checkpoints:
	@(for cp in $$(ls check-points); \
    do \
    jd=$$(echo $$cp | cut -d'.' -f2); \
    echo $$(date --date=@$$jd) - $$cp; \
    done)

cp: checkpoint

checkpoint:
	@mkdir -p check-points
	@tar czf check-points/embryo."$$(date +'%s')".tgz --exclude=check-points .

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
	@make --no-print-directory -C parser clean

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
	@git add include/
	@git add src/
	@git add examples/
	@git add misc/
	@git add test/input/*.c
	@git add parser/Makefile
	@git add parser/src
	@git add parser/include

commit:
	git commit -a

push:
	git push backup master
