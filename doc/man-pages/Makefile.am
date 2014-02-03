EXTRA_DIST = embryo.1.txt

docdir = $(datadir)/doc/@PACKAGE@-@VERSION@

embryo.1.gz: embryo.1.txt
	@if which a2x > /dev/null 2>&1; then a2x -d manpage -f manpage $(srcdir)/embryo.1.txt > /dev/null 2>&1; fi
	@gzip -f embryo.1

embryo.1.pdf: embryo.1.txt
	@if which a2x > /dev/null 2>&1; then a2x -d manpage -f pdf $(srcdir)/embryo.1.txt > /dev/null 2>&1; fi

embryo.1.html: embryo.1.txt
	@if which a2x > /dev/null 2>&1; then a2x -d manpage -f xhtml $(srcdir)/embryo.1.txt > /dev/null 2>&1; fi

embryo.1: embryo.1.gz embryo.1.pdf embryo.1.html

all: embryo.1 all-am

clean-local:
	-rm -f *.1.gz
	-rm -f *.1.pdf
	-rm -f *.1.html
	-rm -f *.css

install-data-local: install-man-local install-pdf-local install-html-local

install-pdf-local:
	@mkdir -p $(docdir)
	@cp *.1.pdf $(docdir)/

install-html-local:
	@mkdir -p $(docdir)/html
	@cp *.1.html $(docdir)/html

install-man-local:
	@mkdir -p $(mandir)/man1
	@cp *.1.gz $(mandir)/man1

uninstall-local:
	@rm -f $(docdir)/*.1.pdf
	@rm -f $(docdir)/html/*.1.html
	@rm -f $(mandir)/man1/embryo.1.gz
