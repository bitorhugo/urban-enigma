//
// Created by Vitor Hugo on 26/12/2021.
//

#include "chromosome.h"
#include <stdlib.h>
#include <math.h>

// Public functions :: Chromosome members
void insert_gene (CHROMOSOME *chromosome, const COUNTRY *booked_trip);
void shuffle_genes (CHROMOSOME *chromosome);
float calculate_fitness (CHROMOSOME *chromosome);

// Private functions
float euclidean_dist (GENE* first, GENE *second);

/*
 * Constructor & Deconstructor
 */
CHROMOSOME* CHROMOSOME_constructor (int size) {
    CHROMOSOME *new_chromo = calloc(size, sizeof(CHROMOSOME));

    // iterates over chromosomes to pass function pointers
    for (size_t i = 0; i < size; ++i) {
        CHROMOSOME *temp_chromo = new_chromo + i;
        temp_chromo->insert_gene = insert_gene;
        temp_chromo->shuffle_genes = shuffle_genes;
        temp_chromo->calculate_fitness = calculate_fitness;
    }

    return new_chromo;
}
void CHROMOSOME_deconstructor (CHROMOSOME *chromo) {
    free(chromo);
}


void insert_gene (CHROMOSOME *chromosome, const COUNTRY *booked_trip) {
    // create genes
    chromosome->genes = GENE_constructor(chromosome->num_genes);
    // copy genes from booked_trip
    for (size_t i = 0; i < chromosome->num_genes; ++i) {
        GENE *temp_gene = chromosome->genes + i;
        CITY *temp_city = booked_trip->cities + i;
        temp_gene->id = i;
        temp_gene->x = temp_city->coordinates.x;
        temp_gene->y = temp_city->coordinates.y;
    }
}

void shuffle_genes (CHROMOSOME *chromosome) {
    if (chromosome->num_genes > 1) { // has to have more than one value for swap to occur
        for (size_t i = 0; i < chromosome->num_genes - 1; ++i) {
            size_t j = i + rand() / (RAND_MAX / (chromosome->num_genes - i) + 1);
            // swap
            GENE t = *(chromosome->genes + j);
            *(chromosome->genes + j) = *(chromosome->genes + i);
            *(chromosome->genes + i) = t;
        }
    }
}

float calculate_fitness (CHROMOSOME *chromosome) {
    float sum = 0;
    GENE *temp_gene;
    for (size_t i = 0; i < chromosome->num_genes; ++i) {
        temp_gene = chromosome->genes + i;
        GENE *a = temp_gene;
        GENE *b = temp_gene + 1;
        if (i == chromosome->num_genes - 1) // a = c0, b = c1, ..., a = c5, b = c0
            b = chromosome->genes;
        sum += euclidean_dist(a, b);
    }
    return ((float)1 / sum);
}


float euclidean_dist (GENE* first, GENE *second) {
    return sqrtf(powf(second->x - first->x, 2) + powf(second->y - first->y, 2));
}