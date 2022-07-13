//
// Created by Vitor Hugo on 25/12/2021.
//

#include "generation.h"
#include <stdio.h>

void insert_initial_population (GENERATION *generation, const COUNTRY *booked_trip, int size_population);
void insert_next_population (GENERATION *generation, int num_elitism, float mutation_prob);


POPULATION breed_selection (POPULATION population, int num_elitism);
CHROMOSOME* fitness_selection (POPULATION population, const float *cumulative_prob);
POPULATION breed (POPULATION population, int num_elitism);
CHROMOSOME cross_over (CHROMOSOME *parent_one, CHROMOSOME *parent_two);
POPULATION mutation (POPULATION population, float mutation_prob);

POPULATION copy_population (POPULATION *population);
CHROMOSOME copy_chromosome (CHROMOSOME *chromosome);
void calculate_cumulative_prob (POPULATION population, float *cumulative_prob);
float sum_population_fitness (POPULATION population);
float float_in_range (float min, float max);
int int_in_range (int min, int max);
void swap_gene (GENE *a, GENE *b);


GENERATION GENERATION_constructor () {
    GENERATION new_generation;

    new_generation.id = 0;
    new_generation.parent_population = NULL;
    new_generation.child_population = NULL;
    new_generation.fittest_chromosomes = NULL;

    new_generation.insert_parent_population = insert_initial_population;
    new_generation.insert_child_population = insert_next_population;

    return new_generation;
}

void GENERATION_deconstructor (GENERATION *generation) {
    free(generation);
}


void insert_initial_population (GENERATION *generation, const COUNTRY *booked_trip, int size_population) {
    // create population
    generation->parent_population = POPULATION_constructor();
    if (generation->parent_population == NULL) {
        fprintf (stderr, "ERROR: NOT ABLE TO ALLOCATE POPULATION\n");
        return;
    }

     // insert chromosomes
    generation->parent_population->num_chromosomes = size_population;
    generation->parent_population->insert_chromosomes(generation->parent_population, booked_trip);

    // sort chromosomes by fitness
    generation->parent_population->sort_chromosomes_by_fitness(generation->parent_population);

}

void insert_next_population (GENERATION *generation, int num_elitism, float mutation_prob) {

    // makes sure that child population does not exit
    generation->child_population = NULL;
    // create child population
    generation->child_population = POPULATION_constructor();
    *generation->child_population = copy_population(generation->parent_population);

    // choose parents for breeding
    *generation->child_population = breed_selection (*generation->child_population, num_elitism);
    // breed with cross-over
    *generation->child_population = breed (*generation->child_population, num_elitism);
    // mutate population
    *generation->child_population = mutation (*generation->child_population, mutation_prob);
    // sorts chromosomes by fitness
    generation->child_population->sort_chromosomes_by_fitness(generation->child_population);

}

