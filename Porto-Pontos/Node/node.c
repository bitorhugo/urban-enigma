//
// Created by Vitor Hugo on 21/12/2021.
//

#include "node.h"
#include <stdlib.h>

NODE* NODE_constructor (CLIENT client) {
    NODE *new_node = calloc(1, sizeof(NODE));
    new_node->client = client;
    new_node->next_node = NULL;
    return new_node;
}

void NODE_deconstructor (NODE *node) {
    free (node);
}