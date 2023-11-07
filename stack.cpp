#include "stack.h"

int main()
{
    //printf ("%d\n", sizeof ( long ) );
    Stack_Data_t Stack = {};
    FILE *f = fopen ( "code.txt", "r" );

    Stack.str = StackCtor ( Stack.size_stack );
    Stack.stack_hash = StackHash ( &Stack );
    //printf ( "stack zero %d\n", Stack.stack_hash );

    //StackHash ( &Stack.canary_left,  &Stack.canary_right );
                                                                      //n_lines * 2
    //StackCreator ( f, &Stack.capacity, &Stack.size_stack, &Stack.str, 22  );
    StackPush ( &Stack, 4 );
    StackPush ( &Stack, 7 );
    StackPop  ( &Stack );

    StackDump ( Stack, INFORMATION );

    //free ( Stack.str );
    StackDtor ( Stack.str, Stack.size_stack );

    //StackDump ( Stack.str, INFORMATION , Stack.size_stack, Stack.capacity );

    //StackHash ( &Stack.canary_left,  &Stack.canary_right );

    return 0;
}

// stackResize
elem_t * StackCtor ( const int size_stack )   //void enum
{
    elem_t *str_begine = (elem_t *)calloc ( size_stack + sizeof( canary_t ) * 2, sizeof ( elem_t ) );   //free
    // str_begin == nullptr
    // StackRealloc()
    elem_t *str = str_begine + sizeof ( canary_t );

    return str;
$
}
                                       //data
elem_t* StackRedistribute ( elem_t *str, int size_stack )
{
                                                //#warning no canary
    // int main()
    //realloc
    Stack_Data_t Stack = {};
$   elem_t *ptr_begin = (elem_t *)calloc ( size_stack + sizeof( canary_t ) * 2, sizeof ( elem_t ) );   //free
    if ( sizeof ( elem_t ) == 4 || sizeof ( elem_t ) == 8 ) {
        *ptr_begin = Stack.canary_left;
        *(ptr_begin + size_stack * sizeof ( elem_t ) + sizeof( canary_t ) ) = Stack.canary_right;
    }
    // callloc == nullptr
$   elem_t *ptr = ptr_begin + sizeof ( canary_t );

$   memcpy ( ptr, str, size_stack * sizeof ( elem_t ) / 2 );

$   return ptr;
}

void StackDump ( Stack_Data_t Stack, const char* func_name, const char* file_name )    // void
{
$   printf ( "Stack [%p] ", Stack.str );
    name_print( Stack.str )
    printf ( " called from%s\n "
             "{\n\t%s  \n\t{ \n "
             " \t\tsize = %d \n "
             " \t\tcapacity = %d \n "
             " \t\tdata [%p]:\n", file_name, func_name, Stack.size_stack, Stack.capacity, Stack.str  ); // data
$   for ( size_t i = 0; i < Stack.size_stack; ++i ) {
$       printf ( "\t\tdata[%d] = ", i );
        printf ( SPECIFIER, Stack.str[i] );
        printf ( "\n" );
    }
$   printf ( "\t}\n}\n");
}

int StackDtor ( elem_t *stack, size_t size_stack )      // plus errors check
{
    assert ( stack != nullptr );

$   memset ( stack - sizeof ( canary_t ), 0, size_stack * sizeof ( elem_t )+ 2 * sizeof ( canary_t ) ) ;

    free ( stack - sizeof ( canary_t ) );// sizeof ( canary )

    return NO_ERRORS;
}

Errors_t StackPush ( Stack_Data_t *Stack, const elem_t value )
{
    assert ( Stack != nullptr );

    StackRehash ( Stack );

    ++(Stack->capacity);
$   if ( Stack->capacity == Stack->size_stack ) {
$       Stack->size_stack = 2 * (Stack->size_stack);

$       Stack->str = StackRedistribute ( Stack->str, Stack->size_stack );
$   }
$   *( Stack->str + Stack->capacity - 1 ) = value;

    StackHash ( Stack );

    return NO_ERRORS;
}

elem_t StackPop ( Stack_Data_t *Stack  )
{
    //--str_1;
    StackRehash ( Stack );

    elem_t temp = *( Stack->str + Stack->capacity - 1 );
    --(Stack->capacity);
    *( Stack->str + Stack->capacity ) = 0; // const

    StackHash ( Stack );

    return temp;   //errors   // *str_1 // str_1  name
}


/*// test.cpp
void StackCreator ( FILE *f, int *capacity, int *size_stack, char_t *str[], int n_lines  )    // *
{
    char_t c = 0;
    for ( int i = 0; i < n_lines; ++ i ) {
        fscanf ( f, SPECIFIER, &c );
        ++*capacity;
        StackDump ( *str, __PRETTY_FUNCTION__, __FILE__, *size_stack, *capacity );
$       StackPush ( str, c, size_stack, *capacity );
$       //StackPop ( *str + i, *stack_data + i );
    }
}  */

int StackHash ( Stack_Data_t *Stack )
{
    //int size = &Stack->canary_left - &Stack->canary_right;   // sizeof ( stack)
    long sum  = 0;
    Stack->stack_hash = 0;

    int stack_size = sizeof ( *Stack );
    //printf ( "size %d\n", stack_size );
    for ( int i = 0; i < stack_size; ++i ) {
        sum += *( (char *)Stack + i );
    }
    //printf ( "sum %d\n", sum );

    Stack->stack_hash = sum;

    return sum;
}

int StackRehash ( Stack_Data_t *Stack )
{
    long long hash_before = Stack->stack_hash;
    long long hash_after  = StackHash ( Stack );

    if ( hash_before != hash_after ) {
        printf ( "before %d\n", hash_before );
        printf ( "after %d\n", hash_after );
    }
    Stack->stack_hash = 0;
}
                                                                      //switch
void Verificator ( Stack_Data_t *Stack, int *error_indificate )   // struct
{
    //int sum = StackHash ( Stack );

    if ( Stack->capacity < 0 ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 0 );//enum
        printf ( "Capacity error\n" );
    }
    if ( Stack->size_stack < 0 || Stack->size_stack < Stack->capacity ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 1 );
        printf ( "Size error\n" );
    }
    if ( Stack->str == nullptr ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 2 );
        printf ( "Buffer error\n" );
    }
    /*if ( sum != *start_sum ) {
        (*error_indificate ) | ( (*error_indificate) | 1 << 3 );
        printf ( "Hash error\n" );
    }  */
    /*printf ( "%d\n", sum );
    printf ( "%d\n", *start_sum );
    *start_sum = sum;  */
}




