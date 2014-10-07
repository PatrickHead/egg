AM_CFLAGS = -O3 -I .. -I $(top_srcdir)/include
AM_LDFLAGS =

BUILT_SOURCES = usage-include-files

bin_PROGRAMS = embryo egg-walker egg-mapper

lib_LTLIBRARIES = libegg-parser.la

embryo_SOURCES = embryo.c generator.c map.c
embryo_CFLAGS = ${AM_CFLAGS} ${GRAY_CFLAGS}
embryo_LDADD = libegg-parser.la ${GRAY_LIBS}

egg_mapper_SOURCES = egg-mapper.c map.c
egg_mapper_CFLAGS = ${AM_CFLAGS} ${GRAY_CFLAGS}
egg_mapper_LDADD = libegg-parser.la ${GRAY_LIBS}

egg_walker_SOURCES = egg-walker.c
egg_walker_CFLAGS = ${AM_CFLAGS} ${GRAY_CFLAGS}
egg_walker_LDADD = libegg-parser.la ${GRAY_LIBS}

libegg_parser_la_SOURCES = egg-parser.c egg-token.c egg-token-util.c
libegg_parser_la_LDFLAGS = -release ${PACKAGE_VERSION}

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
