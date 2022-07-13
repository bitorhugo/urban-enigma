//
// Created by Vitor Hugo on 24/12/2021.
//
#include "Coordinates/coordinates.h"
#include "POI/poi.h"

#ifndef TEST_CITIES_H
#define TEST_CITIES_H

typedef struct city {
    char *name;
    POINTS coordinates;
    POI *poi;
    int num_of_poi;

    void (*insert_poi) (struct city *city, char *poi);
    void (*remove_poi) (struct city *city, char *poi);
    POI* (*search_poi) (struct city *city, char *poi);

}CITY;

CITY CITY_constructor (char *city_name, float coordinate_x, float coordinate_y);
void CITY_deconstructor (CITY *city);

#endif //TEST_CITIES_H
