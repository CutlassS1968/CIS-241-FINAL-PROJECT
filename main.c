/**
 *          CIS 241 02, Professor Vijay Bhuse
 *                  FINAL PROJECT
 *
 * This program analyzes data from the SPY Index over the
 * last 10 years and presents different statistics.
 *
 * @authors Andreas Martinez, Andrew Regan, Evan Johns
 * @date 12/4/2020
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
void highestPCRatio(void);
void lowestPCRatio(void);
void seqHighPCRatio(size_t l);
void seqLowPCRatio(size_t l);
void findHighPCRatios(void);
void findLowPCRatios(void);
void seqPCRatioFromUser(size_t l, float userPCR, char operation);

/** Various printing functions */
void printSequence(const int* seq, size_t l);
void printIndex(int c);
void printData(size_t l);
void findDataByDate(char*);

/** structure for each entry in the file*/
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
}

/**
 * Primary loop of the program, this prompts the user for what
 * they want to do and executes the corresponding functions
 */
void userControl(void) {
    int c;      // User's chosen operation
    size_t l;   // User's desired length for a sequence of indexes'
    float pcr;  // User's chosen Put / Call ratio
    char date[10];
    char operation;
    do {
        display();
        scanf("%i", &c);
        switch (c) {
            case 0:
                break;
            case 1:
                highestPCRatio();
                break;
            case 2:
                lowestPCRatio();
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
                findHighPCRatios();
                break;
            case 6:
                findLowPCRatios();
                break;
            case 7:
                printf("How many days in sequence do you want to analyze\n");
                scanf("%lu", &l);
                printf("Enter the put / call ratio to search by\n");
                scanf("%f", &pcr);
                printf("Would you like to analyze dates with a put / call ratio greater or less than %.2lf on average? [<, >]\n", pcr);
                getchar();
                operation = getchar();
                while (operation != '>' && operation != '<') {
                    printf("Please enter [<] or [>] to analyze the put / call ratio\n");
                    getchar();
                    operation = getchar();
                }
                seqPCRatioFromUser(l, pcr, operation);
                break;
            case 8:
                printf("Please enter a date in the format [MM/DD/YY]: ");
                scanf("%s", date);
                findDataByDate(date);
                break;
            case 9:
                printf("How many entries do you want to see per page?\n");
                scanf("%lu", &l);
                printData(l);
                break;
            default:
                printf("Could not find the selected option\n");
        }
        l = 0;
    } while (c != 0);
    printf("Exiting program...\n");
}

/**
 * Displays all possible options
 */
void display(void) {
    printf("---------------------------------------------------------\n");
    printf("What data would you like to view from the SPY Index?\n");
    printf("[1]\t\tView highest put / call ratio\n"
           "[2]\t\tView lowest put / call ratio\n"
           "[3]\t\tView a sequence of the highest put / call ratio's\n"
           "[4]\t\tView a sequence of the lowest put / call ratio's\n"
           "[5]\t\tView a list of put / call ratio's higher than 3, indicating a market crash\n"
           "[6]\t\tView a list of put / call ratio's lower than 1, indicating a market boom\n"
           "[7]\t\tView a sequence of put / call ratio's based on input criteria\n"
           "[8]\t\tLook up SPY from date\n"
           "[9]\t\tView entire SPY index\n"
           "[0]\t\tExit Program...\n");
    printf("---------------------------------------------------------\n");
}

/**
 * Calculate the highest Put/Call ratio from the given data set
 */
