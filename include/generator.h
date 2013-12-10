/*!
    \file generator.h

    \brief Header file for parser code generation routines for EGG grammars.

    \version 20131210022217

    \author Patrick Head  mailto:patrickhead@gmail.com

    \copyright Copyright (C) 2013  Patrick Head

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
void generate_token_util_header(FILE *of, char *parser_name);
void generate_walker_source(FILE *of, char *parser_name, egg_token *t);
void generate_input_source(FILE *of, char *parser_name);
void generate_input_header(FILE *of, char *parser_name);
void generate_strapp_source(FILE *of, char *parser_name);
void generate_strapp_header(FILE *of, char *parser_name);
void generate_common_header(FILE *of, char *parser_name);
void generate_makefile(FILE *of, char *parser_name);

boolean generator_get_doxygen_flag(void);
void generator_set_doxygen_flag(boolean flag);
char * generator_get_file_name(void);
void generator_set_file_name(char *file_name);
char * generator_get_project_brief(void);
void generator_set_project_brief(char *brief);
char * generator_get_version(void);
void generator_set_version(char *version);
char * generator_get_author(void);
void generator_set_author(char *author);
char * generator_get_email(void);
void generator_set_email(char *email);
int generator_get_first_year(void);
void generator_set_first_year(int year);
char * generator_get_license(void);
void generator_set_license(char *license);

#endif // GENERATOR_H
