//
// Created by Vitor Hugo on 26/12/2021.
//

#ifndef TSP_GENETIC_GENE_H
#define TSP_GENETIC_GENE_H

typedef struct gene {
    int id;
    float x;
    float y;
}GENE;

GENE* GENE_constructor (int size);
void GENE_doconstructor (GENE *gene);


#endif //TSP_GENETIC_GENE_H
