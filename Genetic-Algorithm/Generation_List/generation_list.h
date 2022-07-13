//
// Created by Vitor Hugo on 25/12/2021.
//
#include "../Node_Generation/node_generation.h"
#include <stdlib.h>
#include <stdbool.h>
#ifndef TSP_GENETIC_GENERATION_LIST_H
#define TSP_GENETIC_GENERATION_LIST_H

typedef struct generation_list {
    NODE_GENERATION *head;
    int size_list;

    void (*insert_generation) (struct generation_list *list, bool at_head, GENERATION generation);
    GENERATION* (*search_generation) (struct generation_list *list, uint32_t id);

}GENERATION_LIST;

GENERATION_LIST GL_constructor ();
void GL_deconstructor (GENERATION_LIST *list);

#endif //TSP_GENETIC_GENERATION_LIST_H
