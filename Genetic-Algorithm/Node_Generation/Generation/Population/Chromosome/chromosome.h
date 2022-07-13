//
// Created by Vitor Hugo on 26/12/2021.
//
#include "Gene/gene.h"
#include "../../../../../Porto-Pontos/Node/Client/Trips/trips.h"

#ifndef TSP_GENETIC_CHROMOSOME_H
#define TSP_GENETIC_CHROMOSOME_H

typedef struct chromosome {
    GENE *genes;
    int num_genes;
    float fitness_value;

    void (*insert_gene) (struct chromosome *chromosome, const COUNTRY *booked_trip);
    void (*shuffle_genes) (struct chromosome *chromosome);
    float (*calculate_fitness) (struct chromosome *chromosome);

}CHROMOSOME;

CHROMOSOME* CHROMOSOME_constructor (int size);
void CHROMOSOME_deconstructor (CHROMOSOME *chromo);

#endif //TSP_GENETIC_CHROMOSOME_H
