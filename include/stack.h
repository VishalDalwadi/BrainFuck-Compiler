#ifndef _STACK_H_
#define _STACK_H_

#include <vector.h>

typedef Vector Stack;

Stack *create_stack( size_t element_size );

int push( Stack *stack , void *node_data );

void *pop( Stack *stack );

void delete_stack( Stack *stack );

#endif
