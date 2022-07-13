//
// Created by Vitor Hugo on 25/12/2021.
//

#include "generation_list.h"
#include <stdio.h>
#include <stdlib.h>

void insert_generation (GENERATION_LIST *list, bool at_head, GENERATION generation);
GENERATION* search_generation (GENERATION_LIST *list, uint32_t id);

GENERATION_LIST GL_constructor () {
    GENERATION_LIST new_list;

    new_list.head = NULL;
    new_list.size_list = 0;

    new_list.insert_generation = insert_generation;

    return new_list;
}

void GL_deconstructor (GENERATION_LIST *list) {
    free(list);
}

void insert_generation (GENERATION_LIST *list, bool at_head, GENERATION generation) {
    if (list->size_list < 1) {
        list->head = NG_constructor(generation);
        list->size_list = 1;
    }
    else {
        NODE_GENERATION *new_node = NG_constructor(generation);
        if (at_head) {
            new_node->next_node_generation = list->head;
            list->head = new_node;
            list->size_list += 1;
        }
        else {
            NODE_GENERATION *temp_node = list->head;
            while (temp_node->next_node_generation != NULL) {
                temp_node = temp_node->next_node_generation;
            }
            temp_node->next_node_generation = new_node;
            list->size_list += 1;
        }
    }
}

GENERATION* search_generation (GENERATION_LIST *list, uint32_t id) {
    if (list->size_list < 1) {
        fprintf(stderr, "ERROR: NO GENERATIONS FOUND\n");
        return NULL;
    }

    NODE_GENERATION * temp_node = list->head;
    while (temp_node != NULL) {
        if (temp_node->generation.id == id) {
            return &temp_node->generation;
        }
    }

    fprintf(stderr, "ERROR: GENERATION NOT FOUND\n");
    return NULL;
}