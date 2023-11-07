#include "stack.h"

int main()
{
    Stack_Data_t Stack = {};

    FILE *f = fopen ( "code.txt", "r" );
    if ( !f ) {
        perror( "File opening failed" );

        return -1;
    }

    StackCtor ( &Stack );

    StackPush ( &Stack, 4 );
    StackPush ( &Stack, 7 );
    StackPop  ( &Stack );

    StackDump ( Stack, INFORMATION );

    StackDtor ( &Stack );

    return 0;
}

// stackResize
void StackCtor ( Stack_Data_t *Stack )
{
    Stack->data = (elem_t *)calloc( Stack->size_stack + sizeof( canary_t ) * 2, sizeof ( elem_t ) ) + sizeof ( canary_t );
    assert ( Stack->data != nullptr );
    // StackRealloc()

$   Stack->stack_hash = StackHash ( Stack );
}

elem_t* StackRealloc ( elem_t *str, int size_stack )
{                                        //#warning no canary    //realloc
    Stack_Data_t Stack = {};
$   elem_t *ptr_begine = (elem_t *)calloc ( size_stack + sizeof( canary_t ) * 2, sizeof ( elem_t ) );
    assert ( ptr_begine != nullptr );

    // not char
    *(canary_t *)ptr_begine = Stack.canary_left;
    *( (canary_t *)ptr_begine + size_stack * sizeof ( elem_t ) + sizeof( canary_t ) ) = Stack.canary_right;

$   elem_t *ptr = ptr_begine + sizeof ( canary_t );

$   memcpy ( ptr, str, size_stack * sizeof ( elem_t ) / 2 );

$   return ptr;
}

void StackDump ( Stack_Data_t Stack, const char* func_name, const char* file_name )
{
$   printf ( "Stack [%p] ", Stack.data );
    name_print( Stack.data )
    printf ( " called from%s\n "
             "{\n\t%s  \n\t{ \n "
             " \t\tsize = %d \n "
             " \t\tcapacity = %d \n "
             " \t\tdata [%p]:\n", file_name, func_name, Stack.size_stack, Stack.capacity, Stack.data  );
$   for ( size_t i = 0; i < Stack.size_stack; ++i ) {
$       printf ( "\t\tdata[%d] = ", i );
        printf ( SPECIFIER, Stack.data[i] );
        printf ( "\n" );
    }
$   printf ( "\t}\n}\n");
}

void StackDtor ( Stack_Data_t *Stack )      // plus errors check
{
    Verificator ( Stack );

$   memset ( Stack->data - sizeof ( canary_t ), 0, Stack->size_stack * sizeof ( elem_t )+ 2 * sizeof ( canary_t ) )
;

    free ( Stack->data - sizeof ( canary_t ) );
}

void StackPush ( Stack_Data_t *Stack, const elem_t value )
{
    assert ( Stack != nullptr );

    Verificator ( Stack );

    StackRehash ( Stack );

    ++(Stack->capacity);

$   if ( Stack->capacity == Stack->size_stack ) {
$       Stack->size_stack = 2 * (Stack->size_stack);

$       Stack->data = StackRealloc ( Stack->data, Stack->size_stack );
$   }
$   *( Stack->data + Stack->capacity - 1 ) = value;

    StackHash ( Stack );
}

elem_t StackPop ( Stack_Data_t *Stack  )
{
    Verificator ( Stack );

    StackRehash ( Stack );

    elem_t temp = *( Stack->data + Stack->capacity - 1 );
    --(Stack->capacity);
    *( Stack->data + Stack->capacity ) = 0; // const

    StackHash ( Stack );

    return temp;
}

int StackHash ( Stack_Data_t *Stack )
{
    long sum  = 0;
    int stack_size = sizeof ( *Stack );

    Stack->stack_hash = 0;

    for ( int i = 0; i < stack_size; ++i ) {
        sum += *( (char *)Stack + i );
    }

    Stack->stack_hash = sum;

    return sum;
}

void StackRehash ( Stack_Data_t *Stack )
{
    long long hash_before = Stack->stack_hash;
    long long hash_after  = StackHash ( Stack );

    if ( hash_before != hash_after ) {
        Stack->stack_status = Stack->stack_status | ( ( Stack->stack_status | 1 ) << 1 );
    }
}
                                                                      //switch
Err_t Verificator ( Stack_Data_t *Stack )
{
    if ( Stack->size_stack < 0 || Stack->size_stack < Stack->capacity ) {
        Stack->stack_status = Stack->stack_status | ( ( Stack->stack_status | 1 ) << 0 );
        printf ( "Size error\n" );

        return SIZE_ERR;
    }
    if ( Stack->stack_status == HASH_ERR ) {                                   // << 1
        printf ( "Hash error\n" );

        return HASH_ERR;
    }
    if ( Stack->data == nullptr ) {
        Stack->stack_status = Stack->stack_status | ( ( Stack->stack_status | 1 ) << 2 );
        printf ( "Buffer error\n" );

        return DATA_ERR;
    }
    if ( Stack->canary_left != 0xDED || Stack->canary_right != 0xDED ) {
         //Stack->data[-sizeof ( canary_t )] != 0xDED ) { // ||
         //Stack->data[Stack->size_stack] != 0xDED ) {

        Stack->stack_status = Stack->stack_status | ( ( Stack->stack_status | 1 ) << 3 );
        printf ( "Canary error\n" );

        return CANA_ERR;
    }
    if ( Stack->capacity < 0 ) {
        Stack->stack_status = Stack->stack_status | ( ( Stack->stack_status | 1 ) << 4 );
        printf ( "Capacity error\n" );

        return CAPA_ERR;
    }

    return OK;
}
