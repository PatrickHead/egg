/*!

  \file egg-token-type.h

  \brief Source code for egg-token-type.h

  \version 20131211163732

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

#ifndef EGG_TOKEN_TYPE_H
#define EGG_TOKEN_TYPE_H

typedef enum
{
  egg_token_type_none,
  egg_token_type_nul,
  egg_token_type_soh,
  egg_token_type_stx,
  egg_token_type_etx,
  egg_token_type_eot,
  egg_token_type_enq,
  egg_token_type_ack,
  egg_token_type_bel,
  egg_token_type_bs,
  egg_token_type_ht,
  egg_token_type_lf,
  egg_token_type_vt,
  egg_token_type_ff,
  egg_token_type_cr,
  egg_token_type_so,
  egg_token_type_si,
  egg_token_type_dle,
  egg_token_type_dc1,
  egg_token_type_dc2,
  egg_token_type_dc3,
  egg_token_type_dc4,
  egg_token_type_nak,
  egg_token_type_syn,
  egg_token_type_etb,
  egg_token_type_can,
  egg_token_type_em,
  egg_token_type_sub,
  egg_token_type_esc,
  egg_token_type_fs,
  egg_token_type_gs,
  egg_token_type_rs,
  egg_token_type_us,
  egg_token_type_space,
  egg_token_type_exclamation_point,
  egg_token_type_quote,
  egg_token_type_number_sign,
  egg_token_type_dollar,
  egg_token_type_percent,
  egg_token_type_ampersand,
  egg_token_type_single_quote,
  egg_token_type_open_parenthesis,
  egg_token_type_close_parenthesis,
  egg_token_type_asterisk,
  egg_token_type_plus,
  egg_token_type_comma,
  egg_token_type_minus,
  egg_token_type_period,
  egg_token_type_slash,
  egg_token_type_zero,
  egg_token_type_one,
  egg_token_type_two,
  egg_token_type_three,
  egg_token_type_four,
  egg_token_type_five,
  egg_token_type_six,
  egg_token_type_seven,
  egg_token_type_eight,
  egg_token_type_nine,
  egg_token_type_colon,
  egg_token_type_semicolon,
  egg_token_type_less_than,
  egg_token_type_equal,
  egg_token_type_greater_than,
  egg_token_type_question_mark,
  egg_token_type_at,
  egg_token_type_A,
  egg_token_type_B,
  egg_token_type_C,
  egg_token_type_D,
  egg_token_type_E,
  egg_token_type_F,
  egg_token_type_G,
  egg_token_type_H,
  egg_token_type_I,
  egg_token_type_J,
  egg_token_type_K,
  egg_token_type_L,
  egg_token_type_M,
  egg_token_type_N,
  egg_token_type_O,
  egg_token_type_P,
  egg_token_type_Q,
  egg_token_type_R,
  egg_token_type_S,
  egg_token_type_T,
  egg_token_type_U,
  egg_token_type_V,
  egg_token_type_W,
  egg_token_type_X,
  egg_token_type_Y,
  egg_token_type_Z,
  egg_token_type_open_bracket,
  egg_token_type_back_slash,
  egg_token_type_close_bracket,
  egg_token_type_carat,
  egg_token_type_underscore,
  egg_token_type_back_quote,
  egg_token_type_a,
  egg_token_type_b,
  egg_token_type_c,
  egg_token_type_d,
  egg_token_type_e,
  egg_token_type_f,
  egg_token_type_g,
  egg_token_type_h,
  egg_token_type_i,
  egg_token_type_j,
  egg_token_type_k,
  egg_token_type_l,
  egg_token_type_m,
  egg_token_type_n,
  egg_token_type_o,
  egg_token_type_p,
  egg_token_type_q,
  egg_token_type_r,
  egg_token_type_s,
  egg_token_type_t,
  egg_token_type_u,
  egg_token_type_v,
  egg_token_type_w,
  egg_token_type_x,
  egg_token_type_y,
  egg_token_type_z,
  egg_token_type_open_brace,
  egg_token_type_bar,
  egg_token_type_close_brace,
  egg_token_type_tilde,
  egg_token_type_del,
  egg_token_type_control_character,
  egg_token_type_upper_case_letter,
  egg_token_type_lower_case_letter,
  egg_token_type_letter,
  egg_token_type_binary_digit,
  egg_token_type_octal_digit,
  egg_token_type_decimal_digit,
  egg_token_type_hexadecimal_digit,
  egg_token_type_white_space,
  egg_token_type_common_character,
  egg_token_type_literal_character,
  egg_token_type_comment_basic_character,
  egg_token_type_non_comment_start_character,
  egg_token_type_non_comment_end_character,
  egg_token_type_non_comment_start_sequence,
  egg_token_type_non_comment_end_sequence,
  egg_token_type_comment_character,
  egg_token_type_single_quoted_character,
  egg_token_type_quoted_character,
  egg_token_type_phrase_conjugator,
  egg_token_type_phrase_name_character,
  egg_token_type_binary_indicator,
  egg_token_type_octal_indicator,
  egg_token_type_hexadecimal_indicator,
  egg_token_type_comment_start_symbol,
  egg_token_type_comment_end_symbol,
  egg_token_type_alternation_symbol,
  egg_token_type_concatenation_symbol,
  egg_token_type_phrase_terminator_symbol,
  egg_token_type_binary_integer,
  egg_token_type_octal_integer,
  egg_token_type_hexadecimal_integer,
  egg_token_type_decimal_integer,
  egg_token_type_integer,
  egg_token_type_single_quoted_literal,
  egg_token_type_quoted_literal,
  egg_token_type_absolute_literal,
  egg_token_type_literal,
  egg_token_type_comment_item,
  egg_token_type_comment,
  egg_token_type_illumination,
  egg_token_type_non_grammar_item,
  egg_token_type_non_grammar_element,
  egg_token_type_phrase_name,
  egg_token_type_quantifier_item,
  egg_token_type_quantifier_option,
  egg_token_type_quantifier,
  egg_token_type_atom,
  egg_token_type_item,
  egg_token_type_sequence_continuation,
  egg_token_type_sequence,
  egg_token_type_definition_continuation,
  egg_token_type_definition,
  egg_token_type_phrase,
  egg_token_type_grammar_element,
  egg_token_type_grammar,
} egg_token_type;

#endif // EGG_TOKEN_TYPE_H
