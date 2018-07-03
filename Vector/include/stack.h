#ifndef STACK_H
#define STACK_H

#define STACK_TYPE int

void push(STACK_TYPE value);
STACK_TYPE pop();
STACK_TYPE top();
int is_empty();
int is_full();

#endif // STACK_H
