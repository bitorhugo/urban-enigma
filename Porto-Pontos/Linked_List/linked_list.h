//
// Created by Vitor Hugo on 21/12/2021.
//

#ifndef TEST_LINKED_LIST_H
#define TEST_LINKED_LIST_H
#include "../Node/node.h"
#include <stdlib.h>
#include <stdbool.h>

/*
 * A linked list is represented by a pointer to the first node of the linked list.
 * The first node is called the head.
 * If the linked list is empty, then the value of the head is NULL.
 */

typedef struct linked_list {
    NODE *head;
    int list_size;

    void (*insert_client) (struct linked_list *list, bool at_head, CLIENT client);
    CLIENT* (*search_client) (struct linked_list *list, CLIENT client);
    void (*remove_client) (struct linked_list *list, CLIENT client);
    void (*print_clients) (struct linked_list *list);
    void (*sort_clients) (struct linked_list *list, short attribute);


}LINKED_LIST;


LINKED_LIST LL_constructor ();
void LL_deconstructor (LINKED_LIST* list);




#endif //TEST_LINKED_LIST_H