void highestPCRatio(void) {
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
void lowestPCRatio(void) {
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

    float tavg, avg = 0, sum = 0;
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

    float tavg, avg = 0, sum = 0;
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
 * Finds a list of dates where the put call ratio is above 3, which indicates
 * a market crash, or where the spy closes lower than it opens
 */
void findHighPCRatios(void) {
    // Initialize storage for high put call ratios
    int listHighPCRs[30];
    for (int i = 0; i < 30; i++) listHighPCRs[i] = -1;

    int listIndex = 0; // Used to count up listHighPCRs

    // Searches through all dates and finds days with a put call ratio greater than 3
    // Saves those in array listHighPCRs
    for (int i = 0; i < LINES; i++) {
        if (data[i].pcRatio > 3) {
            listHighPCRs[listIndex] = i;
            listIndex++;
        }
    }

    // Cycles through the array until it finds where the array isn't filled and cuts it off when printing sequence
    int index = 0;
    while (listHighPCRs[index] != -1) index++;
    printSequence(listHighPCRs, index);
}

/**
 * Finds a list of dates where the put call ratio is below 1, which indicates
 * a positive day for the market
 */
void findLowPCRatios(void) {
    // Initialize storage for lowest put call ratios
    int listLowPCRs[30];
    for (int i = 0; i < 30; i++) listLowPCRs[i] = -1;

    int listIndex = 0; // Used to count up listLowPCRs

    // Searches through all dates and finds days with a put call ratio lower than 1
    // Saves those in array listLowPCRs
    for (int i = 0; i < LINES; i++) {
        if (data[i].pcRatio < 1) {
            listLowPCRs[listIndex] = i;
            listIndex++;
        }
    }

    // Cycles through the array until it finds where the array isn't filled and cuts it off when printing sequence
    int index = 0;
    while (listLowPCRs[index] != -1) index++;
    printSequence(listLowPCRs, index);
}

/**
 * This function allows the user to search the data for a sequence of dates
 * that have a PCR average above or below userPCR (a PCR determined by the user)
 * @param l Size of displayed sequence
 * @param userPCR   Users chosen Pull / Call Ratio
 * @param operation Users chosen operation (<, >)
 */
void seqPCRatioFromUser(size_t l, float userPCR, char operation) {
    // Initialize the PCRS
    int pCRs[l];

    int flag = 0;
    float tavg, avg = userPCR, sum = 0;
    for (int i = l; i < LINES; i++) {

        // Calculate the avg of the current and previous terms
        for (int j = 0; j < l; j++) sum += data[i - (l - j)].pcRatio;
        tavg = sum / l;

        // If the dates that fit the criteria is found, print the top information
        if ((tavg < avg || tavg > avg) && flag != 1) {
            printf("Date\t   Put\\Call Ratio\t  Put Volume\t Call Volume\t  Total Volume\n");
            flag = 1;
        }

        // Depending on what the operation performed is, check if the average of the PCR dates
        // are greater or less than the avg specified by the user, if true print the dates
        if (operation == '<') {
            if (tavg < avg) {
                for (int k = 0; k < l; k++)
                    printf("%-9s\t\t\t %0.2f\t\t%8d\t\t%8d\t\t%10d\n",
                           data[i - (l - k)].date, data[i - (l - k)].pcRatio, data[i - (l - k)].pVol,
                           data[i - (l - k)].cVol, data[i - (l - k)].tVol);;
                printf("\n");
            }
        } else {
            if (tavg > avg) {
                for (int k = 0; k < l; k++)
                    printf("%-9s\t\t\t %0.2f\t\t%8d\t\t%8d\t\t%10d\n",
                           data[i - (l - k)].date, data[i - (l - k)].pcRatio, data[i - (l - k)].pVol,
                           data[i - (l - k)].cVol, data[i - (l - k)].tVol);;
                printf("\n");
            }
        }
        sum = 0;
    }

    if (flag == 0) {
        printf("No dates were found that fit that criteria. Press ENTER to Continue\n");
        getchar();
        getchar();
    }
}

/**
 * This function finds and prints the SPY data
 * for a given date
 */
void findDataByDate(char date[]) {
    // Searches the data for the date, if found prints the data and returns back to main

    for (int i = 0; i < LINES; i++) {
        if (strcmp(data[i].date, date) == 0) {
            printIndex(i);
            return;
        }
    }

    // If not found, let user know and return to main
    printf("Date not found.\nPress ENTER to Continue");
    getchar();
    getchar();
}

/**
 * Print out the values in an index
 * @param c index to be printed
 */
void printIndex(int c) {
    printf("Date\t   Put\\Call Ratio\t  Put Volume\t Call Volume\t  Total Volume\n");
    printf("%-9s\t\t\t %0.2f\t\t%8d\t\t%8d\t\t%10d\n",
           data[c].date, data[c].pcRatio, data[c].pVol, data[c].cVol, data[c].tVol);
    printf("\nPress ENTER to Continue\n");
    getchar();
    getchar();
}

/**
 * Prints a list of indexes
 * @param seq The sequence of indexes to be printed
 * @param l   The Size of the sequence to be printed
 */
void printSequence(const int* seq, size_t l) {
    printf("Date\t   Put\\Call Ratio\t  Put Volume\t Call Volume\t  Total Volume\n");
    for (int i = 0; i < l; i++) {
        printf("%-9s\t %0.2f\t\t%8d\t%8d\t%10d\n",
               data[seq[i]].date, data[seq[i]].pcRatio,
               data[seq[i]].pVol, data[seq[i]].cVol, data[seq[i]].tVol);
    }
    printf("\nPress ENTER to Continue\n");
    getchar();
    getchar();
}

/**
 * Print out all values in the data struct in pages
 * @param l     The size of lines to be printed
 */
void printData(size_t l) {
    int c = 1;
    printf("-----------------------------------Page %d-----------------------------------\n", c);
    printf("Date\t   Put\\Call Ratio\t  Put Volume\t Call Volume\t  Total Volume\n");
    for (int i = 0; i < LINES; i++) {
        printf("%-9s\t\t\t %0.2f\t\t%8d\t\t%8d\t\t%10d\n", data[i].date, data[i].pcRatio, data[i].pVol, data[i].cVol, data[i].tVol);
        if ((i + 1) % l == 0) {
            printf("-----------------------------------Page %d-----------------------------------\n", c);
            printf("\nPress ENTER to Continue...\n");
            getchar();
            c++;
            printf("-----------------------------------Page %d-----------------------------------\n", c);
        }
    }
}