#include "stack.h"

int main()
{
    //printf ("%d\n", sizeof ( long ) );
    Stack_Data_t Stack = {};
$
    Stack.str = StackCtor ( Stack.size_stack );

    //StackHash ( &Stack.canary_left,  &Stack.canary_right );

    StackCreator ( &Stack.capacity, &Stack.size_stack, &Stack.str  );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    //free ( Stack.str );
    StackDtor ( Stack. str, Stack.size_stack );

    StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    //StackHash ( &Stack.canary_left,  &Stack.canary_right );

    return 0;
}

// stackResize
char * StackCtor ( const int size_stack )   //void enum
{
    char *str_begine = (char *)calloc ( size_stack + sizeof(long long) * 2, sizeof ( char) );   //free
    // str_begin == nullptr

    // StackRealloc()
    char *str = str_begine + sizeof ( long long );

    return str;
$
}
                                       //data
char* StackRedistribute ( const char *str, int size_stack )
{
                                                //#warning no canary
    // int main()
    //realloc
    char *ptr_begine = (char *)calloc ( size_stack + sizeof(long long) * 2, sizeof ( char) );   //free
    // callloc == nullptr
    char *ptr = ptr_begine + sizeof ( long long );

    memset ( ptr, 0, size_stack * sizeof ( char ) ); // ptr + capacity

    strcpy ( ptr, str );

$   return ptr;
}

void StackDump ( const char *stack, const char* func_name, const char* file_name,
                 size_t size_stack, const size_t capacity )    // void
{
$   printf ( "Stack [%p] ", stack );
    name_print( stack )
    printf ( " called from%s\n "
             "{\n\t%s  \n\t{ \n "
             " \t\tsize = %d \n "
             " \t\tcapacity = %d \n "
             " \t\tdata [%p]:\n", file_name, func_name, size_stack, capacity, stack  ); // data
$   for ( int i = 0; i < size_stack; ++i ) {
$       printf ( "\t\tdata[%d] = %c \n", i, stack[i] );
    }
$   printf ( "\t}\n}\n");
}

int StackDtor ( char *stack, size_t size_stack )      // plus errors check
{
    assert ( stack != nullptr );

// 3?
$   memset ( stack - 8 , 3, sizeof ( size_stack ) + 2 * sizeof ( long long ) ) ;

    free ( stack - 8 );// sizeof ( canary )

    return NO_ERRORS;
}

Errors_t StackPush ( char *str[], const char value, int * size_stack, const int capacity ) // struct Stack
{

// asserttttttttt!!!!
    if ( capacity == *size_stack ) {
        *size_stack = 2 * (*size_stack);

        *str = StackRedistribute ( *str, *size_stack );
        printf ("lox inside %p\n", *str );
$   }
$   *( *str + capacity - 1 ) = value;

    return NO_ERRORS;   //errors
}

Errors_t StackPop ( const char *str_1, char *str_2 )
{
    //--str_1;
    *str_2 = *str_1;

    return NO_ERRORS;   //errors   // *str_1 // str_1  name
}


// test.cpp
void StackCreator ( int *capacity, int *size_stack, char *str[]  )    // *
{
    char c = 0;
    for ( int i = 0; ( c = getchar() ) != '\n'; ++ i ) {
        ++*capacity;
        StackDump ( *str, __PRETTY_FUNCTION__, __FILE__, *size_stack, *capacity );
$       StackPush ( str, c, size_stack, *capacity );
$       //StackPop ( *str + i, *stack_data + i );
    }
}

int StackHash ( void *begin_stack, void *end_stack ) // struc Stack
{
    // char * usuc = ( char *)
    int size_stack = (char *)end_stack - (char *)begin_stack;   // sizeof ( stack)
    long long sum  = 0;

    for ( int i = 0; i < size_stack; ++i ) {
        sum += *( (char *)begin_stack + i );
    }

    printf ("%d\n", size_stack);
    printf ("%lld\n", sum );

    return sum;
}
                                                                      //switch
int Verificator ( const char *str, size_t size_stack,
                  const size_t capacity, int *error_indificate )   // struct
{
    if ( str == nullptr ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 2 );
    }
    if ( size_stack < 0 || size_stack < capacity ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 1 );
    }
    if ( capacity < 0 ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 0 );//enum
    }
}


