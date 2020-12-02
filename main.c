/**
 *          CIS 241 02, Professor Vijay Bhuse
 *                  FINAL PROJECT
 *
 * This program analyzes data from the SPY Index over the
 * last 10 years and presents different statistics.
 *
 * @authors Andreas Martinez, Andrew Regan, Evan Johns
 * @date 12/1/2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 2330
#define MAXLEN 90

/** User interface/input */
void readFile(char *filename);
void userControl(void);
void display(void);

/** Different statistical functions */
void highPCRatio(void);
void lowPCRatio(void);
void seqHighPCRatio(size_t l);
void seqLowPCRatio(size_t l);

/** Various printing functions */
void printSequence(const int* seq, size_t l);
void printIndex(int c);
void printData(void);


struct index {
    char date[10];
    float pcRatio;
    int pVol;
    int cVol;
    int tVol;
};

/** The List of all data entries from a given file */
struct index data[LINES];

int main(void) {
    readFile("SPY241Project.txt");
    userControl();
    return 0;
}

/**
 * Read the given file fp and save its data to the data struct
 * @param filename
 */
void readFile(char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("ERROR: Could not load file: %s", filename);
        exit(1);
    }

    char buffer[MAXLEN];
    fgets(buffer, MAXLEN, fp);  // Take off the top line of the file

    for (int i = 0; fgets(buffer, MAXLEN, fp) != NULL; i++) {
        sscanf(buffer,"%[^,],%f,%d,%d,%d", data[i].date, &data[i].pcRatio, &data[i].pVol, &data[i].cVol, &data[i].tVol);
    }

    fclose(fp);
//    printData();  // FOR DEBUG
}

/**
 * Primary loop of the program, this prompts the user for what
 * they want to do and executes the corresponding functions
 */
void userControl(void) {
    int c;
    size_t l;   // user's desired length for a sequence of indexes
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
                printf("How many days in sequence do you want to analyze?\n");
                scanf("%lu", &l);
                seqHighPCRatio(l);
                break;
            case 4:
                printf("How many days in sequence do you want to analyze?\n");
                scanf("%lu", &l);
                seqLowPCRatio(l);
                break;
            case 5:
                // TODO: ADD FUNCTION 5 [COULD BE LOOK UP SPY FROM GIVEN DATE]
                break;
            case 6:
                // TODO: ADD FUNCTION 6
                break;
            case 7:
                // TODO: ADD FUNCTION 7
                break;
            case 8:
                // TODO: ADD FUNCTION 8
                break;
            case 9:
                // TODO: ADD FUNCTION 9
                break;
            default:
                printf("Could not find the selected option\n");
        }
        l = 0;
    } while (c != 0);
    printf("Exiting program...");
}

/**
 * Displays all possible options
 *
 * NOTE: Instead of having all the options right here, we could give them catagories and they could pick which catagory
 *       and then which corresponding function. This would just essentially be a big switch statement with nested
 *       switch statements. Most of these functions are really easy to make so I just wrote a ton of different ones
 *       as examples
 *
 *          [1]     Put / Call Ratios
 *              [1]     High Put / Call Ratios
 *              [2]     Low Put / Call Ratios
 *              [3]     Highest Put / Call Ratios in sequence
 *              [4]     Lowest Put / Call Ratios in sequence
 *
 *          [2]     Search by date
 *              [1]     Record for a given date
 *              [2]     All records between two given dates
 *
 *          [3]     Total Volume
 *              [1]     Highest Total Volume
 *              [2]     Lowest Total Volume
 *
 *          [4]     Put Volume
 *              [1]     Highest Put Volume
 *              [2]     Lowest Put Volume
 *
 *          [5]     Call Volume
 *              [1]     Highest Call Volume
 *              [2]     Lowest Call Volume
 *
 *          [0]     Exit Program...
 *
 */
void display(void) {
    printf("---------------------------------------------------------\n");
    printf("What data would you like to view from the SPY Index?\n");
    printf("[1]\t\tView highest put / call ratio\n"
           "[2]\t\tView lowest put / call ratio\n"
           "[3]\t\tView a sequence of the highest put / call ratio's\n"
           "[4]\t\tView a sequence of the lowest put / call ratio's\n"
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
    float min = 10;
    for (int i = 0; i < LINES; i++) {
        if (data[i].pcRatio < min) {
            c = i;
            min = data[i].pcRatio;
        }
    }
    printIndex(c);
}

/**
 * Find the highest put / call ratios that are in sequence to each other
 * given by size_t l
 */
void seqHighPCRatio(size_t l) {
    // Initialize highest put call ratios
    int hPCRs[l];
    for (int i = 0; i < l; i++) hPCRs[i] = i;

    float tavg, avg, sum = 0;
    for (int i = l; i < LINES; i++) {

        // Calculate the avg of the current and previous terms
        for (int j = 0; j < l; j++) sum += data[i - (l - j)].pcRatio;
        tavg = sum / l;

        if (tavg > avg) {
            avg = tavg;
            for (int k = 0; k < l; k++) hPCRs[k] = i - (l - k);
        }
        sum = 0;
    }
    printSequence(hPCRs, l);
}

/**
 * Find the highest put / call ratios that are in sequence to each other
 * given by size_t l
 */
void seqLowPCRatio(size_t l) {
    // Initialize lowest put call ratios
    int lPCRs[l];
    for (int i = 0; i < l; i++) lPCRs[i] = i;

    float tavg, avg, sum = 0;
    for (int i = l; i < LINES; i++) {

        // Calculate the avg of the current and previous terms
        for (int j = 0; j < l; j++) sum += data[i - (l - j)].pcRatio;
        tavg = sum / l;

        if (tavg < avg) {
            avg = tavg;
            for (int k = 0; k < l; k++) lPCRs[k] = i - (l - k);
        }
        sum = 0;
    }
    printSequence(lPCRs, l);
}

/**
 * Print out the values in an index
 * @param c index to be printed
 */
void printIndex(int c) {
    printf("Date\t\t Put\\Call Ratio\t\tPut Volume\t\tCall Volume\t\tTotal Volume\n");
    printf("%-9s\t %0.2f\t\t\t\t%-8d\t\t%-8d\t\t%-10d\n",
           data[c].date, data[c].pcRatio, data[c].pVol, data[c].cVol, data[c].tVol);
    printf("\nPress ENTER to Continue");
    getchar();
    getchar();
}

/**
 * Prints a list of indexes
 * @param seq
 * @param l
 */
void printSequence(const int* seq, size_t l) {
    printf("Date\t\t Put\\Call Ratio\t\tPut Volume\t\tCall Volume\t\tTotal Volume\n");
    for (int i = 0; i < l; i++) {
        printf("%-9s\t %0.2f\t\t\t\t%-8d\t\t%-8d\t\t%-10d\n",
               data[seq[i]].date, data[seq[i]].pcRatio,
               data[seq[i]].pVol, data[seq[i]].cVol, data[seq[i]].tVol);
    }
    printf("\nPress ENTER to Continue");
    getchar();
    getchar();
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