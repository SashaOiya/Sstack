#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>

//#include "color.h"

#ifdef DEBUGG     //
#define $ printf ( "function <%s> line <%d>\n ", __PRETTY_FUNCTION__, __LINE__ );
#else
#define $
#endif
    //color

#define INFORMATION __PRETTY_FUNCTION__, __FILE__
#define name_print(a) printf ( #a " = %s\n", a );

enum Errors_t {
    NO_ERRORS = 1,
    ERROR     = 2
};

struct Error_t {
    int ERROR = 0;
};

struct Stack_Data_t {
    long long canary_left   = 0xDED0F;
    char *str_begine        = 0;
    char *str               = 0;             //free
    int capacity            = 0;
    int size_stack          = 2;
    char *stack_data_begine = 0;
    char *stack_data        = 0;
    long long canary_right  = 0xDED0F;
};

int StackCheck ( char **str, char **stack_data, int *size_stack, const int capacity );
int StackCtor ( char **str, int *size_stack, const int capacity );
void StackDump ( const char *begine_line, const char* func_name, const char* file_name,
                 size_t size_stack, const size_t capacity );
int StackDtor ( char **begine_line, size_t size_stack );
Errors_t StackPop ( const char *str_1, char *str_2 );
Errors_t StackPush ( char **str, char **str_2, const char value, int * size_stack, const int capacity );
void StackCreator ( int *capacity,   char **stack_data,
                    int *size_stack, char *str[]  );
int StackHash ( void *begine_stack, void *end_stack );

int main()
{
    //printf ("%d\n", sizeof ( long ) );
    Stack_Data_t Stack = {};
$
    Stack.str_begine = (char *)calloc ( Stack.size_stack + sizeof(long long) * 2, sizeof ( char) );   //free
    Stack.str = Stack.str_begine + sizeof ( long long );

    StackHash ( &Stack.canary_left,  &Stack.canary_right );

    Stack.stack_data_begine = (char *)calloc ( Stack.size_stack + sizeof(long long) * 2, sizeof ( char) ); //   assert
    Stack.stack_data = Stack.stack_data_begine + sizeof ( long long );     //stackctor

    //printf ("begine <%p> str <%p>", Stack.str_begine, Stack.str );

    StackCreator ( &Stack.capacity, &Stack.stack_data, &Stack.size_stack, &Stack.str  );

    StackDump ( Stack.stack_data, INFORMATION , Stack.size_stack, Stack.capacity );

    free ( Stack.str );
    free ( Stack.stack_data );

    StackHash ( &Stack.canary_left,  &Stack.canary_right );

    return 0;
}

// stackResize
int StackCtor ( char **str, int *size_stack, int capacity )   //void enum
{
    assert ( *str != nullptr );   // not assert
                                                     #warning no canary
    char *ptr_begine = (char *)calloc ( *size_stack + sizeof(long long) * 2, sizeof ( char) );   //free
    char *ptr = ptr_begine + sizeof ( long long );

    memset ( *begine_line, 3, size_stack * sizeof ( char ) );



    //StackDtor ( &ptr, *size_stack );

    strcpy ( ptr, *str );

$   *str = ptr;
$
}

void StackDump ( const char *stack, const char* func_name, const char* file_name,
                 size_t size_stack, const size_t capacity )    // void
{
$   printf ( "Stack [%p] " );
    name_print( stack )
    printf ( " called from%s\n "
             "{\n\t%s  \n\t{ \n "
             " \t\tsize = %d \n "
             " \t\tcapacity = %d \n "
             " \t\tdata [%p]:\n", file_name, func_name, size_stack, capacity, stack  ); // data
$   for ( int i = 0; i < size_stack; ++i ) {
        printf ( "\t\tdata[%d] = %c \n", i, stack[i] );
    }
    printf ( "\t}\n}\n");
}

int StackDtor ( char **begine_line, size_t size_stack )      // plus errors check
{
    assert ( *begine_line != nullptr );

$   memset ( *begine_line, 3, size_stack * sizeof ( char ) );

    return NO_ERRORS;
}

Errors_t StackPush ( char *str[], char **str_2, const char value, int * size_stack, const int capacity )
{

    if ( capacity == *size_stack ) {
$       char *ptr = (char *)calloc( *size_stack + 1, sizeof( char ) );
$       memset ( ptr, 3, *size_stack );
        printf ("address %p\t%s size %d str %s\n", ptr, ptr, strlen(ptr), *str );
        strcpy ( ptr, *str );
        *str = ptr;
$    }

$   **( str + capacity - 1 ) = value;

    return NO_ERRORS;   //errors
}

Errors_t StackPop ( const char *str_1, char *str_2 )
{
    //--str_1;
    *str_2 = *str_1;

    return NO_ERRORS;   //errors
}

int StackCheck ( char **str, char **stack_data, int *size_stack, const int capacity )
{
    if ( capacity == *size_stack ) {
        *size_stack = 2 * (*size_stack);     // push

        StackCtor ( str, size_stack, capacity );

        StackCtor ( stack_data, size_stack, capacity );
$   }
}

void StackCreator ( int *capacity,   char **stack_data,
                    int *size_stack, char *str[]  )
{
    char c = 0;
    for ( int i = 0; ( c = getchar() ) != '\n'; ++ i ) {
        ++*capacity;
        if ( *capacity == *size_stack ) {

$           StackCheck ( str, stack_data, size_stack, *capacity );
$           StackDump ( *stack_data, __PRETTY_FUNCTION__, __FILE__, *size_stack, *capacity );
            StackDump ( *str, __PRETTY_FUNCTION__, __FILE__, *size_stack, *capacity );
$       }
$       *(*str + i) = c;
$       StackPop ( *str + i, *stack_data + i );
    }
}

int StackHash ( void *begine_stack, void *end_stack )
{
    int size_stack = (char *)end_stack - (char *)begine_stack;
    long long sum  = 0;

    for ( int i = 0; i < size_stack; ++i ) {
        sum += *( (char *)begine_stack + i );
    }

    printf ("%d\n", size_stack);
    printf ("%lld\n", sum );

    return sum;
}
                                                                      //switch
int Verificator ( const char *str, size_t size_stack,
                  const size_t capacity, const char *str_2, int *error_indificate )   // struct
{
    if ( capacity < 0 ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 0 );//enum
    }
    if ( size_stack < 0 && size_stack < capacity ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 1 );
    }
    if ( str == nullptr ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 2 );
    }

}


