#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>

//#include "color.h"

#ifdef DEBUGG
#define $ printf ( "function <%s> line <%d>\n ", __PRETTY_FUNCTION__, __LINE__ );
#else
#define $ printf ("");
#endif
    //color

enum Errors_t {
    NO_ERRORS = 1,
    ERROR = 2
};

/*struct Stack_Data_t {
    char *str         = 0;             //free
    char *begine_line = str;
    size_t capacity   = 0;
    size_t size_stack = 0;
};     */

int StackCtor ( char **str, int *size_stack, const int capacity );
void StackDump ( const char *begine_line, const char* func_name, const char* file_name,
                 size_t size_stack, size_t capacity );
int StackDetore ( char **begine_line, size_t size_stack );  // Dtor Destructor DestructStack ConstructStack
Errors_t Pop ( char *str_1, char *str_2 );   // StackPop
Errors_t Push ( char **str, char **str_2, const char value, int * size_stack, int capacity ); // StackPush

int main()
{
    int capacity = 0;
    int size_stack = 2;  // delete 1
$                            // push
    char *str = (char *)calloc ( size_stack, sizeof ( char) );            //free
    char *begine_line = str;
    char *stack_data = (char *)calloc ( size_stack, sizeof ( char) ); // stack_data {}
    char c = 0;

    for ( int i = 0; ( c = getchar() ) != '\n'; ++ i ) {
        ++capacity;
        if ( capacity == size_stack ) {
            size_stack = 2 * (size_stack);

$           /*char *ptr = (char *)calloc( size_stack + 1, sizeof( char ) );
            StackDetore ( &ptr, size_stack );

            printf ("address %p\t%s size %d\n", ptr, ptr, strlen(ptr) );

            strcpy ( ptr, str );

$           str = ptr;  */

            //free ( ptr );
            StackCtor ( &str, &size_stack, capacity );

            /*char *ptr_2 = (char *)calloc( size_stack + 1, sizeof( char ) );
$           StackDetore ( &ptr_2, size_stack );
            //Pop ( &str, &str_2 );

            //printf ("address %p\t%s size %d\n", ptr_2, ptr_2, strlen(ptr) );

            strcpy ( ptr_2, stack_data );
            stack_data = ptr_2;   */
            //free ( ptr_2 );
            StackCtor ( &stack_data, &size_stack, capacity );
$       }
        //Push ( &str, &str_2, c, &size_stack, capacity );
        str[i] = c;
        printf ("size %d capacity %d value %c str %s \n", size_stack, capacity, c, str );
        Pop ( str + i, stack_data + i );
    }

$

    //int error_name = StackCtor( (void **)&begine_line, size_stack, capacity );   //

    //pop

    StackDump ( stack_data, __PRETTY_FUNCTION__, __FILE__, size_stack, capacity );

    free ( str );
    free ( stack_data );

    return 0;
}

// realloc() [234345********]
// realloc() cppref

int StackCtor ( char **str, int *size_stack, int capacity )   //void enum
{
    assert ( *str != nullptr );   // not assert

    char *ptr = (char *)calloc( *size_stack + 1, sizeof( char ) );
    StackDetore ( &ptr, *size_stack );

    strcpy ( ptr, *str );

$   *str = ptr;
$
}

void StackDump ( const char *begine_line, const char* func_name, const char* file_name,
                 size_t size_stack, size_t capacity )    // void
{
$   printf ( "Stack [%p] "" 'stk' called from%s\n "   // from main.cpp
             "{\n\t%s  \n\t{ \n "                      //__PRETTY_FINC__
             " \t\tsize = %d \n "
             " \t\tcapacity = %d \n "
             " \t\tdata [%p]:\n", begine_line , file_name, func_name, size_stack, capacity, begine_line  ); // data
$   for ( int i = 0; i < size_stack; ++i ) { // < or <=
        printf ( "\t\tdata[%d] = %c \n", i, begine_line[i] );
    }
    printf ( "\t}\n}\n");
}

int StackDetore ( char **begine_line, size_t size_stack )      // plus errors check
{
    assert ( *begine_line != nullptr );

$   memset ( *begine_line, 3, size_stack * sizeof ( char ) );

    return NO_ERRORS;
}

Errors_t Push ( char *str[], char **str_2, const char value, int * size_stack, int capacity )   // pointer
{

    if ( capacity == *size_stack ) {
        *size_stack = 2 * (*size_stack);
$       char *ptr = (char *)calloc( *size_stack + 1, sizeof( char ) );
$       memset ( ptr, 3, *size_stack );
        printf ("address %p\t%s size %d str %s\n", ptr, ptr, strlen(ptr), *str );
        strcpy ( ptr, *str );
        *str = ptr;
$    }

$   *str[capacity-1] = value;

    return NO_ERRORS;   //errors
}

Errors_t Pop ( char *str_1, char *str_2 )   // pointer     const
{
    //--str_1;
    *str_2 = *str_1;     //assert

    return NO_ERRORS;   //errors
}



