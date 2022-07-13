//
// Created by Vitor Hugo on 24/12/2021.
//

#include "client.h"
#include <stdio.h>
#include "stdlib.h"
#include "string.h"


void insert_trip (CLIENT *client, COUNTRY country);
void remove_trip (CLIENT *client, COUNTRY country);
void edit_trip (struct client *client, COUNTRY country, char *new_country_name);
void print_trips (struct client *client, bool is_finished);
void print_finished_trip_specific (struct client *client, char *country_name, char *city_name, char *poi);

void print_finished_trips (CLIENT *client);
void print_booked_trips (CLIENT *client);
COUNTRY* search_finished_trip (CLIENT *client, char *country_name);

COUNTRY* allocate_memory_trips ();
COUNTRY* reallocate_memory_trip (CLIENT *client);
char* allocate_memory_name (uint64_t str_size);
char *realloc_memory_name (COUNTRY *country, uint64_t str_size);

CLIENT CLIENT_constructor (char *name, uint32_t VAT, char *address, uint32_t phone_number) {
    CLIENT new_client;

    new_client.name = name;
    new_client.VAT = VAT;
    new_client.address = address;
    new_client.phone_number = phone_number;

    new_client.insert_trip = insert_trip;
    new_client.remove_trip = remove_trip;
    new_client.edit_trip = edit_trip;
    new_client.print_trips = print_trips;
    new_client.print_finished_trip_specific = print_finished_trip_specific;

    return new_client;
}

void CLIENT_deconstructor (CLIENT *client) {
    free(client);
}

void insert_trip (CLIENT *client, COUNTRY country) {

    if (client->size_booked_trips < 1) {
        client->booked_trips = allocate_memory_trips();
        *client->booked_trips = country;
        client->size_booked_trips = 1;
    }
    else {
        client->booked_trips = reallocate_memory_trip(client);
        COUNTRY *temp_country = client->booked_trips + client->size_booked_trips;
        temp_country->name = 0, temp_country->cities = 0, temp_country->num_of_cities = 0;
        *temp_country = country;
        client->size_booked_trips +=1;
    }
}

void remove_trip (CLIENT *client, COUNTRY country) {
    for (size_t i = 0; i < client->size_booked_trips; ++i) {
        COUNTRY *temp_country = client->booked_trips + i;
        if (strcmp(temp_country->name, country.name) == 0) {
            for (size_t j = i; j < client->size_booked_trips; ++j) {
                *(client->booked_trips + j) = *(client->booked_trips + j + 1);
            }
            client->size_booked_trips -= 1;
            client->booked_trips = reallocate_memory_trip(client);
            return;
        }
    }
    fprintf(stderr, "ERROR: TRIP NOT FOUND\n");
}

void edit_trip (struct client *client, COUNTRY country, char *new_country_name) {
    COUNTRY new_country = COUNTRY_constructor(new_country_name);
    for (size_t i = 0; i < client->size_booked_trips; ++i) {
        COUNTRY *temp_country = client->booked_trips + i;
        if (strcmp(temp_country->name, country.name) == 0) {
            *temp_country = new_country;
            fprintf(stdout, "WARNING: COUNTRY NAME CHANGED, VARIABLE NAME MIGHT NOT BE THE SAME AS COUNTRY NAME\n");
            return;
        }
    }
}

void print_trips (struct client *client, bool is_finished) {
    if (is_finished) {
        print_finished_trips (client);
    }
    else {
        print_booked_trips (client);
    }
}

void print_finished_trip_specific (struct client *client, char *country_name, char *city_name, char *poi) {

    COUNTRY *temp_country = search_finished_trip(client, country_name);
    if (temp_country == NULL) {
        fprintf(stderr, "ERROR: FINISHED TRIP NOT FOUND\n");
        return;
    }
    printf ("Country %s", temp_country->name);
    // TODO: CITY AND POI SEARCH
}

void print_booked_trips (CLIENT *client) {
    if (client->size_booked_trips < 1) {
        fprintf(stderr, "ERROR: NO BOOKED TRIPS AVAILABLE\n");
        return;
    }
    printf("Booked trips list:\n");
    for (size_t i = 0; i < client->size_booked_trips; ++i) {
        COUNTRY *temp_country = client->booked_trips + i;
        printf ("Country [%zu] :: %s\n", i, temp_country->name); // size_t -> unsigned long format specifier
    }
}

void print_finished_trips (CLIENT *client) {
    if (client->size_finished_trips < 1) {
        fprintf(stderr, "ERROR: NO FINISHED TRIPS AVAILABLE\n");
        return;
    }
    printf ("Finished trips list:\n");
    for (size_t i = 0; i < client->size_finished_trips; ++i) {
        COUNTRY *temp_country = client->finished_trips + i;
        printf ("Country [%zu] :: %s\n", i, temp_country->name);
    }
}

COUNTRY* search_finished_trip (CLIENT *client, char *country_name) {
    if (client->size_finished_trips < 1) {
        fprintf(stderr, "ERROR: NO FINISHED TRIPS AVAILABLE\n");
        return NULL;
    }
    for (size_t i = 0; i < client->size_finished_trips; ++i) {
        COUNTRY *temp_country = client->finished_trips + i;
        if (strcmp(temp_country->name, country_name) == 0) {
            return temp_country;
        }
    }
    return NULL;
}

COUNTRY* allocate_memory_trips () {
    COUNTRY *new_country = calloc(1, sizeof(COUNTRY));
    if (new_country == NULL){
        fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE TRIP\n");
    }
    return new_country;
}

COUNTRY* reallocate_memory_trip (CLIENT *client) {
    client->booked_trips = realloc(client->booked_trips, (client->size_booked_trips + 1) * sizeof(COUNTRY));
    if (client->booked_trips == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO REALLOCATE TRIP\n");
    }
    return client->booked_trips;
}


