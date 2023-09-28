#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cassert>

//#include "color.h"

#ifndef DEBUGG
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

int StackCtor ( char **str, int size_stack, int capacity );
void StackDump ( const char *begine_line, const char* func_name, const char* file_name,
                 size_t size_stack, size_t capacity );
int StackDetore ( char *begine_line, size_t size_stack );  // Dtor Destructor DestructStack ConstructStack
Errors_t Pop ( char **str_1, char **str_2 );   // StackPop
Errors_t Push ( char **str, char **str_2, const char value, int * size_stack, int capacity ); // StackPush

int main()
{
    char *str;             //free
    char *begine_line = str;
    char *str_2; // stack_data {}
    char c = 0;

    int capacity = 0;
    int size_stack = 2;  // delete 1
$                            // push
    for ( int i = 0; ( c = getchar() ) != '\n'; ++ i ) {
        ++capacity;
        printf ("size %d capacity %d value %c\n", size_stack, capacity, c );
$       str = str + capacity;  //
$       Push ( &str, &str_2, c, &size_stack, capacity );
$       //Pop ( &str, &str_2 );
    }

    /*Stack_Data_t Stack;
    Stack.str = strdup ( "Meow" );
    Stack.begine_line = Stack.str;   */
$
    printf ( "<%p>\t%s\t%c\n", str, str, *str );
$   begine_line = str - capacity;

    //int error_name = StackCtor( (void **)&begine_line, size_stack, capacity );   //

    //pop

    StackDump ( begine_line, __PRETTY_FUNCTION__, __FILE__, size_stack, capacity );

    return 0;
}

// realloc() [234345********]
// realloc() cppref

int StackCtor ( char **str, int size_stack, int capacity )   //void enum
{
    assert ( *str != nullptr );   // not assert

$   //StackDump ( *str, __PRETTY_FUNCTION__, __FILE__, size_stack, capacity );  // macro
    // for realloc use dinamic memory
    printf ("%p\n", *str);

$   char *ptr = ( char *)realloc( *str, 2 * size_stack );     //memset      //+capacity
    printf ("%p\n", ptr);
$
    //ptr = strcpy ( ptr, *str );  //

    //free ( str ); //

    /*if ( ptr == nullptr ) {                                         // pointer to the begginig of the line

        return ERROR;
    }    */

    //StackDetore ( *( char **)str, size_stack );

    //StackDump ( *(char **)str, __PRETTY_FUNCTION__, __FILE__, size_stack, capacity );

$   //printf ( "%s : <%p>\n", __PRETTY_FUNCTION__, ptr );      //

    *str = ptr;
    printf ("str : %p\n", *str );
$
    return 2 * size_stack ;
}

void StackDump ( const char *begine_line, const char* func_name, const char* file_name,
                 size_t size_stack, size_t capacity )    // void
{
$   printf ( "Stack [%p] "" 'stk' called from%s\n "   // from main.cpp
             "{\n\t%s  \n\t{ \n "                      //__PRETTY_FINC__
             " \t\tsize = %d \n "
             " \t\tcapacity = %d \n "
             " \t\tdata [%p]:\n", begine_line , file_name, func_name, size_stack, capacity, begine_line  ); // data
$   for ( int i = 0; i < capacity; ++i ) { // < or <=
        printf ( "\t\tdata[%d] = %c \n", i, begine_line[i] );
    }
    printf ( "\t}\n}\n");
}

int StackDetore ( char *begine_line, size_t size_stack )      // plus errors check
{
    assert ( begine_line != nullptr );

//    free ( begine_line );

$   memset ( begine_line, 3, size_stack * sizeof ( char ) );

    return NO_ERRORS;
}

Errors_t Push ( char **str, char **str_2, const char value, int * size_stack, int capacity )   // pointer
{
$   char *start = *str;
    *str = *str - capacity + 1;
    printf ("%p\n", *str);
    if ( capacity == *size_stack ) {             // sizeof ( str )
        printf ("PUSH : size %d capacity %d\n", *size_stack, capacity );
        printf ("str, value : %s\t%c\n", *str, value );
$       //*size_stack = StackCtor ( str, *size_stack, capacity );   //
        *size_stack = 2 * *size_stack;
$        char *ptr = (char *)calloc( *size_stack, sizeof( char ) );
$        memset ( ptr, 15, sizeof ( char ) );
        strcpy ( ptr, *str );

        /*char *ptr_2 = (char *)calloc( *size_stack, sizeof( char ) );
        strcpy ( ptr_2, *str_2 );   */

        printf ("%p\n", ptr);
$       // strcpy ( ptr, *str );
$        *str = ptr;
$    }

$    *str = start;
$    **str = value;
$    ++*str;
    //printf ("str : %p\n", *str );

    return NO_ERRORS;   //errors
}

Errors_t Pop ( char **str_1, char **str_2 )   // pointer     const
{
    //--str_1;
    **str_2 = **str_1;     //assert

    return NO_ERRORS;   //errors
}



