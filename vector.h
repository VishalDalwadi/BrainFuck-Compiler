#ifndef _VECTOR_H_
#include <stddef.h>
#define _VECTOR_H_
#define INITIAL_SIZE 10

typedef struct {

  size_t element_size;
  unsigned long capacity;
  unsigned long num_elements;
  void **elements;

} Vector;

Vector *create_vector(size_t element_size);

unsigned long length(Vector *vector);

int insert_element(Vector *vector, void *node_data);

int insert_element_at(Vector *vector, unsigned long index, void *node_data);

void *get_element_at(Vector *vector, long index);

void set_element_at(Vector *vector, long index, void *node_data);

void *delete_element(Vector *vector, long index);

void delete_vector(Vector *vector);

#endif
