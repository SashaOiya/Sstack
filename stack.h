#ifndef STACK
#define STACK

#define SPECIFIER "%d"
#define CANARY_PROTECTION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>
#include "my_prog.h"

#define INFORMATION __PRETTY_FUNCTION__, __FILE__
const int stack_mul_coeff = 2;

enum Stack_Errors_t {
    STACK_NO_ERR   = 0,
    STACK_SIZE_ERR = 1,
    STACK_HASH_ERR = 2,
    STACK_DATA_ERR = 3,
    STACK_CANA_ERR = 4,
    STACK_CAPA_ERR = 5
};

typedef long canary_t;
typedef int elem_t;

struct Stack_t {
    canary_t canary_left   = 0xDED;
    elem_t *data           = 0;
    int capacity           = 0;
    int size_stack         = 1;
    long stack_hash        = 0;
    int stack_status       = 0;
    canary_t canary_right  = 0xDED;
};

Errors_t Stack_Ctor    ( Stack_t *stack );
void     Stack_Dtor    ( Stack_t *stack );

Errors_t Stack_Resize ( Stack_t *stack );
void     Stack_Dump   ( Stack_t *stack, const char* func_name, const char* file_name );
void     Stack_Push   ( Stack_t *stack, const elem_t value );
elem_t   Stack_Pop    ( Stack_t *stack );

int            Stack_Hash        ( Stack_t *stack );
void           Stack_Rehash      ( Stack_t *stack );
void           Canary_Protection ( Stack_t *stack, elem_t *canary_begine );
Stack_Errors_t Stack_Verificator ( Stack_t *stack );

#endif  //STACK
