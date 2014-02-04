/*!

  @file egg-token-type.h

  @brief Source code for egg-token-type.h

  @version 0.4.0

  @author Patrick Head mailto:patrickhead@gmail.com

  @copyright Copyright (C) 2013-2014 Patrick Head

  @license
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.@n
  @n
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.@n
  @n
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see   \<http://www.gnu.org/licenses/\>.

*/

  /*!

    @file egg-token-type.h

    This is the header file for the egg grammar token type definitions

    Each egg grammar phrase has an associated token type

  */

#ifndef EGG_TOKEN_TYPE_H
#define EGG_TOKEN_TYPE_H

  /*!
    @brief Definition of allowed token types for egg_token.
  */

typedef enum
{
    /*! @brief Special token type for unknown tokens */
  egg_token_type_none,
    /*! @brief Token type for nul phrase*/
  egg_token_type_nul,
    /*! @brief Token type for soh phrase*/
  egg_token_type_soh,
    /*! @brief Token type for stx phrase*/
  egg_token_type_stx,
    /*! @brief Token type for etx phrase*/
  egg_token_type_etx,
    /*! @brief Token type for eot phrase*/
  egg_token_type_eot,
    /*! @brief Token type for enq phrase*/
  egg_token_type_enq,
    /*! @brief Token type for ack phrase*/
  egg_token_type_ack,
    /*! @brief Token type for bel phrase*/
  egg_token_type_bel,
    /*! @brief Token type for bs phrase*/
  egg_token_type_bs,
    /*! @brief Token type for ht phrase*/
  egg_token_type_ht,
    /*! @brief Token type for lf phrase*/
  egg_token_type_lf,
    /*! @brief Token type for vt phrase*/
  egg_token_type_vt,
    /*! @brief Token type for ff phrase*/
  egg_token_type_ff,
    /*! @brief Token type for cr phrase*/
  egg_token_type_cr,
    /*! @brief Token type for so phrase*/
  egg_token_type_so,
    /*! @brief Token type for si phrase*/
  egg_token_type_si,
    /*! @brief Token type for dle phrase*/
  egg_token_type_dle,
    /*! @brief Token type for dc1 phrase*/
  egg_token_type_dc1,
    /*! @brief Token type for dc2 phrase*/
  egg_token_type_dc2,
    /*! @brief Token type for dc3 phrase*/
  egg_token_type_dc3,
    /*! @brief Token type for dc4 phrase*/
  egg_token_type_dc4,
    /*! @brief Token type for nak phrase*/
  egg_token_type_nak,
    /*! @brief Token type for syn phrase*/
  egg_token_type_syn,
    /*! @brief Token type for etb phrase*/
  egg_token_type_etb,
    /*! @brief Token type for can phrase*/
  egg_token_type_can,
    /*! @brief Token type for em phrase*/
  egg_token_type_em,
    /*! @brief Token type for sub phrase*/
  egg_token_type_sub,
    /*! @brief Token type for esc phrase*/
  egg_token_type_esc,
    /*! @brief Token type for fs phrase*/
  egg_token_type_fs,
    /*! @brief Token type for gs phrase*/
  egg_token_type_gs,
    /*! @brief Token type for rs phrase*/
  egg_token_type_rs,
    /*! @brief Token type for us phrase*/
  egg_token_type_us,
    /*! @brief Token type for space phrase*/
  egg_token_type_space,
    /*! @brief Token type for exclamation-point phrase*/
  egg_token_type_exclamation_point,
    /*! @brief Token type for quote phrase*/
  egg_token_type_quote,
    /*! @brief Token type for number-sign phrase*/
  egg_token_type_number_sign,
    /*! @brief Token type for dollar phrase*/
  egg_token_type_dollar,
    /*! @brief Token type for percent phrase*/
  egg_token_type_percent,
    /*! @brief Token type for ampersand phrase*/
  egg_token_type_ampersand,
    /*! @brief Token type for single-quote phrase*/
  egg_token_type_single_quote,
    /*! @brief Token type for open-parenthesis phrase*/
  egg_token_type_open_parenthesis,
    /*! @brief Token type for close-parenthesis phrase*/
  egg_token_type_close_parenthesis,
    /*! @brief Token type for asterisk phrase*/
  egg_token_type_asterisk,
    /*! @brief Token type for plus phrase*/
  egg_token_type_plus,
    /*! @brief Token type for comma phrase*/
  egg_token_type_comma,
    /*! @brief Token type for minus phrase*/
  egg_token_type_minus,
    /*! @brief Token type for period phrase*/
  egg_token_type_period,
    /*! @brief Token type for slash phrase*/
  egg_token_type_slash,
    /*! @brief Token type for zero phrase*/
  egg_token_type_zero,
    /*! @brief Token type for one phrase*/
  egg_token_type_one,
    /*! @brief Token type for two phrase*/
  egg_token_type_two,
    /*! @brief Token type for three phrase*/
  egg_token_type_three,
    /*! @brief Token type for four phrase*/
  egg_token_type_four,
    /*! @brief Token type for five phrase*/
  egg_token_type_five,
    /*! @brief Token type for six phrase*/
  egg_token_type_six,
    /*! @brief Token type for seven phrase*/
  egg_token_type_seven,
    /*! @brief Token type for eight phrase*/
  egg_token_type_eight,
    /*! @brief Token type for nine phrase*/
  egg_token_type_nine,
    /*! @brief Token type for colon phrase*/
  egg_token_type_colon,
    /*! @brief Token type for semicolon phrase*/
  egg_token_type_semicolon,
    /*! @brief Token type for less-than phrase*/
  egg_token_type_less_than,
    /*! @brief Token type for equal phrase*/
  egg_token_type_equal,
    /*! @brief Token type for greater-than phrase*/
  egg_token_type_greater_than,
    /*! @brief Token type for question-mark phrase*/
  egg_token_type_question_mark,
    /*! @brief Token type for at phrase*/
  egg_token_type_at,
    /*! @brief Token type for A phrase*/
  egg_token_type_A,
    /*! @brief Token type for B phrase*/
  egg_token_type_B,
    /*! @brief Token type for C phrase*/
  egg_token_type_C,
    /*! @brief Token type for D phrase*/
  egg_token_type_D,
    /*! @brief Token type for E phrase*/
  egg_token_type_E,
    /*! @brief Token type for F phrase*/
  egg_token_type_F,
    /*! @brief Token type for G phrase*/
  egg_token_type_G,
    /*! @brief Token type for H phrase*/
  egg_token_type_H,
    /*! @brief Token type for I phrase*/
  egg_token_type_I,
    /*! @brief Token type for J phrase*/
  egg_token_type_J,
    /*! @brief Token type for K phrase*/
  egg_token_type_K,
    /*! @brief Token type for L phrase*/
  egg_token_type_L,
    /*! @brief Token type for M phrase*/
  egg_token_type_M,
    /*! @brief Token type for N phrase*/
  egg_token_type_N,
    /*! @brief Token type for O phrase*/
  egg_token_type_O,
    /*! @brief Token type for P phrase*/
  egg_token_type_P,
    /*! @brief Token type for Q phrase*/
  egg_token_type_Q,
    /*! @brief Token type for R phrase*/
  egg_token_type_R,
    /*! @brief Token type for S phrase*/
  egg_token_type_S,
    /*! @brief Token type for T phrase*/
  egg_token_type_T,
    /*! @brief Token type for U phrase*/
  egg_token_type_U,
    /*! @brief Token type for V phrase*/
  egg_token_type_V,
    /*! @brief Token type for W phrase*/
  egg_token_type_W,
    /*! @brief Token type for X phrase*/
  egg_token_type_X,
    /*! @brief Token type for Y phrase*/
  egg_token_type_Y,
    /*! @brief Token type for Z phrase*/
  egg_token_type_Z,
    /*! @brief Token type for open-bracket phrase*/
  egg_token_type_open_bracket,
    /*! @brief Token type for back-slash phrase*/
  egg_token_type_back_slash,
    /*! @brief Token type for close-bracket phrase*/
  egg_token_type_close_bracket,
    /*! @brief Token type for carat phrase*/
  egg_token_type_carat,
    /*! @brief Token type for underscore phrase*/
  egg_token_type_underscore,
    /*! @brief Token type for back-quote phrase*/
  egg_token_type_back_quote,
    /*! @brief Token type for a phrase*/
  egg_token_type_a,
    /*! @brief Token type for b phrase*/
  egg_token_type_b,
    /*! @brief Token type for c phrase*/
  egg_token_type_c,
    /*! @brief Token type for d phrase*/
  egg_token_type_d,
    /*! @brief Token type for e phrase*/
  egg_token_type_e,
    /*! @brief Token type for f phrase*/
  egg_token_type_f,
    /*! @brief Token type for g phrase*/
  egg_token_type_g,
    /*! @brief Token type for h phrase*/
  egg_token_type_h,
    /*! @brief Token type for i phrase*/
  egg_token_type_i,
    /*! @brief Token type for j phrase*/
  egg_token_type_j,
    /*! @brief Token type for k phrase*/
  egg_token_type_k,
    /*! @brief Token type for l phrase*/
  egg_token_type_l,
    /*! @brief Token type for m phrase*/
  egg_token_type_m,
    /*! @brief Token type for n phrase*/
  egg_token_type_n,
    /*! @brief Token type for o phrase*/
  egg_token_type_o,
    /*! @brief Token type for p phrase*/
  egg_token_type_p,
    /*! @brief Token type for q phrase*/
  egg_token_type_q,
    /*! @brief Token type for r phrase*/
  egg_token_type_r,
    /*! @brief Token type for s phrase*/
  egg_token_type_s,
    /*! @brief Token type for t phrase*/
  egg_token_type_t,
    /*! @brief Token type for u phrase*/
  egg_token_type_u,
    /*! @brief Token type for v phrase*/
  egg_token_type_v,
    /*! @brief Token type for w phrase*/
  egg_token_type_w,
    /*! @brief Token type for x phrase*/
  egg_token_type_x,
    /*! @brief Token type for y phrase*/
  egg_token_type_y,
    /*! @brief Token type for z phrase*/
  egg_token_type_z,
    /*! @brief Token type for open-brace phrase*/
  egg_token_type_open_brace,
    /*! @brief Token type for bar phrase*/
  egg_token_type_bar,
    /*! @brief Token type for close-brace phrase*/
  egg_token_type_close_brace,
    /*! @brief Token type for tilde phrase*/
  egg_token_type_tilde,
    /*! @brief Token type for del phrase*/
  egg_token_type_del,
    /*! @brief Token type for control-character phrase*/
  egg_token_type_control_character,
    /*! @brief Token type for upper-case-letter phrase*/
  egg_token_type_upper_case_letter,
    /*! @brief Token type for lower-case-letter phrase*/
  egg_token_type_lower_case_letter,
    /*! @brief Token type for letter phrase*/
  egg_token_type_letter,
    /*! @brief Token type for binary-digit phrase*/
  egg_token_type_binary_digit,
    /*! @brief Token type for octal-digit phrase*/
  egg_token_type_octal_digit,
    /*! @brief Token type for decimal-digit phrase*/
  egg_token_type_decimal_digit,
    /*! @brief Token type for hexadecimal-digit phrase*/
  egg_token_type_hexadecimal_digit,
    /*! @brief Token type for white-space phrase*/
  egg_token_type_white_space,
    /*! @brief Token type for common-character phrase*/
  egg_token_type_common_character,
    /*! @brief Token type for literal-character phrase*/
  egg_token_type_literal_character,
    /*! @brief Token type for comment-basic-character phrase*/
  egg_token_type_comment_basic_character,
    /*! @brief Token type for non-comment-start-character phrase*/
  egg_token_type_non_comment_start_character,
    /*! @brief Token type for non-comment-end-character phrase*/
  egg_token_type_non_comment_end_character,
    /*! @brief Token type for non-comment-start-sequence phrase*/
  egg_token_type_non_comment_start_sequence,
    /*! @brief Token type for non-comment-end-sequence phrase*/
  egg_token_type_non_comment_end_sequence,
    /*! @brief Token type for comment-character phrase*/
  egg_token_type_comment_character,
    /*! @brief Token type for single-quoted-character phrase*/
  egg_token_type_single_quoted_character,
    /*! @brief Token type for quoted-character phrase*/
  egg_token_type_quoted_character,
    /*! @brief Token type for phrase-conjugator phrase*/
  egg_token_type_phrase_conjugator,
    /*! @brief Token type for phrase-name-character phrase*/
  egg_token_type_phrase_name_character,
    /*! @brief Token type for binary-indicator phrase*/
  egg_token_type_binary_indicator,
    /*! @brief Token type for octal-indicator phrase*/
  egg_token_type_octal_indicator,
    /*! @brief Token type for hexadecimal-indicator phrase*/
  egg_token_type_hexadecimal_indicator,
    /*! @brief Token type for comment-start-symbol phrase*/
  egg_token_type_comment_start_symbol,
    /*! @brief Token type for comment-end-symbol phrase*/
  egg_token_type_comment_end_symbol,
    /*! @brief Token type for alternation-symbol phrase*/
  egg_token_type_alternation_symbol,
    /*! @brief Token type for concatenation-symbol phrase*/
  egg_token_type_concatenation_symbol,
    /*! @brief Token type for phrase-terminator-symbol phrase*/
  egg_token_type_phrase_terminator_symbol,
    /*! @brief Token type for binary-integer phrase*/
  egg_token_type_binary_integer,
    /*! @brief Token type for octal-integer phrase*/
  egg_token_type_octal_integer,
    /*! @brief Token type for hexadecimal-integer phrase*/
  egg_token_type_hexadecimal_integer,
    /*! @brief Token type for decimal-integer phrase*/
  egg_token_type_decimal_integer,
    /*! @brief Token type for integer phrase*/
  egg_token_type_integer,
    /*! @brief Token type for single-quoted-literal phrase*/
  egg_token_type_single_quoted_literal,
    /*! @brief Token type for quoted-literal phrase*/
  egg_token_type_quoted_literal,
    /*! @brief Token type for absolute-literal phrase*/
  egg_token_type_absolute_literal,
    /*! @brief Token type for literal phrase*/
  egg_token_type_literal,
    /*! @brief Token type for comment-item phrase*/
  egg_token_type_comment_item,
    /*! @brief Token type for comment phrase*/
  egg_token_type_comment,
    /*! @brief Token type for illumination phrase*/
  egg_token_type_illumination,
    /*! @brief Token type for non-grammar-item phrase*/
  egg_token_type_non_grammar_item,
    /*! @brief Token type for non-grammar-element phrase*/
  egg_token_type_non_grammar_element,
    /*! @brief Token type for phrase-name phrase*/
  egg_token_type_phrase_name,
    /*! @brief Token type for quantifier-item phrase*/
  egg_token_type_quantifier_item,
    /*! @brief Token type for quantifier-option phrase*/
  egg_token_type_quantifier_option,
    /*! @brief Token type for quantifier phrase*/
  egg_token_type_quantifier,
    /*! @brief Token type for atom phrase*/
  egg_token_type_atom,
    /*! @brief Token type for item phrase*/
  egg_token_type_item,
    /*! @brief Token type for sequence-continuation phrase*/
  egg_token_type_sequence_continuation,
    /*! @brief Token type for sequence phrase*/
  egg_token_type_sequence,
    /*! @brief Token type for definition-continuation phrase*/
  egg_token_type_definition_continuation,
    /*! @brief Token type for definition phrase*/
  egg_token_type_definition,
    /*! @brief Token type for phrase phrase*/
  egg_token_type_phrase,
    /*! @brief Token type for grammar-element phrase*/
  egg_token_type_grammar_element,
    /*! @brief Token type for grammar phrase*/
  egg_token_type_grammar,
} egg_token_type;

#endif // EGG_TOKEN_TYPE_H

