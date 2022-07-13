//
// Created by Vitor Hugo on 26/12/2021.
//

#include "gene.h"
#include <stdlib.h>

GENE* GENE_constructor (int size) {
    GENE *new_gene = calloc(size, sizeof(GENE));
    return new_gene;
}

void GENE_doconstructor (GENE *gene) {
    free(gene);
}