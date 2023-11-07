#ifndef STACK
#define STACK

typedef float elem_t;
#define SPECIFIER "%g"

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

enum Errors_t {
    NO_ERRORS = 1,
    ERROR     = 2
};

struct Error_t {        // typedef
    int ERROR = 0;
};

typedef long canary_t;

// #ifdef CANARY_PROTECTION
struct Stack_Data_t {          // Stack_t
    long canary_left    = 0xDED;
    elem_t *str             = 0;             //free
    int capacity            = 0;
    int size_stack          = 2;
    long stack_hash    = 0;
    long canary_right   = 0xDED;
};

elem_t * StackCtor ( const int size_stack );
elem_t* StackRedistribute ( elem_t *str, int size_stack );
void StackDump ( Stack_Data_t Stack, const char* func_name, const char* file_name );
int StackDtor ( elem_t *stack, size_t size_stack );
Errors_t StackPush ( Stack_Data_t *Stack, const elem_t value );
elem_t StackPop ( Stack_Data_t *Stack );
//void StackCreator ( FILE *f, int *capacity, int *size_stack, char_t *str[], int n_lines  );
int StackHash ( Stack_Data_t *Stack );
int StackRehash ( Stack_Data_t *Stack );
void Verificator ( Stack_Data_t *Stack, int *error_indificate );
int GetFileSize ( FILE * f );

#endif //STACK