POPULATION copy_population (POPULATION *population) {

    POPULATION new_population = {0};

    new_population.chromosomes = calloc(population->num_chromosomes, sizeof(CHROMOSOME));
    new_population.num_chromosomes = population->num_chromosomes;
    new_population.sort_chromosomes_by_fitness = population->sort_chromosomes_by_fitness;

    for (size_t i = 0; i < population->num_chromosomes; ++i) {
        // set function pointers for each chromosome
        CHROMOSOME *temp_chromo_old = population->chromosomes + i;
        CHROMOSOME *temp_chromo_new = new_population.chromosomes + i;
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

CHROMOSOME copy_chromosome (CHROMOSOME *chromosome) {
    CHROMOSOME new_chromosome;

    new_chromosome.calculate_fitness = chromosome->calculate_fitness;
    new_chromosome.shuffle_genes = chromosome->shuffle_genes;
    new_chromosome.num_genes = chromosome->num_genes;
    new_chromosome.fitness_value = chromosome->fitness_value;

    for (size_t i = 0; i < new_chromosome.num_genes; ++i) {
        GENE *temp_gene_new = new_chromosome.genes + i;
        GENE *temp_gene_old = chromosome->genes + i;

        temp_gene_new->id = temp_gene_old->id;
        temp_gene_new->x = temp_gene_old->x;
        temp_gene_new->y = temp_gene_old->y;
    }

    return new_chromosome;

}

POPULATION breed_selection (POPULATION population, int num_elitism) {

    /*
     * Selection can be performed via:
     * fitness selection (Roulette Wheel)
     * Elitism (most fit chromosomes pass onto next generation automatically)
     */

    // holds the sum of each chromosome probability to be selected
    float cumulative_prob [population.num_chromosomes];
    calculate_cumulative_prob(population, cumulative_prob);

    /*
     * if any chromosome is to be passed via elitism
     * we start to iterate from next chromosome to it
    */
    for (size_t i = num_elitism; i < population.num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population.chromosomes + i;
        temp_chromo = fitness_selection(population, cumulative_prob);
    }

    return population;

}

CHROMOSOME* fitness_selection (POPULATION population, const float *cumulative_prob) {
    // range acts like the spinning mechanism of roulette
    float range = float_in_range(0.0f, 1.0f);

    // iterate over population to find chromosome selected
    for (size_t i = 1; i < population.num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population.chromosomes + i;
        if (range <= cumulative_prob [i] && range > cumulative_prob [i - 1]) {
            return temp_chromo;
        }
    }
    return population.chromosomes; // return first chromosome if failed
}

POPULATION breed (POPULATION population, int num_elitism) {
    /*
     * Cross-over is done by combining n parent chromosomes
     * i.e.
     * CHROMOSOME n0 * CHROMOSOME n1 = CHROMOSOME (n0 * n1)
     * CHROMOSOME n1 * CHROMOSOME n2 = CHROMOSOME (n1 * n2)
     * ...
     * CHROMOSOME nx * CHROMOSOME n0 = CHROMOSOME (nx * n0)
     */

    // save first chromo for successful cross-over
    CHROMOSOME saved_chromo = copy_chromosome ((population.chromosomes + num_elitism));

    CHROMOSOME *parent_one = NULL;
    CHROMOSOME *parent_two = NULL;

    for (size_t i = num_elitism; i < population.num_chromosomes; ++i) {
        parent_one = population.chromosomes + i;
        if (i == population.num_chromosomes - 1) {
            *parent_two = saved_chromo;
        }
        else {
            parent_two = population.chromosomes + i + 1;
        }
        CHROMOSOME *temp_chromo = population.chromosomes + i;
        *temp_chromo = cross_over(parent_one, parent_two);
    }

    return population;
}

CHROMOSOME cross_over (CHROMOSOME *parent_one, CHROMOSOME *parent_two) {
    // choose random non-repeating numbers from parent one
    int num_of_random_numbers = parent_one->num_genes / 2;
    CHROMOSOME *child = parent_one; // copies parent_one
    child->fitness_value = 0; // makes sure that fitness value is 0
    child->shuffle_genes(child); // shuffles genes
    child->num_genes = num_of_random_numbers;

    // fill the rest of child_cromo with parent_two genes
    int flag = 0;
    for (size_t i = 0; i < parent_two->num_genes ; ++i) {
        GENE *temp_parent = parent_two->genes + i;
        for (size_t j = 0; j < child->num_genes; ++j) {
            GENE *temp_child = child->genes + j;
            if (temp_parent->id == temp_child->id) {
                flag = 1;
                break;
            }
        }
        if (flag != 1) {
            GENE *temp_child = child->genes + child->num_genes;
            *temp_child = *temp_parent;
            child->num_genes += 1;
        }
        if (child->num_genes == parent_two->num_genes) break;
        flag = 0;
    }
    return *child;
}

POPULATION mutation (POPULATION population, float mutation_prob) {
    int random_gene_index = 0;
    CHROMOSOME *temp_chromo;
    for (size_t i = 0; i < population.num_chromosomes; ++i) {
        temp_chromo = population.chromosomes + i;
        GENE *temp_gene;
        for (size_t j = 0; j < temp_chromo->num_genes; ++j) {
            temp_gene = temp_chromo->genes + j;
            float p_range = float_in_range(0.0f, 1.0f);
            if (p_range < mutation_prob) {
                do {
                    // random index must be different than current chromosome index
                    random_gene_index = int_in_range(0, temp_chromo->num_genes - 1);
                }
                while (random_gene_index == i);
                swap_gene(temp_gene, temp_chromo->genes + random_gene_index);
            }
        }
        // calculates fitness values of chromosome
        temp_chromo->fitness_value = temp_chromo->calculate_fitness(temp_chromo);
    }
    return population;
}

void calculate_cumulative_prob (POPULATION population, float *cumulative_prob) {

    /*
     * Probability is calculated via the formula
     * Pi = Ai / ∑Aj
     * Pi = probability of each chromosome
     * Ai = fitness of each chromosome
     * ∑Aj = sum of all chromosomes fitness
     */

    // ∑Aj
    float sum_chromosome_fitness = sum_population_fitness(population);

    /*
     * We can think about the sum_prob as a roulette
     * Each section of the roulette represent a percentage
     * that each chromosome have to be selected
     */
    float roulette [population.num_chromosomes];

    for (size_t i = 0; i < population.num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population.chromosomes + i;
        // calculate prob of each chromosome
        roulette [i] = temp_chromo->fitness_value / sum_chromosome_fitness;
        // calculate cumulative probability of each chromosomes
        if (i < 1) {
            cumulative_prob [i] = roulette [i];
        }
        else {
            cumulative_prob [i] = roulette [i] + cumulative_prob [i - 1];
        }
    }
}

float sum_population_fitness (POPULATION population) {
    float sum = 0;
    for (size_t i = 0; i < population.num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population.chromosomes + i;
        sum += temp_chromo->fitness_value;
    }
    return sum;
}

float float_in_range (float min, float max) {
    float scale = rand() / (float) RAND_MAX;
    return min + scale * (max - min);
}

int int_in_range (int min, int max) {
    int num = (rand() % (max - min + 1)) + min;
    return num;
}

void swap_gene (GENE *a, GENE *b) {
    GENE temp = *a;
    *a = *b;
    *b = temp;
}