//
// Created by Vitor Hugo on 25/12/2021.
//

#include "node_generation.h"

NODE_GENERATION * NG_constructor (GENERATION generation) {
    NODE_GENERATION *new_node = calloc(1, sizeof(NODE_GENERATION));

    new_node->generation = generation;
    new_node->next_node_generation = NULL;

    return new_node;
}

void NG_deconstructor (NODE_GENERATION *node) {
    free (node);
}
