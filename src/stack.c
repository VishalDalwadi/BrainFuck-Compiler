#include <stack.h>

Stack *create_stack( size_t element_size ) {

  return create_vector( element_size );

}

int push( Stack *stack , void *node_data ) {

  return insert_element( stack , node_data );

}

void *pop( Stack *stack ) {

  return delete_element( stack , stack->num_elements - 1 );

}

void delete_stack( Stack *stack ) { 

  delete_vector( stack );

}

