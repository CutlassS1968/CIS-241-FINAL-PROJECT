/*
 * Andreas Martinez
 * 11.29.2020
 * This program will process stock market data about the SPY index and analyze it
 */

#include <stdio.h>

// Holds the amount of days/lines the file has
const int amtOfDays = 2330;

// To hold the information about a stock
struct stockDay
{
    char* date;
    float putCallRatio;
    int putVolume;
    int callVolume;
    int totalVolume;
};

// To hold all the stock information in a week
struct stockWeek
{
    struct stockDay MONDAY;
    struct stockDay TUESDAY;
    struct stockDay WEDNESDAY;
    struct stockDay THURSDAY;
    struct stockDay FRIDAY;
};

void findHighRatio(struct stockDay[]); // Finds days where the put-call ratio is above 3, indicating a bearish day
void findLowRatio(struct stockDay[]); // Find days where the put-call ratio is below 1, indicating a bullish day
void findHighVolume(struct stockDay[]); // Find days where volume is unusually high, indicating a volatile day
void findHighRatioWeek(struct stockWeek[]); // Find weeks where the stock market didn't perform well
void findLowRatioWeek(struct stockWeek[]); // Find weeks where the stock market did perform well

int main(void)
{


    return 0;
}

// This function cycles through all the days in the struct array and finds the ones with a put-call ratio above 3, then
// it prints them out to the user
void findHighRatio(struct stockDay day[])
{
    for(int i = 0; i < 2330; i++)
    {
        if (day[i].putCallRatio > 3)
        {
            printf("\n%s has a ratio of %d", day[i].date, day[i].putCallRatio);
        }
    }
    printf("\nThis indicates that the market was bearish on these days.");
}

// This function cycles through all the days in the struct array and finds the ones with a put-call ratio above 3, then
// it prints them out to the user
void findLowRatio(struct stockDay day[])
{
    for(int i = 0; i < 2330; i++)
    {
        if (day[i].putCallRatio < 1)
        {
            printf("\n%s has a ratio of %d", day[i].date, day[i].putCallRatio);
        }
    }
    printf("\nThis indicates that the market was bullish on these days.");
}


