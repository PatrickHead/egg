ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src include doc tools misc

EXTRA_DIST = AUTHORS ChangeLog COPYING COPYING_DOCUMENTATION INSTALL NEWS README packages

docdir = $(datadir)/doc/@PACKAGE@-@VERSION@
doc_DATA = AUTHORS ChangeLog COPYING INSTALL NEWS README

parser-code: src/embryo
	src/embryo -p egg -g hs -d . doc/.egg \
		--email=patrickhead@gmail.com \
		--author "Patrick Head" \
		--use-doxygen=true \
		--code-version=$$(grep AC_INIT configure.ac | \
											sed -e 's/^[^,]*,\[\(.*\)],.*$$/\1/') \
		--use-external-usage=true

clean-local:
	@if [ -d packages ]; then rm -f packages/*; fi
