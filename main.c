#include <stdio.h>
#include <stdlib.h>

#define MAX_FOOD_NAME 10
#define MAX_LINE 10
#define MAX_DRINK_NAME 10

void readSpeciality(char *speciality) {
    char c = getchar();
    int i = 0;
    while (c != '(') {
        speciality[i] = c;
        c = getchar();
        i++;
    }

    speciality[i - 1] = '\0';
}

int main() {
    int noOfFoods;
    printf("Please enter number of food types:\n>");
    scanf("%d", &noOfFoods);
    getchar();

    char **foods;
    foods = (char **) malloc(noOfFoods * sizeof(char *));
    if (noOfFoods > 0)
        printf("Please enter %d food types(each on a new line, may contain spaces)\n", noOfFoods);
    for (int i = 0; i < noOfFoods; i++) {
        foods[i] = (char *) malloc(MAX_FOOD_NAME * sizeof(char));
        printf(">");
        gets(foods[i]);
    }

    char ***specialities;
    specialities = (char ***) malloc(noOfFoods * sizeof(char **));
    int *noOfSpecialities;
    noOfSpecialities = (int *) malloc(noOfFoods * sizeof(int));
    double **prices;
    prices = (double **) malloc(noOfFoods * sizeof(double *));

    for (int i = 0; i < noOfFoods; i++) {
        printf("Please input the number of specialities for food %s:\n>", foods[i]);
        scanf("%d", &noOfSpecialities[i]);
        specialities[i] = (char **) malloc(noOfSpecialities[i] * sizeof(char *));
        prices[i] = (double *) malloc(noOfSpecialities[i] * sizeof(double));
        if (noOfSpecialities[i] > 0) {
            getchar();
            printf("Please input %d food(s) of type %s: each line in the format <specific food> (price):\n",
                   noOfSpecialities[i], foods[i]);
            for (int j = 0; j < noOfSpecialities[i]; j++) {
                specialities[i][j] = (char *) malloc(MAX_FOOD_NAME * sizeof(char));
                printf(">");
                readSpeciality(specialities[i][j]);
                char line[MAX_LINE];
                gets(line);
                sscanf(line, "%lf)", &prices[i][j]);
            }
        }
    }
    int noOfDrinks;
    printf("Please input the number of drinks:\n>");
    scanf("%d", &noOfDrinks);
    getchar();
    char **drinks;
    drinks = (char **) malloc(noOfDrinks * sizeof(char *));
    double *drinkPrices;
    drinkPrices = (double *) malloc(noOfDrinks * sizeof(double));

    if (noOfDrinks > 0) {
        printf("Please input %d drink(s): each line in the format <drink> (price):\n", noOfDrinks);
        for (int i = 0; i < noOfDrinks; i++) {
            drinks[i] = (char *) malloc(MAX_DRINK_NAME * sizeof(char));
            printf(">");
            readSpeciality(drinks[i]);
            char line[MAX_LINE];
            gets(line);
            sscanf(line, "%lf)", &drinkPrices[i]);
        }
    }
    FILE *f;
    f=fopen("data.txt","w");
    fprintf(f,"%d:\n",noOfFoods);
    for (int i = 0; i < noOfFoods; i++) {
        fprintf(f,"%s: ", foods[i]);
        for (int j = 0; j < noOfSpecialities[i]; j++)
            fprintf(f,"(%s - %.2lf) ", specialities[i][j], prices[i][j]);
        fprintf(f,"\n");
    }


    for (int i = 0; i < noOfFoods; i++) {
        for (int j = 0; j < noOfSpecialities[i]; j++)
            free(specialities[i][j]);
        free(specialities[i]);
        free(foods[i]);
        free(prices[i]);
    }
    free(specialities);
    free(foods);
    free(prices);


    if (noOfDrinks > 0) {
        fprintf(f,"%d:\n",noOfDrinks);
        fprintf(f,"drinks: ");
        for (int i = 0; i < noOfDrinks - 1; i++)
            fprintf(f,"%s, ", drinks[i]);
        fprintf(f,"%s\n", drinks[noOfDrinks - 1]);
        fprintf(f,"prices: ");
        for (int i = 0; i < noOfDrinks - 1; i++)
            fprintf(f,"%0.0lf, ", drinkPrices[i]);
        fprintf(f,"%0.0lf\n", drinkPrices[noOfDrinks - 1]);
    }

    for (int i = 0; i < noOfDrinks; i++)
        free(drinks[i]);
    free(drinks);
    free(drinkPrices);


    return 0;
}