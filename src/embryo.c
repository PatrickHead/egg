/*!
    \file embryo.c

    \brief Source code for embryo parser generator.

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "common.h"
#include "input.h"
#include "egg-token.h"
#include "egg-token-util.h"
#include "generator.h"
#include "mkdir_p.h"
#include "egg-parser.h"


static void usage(char *program_name);
static char *build_file_name(char *dir, char *project_name, char *file_name);
static char *build_path(char *dir, char *sub);
static int create_directories(char *top);

  /*!

     \brief main function for \b embryo utility command.
    
     This is the main function for the \b embryo utility.\n
       - Accepts and parses command line arguments
       - Initializes the input source
       - Creates directories required for generated source code files
       - Calls appropriate code generation functions based on command line
         arguments
       - Cleans up input source and other data
    
     \param argc count of command line arguments
     \param argv array of command line argument strings
    
     \retval 0 success
     \retval 1 any failure

  */

int main(int argc, char **argv)
{
  int c;
  extern char *optarg;
  extern int optind;
  struct option long_opts[] =
    {
      { "project-name", 1, 0, 'p' },
      { "generate-list", 1, 0, 'g' },
      { "output-type", 1, 0, 'o' },
      { "directory", 1, 0, 'd' },
      { "use-doxygen", 1, 0, 1000 },
      { "code-version", 1, 0, 1001 },
      { "author", 1, 0, 1002 },
      { "email", 1, 0, 1003 },
      { "first-year", 1, 0, 1004 },
      { "license-text", 1, 0, 1005 },
      { "help", 0, 0, 'h' }
    };
  char *directory = NULL;
  char *generate_list = NULL;
  char *output_type = NULL;
  char *project_name = NULL;
  char *input_file = NULL;
  char *fn;
  egg_token *t;
  boolean gen_sources = false;
  boolean gen_headers = false;
  boolean gen_makefile = false;
  boolean use_doxygen = false;
  char *code_version = NULL;
  char *author = NULL;
  char *email = NULL;
  int first_year = 2013;
  char *license_text = NULL;
  FILE *fo;
  char *path;

  while ((c = getopt_long(argc, argv, "g:d:o:p:h", long_opts, NULL)) != -1)
  {
    switch (c)
    {
      case 'g':
        generate_list = strdup(optarg);
        break;
      case 'd':
        directory = strdup(optarg);
        if (output_type)
          free(output_type);
        output_type = strdup("f");
        break;
      case 'o':
        if (!output_type)
          output_type = strdup(optarg);
        break;
      case 'p':
        project_name = strdup(optarg);
        break;
      case 1000:
        if (!strcmp(optarg, "true"))
          use_doxygen = true;
        else if (!strcmp(optarg, "on"))
          use_doxygen = true;
        else if (!strcmp(optarg, "1"))
          use_doxygen = true;
        else
          use_doxygen = false;
        break;
      case 1001:
        code_version = strdup(optarg);
        break;
      case 1002:
        author = strdup(optarg);
        break;
      case 1003:
        email = strdup(optarg);
        break;
      case 1004:
        first_year = atoi(optarg);
        break;
      case 1005:
        license_text = strdup(optarg);
        break;
      case 'h':
      default:
        usage(argv[0]);
        return 1;
    }
  }

  if (!project_name)
  {
    usage(argv[0]);
    return 1;
  }

  if (!generate_list)
    generate_list = strdup("hs");

  if (strchr(generate_list, 's'))
    gen_sources = true;
  if (strchr(generate_list, 'h'))
    gen_headers = true;
  if (strchr(generate_list, 'm'))
    gen_makefile = true;

  if (output_type && !directory)
    directory = strdup(".");

  generator_set_doxygen_flag(use_doxygen);

  if (code_version)
    generator_set_version(code_version);

  if (author)
    generator_set_author(author);

  if (email)
    generator_set_email(email);

  if (first_year)
    generator_set_first_year(first_year);

  if (license_text)
    generator_set_license(license_text);

  input_file = NULL;
  if (optind < argc)
    if (strcmp(argv[optind], "-"))
      input_file = strdup(argv[optind]);

  if (directory)
    create_directories(directory);
  else
    directory = strdup(".");

  if (!input_initialize(input_file))
    return 1;

  t = grammar();

  if (gen_headers)
  {
    path = build_path(directory, "include");
    fn = build_file_name(path, project_name, "parser.h");
    if (path && fn)
    {
      if (output_type)
        fo = fopen(fn, "w");
      else
        fo = stdout;
      free(path);
      free(fn);
      if (fo)
      {
        generate_parser_header(fo, project_name, t);
        if (output_type)
          fclose(fo);
      }
    }

    path = build_path(directory, "include");
    fn = build_file_name(path, project_name, "token.h");
    if (path && fn)
    {
      if (output_type)
        fo = fopen(fn, "w");
      else
        fo = stdout;
      free(path);
      free(fn);
      if (fo)
      {
        generate_token_header(fo, project_name);
        if (output_type)
          fclose(fo);
      }
    }

    path = build_path(directory, "include");
    fn = build_file_name(path, project_name, "token-type.h");
    if (path && fn)
    {
      if (output_type)
        fo = fopen(fn, "w");
      else
        fo = stdout;
      free(path);
      free(fn);
      if (fo)
      {
        generate_token_type_header(fo, project_name, t);
        if (output_type)
          fclose(fo);
      }
    }

    path = build_path(directory, "include");
    fn = build_file_name(path, project_name, "token-util.h");
    if (path && fn)
    {
      if (output_type)
        fo = fopen(fn, "w");
      else
        fo = stdout;
      free(path);
      free(fn);
      if (fo)
      {
        generate_token_util_header(fo, project_name);
        if (output_type)
          fclose(fo);
      }
    }
  }

  if (gen_sources)
  {
    path = build_path(directory, "src");
    fn = build_file_name(path, project_name, "parser.c");
    if (path && fn)
    {
      if (output_type)
        fo = fopen(fn, "w");
      else
        fo = stdout;
      free(path);
      free(fn);
      if (fo)
      {
        generate_parser_source(fo, project_name, t);
        if (output_type)
          fclose(fo);
      }
    }

    path = build_path(directory, "src");
    fn = build_file_name(path, project_name, "token.c");
    if (path && fn)
    {
      if (output_type)
        fo = fopen(fn, "w");
      else
        fo = stdout;
      free(path);
      free(fn);
      if (fo)
      {
        generate_token_source(fo, project_name);
        if (output_type)
          fclose(fo);
      }
    }

    path = build_path(directory, "src");
    fn = build_file_name(path, project_name, "token-util.c");
    if (path && fn)
    {
      if (output_type)
        fo = fopen(fn, "w");
      else
        fo = stdout;
      free(path);
      free(fn);
      if (fo)
      {
        generate_token_util_source(fo, project_name, t);
        if (output_type)
          fclose(fo);
      }
    }

    path = build_path(directory, "src");
    fn = build_file_name(path, project_name, "walker.c");
    if (path && fn)
    {
      if (output_type)
        fo = fopen(fn, "w");
      else
        fo = stdout;
      free(path);
      free(fn);
      if (fo)
      {
        generate_walker_source(fo, project_name, t);
        if (output_type)
          fclose(fo);
      }
    }
  }

  if (gen_makefile)
  {
    if (output_type)
      fo = fopen(fn = build_file_name(directory, NULL, "Makefile"), "w");
    else
      fo = stdout;
    free(fn);
    generate_makefile(fo, project_name);
    if (output_type)
      fclose(fo);
  }

  input_cleanup();

  if (directory)
    free(directory);

  if (generate_list)
    free(generate_list);

  if (output_type)
    free(output_type);

  if (project_name)
    free(project_name);

  if (input_file)
    free(input_file);

  if (!t)
    return 1;

  return 0;
}

  /*!

     \brief Displays usage/help message in conventional format.
    
     This function displays a help and usage message for the \b embryo
     utility in the mostly ubiquitous POSIX/GNU format.
    
     \param program_name string containing the program name used in the
                         usage message
    
  */

