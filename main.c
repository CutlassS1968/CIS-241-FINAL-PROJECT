/**
 *          CIS 241 02, Professor Vijay Bhuse
 *                  FINAL PROJECT
 *
 * This program analyzes data from the SPY Index over the
 * last 10 years and presents different statistics.
 *
 * @authors Evan Johns, Andreas Martinez, Andrew Regan
 * @date 12/1/2020
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 2330
#define MAXLEN 90

struct index {
    char date[10];
    float pcRatio;
    int pVol;
    int cVol;
    int tVol;
};

struct index data[LINES];

void readFile(FILE *fp);
void highPCRatio();
void printData();

int main() {

    FILE *fp;
    fp = fopen("SPY241Project.txt", "r");

    if (fp == NULL) {
        printf("Could not open file!");
        return 1;
    }

    readFile(fp);
    fclose(fp);
    //    printData();  // FOR DEBUG

    int choice;

    do {
        printf("---------------------------------------------------------\n");
        printf("What data would you like to conclude from the SPY Index?\n");
        printf("[1]\t\tView highest pull / call ratio\n"
               "[2]\t\tView [insert function here]\n"
               "[3]\t\tView [insert function here]\n"
               "[4]\t\tView [insert function here]\n"
               "[5]\t\tView [insert function here]\n"
               "[0]\t\tExit Program...\n");
        printf("---------------------------------------------------------\n");
        scanf("%i", &choice);

        switch (choice) {
            case 0:
                break;
            case 1:
                highPCRatio();
                break;
            case 2:
                // TODO: ADD FUNCTION 2
                break;
            case 3:
                // TODO: ADD FUNCTION 3
                break;
            case 4:
                // TODO: ADD FUNCTION 4
                break;
            case 5:
                // TODO: ADD  FUNCTION 5
                break;
            default:
                printf("Could not find the selected option\n");
        }
    } while (choice != 0);
    printf("Exiting program...");
    return 0;
}

/**
 * Read the given file fp and save its data to the data struct
 * @param fp
 */
void readFile(FILE *fp) {
    char buffer[MAXLEN];

    fgets(buffer, MAXLEN, fp);  // Need to take off the top line of the file

    for (int i = 0; fgets(buffer, MAXLEN, fp) != NULL; i++) {

        // Set index's date
        char *p = strtok(buffer, ",");
        strcpy(data[i].date, p);

        // Set index's Put / Call Ratio
        p = strtok(NULL, ",");
        data[i].pcRatio = atof(p);

        // Set index's Put Volume
        p = strtok(NULL, ",");
        data[i].pVol = atoi(p);

        // Set index's Call Volume
        p = strtok(NULL, ",");
        data[i].cVol = atoi(p);

        // Set index's Total Volume
        p = strtok(NULL, ",");
        data[i].tVol = atoi(p);
    }
}

/**
 * Calculate the highest Pull/Call ratio from the given data set
 */
void highPCRatio() {
    int c = 0;
    float max = 0;
    for (int i = 0; i < LINES; i++) {
        if (data[i].pcRatio > max) {
            c = i;
            max = data[i].pcRatio;
        }
    }
    printf("The highest Put / Call ratio was on %s and was %g\n\n", data[c].date, data[c].pcRatio);
}

/**
 * Print out all values in the data struct
 */
void printData() {
    for (int i = 0; i < LINES; i++) {
        printf("date=%-10s\tpcRatio=%-4g\tpVol=%-8i\tcVol=%-8i\ttVol=%-10i\n",
               data[i].date, data[i].pcRatio, data[i].pVol, data[i].cVol, data[i].tVol);
    }
}