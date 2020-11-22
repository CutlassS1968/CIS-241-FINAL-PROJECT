#include <stdio.h>

#define MAXCHAR 1000
int main(void) {

    char* data[3000];

    FILE *fp;
    char str[MAXCHAR];
    char* filename = "C:\\Users\\evanl\\CLionProjects\\CIS-241-FINAL-PROJECT\\SPY241Project.txt";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s", filename);
        return 1;
    }

    int c = 0;
    while (fgets(str, MAXCHAR, fp)!= NULL) {
        data[c] = str;
        ++c;
    }

    fclose(fp);

    return 0;
}