#include "stack.h"

Error_t Stack_Ctor ( Stack_t *stack )
{
    assert ( stack != nullptr );

    #ifdef CANARY_PROTECTION
    stack->data = (elem_t *)calloc( stack->size_stack * sizeof ( elem_t ) + 2 * sizeof ( canary_t ), 1 );
    #else
    stack->data = (elem_t *)calloc( stack->size_stack * sizeof ( elem_t ), 1 );
    #endif
    if ( !stack->data ) {

        return MEMMORY_ERR;
    }
    #ifdef CANARY_PROTECTION
    stack->data = (elem_t*)((char*)stack->data + sizeof(canary_t) );
    Canary_Protection ( stack, (elem_t*)((char*)stack->data - sizeof(canary_t) ) );
    #endif
$   stack->stack_hash = Stack_Hash ( stack );

    return NO_ERR;
}

Error_t Stack_Resize ( Stack_t *stack )
{
    assert ( stack != nullptr );

    stack->size_stack *= stack_mul_coeff;

    #ifdef CANARY_PROTECTION
$   elem_t *canary_begin = (elem_t *)calloc ( stack->size_stack * sizeof ( elem_t ) + 2 * sizeof ( canary_t ), 1 );
    #else
    elem_t *canary_begin = (elem_t *)calloc ( stack->size_stack * sizeof ( elem_t ), 1 );
    #endif
    if ( !canary_begin ) {

        return MEMMORY_ERR;
    }

    #ifdef CANARY_PROTECTION
    elem_t *stack_begin = (elem_t*)((char*)canary_begin + sizeof(canary_t));
$   memcpy ( stack_begin, stack->data, stack->size_stack * ( sizeof ( elem_t ) / stack_mul_coeff ) );
    free ( (char *)stack->data - sizeof ( canary_t ) );
    stack->data = stack_begin;
    Canary_Protection ( stack, canary_begin );
    #else
    memcpy ( canary_begin, stack->data, stack->size_stack * ( sizeof ( elem_t ) / stack_mul_coeff ) );
    free ( stack->data );
    stack->data = canary_begin;
    #endif

    return NO_ERR;
}

void Stack_Dump ( Stack_t *stack, const char* func_name, const char* file_name )
{
    assert ( func_name != nullptr );
    assert ( file_name != nullptr );
    assert ( stack     != nullptr );

    Stack_Verificator ( stack );

$   printf ( "Stack [%p] ", stack->data );
    printf ( " called from%s\n "
             "{\n\t%s  \n\t{ \n "
             " \t\tsize = %d \n "
             " \t\tcapacity = %d \n "
             " \t\tdata [%p]:\n", file_name, func_name, stack->size_stack, stack->capacity, stack->data  );
$   for ( int i = 0; i < stack->size_stack; ++i ) {
$       printf ( "\t\tdata[%d] = ", i );
        printf ( SPECIFIER, stack->data[i] );
        printf ( "\n" );
    }
$   printf ( "\t}\n}\n");
}

void Stack_Dtor ( Stack_t *stack )
{
    assert ( stack != nullptr );
    Stack_Verificator ( stack );
$
    #ifdef CANARY_PROTACTION
    free ( (char*)stack->data - sizeof ( canary_t ) );
    #else
    free ( stack->data );
    #endif
    stack->data = nullptr;
}

void Stack_Push ( Stack_t *stack, const elem_t value )
{
    assert ( stack != nullptr );
    Stack_Rehash ( stack );
    Stack_Verificator ( stack );

    ++(stack->capacity);

$   if ( stack->capacity == stack->size_stack ) {
$       while ( Stack_Resize ( stack ) != NO_ERR ) {     // error
            ;
        }
$   }
$   *( stack->data + stack->capacity - 1 ) = value;

    Stack_Hash ( stack );
}

elem_t Stack_Pop ( Stack_t *stack  )
{
    assert ( stack != nullptr );
    Stack_Rehash ( stack );
    Stack_Verificator ( stack ); // capacity

    elem_t temp = *( stack->data + stack->capacity - 1 );
    --(stack->capacity);
    *( stack->data + stack->capacity ) = 0;

    Stack_Hash ( stack );

    return temp;
}

int Stack_Hash ( Stack_t *stack )
{
    assert ( stack != nullptr );
    Stack_Verificator ( stack );

    long sum  = 0;
    const int stack_size = sizeof ( *stack );
    stack->stack_hash = 0;

    for ( int i = 0; i < stack_size; ++i ) {
        sum += *( (char *)stack + i );
    }

    stack->stack_hash = sum;

    return sum;
}

void Stack_Rehash ( Stack_t *stack )
{
    assert ( stack != nullptr );

    const long long hash_before = stack->stack_hash;
    const long long hash_after  = Stack_Hash ( stack );

    if ( hash_before != hash_after ) {
        stack->stack_status |=  ( stack->stack_status | 1 ) << STACK_HASH_ERR;
    }
}

Stack_Errors_t Stack_Verificator ( Stack_t *stack )
{
    assert ( stack != nullptr );

    if ( stack->size_stack < 0 || stack->size_stack < stack->capacity ) {
        stack->stack_status |= ( stack->stack_status | 1 ) << STACK_SIZE_ERR;
        printf ( "Size error\n" );

        return STACK_SIZE_ERR;
    }
    if ( ( stack->stack_status >> STACK_HASH_ERR ) & 1 ) {
        printf ( "Hash error\n" );

        return STACK_HASH_ERR;
    }
    if ( stack->data == nullptr ) {
        stack->stack_status |= ( stack->stack_status | 1 ) << STACK_DATA_ERR;
        printf ( "Buffer error\n" );

        return STACK_DATA_ERR;
    }
    #ifdef CANARY_PROTECTION
    if ( stack->canary_left != 0xDED || stack->canary_right != 0xDED ||
         stack->data[-sizeof ( canary_t ) / sizeof ( elem_t )] != 0xDED ||
         stack->data[stack->size_stack] != 0xDED ) {

        stack->stack_status |= ( stack->stack_status | 1 ) << STACK_CANA_ERR;
        printf ( "Canary error\n" );

        return STACK_CANA_ERR;
    }
    #endif
    if ( stack->capacity < 0 ) {
        stack->stack_status |= ( stack->stack_status | 1 ) << STACK_CAPA_ERR;
        printf ( "Capacity error\n" );

        return STACK_CAPA_ERR;
    }

    return STACK_NO_ERR;
}

void Canary_Protection ( Stack_t *stack, elem_t *canary_begine )
{
    assert ( canary_begine != nullptr );
    assert ( stack != nullptr );

    *(canary_t *)canary_begine = stack->canary_left;
    *( canary_begine + sizeof( canary_t ) / sizeof ( elem_t ) + stack->size_stack ) = stack->canary_right;
}
