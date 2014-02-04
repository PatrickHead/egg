AM_CFLAGS = -O3 -I .. -I $(top_srcdir)/include
AM_LDFLAGS =

bin_PROGRAMS = embryo egg-walker egg-mapper

lib_LTLIBRARIES = libegg-common.la libegg-parser.la

LDADD = libegg-common.la libegg-parser.la

embryo_SOURCES = embryo.c embryo-usage.inc generator.c map.c

egg_mapper_SOURCES = egg-mapper.c egg-mapper-usage.inc map.c

egg_walker_SOURCES = egg-walker.c egg-walker-usage.inc

libegg_common_la_SOURCES = callback.c input.c strapp.c mkdir_p.c
libegg_common_la_LDFLAGS = -version-info 1:0:1

libegg_parser_la_SOURCES = egg-parser.c egg-token.c egg-token-util.c
libegg_parser_la_LDFLAGS = -version-info 1:0:1

.PHONY: timestamps usage-include-files

timestamps:
	@$(top_srcdir)/tools/auto-timestamp $(top_srcdir)

embryo-usage.inc: $(top_srcdir)/doc/man-pages/embryo.1.txt
	@cat $(top_srcdir)/doc/man-pages/embryo.1.txt \
     | $(top_srcdir)/tools/man2usage > embryo-usage.inc

egg-mapper-usage.inc: $(top_srcdir)/doc/man-pages/egg-mapper.1.txt
	@cat $(top_srcdir)/doc/man-pages/egg-mapper.1.txt \
     | $(top_srcdir)/tools/man2usage > egg-mapper-usage.inc

egg-walker-usage.inc: $(top_srcdir)/doc/man-pages/egg-walker.1.txt
	@cat $(top_srcdir)/doc/man-pages/egg-walker.1.txt \
     | $(top_srcdir)/tools/man2usage > egg-walker-usage.inc

usage-include-files: embryo-usage.inc egg-mapper-usage.inc egg-walker-usage.inc

all: usage-include-files timestamps all-am

clean-local:
	@rm -f *.inc
