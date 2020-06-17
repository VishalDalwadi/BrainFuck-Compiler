#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#define RED     "\033[1m\033[31m"
#define GREEN   "\033[1m\x1B[32m"
#define RESET   "\033[1m\x1B[0m"

void print_usage() {

  printf(RED "Usage: bfc file [-d destination] [-s source]\n" RESET);
  printf(GREEN "Required argument:\n" RESET);
  printf("file                  : Brainfuck file (.bf file)\n");
  printf(GREEN "Optional arguments:\n" RESET);
  printf("destination           : Address to print at (Default: 0x2000)\n");
  printf("source                : Address to read from (Default: 0x3000)\n");

}

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
  
  return 0;
}
