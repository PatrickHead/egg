/*!

  \file egg-parser.h

  \brief Source code for egg-parser.h

  \version 20131212072057

  \author Patrick Head mailto:patrickhead@gmail.com

  \copyright Copyright (C) 2013 Patrick Head

  \license
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.\n
  \n
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.\n
  \n
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see   \<http://www.gnu.org/licenses/\>.

*/

  /*!

    \file egg-parser.h

    This is the header file for the egg grammar phrase parsing
    functions module.

    An individual phrase parsing function exists for each
    egg grammar phrase.

    Also the egg_get_callback_table function is defined in
    this module.

  */

#ifndef EGG_PARSER_H
#define EGG_PARSER_H

#include "callback.h"

callback_table *egg_get_callback_table(void);

egg_token *nul(void);
egg_token *soh(void);
egg_token *stx(void);
egg_token *etx(void);
egg_token *eot(void);
egg_token *enq(void);
egg_token *ack(void);
egg_token *bel(void);
egg_token *bs(void);
egg_token *ht(void);
egg_token *lf(void);
egg_token *vt(void);
egg_token *ff(void);
egg_token *cr(void);
egg_token *so(void);
egg_token *si(void);
egg_token *dle(void);
egg_token *dc1(void);
egg_token *dc2(void);
egg_token *dc3(void);
egg_token *dc4(void);
egg_token *nak(void);
egg_token *syn(void);
egg_token *etb(void);
egg_token *can(void);
egg_token *em(void);
egg_token *sub(void);
egg_token *esc(void);
egg_token *fs(void);
egg_token *gs(void);
egg_token *rs(void);
egg_token *us(void);
egg_token *space(void);
egg_token *exclamation_point(void);
egg_token *quote(void);
egg_token *number_sign(void);
egg_token *dollar(void);
egg_token *percent(void);
egg_token *ampersand(void);
egg_token *single_quote(void);
egg_token *open_parenthesis(void);
egg_token *close_parenthesis(void);
egg_token *asterisk(void);
egg_token *plus(void);
egg_token *comma(void);
egg_token *minus(void);
egg_token *period(void);
egg_token *slash(void);
egg_token *zero(void);
egg_token *one(void);
egg_token *two(void);
egg_token *three(void);
egg_token *four(void);
egg_token *five(void);
egg_token *six(void);
egg_token *seven(void);
egg_token *eight(void);
egg_token *nine(void);
egg_token *colon(void);
egg_token *semicolon(void);
egg_token *less_than(void);
egg_token *equal(void);
egg_token *greater_than(void);
egg_token *question_mark(void);
egg_token *at(void);
egg_token *A(void);
egg_token *B(void);
egg_token *C(void);
egg_token *D(void);
egg_token *E(void);
egg_token *F(void);
egg_token *G(void);
egg_token *H(void);
egg_token *I(void);
egg_token *J(void);
egg_token *K(void);
egg_token *L(void);
egg_token *M(void);
egg_token *N(void);
egg_token *O(void);
egg_token *P(void);
egg_token *Q(void);
egg_token *R(void);
egg_token *S(void);
egg_token *T(void);
egg_token *U(void);
egg_token *V(void);
egg_token *W(void);
egg_token *X(void);
egg_token *Y(void);
egg_token *Z(void);
egg_token *open_bracket(void);
egg_token *back_slash(void);
egg_token *close_bracket(void);
egg_token *carat(void);
egg_token *underscore(void);
egg_token *back_quote(void);
egg_token *a(void);
egg_token *b(void);
egg_token *c(void);
egg_token *d(void);
egg_token *e(void);
egg_token *f(void);
egg_token *g(void);
egg_token *h(void);
egg_token *i(void);
egg_token *j(void);
egg_token *k(void);
egg_token *l(void);
egg_token *m(void);
egg_token *n(void);
egg_token *o(void);
egg_token *p(void);
egg_token *q(void);
egg_token *r(void);
egg_token *s(void);
egg_token *t(void);
egg_token *u(void);
egg_token *v(void);
egg_token *w(void);
egg_token *x(void);
egg_token *y(void);
egg_token *z(void);
egg_token *open_brace(void);
egg_token *bar(void);
egg_token *close_brace(void);
egg_token *tilde(void);
egg_token *del(void);
egg_token *control_character(void);
egg_token *upper_case_letter(void);
egg_token *lower_case_letter(void);
egg_token *letter(void);
egg_token *binary_digit(void);
egg_token *octal_digit(void);
egg_token *decimal_digit(void);
egg_token *hexadecimal_digit(void);
egg_token *white_space(void);
egg_token *common_character(void);
egg_token *literal_character(void);
egg_token *comment_basic_character(void);
egg_token *non_comment_start_character(void);
egg_token *non_comment_end_character(void);
egg_token *non_comment_start_sequence(void);
egg_token *non_comment_end_sequence(void);
egg_token *comment_character(void);
egg_token *single_quoted_character(void);
egg_token *quoted_character(void);
egg_token *phrase_conjugator(void);
egg_token *phrase_name_character(void);
egg_token *binary_indicator(void);
egg_token *octal_indicator(void);
egg_token *hexadecimal_indicator(void);
egg_token *comment_start_symbol(void);
egg_token *comment_end_symbol(void);
egg_token *alternation_symbol(void);
egg_token *concatenation_symbol(void);
egg_token *phrase_terminator_symbol(void);
egg_token *binary_integer(void);
egg_token *octal_integer(void);
egg_token *hexadecimal_integer(void);
egg_token *decimal_integer(void);
egg_token *integer(void);
egg_token *single_quoted_literal(void);
egg_token *quoted_literal(void);
egg_token *absolute_literal(void);
egg_token *literal(void);
egg_token *comment_item(void);
egg_token *comment(void);
egg_token *illumination(void);
egg_token *non_grammar_item(void);
egg_token *non_grammar_element(void);
egg_token *phrase_name(void);
egg_token *quantifier_item(void);
egg_token *quantifier_option(void);
egg_token *quantifier(void);
egg_token *atom(void);
egg_token *item(void);
egg_token *sequence_continuation(void);
egg_token *sequence(void);
egg_token *definition_continuation(void);
egg_token *definition(void);
egg_token *phrase(void);
egg_token *grammar_element(void);
egg_token *grammar(void);

#endif // EGG_PARSER_H
