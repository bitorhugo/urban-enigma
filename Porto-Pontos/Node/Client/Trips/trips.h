//
// Created by Vitor Hugo on 24/12/2021.
//
#include "Cities/cities.h"

#ifndef TEST_TRIPS_H
#define TEST_TRIPS_H

typedef struct country {
    char *name;
    CITY *cities;
    int num_of_cities;

    void (*insert_city) (struct country *country, CITY city);
    void (*remove_city) (struct country *country, CITY city);
    void (*edit_city) (struct country *country, CITY city, char* new_city_name, float new_x, float new_y);
    CITY* (*search_city) (struct country *country, CITY city);

}COUNTRY;

COUNTRY COUNTRY_constructor (char *country_name);
void COUNTRY_deconstructor (COUNTRY *country);

#endif //TEST_TRIPS_H
