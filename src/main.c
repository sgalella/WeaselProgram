#include<stdio.h>
#include<stdlib.h>
#include "weasel_program.h"

int main(int argc, char **argv){
    // Initialize random seed
    srand(1234);

    // Initialize file with fitness over iterations
    FILE *fp = fopen("results/fitness.txt", "w");

    // Generate target sequence
    char *sentence = NULL;
    if (argc == 1){
        sentence = "This is the weasel program.";
    } else {
        sentence = argv[1];
    }
    Sequence *sequence = create_sequence(sentence);
    print_sequence(sequence);

    // The Weasel Program
    int num_selected = 5;
    int num_individuals = 100;
    int num_iterations = 500;
    Population *population = initialize_population(sequence, num_individuals, num_selected);

    int iteration = 0;
    int *best_indices;
    float best_fitness, mean_fitness;

    while (iteration < num_iterations){
        best_fitness = calculate_fitness(population, sequence);
        mean_fitness = calculate_mean_fitness(population);
        best_indices = argsort(population);
        mutation(best_indices, population, sequence);

        if (best_fitness == 1){
            printf("\nGoal achieved at iteration %d!\n", iteration);
            print_best_solution(iteration, population, sequence, best_indices);
            printf("\n");
            break;
        } else if (iteration % 10 == 0){
            printf("[Iteration: %3d]  ", iteration);
            print_best_solution(iteration, population, sequence, best_indices);
        }
       fprintf(fp, "%d %f %f\n", iteration, best_fitness, mean_fitness);
       iteration += 1;
    }
    return 0;
}
