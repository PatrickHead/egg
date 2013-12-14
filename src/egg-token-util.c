/*!

  \file egg-token-util.c

  \brief Source code for grammer specific token utility functions

  \version 0

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

    \file egg-token-util.c

    This is the source code file for the egg grammar token utility
    functions module.

    The egg_token_type_to_string function is defined in
    this module.

  */

#include <stdlib.h>
#include <string.h>

#include "egg-token.h"
#include "egg-token-util.h"

  /*!

    \brief Returns a string representation of egg_token.

    \warning This function returns a pointer to dynamically allocated memory.
          It is the caller's responsibility to free this memory when
          appropriate.

    \param t egg_token * to egg_token to string-ize

  */

char *egg_token_type_to_string(egg_token *t)
{
  char *s;

  if (!t)
    return NULL;

  switch (t->type)
  {
    case egg_token_type_none:
      s = "<none>";
      break;
    case egg_token_type_nul:
      s = "\x00";
      break;
    case egg_token_type_soh:
      s = "\x01";
      break;
    case egg_token_type_stx:
      s = "\x02";
      break;
    case egg_token_type_etx:
      s = "\x03";
      break;
    case egg_token_type_eot:
      s = "\x04";
      break;
    case egg_token_type_enq:
      s = "\x05";
      break;
    case egg_token_type_ack:
      s = "\x06";
      break;
    case egg_token_type_bel:
      s = "\x07";
      break;
    case egg_token_type_bs:
      s = "\x08";
      break;
    case egg_token_type_ht:
      s = "\x09";
      break;
    case egg_token_type_lf:
      s = "\x0a";
      break;
    case egg_token_type_vt:
      s = "\x0b";
      break;
    case egg_token_type_ff:
      s = "\x0c";
      break;
    case egg_token_type_cr:
      s = "\x0d";
      break;
    case egg_token_type_so:
      s = "\x0e";
      break;
    case egg_token_type_si:
      s = "\x0f";
      break;
    case egg_token_type_dle:
      s = "\x10";
      break;
    case egg_token_type_dc1:
      s = "\x11";
      break;
    case egg_token_type_dc2:
      s = "\x12";
      break;
    case egg_token_type_dc3:
      s = "\x13";
      break;
    case egg_token_type_dc4:
      s = "\x14";
      break;
    case egg_token_type_nak:
      s = "\x15";
      break;
    case egg_token_type_syn:
      s = "\x16";
      break;
    case egg_token_type_etb:
      s = "\x17";
      break;
    case egg_token_type_can:
      s = "\x18";
      break;
    case egg_token_type_em:
      s = "\x19";
      break;
    case egg_token_type_sub:
      s = "\x1a";
      break;
    case egg_token_type_esc:
      s = "\x1b";
      break;
    case egg_token_type_fs:
      s = "\x1c";
      break;
    case egg_token_type_gs:
      s = "\x1d";
      break;
    case egg_token_type_rs:
      s = "\x1e";
      break;
    case egg_token_type_us:
      s = "\x1f";
      break;
    case egg_token_type_space:
      s = "\x20";
      break;
    case egg_token_type_exclamation_point:
      s = "\x21";
      break;
    case egg_token_type_quote:
      s = "\x22";
      break;
    case egg_token_type_number_sign:
      s = "\x23";
      break;
    case egg_token_type_dollar:
      s = "\x24";
      break;
    case egg_token_type_percent:
      s = "\x25";
      break;
    case egg_token_type_ampersand:
      s = "\x26";
      break;
    case egg_token_type_single_quote:
      s = "\x27";
      break;
    case egg_token_type_open_parenthesis:
      s = "\x28";
      break;
    case egg_token_type_close_parenthesis:
      s = "\x29";
      break;
    case egg_token_type_asterisk:
      s = "\x2a";
      break;
    case egg_token_type_plus:
      s = "\x2b";
      break;
    case egg_token_type_comma:
      s = "\x2c";
      break;
    case egg_token_type_minus:
      s = "\x2d";
      break;
    case egg_token_type_period:
      s = "\x2e";
      break;
    case egg_token_type_slash:
      s = "\x2f";
      break;
    case egg_token_type_zero:
      s = "\x30";
      break;
    case egg_token_type_one:
      s = "\x31";
      break;
    case egg_token_type_two:
      s = "\x32";
      break;
    case egg_token_type_three:
      s = "\x33";
      break;
    case egg_token_type_four:
      s = "\x34";
      break;
    case egg_token_type_five:
      s = "\x35";
      break;
    case egg_token_type_six:
      s = "\x36";
      break;
    case egg_token_type_seven:
      s = "\x37";
      break;
    case egg_token_type_eight:
      s = "\x38";
      break;
    case egg_token_type_nine:
      s = "\x39";
      break;
    case egg_token_type_colon:
      s = "\x3a";
      break;
    case egg_token_type_semicolon:
      s = "\x3b";
      break;
    case egg_token_type_less_than:
      s = "\x3c";
      break;
    case egg_token_type_equal:
      s = "\x3d";
      break;
    case egg_token_type_greater_than:
      s = "\x3e";
      break;
    case egg_token_type_question_mark:
      s = "\x3f";
      break;
    case egg_token_type_at:
      s = "\x40";
      break;
    case egg_token_type_A:
      s = "\x41";
      break;
    case egg_token_type_B:
      s = "\x42";
      break;
    case egg_token_type_C:
      s = "\x43";
      break;
    case egg_token_type_D:
      s = "\x44";
      break;
    case egg_token_type_E:
      s = "\x45";
      break;
    case egg_token_type_F:
      s = "\x46";
      break;
    case egg_token_type_G:
      s = "\x47";
      break;
    case egg_token_type_H:
      s = "\x48";
      break;
    case egg_token_type_I:
      s = "\x49";
      break;
    case egg_token_type_J:
      s = "\x4a";
      break;
    case egg_token_type_K:
      s = "\x4b";
      break;
    case egg_token_type_L:
      s = "\x4c";
      break;
    case egg_token_type_M:
      s = "\x4d";
      break;
    case egg_token_type_N:
      s = "\x4e";
      break;
    case egg_token_type_O:
      s = "\x4f";
      break;
    case egg_token_type_P:
      s = "\x50";
      break;
    case egg_token_type_Q:
      s = "\x51";
      break;
    case egg_token_type_R:
      s = "\x52";
      break;
    case egg_token_type_S:
      s = "\x53";
      break;
    case egg_token_type_T:
      s = "\x54";
      break;
    case egg_token_type_U:
      s = "\x55";
      break;
    case egg_token_type_V:
      s = "\x56";
      break;
    case egg_token_type_W:
      s = "\x57";
      break;
    case egg_token_type_X:
      s = "\x58";
      break;
    case egg_token_type_Y:
      s = "\x59";
      break;
    case egg_token_type_Z:
      s = "\x5a";
      break;
    case egg_token_type_open_bracket:
      s = "\x5b";
      break;
    case egg_token_type_back_slash:
      s = "\x5c";
      break;
    case egg_token_type_close_bracket:
      s = "\x5d";
      break;
    case egg_token_type_carat:
      s = "\x5e";
      break;
    case egg_token_type_underscore:
      s = "\x5f";
      break;
    case egg_token_type_back_quote:
      s = "\x60";
      break;
    case egg_token_type_a:
      s = "\x61";
      break;
    case egg_token_type_b:
      s = "\x62";
      break;
    case egg_token_type_c:
      s = "\x63";
      break;
    case egg_token_type_d:
      s = "\x64";
      break;
    case egg_token_type_e:
      s = "\x65";
      break;
    case egg_token_type_f:
      s = "\x66";
      break;
    case egg_token_type_g:
      s = "\x67";
      break;
    case egg_token_type_h:
      s = "\x68";
      break;
    case egg_token_type_i:
      s = "\x69";
      break;
    case egg_token_type_j:
      s = "\x6a";
      break;
    case egg_token_type_k:
      s = "\x6b";
      break;
    case egg_token_type_l:
      s = "\x6c";
      break;
    case egg_token_type_m:
      s = "\x6d";
      break;
    case egg_token_type_n:
      s = "\x6e";
      break;
    case egg_token_type_o:
      s = "\x6f";
      break;
    case egg_token_type_p:
      s = "\x70";
      break;
    case egg_token_type_q:
      s = "\x71";
      break;
    case egg_token_type_r:
      s = "\x72";
      break;
    case egg_token_type_s:
      s = "\x73";
      break;
    case egg_token_type_t:
      s = "\x74";
      break;
    case egg_token_type_u:
      s = "\x75";
      break;
    case egg_token_type_v:
      s = "\x76";
      break;
    case egg_token_type_w:
      s = "\x77";
      break;
    case egg_token_type_x:
      s = "\x78";
      break;
    case egg_token_type_y:
      s = "\x79";
      break;
    case egg_token_type_z:
      s = "\x7a";
      break;
    case egg_token_type_open_brace:
      s = "\x7b";
      break;
    case egg_token_type_bar:
      s = "\x7c";
      break;
    case egg_token_type_close_brace:
      s = "\x7d";
      break;
    case egg_token_type_tilde:
      s = "\x7e";
      break;
    case egg_token_type_del:
      s = "\x7f";
      break;
    case egg_token_type_control_character:
      s = "control-character";
      break;
    case egg_token_type_upper_case_letter:
      s = "upper-case-letter";
      break;
    case egg_token_type_lower_case_letter:
      s = "lower-case-letter";
      break;
    case egg_token_type_letter:
      s = "letter";
      break;
    case egg_token_type_binary_digit:
      s = "binary-digit";
      break;
    case egg_token_type_octal_digit:
      s = "octal-digit";
      break;
    case egg_token_type_decimal_digit:
      s = "decimal-digit";
      break;
    case egg_token_type_hexadecimal_digit:
      s = "hexadecimal-digit";
      break;
    case egg_token_type_white_space:
      s = "white-space";
      break;
    case egg_token_type_common_character:
      s = "common-character";
      break;
    case egg_token_type_literal_character:
      s = "literal-character";
      break;
    case egg_token_type_comment_basic_character:
      s = "comment-basic-character";
      break;
    case egg_token_type_non_comment_start_character:
      s = "non-comment-start-character";
      break;
    case egg_token_type_non_comment_end_character:
      s = "non-comment-end-character";
      break;
    case egg_token_type_non_comment_start_sequence:
      s = "non-comment-start-sequence";
      break;
    case egg_token_type_non_comment_end_sequence:
      s = "non-comment-end-sequence";
      break;
    case egg_token_type_comment_character:
      s = "comment-character";
      break;
    case egg_token_type_single_quoted_character:
      s = "single-quoted-character";
      break;
    case egg_token_type_quoted_character:
      s = "quoted-character";
      break;
    case egg_token_type_phrase_conjugator:
      s = "phrase-conjugator";
      break;
    case egg_token_type_phrase_name_character:
      s = "phrase-name-character";
      break;
    case egg_token_type_binary_indicator:
      s = "binary-indicator";
      break;
    case egg_token_type_octal_indicator:
      s = "octal-indicator";
      break;
    case egg_token_type_hexadecimal_indicator:
      s = "hexadecimal-indicator";
      break;
    case egg_token_type_comment_start_symbol:
      s = "comment-start-symbol";
      break;
    case egg_token_type_comment_end_symbol:
      s = "comment-end-symbol";
      break;
    case egg_token_type_alternation_symbol:
      s = "alternation-symbol";
      break;
    case egg_token_type_concatenation_symbol:
      s = "concatenation-symbol";
      break;
    case egg_token_type_phrase_terminator_symbol:
      s = "phrase-terminator-symbol";
      break;
    case egg_token_type_binary_integer:
      s = "binary-integer";
      break;
    case egg_token_type_octal_integer:
      s = "octal-integer";
      break;
    case egg_token_type_hexadecimal_integer:
      s = "hexadecimal-integer";
      break;
    case egg_token_type_decimal_integer:
      s = "decimal-integer";
      break;
    case egg_token_type_integer:
      s = "integer";
      break;
    case egg_token_type_single_quoted_literal:
      s = "single-quoted-literal";
      break;
    case egg_token_type_quoted_literal:
      s = "quoted-literal";
      break;
    case egg_token_type_absolute_literal:
      s = "absolute-literal";
      break;
    case egg_token_type_literal:
      s = "literal";
      break;
    case egg_token_type_comment_item:
      s = "comment-item";
      break;
    case egg_token_type_comment:
      s = "comment";
      break;
    case egg_token_type_illumination:
      s = "illumination";
      break;
    case egg_token_type_non_grammar_item:
      s = "non-grammar-item";
      break;
    case egg_token_type_non_grammar_element:
      s = "non-grammar-element";
      break;
    case egg_token_type_phrase_name:
      s = "phrase-name";
      break;
    case egg_token_type_quantifier_item:
      s = "quantifier-item";
      break;
    case egg_token_type_quantifier_option:
      s = "quantifier-option";
      break;
    case egg_token_type_quantifier:
      s = "quantifier";
      break;
    case egg_token_type_atom:
      s = "atom";
      break;
    case egg_token_type_item:
      s = "item";
      break;
    case egg_token_type_sequence_continuation:
      s = "sequence-continuation";
      break;
    case egg_token_type_sequence:
      s = "sequence";
      break;
    case egg_token_type_definition_continuation:
      s = "definition-continuation";
      break;
    case egg_token_type_definition:
      s = "definition";
      break;
    case egg_token_type_phrase:
      s = "phrase";
      break;
    case egg_token_type_grammar_element:
      s = "grammar-element";
      break;
    case egg_token_type_grammar:
      s = "grammar";
      break;
  }

  return s;
}

