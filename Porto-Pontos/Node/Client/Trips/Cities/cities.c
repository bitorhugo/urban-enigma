//
// Created by Vitor Hugo on 24/12/2021.
//

#include "cities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void insert_poi (CITY *city, char *poi);
void remove_poi (CITY *city, char *poi);
POI* search_poi (struct city *city, char *poi);

POINTS insert_coordinates (CITY *city, float coordinate_x, float coordinate_y);
POI* allocate_memory_poi ();
POI* reallocate_memory_poi (CITY *city);
char* allocate_memory_name (uint64_t str_size);
char *realloc_memory_name (POI *poi, uint64_t str_size);

CITY CITY_constructor (char *city_name, float coordinate_x, float coordinate_y) {
    CITY new_city;

    new_city.name = city_name;
    new_city.coordinates = insert_coordinates(&new_city, coordinate_x, coordinate_y);

    new_city.insert_poi = insert_poi;
    new_city.remove_poi = remove_poi;
    new_city.search_poi = search_poi;

    return new_city;
}

void insert_poi (CITY *city, char *poi) {
    if (city->num_of_poi < 1) {
        city->poi = allocate_memory_poi();
        city->poi->name = allocate_memory_name(strlen(poi));
        strcpy(city->poi->name, poi);
        city->num_of_poi = 1;
    }
    else {
        city->poi = reallocate_memory_poi(city);
        POI *temp_poi = city->poi + city->num_of_poi;
        temp_poi->name = allocate_memory_name(strlen(poi));
        strcpy(temp_poi->name, poi);
        city->num_of_poi += 1;
    }
}

void remove_poi (CITY *city, char *poi) {
    if (city->num_of_poi < 1) {
        fprintf(stderr, "ERROR: NO POI AVAILABLE\n");
        return;
    }
    for (size_t i = 0; i < city->num_of_poi; ++i) {
        POI *temp_poi = city->poi + i;
        if (strcmp(temp_poi->name, poi) == 0) {
            for (size_t j = i; j < city->num_of_poi; j++) {
                *(temp_poi + j) = *(temp_poi + j + 1);
            }
            city->num_of_poi -= 1;
            reallocate_memory_poi(city);
            return;
        }
    }
    fprintf(stderr, "ERROR: POI NOT FOUND\n");
}

POI* search_poi (struct city *city, char *poi) {
    if (city->num_of_poi < 1) {
        fprintf(stderr, "ERROR: NO POI AVAILABLE\n");
        return NULL;
    }
    for (size_t i = 0; i < city->num_of_poi; ++i) {
        POI *temp_poi = city->poi + i;
        if (strcmp(temp_poi->name, poi) == 0) {
            return temp_poi;
        }
    }
    fprintf(stderr, "ERROR: POI NOT FOUND\n");
    return NULL;
}

POINTS insert_coordinates (CITY *city, float coordinate_x, float coordinate_y) {
    city->coordinates.x = coordinate_x;
    city->coordinates.y = coordinate_y;
    return city->coordinates;
}

POI* allocate_memory_poi () {
    POI *new_poi = calloc(1, sizeof(POI));
    if (new_poi == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE POI\n");
    }
    return new_poi;
}

POI* reallocate_memory_poi (CITY *city) {
    city->poi = realloc(city->poi, (city->num_of_poi + 1) * sizeof(POI));
    if (city->poi == NULL) {
        fprintf (stderr, "ERROR: NOT ABLE TO REALLOCATE POI\n");
    }
    return city->poi;
}

char* allocate_memory_name (uint64_t str_size) {
    char * name = calloc(str_size, sizeof (char));
    if (name == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE NAME\n");
    }
    return name;
}

char *realloc_memory_name (POI *poi, uint64_t str_size) {
    poi->name = realloc(poi->name, str_size * sizeof(char));
    if (poi->name == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO REALLOCATE COUNTRY NAME\n");
    }
    return poi->name;
}