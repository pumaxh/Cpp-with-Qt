#include "stack.h"
#include <assert.h>

#define STACK_SIZE 100

static STACK_TYPE stack[STACK_SIZE];
static int        top_element = -1;

void push(STACK_TYPE value)
{
    assert(!is_full());
    top_element += 1;
    stack[top_element] = value;
}

STACK_TYPE pop()
{
    assert(!is_empty());
    return stack[top_element--];
}

STACK_TYPE top()
{
    assert(!is_empty());
    return stack[top_element];
}

int is_empty()
{
    return top_element == -1;
}

int is_full()
{
    return top_element == STACK_SIZE - 1;
}
