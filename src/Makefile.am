CFLAGS = -O3 -I $(top_srcdir)/include
LDFLAGS =

bin_PROGRAMS = embryo egg-walker

lib_LTLIBRARIES = libegg-common.la libegg-parser.la

LDADD = libegg-common.la libegg-parser.la

embryo_SOURCES = embryo.c generator.c map.c

egg_walker_SOURCES = egg-walker.c

libegg_common_la_SOURCES = callback.c input.c strapp.c mkdir_p.c

libegg_parser_la_SOURCES = egg-parser.c egg-token.c egg-token-util.c
