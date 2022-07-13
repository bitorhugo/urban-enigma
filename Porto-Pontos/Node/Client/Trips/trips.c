//
// Created by Vitor Hugo on 24/12/2021.
//

#include "trips.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void insert_city (COUNTRY *country, CITY city);
void remove_city (COUNTRY *country, CITY city);
void edit_city (struct country *country, CITY city, char* new_city_name, float new_x, float new_y);
CITY* search_city (struct country *country, CITY city);

CITY* allocate_memory_city ();
CITY* reallocate_memory_city (COUNTRY *country);

COUNTRY COUNTRY_constructor (char *country_name) {
    COUNTRY new_country;

    new_country.name = country_name;

    new_country.insert_city = insert_city;
    new_country.remove_city = remove_city;
    new_country.edit_city = edit_city;
    new_country.search_city = search_city;

    return new_country;
}

void COUNTRY_deconstructer (COUNTRY *country) {
    free (country);
}

void insert_city (COUNTRY *country, CITY city) {
    if (country->num_of_cities < 1) {
        country->cities = allocate_memory_city();
        *country->cities = city;
        country->num_of_cities += 1;
    }
    else {
        country->cities = reallocate_memory_city(country);
        CITY *temp_city = country->cities + country->num_of_cities;
        temp_city->name = 0, temp_city->coordinates.x = 0, temp_city->coordinates.y = 0, temp_city->poi = 0, temp_city->num_of_poi = 0;
        *temp_city = city;
        country->num_of_cities += 1;
    }
}

void remove_city (COUNTRY *country, CITY city) {
    for (size_t i = 0; i < country->num_of_cities; ++i) {
        CITY *temp_city = country->cities + i;
        if (strcmp(temp_city->name, city.name) == 0) {
            for (size_t j = i; j < country->num_of_cities; ++j) {
                *(temp_city + j) = *(temp_city + j + 1);
            }
            country->num_of_cities -= 1;
            country->cities = reallocate_memory_city(country);
            return;
        }
    }
    fprintf(stderr, "ERROR: CITY NOT FOUND\n");
}

void edit_city (struct country *country, CITY city, char* new_city_name, float new_x, float new_y) {
    CITY new_city = CITY_constructor(new_city_name, new_x, new_y);
    CITY *temp_city = search_city(country, city);
    if (temp_city == NULL) {
        fprintf(stderr, "ERROR: CITY NOT FOUND\n");
        return;
    }
    *temp_city = new_city;
}

CITY* search_city (struct country *country, CITY city) {
    if (country->num_of_cities < 1) {
        fprintf(stderr, "ERROR: NO CITIES AVAILABLE\n");
        return NULL;
    }
    for (size_t i = 0; i < country->num_of_cities; ++i) {
        CITY *temp_city = country->cities + i;
        if (strcmp(temp_city->name, city.name) == 0) {
            return temp_city;
        }
    }
    return NULL;
}

CITY* allocate_memory_city () {
    CITY *new_city = calloc(1, sizeof(CITY));
    if (new_city == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE CITY\n");
    }
    return new_city;
}

CITY* reallocate_memory_city (COUNTRY *country) {
    country->cities = realloc(country->cities, (country->num_of_cities + 1) * sizeof(CITY));
    if (country->cities == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO REALLOCATE CITY\n");
    }
    return country->cities;
}