static void usage(char *program_name)
{
  if (!program_name)
    program_name = "embryo";

  fprintf(stderr, "\n");
  fprintf(stderr, "Usage:  "
                  "%s \n"
                  "          <-p | --project-name=> <project name> \n"
                  "          [<-g | --generate-list=> <generate list>] \n"
                  "          [<-d | --directory=> <output directory>] \n"
                  "          [<-o | --output-type=> <output type>] \n"
                  "          [--use-doxygen=<true|false|on|off|0|1>] \n"
                  "          [--code-version=<version>] \n"
                  "          [--author=<author>] \n"
                  "          [--email=<email address>] \n"
                  "          [--first-year=<4 digit year>] \n"
                  "          [--license-text=<license string>] \n"
                  "          [<egg file name>]\n",
           program_name);
  fprintf(stderr, "\n");
  fprintf(stderr, "  where:\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "    <project name>     = the name of the parser.\n");
  fprintf(stderr, "    <generate list>    = 's', 'h', and/or 'm'.\n");
  fprintf(stderr, "                           's' = source files (*.c).\n");
  fprintf(stderr, "                           'h' = header files (*.h).\n");
  fprintf(stderr, "                           'm' = Makefile.\n");
  fprintf(stderr, "    <output directory> = the top-level directory where the "
                  "generated files will \n"
                  "                         be created.  This implies 'f' for "
                  "<output type>.\n");
  fprintf(stderr, "    <output type>      = 'f' or '-'.\n");
  fprintf(stderr, "                           'f' = generate files.\n");
  fprintf(stderr, "                           '-' = send output to STDOUT.\n");
  fprintf(stderr, "    <version>          = abritrary version string.\n");
  fprintf(stderr, "    <author>           = abritrary author name.\n");
  fprintf(stderr, "    <email>            = abritrary email address.\n");
  fprintf(stderr, "    <4 digit year>     = first year of copyright.\n");
  fprintf(stderr, "    <license string>   = abritrary license information.\n");
  fprintf(stderr, "    <egg file name>    = pathname to EGG grammar definition "
                  "file.  NONE or '-' \n"
                  "                         implies input from STDIN.\n");
  fprintf(stderr, "\n");

  return;
}

  /*!

     \brief Builds a pathname for a file.
    
     This function builds a \e pathname for a file that will be created by
     the \b embryo utility.  This \e pathname consists of the user supplied
     project directory, if any, followed by the user supplied project name,
     followed by the base file name.

     \warning This function returns a pointer to dynamically allocated memory.
              It is the caller's responsibility to free this memory when
              appropriate.
    
     \param dir          string containing the project storage directory, if any
            NULL         for no specific project directory
     \param project_name string containing the name of the project
     \param file_name    string containing the name of the file to be generated
    
     \retval "char *"    string containing \e pathname of file to be generated

  */

static char *build_file_name(char *dir, char *project_name, char *file_name)
{
  char *fn;
  int len;

  if (!file_name)
    return NULL;

  if (dir)
  {
    len = strlen(dir);            // len of directory
    ++len;                        // add 1 for '/'
  }

  if (project_name)
  {
    len += strlen(project_name);  // len of project name
    ++len;                        // add 1 for '-'
  }

  len += strlen(file_name);     // len of output file name
  ++len;                        // add 1 for trailing null

  fn = (char *)malloc(len);
  if (!fn)
    return NULL;

  sprintf(fn, "%s%s%s%s%s",
              dir ? dir : "",
              dir ? "/" : "",
              project_name ? project_name : "",
              project_name ? "-" : "",
              file_name);

  return fn;
}

  /*!

     \brief Builds a directory path from two directory components.
    
     This function essentially appends a sub-directory path component to
     a known parent directory path.
    
     \warning This function returns a pointer to dynamically allocated memory.
              It is the caller's responsibility to free this memory when
              appropriate.
    
     \param dir string containing parent directory path component
     \param sub string containing sub-directory path component
    
     \retval "char *" string containing new directory path
     \retval NULL     failure

  */

static char *build_path(char *dir, char *sub)
{
  char *path;

  if (!dir)
    return NULL;

  if (!sub)
    return strdup(dir);

  path = malloc(strlen(dir) + 1 + strlen(sub) + 1);
  if (!path)
    return NULL;

  sprintf(path, "%s/%s", dir, sub);

  return path;
}

  /*!

     \brief Creates all project related directories.
    
     This function creates all essential project related directories and
     sub-directories for a project.  All sub-directories are created under a
     single user supplied top-level directory for the project.

     The directories created are:
       - \<PROJECT\> directory
       - \<PROJECT\>/include sub-directory
       - \<PROJECT\>/src sub-directory
       - \<PROJECT\>/bin sub-directory
       - \<PROJECT\>/obj sub-directory
    
     \param top string containing the top-level project directory
    
     \retval  0 success
     \retval -1 failure

  */

static int create_directories(char *top)
{
  char *path = NULL;
  int r = 0;

  if (!top)
    return -1;

  r = mkdir_p(top, 0777);
  if (r)
    return -1;

  path = (char *)malloc(strlen(top) + strlen("/include") + 1);
  if (!path)
    return -1;
  sprintf(path, "%s/%s", top, "include");
  r = mkdir_p(path, 0777);
  free(path);
  if (r)
    return -1;

  path = (char *)malloc(strlen(top) + strlen("/src") + 1);
  if (!path)
    return -1;
  sprintf(path, "%s/%s", top, "src");
  r = mkdir_p(path, 0777);
  free(path);
  if (r)
    return -1;

  path = (char *)malloc(strlen(top) + strlen("/obj") + 1);
  if (!path)
    return -1;
  sprintf(path, "%s/%s", top, "obj");
  r = mkdir_p(path, 0777);
  free(path);
  if (r)
    return -1;

  path = (char *)malloc(strlen(top) + strlen("/bin") + 1);
  if (!path)
    return -1;
  sprintf(path, "%s/%s", top, "bin");
  r = mkdir_p(path, 0777);
  free(path);
  if (r)
    return -1;

  return 0;
}

