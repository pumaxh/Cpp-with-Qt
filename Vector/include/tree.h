#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define TREE_TYPE int

void insert(TREE_TYPE value);
TREE_TYPE *find(TREE_TYPE value);
void pre_order_traverse(void (*callback)(TREE_TYPE value));

#endif // BINARY_TREE_H
