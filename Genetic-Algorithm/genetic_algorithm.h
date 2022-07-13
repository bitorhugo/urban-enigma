//
// Created by Vitor Hugo on 26/12/2021.
//
#include "../Porto-Pontos/Linked_List/linked_list.h"
#include "Generation_List/generation_list.h"

#ifndef TSP_GENETIC_GENETIC_ALGORITHM_H
#define TSP_GENETIC_GENETIC_ALGORITHM_H

/**
 * initializes genetic algorithm for booked trip
 * @param booked_trip booked trip
 * @param num_iterations algorithm iterations
 * @param size_of_population number of different routes
 * @param num_elitism number of routes that pass automatically due to being good options
 * @param mutation_prob probability of route being mutated
 */
void initialize_algorithm (const COUNTRY *booked_trip, int num_iterations, int size_of_population, int num_elitism, float mutation_prob);

#endif //TSP_GENETIC_GENETIC_ALGORITHM_H
