#ifndef STACK
#define STACK

#define SPECIFIER "%d"
#define CANARY_PROTECTION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>

#ifdef DEBUGG
#define $ printf ( "function <%s> line <%d>\n ", __PRETTY_FUNCTION__, __LINE__ );
#else
#define $
#endif

#define INFORMATION __PRETTY_FUNCTION__, __FILE__
#define name_print(a) printf ( #a " = %s\n", a );

enum Err_t {
    SIZE_ERR  = 1,
    HASH_ERR  = 2,
    DATA_ERR  = 3,
    CANA_ERR  = 4,
    CAPA_ERR  = 5,
    OK        = 6
};

typedef long canary_t;
typedef int elem_t;

struct Stack_Data_t {
    canary_t canary_left = 0xDED;
    elem_t *data           = 0;
    int capacity           = 0;
    int size_stack         = 1;
    long stack_hash        = 0;
    int stack_status       = 0;
    canary_t canary_right = 0xDED;
};

void StackCtor ( Stack_Data_t *Stack );
void StackRealloc ( Stack_Data_t *Stack );
void StackDump ( Stack_Data_t Stack, const char* func_name, const char* file_name );
void StackDtor ( Stack_Data_t *Stack );
void StackPush ( Stack_Data_t *Stack, const elem_t value );
elem_t StackPop ( Stack_Data_t *Stack );
int StackHash ( Stack_Data_t *Stack );
void StackRehash ( Stack_Data_t *Stack );
Err_t Verificator ( Stack_Data_t *Stack );
int GetFileSize ( FILE * f );
void CanaryProtection ( elem_t *canary_begine, Stack_Data_t *Stack );

#endif  //STACK
