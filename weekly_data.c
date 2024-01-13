#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main(){
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    // Extract current date components
    int currentDay = localTime->tm_mday;
    int currentMonth = localTime->tm_mon + 1;  // Months are 0-indexed
    int currentYear = localTime->tm_year + 1900;  // Years since 1900

    // Get the date of the next day
    struct tm previousDayTime = *localTime;
    previousDayTime.tm_mday -= 7;
    mktime(&previousDayTime);  // Adjust the time structure

    // Extract previous day components
    int previousDay = previousDayTime.tm_mday;
    int previousMonth = previousDayTime.tm_mon + 1;
    int previousYear = previousDayTime.tm_year + 1900;

    // Format the current date as a string
    char currentDate[11];  // MM/DD/YYYY + '\0'
    sprintf(currentDate, "%04d-%02d-%02d", currentYear, currentMonth, currentDay);

    // Format the next day as a string
    char nextDate[11];  // MM/DD/YYYY + '\0'
    sprintf(nextDate, "%04d-%02d-%02d", previousYear, previousMonth, previousDay);
    /*char link[200];  // Adjust the size as needed
    sprintf(link, "https://api.carbonintensity.org.uk/intensity/%sT12:00Z/%sT12:00Z", nextDate, currentDate);

    // Print the resulting link
    printf("Resulting Link: %s\n", link);*/
    
    return 0;
};

   
