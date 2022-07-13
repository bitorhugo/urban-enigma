//
// Created by Vitor Hugo on 21/12/2021.
//

#include "Client/client.h"

#ifndef TEST_NODE_H
#define TEST_NODE_H

typedef struct node {
    CLIENT client;
    struct node *next_node;
}NODE;

NODE* NODE_constructor (CLIENT client);
void NODE_deconstructor (NODE* node);


#endif //TEST_NODE_H
