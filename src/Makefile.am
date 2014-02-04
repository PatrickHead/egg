AM_CFLAGS = -O3 -I .. -I $(top_srcdir)/include
AM_LDFLAGS =

BUILT_SOURCES = usage-include-files

bin_PROGRAMS = embryo egg-walker egg-mapper

lib_LTLIBRARIES = libegg-common.la libegg-parser.la

LDADD = libegg-common.la libegg-parser.la

embryo_SOURCES = embryo.c generator.c map.c

egg_mapper_SOURCES = egg-mapper.c map.c

egg_walker_SOURCES = egg-walker.c

libegg_common_la_SOURCES = callback.c input.c strapp.c mkdir_p.c
libegg_common_la_LDFLAGS = -version-info 1:0:1

libegg_parser_la_SOURCES = egg-parser.c egg-token.c egg-token-util.c
libegg_parser_la_LDFLAGS = -version-info 1:0:1


.PHONY: timestamps
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

.PHONY: usage-include-files
usage-include-files: embryo-usage.inc egg-mapper-usage.inc egg-walker-usage.inc

all: usage-include-files timestamps all-am

clean-local:
	rm -f *.inc
