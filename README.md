
egg
===

egg is a free software package that provides the libraries and utilities needed
to produce parsers from EGG input files.   EGG (loosely an acronym for
Expression Grammar, Grammar) files are yet another BNF adaptation.  The intent
of the EGG style BNF is to include the ability to use ANY input coding scheme.
While the ASCII character set is the default, a grammar using any coding can
be described in EGG.  Also, the structure of an EGG file is such that producing
parsers from it is both encouraged and simplified to a great extent.

Many of the ideas and syntax presented in the original BNF, and subsequently
the formal ISO EBNF, and the many variants of ABNF have been incorporated into
the EGG syntax.  EGG is designed to limit the number of syntax options provided
by other extended forms of BNF to those that only produce a more readable form
and a clearer understanding of the presented grammar.  At the same time, EGG
forces the author to abstract almost every element of a grammar into individual
phrases, so that both the grammar definition itself is non-ambiguous, and is
easily translated into a parser.

egg is designed to produce pure recursive descent parsers.  embryo, the utility
included in the egg package is an example of this type of parser generator.

embryo
======

embryo is a generic parser generator that uses the EGG grammar format for
input.  This parser is intended to be able to parse, verify and generate a
grammar parser framework from any grammar defined in EGG.

The resultant parser design uses many of the concepts developed and documented
in tutorial form by Jack W. Crenshaw PHD.  embryo produces pure recursive
descent parsers.

Other code modules are also added to provide utility functionality, such as a
separate grammar framework generation function library, an input source
function library, an input location tracking mechanism, and a callback
mechanism for parsers that need to work "on-the-fly" such as interpreters.

Please note that the embryo parser generator folds the traditional tokenizer
and grammar parser components into one single parser.  While this approach
works well for recursive descent parsers, it is recognized that other types of
parsers such as LR, LALR, etc. will not work this way.  The author of any
grammar in EGG can certainly adapt the tokenizer library portion of EGG to a
different parser style.  This could be accomplished by writing two distinct
grammars.  One for token recognition and the other for grammar syntax, or by
writing one grammar, containing two distinct top-level phrase types, and making
synchronized calls to each parser when needed.   Many possibilities exist for
such needs.

While the embryo parser currently produces correct grammar parsing code and
said code is hopefully quite "unfragile", it is recognized by the creator of
this package that the generated code is far from being the most efficient code
possible.

From a code style viewpoint, the generated code is quite consistent, but
includes a lot of possibly unnecessary code bits that are included either out
of convenience, or to silence a lot of compiler errors and warnings.  Both of
these situations can be remedied by doing more look ahead work to determine
when a parsing function is producing only literal values, only single sequence
phrases, or alternations.  All of these cases can be optimized, sometimes
dramatically, from a code style standpoint.  Doing so should also provide minor
improvements in the run time performance of a parser.

The run time efficiency of the generated code can stand a lot of improvement.
The author has several ideas for providing optimizations, some by user choice
at parser generation time, and others as permanent fixes.  These improvements
will come along in time, as new versions of this package are released.

For more information on installing the egg package, including embryo please
refer to the INSTALL file and other documentation in doc/.

Also, a complete set of user guide, tutorial, manpages, and reference manual
can be built and installed from these sources.

