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

// 482 weeks and 4 days between the two dates

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

void readFile(char *filename);
void userControl(void);
void display(void);
void highPCRatio(void);
void lowPCRatio(void);
void printIndex(int c);
void printData(void);


void seriesHighPCRatio();
void printSeries(int* series);
// SERIES of days that were low/high (running avg)

int main(void) {
    readFile("SPY241Project.txt");
    userControl();
    return 0;
}

/**
 * Read the given file fp and save its data to the data struct
 * @param fp
 */
void readFile(char *filename) {

    FILE *fp;
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("ERROR: Could not load file: %s", filename);
        exit(1);
    }

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
    fclose(fp);
//    printData();  // FOR DEBUG
}

void userControl(void) {
    int c;
    int *ptr;
    do {
        display();
        scanf("%i", &c);
        switch (c) {
            case 0:
                break;
            case 1:
                highPCRatio();
                break;
            case 2:
                lowPCRatio();
                break;
            case 3:
                // TODO: FIX seriesHighPCRatio
//                seriesHighPCRatio();
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
    } while (c != 0);
    printf("Exiting program...");
}

// instead of all the options right here, give them the option to choose their catagory,
// then ask them more about what they would like to know
void display(void) {
    printf("---------------------------------------------------------\n");
    printf("What data would you like to view from the SPY Index?\n");
    printf("[1]\t\tView highest put / call ratio\n"
           "[2]\t\tView lowest put / call ratio\n"
           "[3]\t\tView a series of the highest put / call ratio's\n"
           "[4]\t\tView [insert function here]\n"
           "[5]\t\tView [insert function here]\n"
           "[0]\t\tExit Program...\n");
    printf("---------------------------------------------------------\n");
}

/**
 * Calculate the highest Put/Call ratio from the given data set
 */
void highPCRatio(void) {
    int c = 0;
    float max = 0;
    for (int i = 0; i < LINES; i++) {
        if (data[i].pcRatio > max) {
            c = i;
            max = data[i].pcRatio;
        }
    }
    printIndex(c);
}

/**
 * Calculate the lowest Put/Call ratio from the given data set
 */
void lowPCRatio(void) {
    int c = 0;
    float min = 0;
    for (int i = 0; i < LINES; i++) {
        if (data[i].pcRatio < min) {
            c = i;
            min = data[i].pcRatio;
        }
    }
    printIndex(c);
}

// TODO: THIS is bRoKe
///**
// * Find the highest put / call ratios that are in sequence to each other;
// * right now this goes to 3, but this needs to be modified to be any variable
// * of sizes
// */
//void seriesHighPCRatio(size_t s) {
//
//    // Initialize highest put call ratios
//    int hPCRs[s];
//    for (int i = 0; i < s; i++) hPCRs[i] = i;
//
//    float temp;
//    float avg = 0;
//    for (int i = 0; i < LINES; i++) {
//        temp = (data[i].pcRatio + data[i - 1].pcRatio + data[i - 2].pcRatio) / 3;
//        if (temp > avg) {
//            avg = temp;
//            for (int j = 0; j < s; j++)
//            hPCRs[j] = i - (s - j);
////            hPCRs[j] = i - 1;
////            hPCRs[j] = i - 2;
//        }
//    }
//    printSeries(hPCRs);
//}

/**
 * Print out the values in an index
 * @param c index to be printed
 */
void printIndex(int c) {
    printf("Date\t Put\\Call Ratio\t\tPut Volume\t\tCall Volume\t\tTotal Volume\n");
    printf("%-7s\t %-g\t\t\t\t%-8d\t\t%-8d\t\t%-10d\n",
           data[c].date, data[c].pcRatio, data[c].pVol, data[c].cVol, data[c].tVol);
    printf("\nPress ENTER to Continue");
    getchar();
    getchar();
}

void printSeries(int* series) {
    printf("Date\t Put\\Call Ratio\t\tPut Volume\t\tCall Volume\t\tTotal Volume\n");
    for (int i = 0; i < sizeof series; i++) {
        printf("%-7s\t %-g\t\t\t\t%-8d\t\t%-8d\t\t%-10d\n",
               data[series[i]].date, data[series[i]].pcRatio, data[series[i]].pVol, data[series[i]].cVol, data[series[i]].tVol);
    }
}

/**
 * Print out all values in the data struct
 */
void printData(void) {
    for (int i = 0; i < LINES; i++) {
        printf("date=%-10s\tpcRatio=%-4g\tpVol=%-8i\tcVol=%-8i\ttVol=%-10i\n",
               data[i].date, data[i].pcRatio, data[i].pVol, data[i].cVol, data[i].tVol);
    }
}