#include <stdlib.h>
#include <string.h>
#include "vector.h"

Vector *create_vector(size_t node_size) {

  Vector *vector = malloc( sizeof(Vector) );

  vector->element_size = node_size;
  vector->capacity = 0;
  vector->num_elements = 0;
  vector->elements = NULL;

  return vector;

}

unsigned long length(Vector *vector) {

  return vector->num_elements;

}

int insert_element(Vector *vector, void *node_data) {

  void *data = malloc( vector->element_size );
  memcpy( data, node_data, vector->element_size);

  if ( vector->capacity == 0 ) {

    vector->elements = calloc( sizeof(void *), INITIAL_SIZE);
    vector->capacity = INITIAL_SIZE;

  }

  if ( vector->capacity == vector->num_elements ) {

    vector->elements = realloc( vector->elements, sizeof(void *) * vector->capacity * 1.25);
    vector->capacity = vector->capacity * 1.25;

  }

  if ( vector->elements != NULL ) {

    vector->elements[vector->num_elements] = data;
    vector->num_elements++;

    return 0;

  } else {

    free( data );
    return 1;

  }

}

int insert_element_at(Vector *vector, unsigned long index, void *node_data) {

  void *data = malloc( vector->element_size );
  memcpy( data, node_data, vector->element_size);

  if ( index >= vector->num_elements ) {

    return insert_element( vector, node_data);

  } else {

    if ( vector->capacity == vector->num_elements ) {

      vector->elements = realloc( vector->elements, sizeof(void *) * vector->capacity * 1.25);
      vector->capacity = vector->capacity * 1.25;

    }

    if ( vector->elements == NULL ) {

      free( data );
      return 1;

    }

    memmove( vector->elements + index + 1, vector->elements + index, (vector->num_elements - index) * sizeof(void *));
    vector->elements[index] = data;
    vector->num_elements++;

    return 0;

  }

}

void *get_element_at(Vector *vector, long index) {

  if ( index >= vector->num_elements || index < 0) {

    return NULL;
  
  } else {

    void *data = malloc( vector->element_size );
    memcpy( data, vector->elements[index], vector->element_size);
    return data;

  }

}

void set_element_at(Vector *vector, long index, void *node_data) {

  if ( index < vector->num_elements && index >= 0 ) {

    void *data = malloc( vector->element_size );
    memcpy( data, node_data, vector->element_size);
    vector->elements[index] = data;

  }

}

void *delete_element(Vector *vector, long index) {

  if ( index >= vector->num_elements || index < 0 ) {

    return NULL;
  
  } else {
  
    void *data = malloc( vector->element_size );
    memcpy( data, vector->elements[index], vector->element_size);
    memmove( vector->elements + index, vector->elements + index + 1, (vector->num_elements - index - 1) * sizeof(void *));
    vector->num_elements--;
    return data;
  
  }

}

void delete_vector(Vector *vector) {

  free( vector );

}
