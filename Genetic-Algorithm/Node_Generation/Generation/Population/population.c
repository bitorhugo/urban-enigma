//
// Created by Vitor Hugo on 26/12/2021.
//

#include "population.h"
#include <stdlib.h>

// Public functions :: Members of population
void insert_chromosomes (POPULATION *population, const COUNTRY *booked_trip);
void sort_chromosomes_by_fitness (POPULATION *population);

// Private functions
void swap_cromo (CHROMOSOME *a, CHROMOSOME *b);


POPULATION* POPULATION_constructor () {
    POPULATION *new_population = calloc(1, sizeof(POPULATION));

    new_population->insert_chromosomes = insert_chromosomes;
    new_population->sort_chromosomes_by_fitness = sort_chromosomes_by_fitness;

    return new_population;
}

void POPULATION_deconstructor (POPULATION *population) {
    free(population);
}

void insert_chromosomes (POPULATION *population, const COUNTRY *booked_trip) {
    // create chromosomes
    population->chromosomes = CHROMOSOME_constructor(population->num_chromosomes);
    // insert cities into chromosome
    for (size_t i = 0; i < population->num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population->chromosomes + i;
        temp_chromo->num_genes = booked_trip->num_of_cities;
        // insert genes
        temp_chromo->insert_gene(temp_chromo, booked_trip);
        // shuffle genes :: creates random chromosomes of population
        temp_chromo->shuffle_genes(temp_chromo);
        //calculates fitness of chromosome
        temp_chromo->fitness_value = temp_chromo->calculate_fitness(temp_chromo);
    }

}

void sort_chromosomes_by_fitness (POPULATION *population) {
    // Selection Sort used due to low amount of values to compare
    CHROMOSOME *a;
    CHROMOSOME *b;
    for (int i = 0; i < population->num_chromosomes - 1; ++i) {
        for (int j = i + 1; j < population->num_chromosomes; ++j) {
            a = population->chromosomes + i;
            b = population->chromosomes + j;
            if (b->fitness_value > a->fitness_value) {
                swap_cromo(a, b);
            }
        }
    }
}


void swap_cromo (CHROMOSOME *a, CHROMOSOME *b) {
    CHROMOSOME temp = *a;
    *a = *b;
    *b = temp;
}