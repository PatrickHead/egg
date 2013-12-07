/*!
    \file embryo.c

    \brief Source code for embryo parser generator.

    \version 20131207175824

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


void usage(char *program_name);
char *build_file_name(char *dir, char *project_name, char *file_name);
char *build_path(char *dir, char *sub);
int create_directories(char *top);

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
        generate_token_util_header(fo, project_name, t);
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

void usage(char *program_name)
{
  if (!program_name)
    program_name = "embryo";

  fprintf(stderr, "\n");
  fprintf(stderr, "Usage:  "
                  "%s \\\n"
                  "          <-p | --project-name=> <project name> \\\n"
                  "          [<-g | --generate-list=> <generate list>] \\\n"
                  "          [<-d | --directory=> <output directory>] \\\n"
                  "          [<-o | --output-type=> <output type>] \\\n"
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
  fprintf(stderr, "    <egg file name>    = pathname to EGG grammar definition "
                  "file.  NONE or '-' \n"
                  "                         implies input from STDIN.\n");
  fprintf(stderr, "\n");

  return;
}

char *build_file_name(char *dir, char *project_name, char *file_name)
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

char *build_path(char *dir, char *sub)
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

int create_directories(char *top)
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

