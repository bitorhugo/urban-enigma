//
// Created by Vitor Hugo on 26/12/2021.
//
#include "Chromosome/chromosome.h"
#include "../../../../Porto-Pontos/Node/Client/Trips/trips.h"

#ifndef TSP_GENETIC_POPULATION_H
#define TSP_GENETIC_POPULATION_H

typedef struct population {
    CHROMOSOME *chromosomes;
    int num_chromosomes;

    void (*insert_chromosomes) (struct population *population, const COUNTRY *booked_trip);
    void (*sort_chromosomes_by_fitness) (struct population *population);

}POPULATION;

POPULATION* POPULATION_constructor ();
void POPULATION_deconstructor (POPULATION *population);

#endif //TSP_GENETIC_POPULATION_H
