//
// Created by Vitor Hugo on 24/12/2021.
//
#include "../../../Date/date.h"
#include "Trips/trips.h"
#include <stdlib.h>
#include <stdbool.h>

#ifndef TEST_CLIENT_H
#define TEST_CLIENT_H

typedef struct client {
    uint32_t VAT;
    char *name;
    char *address;
    uint32_t phone_number;
    DATE birth;
    DATE registration;
    COUNTRY *booked_trips;
    int size_booked_trips;
    COUNTRY *finished_trips;
    int size_finished_trips;

    void (*insert_trip) (struct client *client, COUNTRY country);
    void (*remove_trip) (struct client *client, COUNTRY country);
    void (*edit_trip) (struct client *client, COUNTRY country, char *new_country_name);
    void (*print_trips) (struct client *client, bool is_finished);
    void (*print_finished_trip_specific) (struct client *client, char *country_name, char *city_name, char *poi);

}CLIENT;


CLIENT CLIENT_constructor (char *name, uint32_t VAT, char *address, uint32_t phone_number);
void CLIENT_deconstructor (CLIENT *client);

#endif //TEST_CLIENT_H
