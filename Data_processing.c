#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>
#include<time.h>
#define MAX_LINE_LENGTH 256

int compare(const void *a, const void *b) {
    return (*(double *)a - *(double *)b);}
    

    
// Function to calculate standard deviation
double calculate_std(double data[], int n, double mean) {
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += pow(data[i] - mean, 2);
    }

    return sqrt(sum / n);
}
void print_header(char* startdate,char* enddate) {
    printf("+----------------------------------------+\n");
    printf("|             WEEKLY REPORT              |\n");
    printf("|        %s TILL %s      |\n",startdate,enddate);
    printf("+----------------------------------------+\n");
}

void print_footer() {
    printf("+----------------------------------------+\n\n");
}

void print_summary(double avg, double median, double std_dev) {
    printf("|  Average:         %-19.2lf  |\n", avg);
    printf("|  Median:          %-19.2lf  |\n", median);
    printf("|  Standard Dev.:   %-19.2lf  |\n", std_dev);
}

void print_values(int vals[]) {
    printf("|  Moderate Values: %-19d  |\n", vals[0]);
    printf("|  High Values:     %-19d  |\n", vals[1]);
    printf("|  Low Values:      %-19d  |\n", vals[2]);
}

int main() {
    FILE *file;
    char lines[28][MAX_LINE_LENGTH];
    int count = 0;

    // Open the file in binary mode to handle different line endings
    file = fopen("extracted_data.txt", "rb");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Seek to the end of the file
    fseek(file, 0, SEEK_END);

    // Start reading lines from the end of the file
    long position = ftell(file);

    while (count < 28 && position > 0) {
        // Move back two characters to handle both '\r\n' and '\n' line endings
        fseek(file, --position, SEEK_SET);
        if (fgetc(file) == '\n') {
            fseek(file, position + 1, SEEK_SET);
            if (fgets(lines[count], MAX_LINE_LENGTH, file) != NULL) {
                count++;
            }
        }
    }

   /* // Print the last 28 lines in reverse order
    for (int i = count - 1; i >= 0; i--) {
        printf("%s", lines[i]);
    }
    // Print the last 28 lines in reverse order ///get actual from every output
*/
    char temp[50];
    char prefix[20];
    double actual[7]={0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000}; //yahan change kra float se double
    double value;
    int counter=0;
    for (int i =1;i<count - 1; i=i+4) {
           strcpy(temp, lines[i]);
           sscanf(temp, "%s %lf", prefix, &value);
           actual[counter]=value;
           counter++;
           
           
    }
    double sum=0;
    int avg;
    //int n=sizeof(actual)/sizeof(actual[0]);
    int n =counter;
    for(int i=0;i<=n-1;i++){
                    // printf("%lf\n", actual[i]);
                     sum+=actual[i];
    }
    //avg=(int)(sum/n); //avg samjhna hai
    avg = (int)(sum / (double)n);

    char temp2[50];
    char prefix2[20];
    char index[50];
    int mod=0;
    int low=0;
    int high=0;
    int vals[3];
    for (int i =2;i<count - 1; i=i+4) {
           strcpy(temp2, lines[i]);
           sscanf(temp2, "%s %s", prefix2, index);
           if(strcmp(index, "moderate") == 0){
           mod++;
           }
           else if(strcmp(index, "high") == 0){
           high++;
           }
           else if(strcmp(index, "low") == 0){
           low++;
           }
           
    }
    vals[0]=mod;
    vals[1]=high;
    vals[2]=low;
    qsort(actual, n, sizeof(double), compare);
    /*printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%lf ", actual[i]);
    }*/
    printf("\n");
    int mid=(int)((n-1)/2);
    double median=actual[mid];
    //printf("median: %lf\n,AVG: %d\n",median,avg);    
   
    /*for(int i=0;i<3;i++){
    printf("values:%d\n",vals[i]);
    }*/
    // clculating std
    double mean = sum / n;
    double std_dev = calculate_std(actual, n, mean);
    //printf("Standard Deviation: %lf\n", std_dev);
    //TIME STRUCTURES 
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
    printf("\n");
    printf("+------------- DATA ANALYSIS -------------+\n");
    print_header(nextDate,currentDate);
    //print_week_dates();
    print_summary(avg, median, std_dev);
    print_values(vals);
    print_footer();
   
    // Close the file
    fclose(file);
    ///WRITING REPORT TO FILE>>>>
    FILE *file2 = fopen("data_analysis_report.txt", "a");
    if (file2 != NULL) {
    fprintf(file2, "+------------- DATA ANALYSIS -------------+\n");
        fprintf(file2, "|Analysis Period: %s to %s|\n", nextDate, currentDate);
        // Add any additional header information as needed
         fprintf(file2,"|  Average:         %-19d  |\n", avg);
         fprintf(file2,"|  Median:          %-19.2lf  |\n", median);
         fprintf(file2,"|  Standard Dev.:   %-19.2lf  |\n", std_dev);
         fprintf(file2,"|  Moderate Values: %-19d  |\n", vals[0]);
         fprintf(file2,"|  High Values:     %-19d  |\n", vals[1]);
         fprintf(file2,"|  Low Values:      %-19d  |\n", vals[2]);
         fprintf(file2, "+------------- END OF REPORT -------------+\n");
         fprintf(file2,"\n");
        // Close the file
        fclose(file2);
    printf("Report successfully stored in data_analysis_report.txt\n");
}
     else {
        printf("Error opening file for writing.\n");
    }
    fclose(file);
    return 0;
}




