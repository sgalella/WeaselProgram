#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

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

Sequence *create_sequence(char *text){
    Sequence *sequence = malloc(sizeof(Sequence));
    int length = 0;

    // Get length text
    for (char *c = text; *c != '\0'; c++){
        length += 1;
    }
    sequence->length = length;
    sequence->text = text;

    return sequence;
}

void print_sequence(Sequence *sequence){
    printf("\nTarget Sequence: ");
    for (int i=0; i < sequence->length; i++){
        printf(i + 1 == sequence->length ? "%c\n\n" : "%c", sequence->text[i]);
    }
}

Population *initialize_population(const Sequence *sequence, int num_individuals, int num_selected){
    Population *population = malloc(sizeof(Population));
    population->num_individuals = num_individuals;
    population->num_selected = num_selected;
    population->fitness = (float*) calloc(num_individuals, sizeof(float));
    population->individuals = (int*) malloc(sizeof(int) * num_individuals * sequence->length);
    for (int i=0; i < num_individuals; i++){
        for (int j=0; j < sequence->length; j++){
            population->individuals[i * sequence->length + j] = rand() % 95 + 32;
        }
    }
    return population;
}

float calculate_fitness(const Population *population, const Sequence *sequence){
    float current_fitness, best_fitness=0.0;
    for (int i=0; i < population->num_individuals; i++){
        current_fitness = 0.0;
        for (int j=0; j < sequence->length; j++){
            current_fitness += population->individuals[i * sequence->length + j] == sequence->text[j] ? 1 : 0;
        }
        population->fitness[i] = current_fitness / sequence->length;
        if (population->fitness[i] > best_fitness){
            best_fitness = population->fitness[i];
        }
    }
    return best_fitness;
}

int cmp(const void *a, const void *b){
    return (*(int *)b - *(int *)a);
}

int *argsort(const Population *population){
    float *copy_fitness = (float *) malloc(sizeof(float) * population->num_individuals);
    float *sort_fitness = (float *) malloc(sizeof(float) * population->num_individuals);
    
    int *indexes = (int*) malloc(sizeof(int) * population->num_individuals);
    memcpy(copy_fitness, population->fitness, sizeof(float) * population->num_individuals);
    memcpy(sort_fitness, population->fitness, sizeof(float) * population->num_individuals);
    qsort(sort_fitness, population->num_individuals, sizeof(float), cmp);

    for (int i=0; i < population->num_individuals; i++){
        for (int j=0; j < population->num_individuals; j++){
            if (sort_fitness[i] == copy_fitness[j]){
                indexes[i] = j;
                copy_fitness[j] = -1;
                break;
            }
        }
    }
    free(copy_fitness);
    free(sort_fitness);
    return indexes;
}

void mutation(int *best_indices, const Population *population, const Sequence *sequence){
    int progenitor, mutation;
    int *selected_indices = (int *) malloc(sizeof(int) * population->num_selected);
    int *new_indices = (int *) malloc(sizeof(int) * (population->num_individuals - population->num_selected));
    for (int i=0; i < population->num_selected; i++){
        selected_indices[i] = best_indices[i];
    }
    for (int i=0; i < population->num_individuals - population->num_selected; i++){
        new_indices[i] = best_indices[i + population->num_selected];
    }
    for (int i=0; i < population->num_individuals - population->num_selected; i++){
        progenitor = rand() % population->num_selected;
        mutation = rand() % sequence->length;
        for (int j=0; j < sequence->length; j++){
            if (j == mutation){
                population->individuals[new_indices[i] * sequence->length + j] = rand() % 95 + 32; 
            } else {
                population->individuals[new_indices[i] * sequence->length + j] = 
                    population->individuals[selected_indices[progenitor] * sequence->length + j];
            }
        }
    }
    free(selected_indices);
    free(new_indices);
}

void print_best_solution(int iteration, const Population *population, const Sequence *sequence, int *best_indices){

    for (int i=0; i < sequence->length; i++){
        printf("%c", population->individuals[best_indices[0] * sequence->length + i]);
    }
    
    printf("  (Fitness = %f)\n", population->fitness[best_indices[0]]);
}

int main(int argc, char **argv){

    // Initialize random seed
    srand(time(0));

    // Generate target sequence
    char *sentence = "Hello there! This is a cumulative selection example.";
    Sequence *sequence = create_sequence(sentence);
    print_sequence(sequence);

    // Cumulative Selection Algorithm
    int num_selected = 5;
    int num_individuals = 100;
    int num_iterations = 500;
    Population *population = initialize_population(sequence, num_individuals, num_selected);

    int iteration = 0;
    int *best_indices;
    float best_fitness;

    while (iteration < num_iterations){
        best_fitness = calculate_fitness(population, sequence);
        best_indices = argsort(population);
        mutation(best_indices, population, sequence);

        if (best_fitness == 1){
            printf("\nGoal achieved at iteration %d!\n", iteration);
            print_best_solution(iteration, population, sequence, best_indices);
            break;
        } else if (iteration % 10 == 0){
            printf("[Iteration: %3d]  ", iteration);
            print_best_solution(iteration, population, sequence, best_indices);
        }
       
       iteration += 1;
    }
    return 0;
}
