//
// Created by Vitor Hugo on 25/12/2021.
//
#include "Population/population.h"
#include "../../../Porto-Pontos/Node/Client/Trips/trips.h"

#include <stdlib.h>
#ifndef TSP_GENETIC_GENERATION_H
#define TSP_GENETIC_GENERATION_H

typedef struct generation {
    uint32_t id;
    POPULATION *parent_population;
    POPULATION *child_population;
    CHROMOSOME *fittest_chromosomes;

    void (*insert_parent_population) (struct generation *generation, const COUNTRY *booked_trip, int size_population);
    void (*insert_child_population) (struct generation *generation, int num_elitism, float mutation_prob);

}GENERATION;

GENERATION GENERATION_constructor ();
void GENERATION_deconstructor (GENERATION *generation);

#endif //TSP_GENETIC_GENERATION_H
