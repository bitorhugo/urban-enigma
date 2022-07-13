//
// Created by Vitor Hugo on 21/12/2021.
//

#include "linked_list.h"
#include <stdio.h>

void insert_client (LINKED_LIST *list, bool at_head, CLIENT client);
CLIENT* search_client (LINKED_LIST *list, CLIENT client);
void remove_client (LINKED_LIST *list, CLIENT client);
void print_clients (LINKED_LIST *list);
void sort_clients (LINKED_LIST *list, short attribute);

void sort_clients_id (LINKED_LIST *list);
void sort_clients_name (LINKED_LIST *list);

LINKED_LIST LL_constructor () {

    LINKED_LIST new_list;
    new_list.head = NULL;
    new_list.list_size = 0;
    new_list.insert_client = insert_client;
    new_list.search_client = search_client;
    new_list.remove_client = remove_client;
    new_list.print_clients = print_clients;
    //new_list.sort_clients = sort_clients;

    return new_list;
}

void LL_deconstructor (LINKED_LIST* list) {
    free(list);
}

void insert_client (LINKED_LIST *list, bool at_head, CLIENT client) {

    if (list->list_size < 1) {
        list->head = NODE_constructor(client);
        list->list_size = 1;
    }
    else {
        NODE *new_node = NODE_constructor(client);
        if (at_head) {
            new_node->next_node = list->head;
            list->head = new_node;
            list->list_size += 1;
        }
        else {
            NODE *temp_node = list->head;
            while (temp_node->next_node != NULL) {
                temp_node = temp_node->next_node;
            }
            temp_node->next_node = new_node;
            list->list_size += 1;
        }
    }

}

CLIENT* search_client (LINKED_LIST *list, CLIENT client) {

    NODE *temp_node = list->head;
    while (temp_node != NULL) {
        if (temp_node->client.VAT == client.VAT){
            printf("Client %d found\n", temp_node->client.VAT);
            return &temp_node->client;
        }
        temp_node = temp_node->next_node;
    }
    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");
    return NULL;
}

void remove_client (LINKED_LIST *list, CLIENT client) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    NODE *temp_node = list->head;
    while (temp_node != NULL) {
        if (temp_node->client.VAT == client.VAT) { // checks if head is to be removed
            list->head = temp_node->next_node;
            NODE_deconstructor(temp_node);
            list->list_size -= 1;
            return;
        }
        if (temp_node->next_node->client.VAT == client.VAT) {
            temp_node->next_node = temp_node->next_node->next_node;
            NODE_deconstructor(temp_node->next_node);
            list->list_size -= 1;
            return;
        }
        temp_node = temp_node->next_node;
    }
    fprintf (stderr, "ERROR: CLIENT NOT FOUND\n");
}

void print_clients (LINKED_LIST *list) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
    }
    NODE *temp_node = list->head;
    while (temp_node != NULL) {
        printf ("Client %d\n", temp_node->client.VAT);
        temp_node = temp_node->next_node;
    }
}

/*
void sort_clients (LINKED_LIST *list, short attribute) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    if (attribute) {
        sort_clients_id (list);
    }
    else {
        sort_clients_name (list);
    }
}*/

