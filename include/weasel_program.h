#ifndef WEASEL_PROGRAM_H
#define WEASEL_PROGRAM_H

typedef struct {
    int length;
    char *text;
} Sequence;

typedef struct {
    int num_individuals;
    int num_selected;
    float *fitness;
    int *individuals;
} Population;

Sequence *create_sequence(char *text);
void print_sequence(Sequence *sequence);
Population *initialize_population(const Sequence *sequence, int num_individuals, int num_selected);
float calculate_fitness(const Population *population, const Sequence *sequence);
float calculate_mean_fitness(const Population *population);
int cmp(const void *a, const void *b);
int *argsort(const Population *population);
void mutation(int *best_indices, const Population *population, const Sequence *sequence);
void print_best_solution(int iteration, const Population *population, const Sequence *sequence, int *best_indices);

#endif