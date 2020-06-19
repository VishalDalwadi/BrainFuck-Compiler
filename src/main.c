#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "vector.h"

#define RED     "\033[1m\033[31m"
#define GREEN   "\033[1m\x1B[32m"
#define RESET   "\033[1m\x1B[0m"

typedef enum {

  TOK_INC_PTR,  // >
  TOK_DEC_PTR,  // <
  TOK_INC,      // +
  TOK_DEC,      // -
  TOK_READ,     // ,
  TOK_WRITE,    // .
  TOK_LOOP,     // [
  TOK_END_LOOP  // ]

} Token;

void print_usage() {

  printf(RED "Usage: bfc file [-d destination] [-s source]\n" RESET);
  printf(GREEN "Required argument:\n" RESET);
  printf("file                  : Brainfuck file (.bf file)\n");
  printf(GREEN "Optional arguments:\n" RESET);
  printf("destination           : Address to print at (Default: 0x2000)\n");
  printf("source                : Address to read from (Default: 0x3000)\n");

}

int ends_with(const char *str1, const char *str2) {

  int len_str1 = strlen(str1);
  int len_str2 = strlen(str2);

  return ((len_str1 < len_str2) ? 0 : !strcmp( &str1[len_str1 - len_str2], str2));

}

Vector *tokenize(FILE *file) {

  Vector *vector = create_vector( sizeof(Token));

  char c;
  Token token;

  while ((c = getc(file)) != EOF) {

    switch (c) {

      case '>':
        token = TOK_INC_PTR;
		    insert_element(vector, &token);
        break;
      case '<':
        token = TOK_DEC_PTR;
        insert_element(vector, &token);
        break;
      case '+':
        token = TOK_INC;
        insert_element(vector, &token);
        break;
      case '-':
        token = TOK_DEC;
        insert_element(vector, &token);
        break;
      case ',':
        token = TOK_READ;
        insert_element(vector, &token);
        break;
      case '.':
        token = TOK_WRITE;
        insert_element(vector, &token);
        break;
      case '[':
        token = TOK_LOOP;
        insert_element(vector, &token);
        break;
      case ']':
        token = TOK_END_LOOP;
        insert_element(vector, &token);
        break;
    }

  }

  return vector;

}

/*
void print_vector(Vector *vector) {

  long len = length(vector);

  for (long i = 0; i < len; i++) {

    switch (*(Token *) get_element_at(vector, i)) {

      case TOK_INC_PTR:
        printf("INC PTR\n");
        break;
      case TOK_DEC_PTR:
        printf("DEC PTR\n");
        break;
      case TOK_INC:
        printf("INC VALUE AT PTR\n");
        break;
      case TOK_DEC:
        printf("DEC VALUE AT PTR\n");
        break;
      case TOK_READ:
        printf("READ\n");
        break;
      case TOK_WRITE:
        printf("WRITE\n");
        break;
      case TOK_LOOP:
        printf("LOOP\n");
        break;
      case TOK_END_LOOP:
        printf("END LOOP\n");
        break;

    }

  }

}
*/

int main(int argc, char *argv[]) {
  
  char *input_filename = NULL;
  unsigned long destination = 0x2000, source = 0x3000;
  int opt;

  while ((opt = getopt(argc, argv, "-:d:s:h")) != -1) {

    switch (opt) {

    case 'd':
      destination = strtoul(optarg, NULL, 16);
      break;
    case 's':
      source = strtoul(optarg, NULL, 16);
      break;
    case 'h':
      print_usage();
      exit(0);
    case 1:
      input_filename = optarg;
      if ( !ends_with( input_filename, ".bf") ) {
        
        printf(RED "File extension should be .bf\n" RESET);
        exit(1);
      
      }
      break;

    }

  }

  if (input_filename == NULL) {
  
    print_usage();
    exit(1);
  
  }

  FILE *input_file = fopen(input_filename, "r");

  if (input_file == NULL) {
  
    printf(RED "File %s does not exist\n" RESET, input_filename);
    exit(1);
  
  }

  Vector *tokens = tokenize(input_file);

  fclose(input_file);
//  print_vector(tokens);
  
  delete_vector(tokens);

  return 0;

}
