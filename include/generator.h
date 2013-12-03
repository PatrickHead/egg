/*
    generator.h
    Copyright (C) 2013  Patrick Head

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GENERATOR_H
#define GENERATOR_H

void generate_parser_source(FILE *of, char *parser_name, egg_token *t);
void generate_parser_header(FILE *of, char *parser_name, egg_token *t);
void generate_token_header(FILE *of, char *parser_name);
void generate_token_source(FILE *of, char *parser_name);
void generate_token_type_header(FILE *of, char *parser_name, egg_token *t);
void generate_token_util_source(FILE *of, char *parser_name, egg_token *t);
void generate_token_util_header(FILE *of, char *parser_name, egg_token *t);
void generate_walker_source(FILE *of, char *parser_name, egg_token *t);
void generate_input_source(FILE *of, char *parser_name);
void generate_input_header(FILE *of, char *parser_name);
void generate_strapp_source(FILE *of, char *parser_name);
void generate_strapp_header(FILE *of, char *parser_name);
void generate_common_header(FILE *of, char *parser_name);
void generate_makefile(FILE *of, char *parser_name);

#endif // GENERATOR_H
