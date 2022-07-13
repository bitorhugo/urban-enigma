//
// Created by Vitor Hugo on 26/12/2021.
//

#include "genetic_algorithm.h"
#include <stdio.h>

POPULATION* copy_child_population (POPULATION *population);

void initialize_algorithm (const COUNTRY *booked_trip, int num_iterations, int size_population, int num_elitism, float mutation_prob) {

    // create linked list
    GENERATION_LIST generation_list = GL_constructor();

    if (size_population % 2 != 0 || size_population == 0) {
        fprintf (stderr, "ERROR: POPULATION SIZE MUST BE PAIR AND POSITIVE\n");
        return;
    }
    if (num_elitism % 2 != 0 || num_elitism >= booked_trip->num_of_cities) {
        fprintf(stderr, "ERROR: ELITISM NUMBER MUST BE PAIR AND SMALLER THAN NUMBER OF GENES\n");
        return;
    }

    // insert first generation
    GENERATION current_generation = GENERATION_constructor();
    current_generation.insert_parent_population(&current_generation, booked_trip, size_population);
    current_generation.insert_child_population(&current_generation, num_elitism, mutation_prob);
    generation_list.insert_generation(&generation_list, false, current_generation);

    for (size_t i = 1; i <= num_iterations; ++i) {

        // insert parent population
        current_generation.parent_population = copy_child_population(current_generation.child_population);
        current_generation.insert_child_population(&current_generation, num_elitism, mutation_prob);
        current_generation.id = i;
        generation_list.insert_generation(&generation_list, false, current_generation);

    }

}

POPULATION* copy_child_population (POPULATION *population) {

    POPULATION *new_population = POPULATION_constructor();

    new_population->chromosomes = calloc(population->num_chromosomes, sizeof(CHROMOSOME));
    new_population->num_chromosomes = population->num_chromosomes;

    for (size_t i = 0; i < population->num_chromosomes; ++i) {
        // set function pointers for each chromosome
        CHROMOSOME *temp_chromo_old = population->chromosomes + i;
        CHROMOSOME *temp_chromo_new = new_population->chromosomes + i;
        temp_chromo_new->shuffle_genes = population->chromosomes->shuffle_genes;
        temp_chromo_new->calculate_fitness = population->chromosomes->calculate_fitness;

        temp_chromo_new->genes = calloc(population->chromosomes->num_genes, sizeof(GENE));
        temp_chromo_new->num_genes = population->chromosomes->num_genes;

        for (size_t j = 0; j < population->chromosomes->num_genes; ++j) {
            // set coordinates and id for each gene
            GENE *temp_gene_old = temp_chromo_old->genes + j;
            GENE *temp_gene_new = temp_chromo_new->genes + j;
            temp_gene_new->id = temp_gene_old->id;
            temp_gene_new->x = temp_gene_old->x;
            temp_gene_new->y = temp_gene_old->y;
        }

    }

    return new_population;

}