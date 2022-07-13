//
// Created by Vitor Hugo on 25/12/2021.
//

#include "Generation/generation.h"

#ifndef TSP_GENETIC_NODE_GENERATION_H
#define TSP_GENETIC_NODE_GENERATION_H

typedef struct node_generation {
    GENERATION generation;
    struct node_generation *next_node_generation;
}NODE_GENERATION;

NODE_GENERATION * NG_constructor (GENERATION generation);
void NG_deconstructor (NODE_GENERATION *node);

#endif //TSP_GENETIC_NODE_GENERATION_H
