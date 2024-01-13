#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h> // Include cJSON header
#include "/home/laiba/Desktop/email_logs.h"

// Define a new type of struct for storing the response string
typedef struct {
    char *data;
    size_t size;
} Response;

// Define a new type of struct for storing relevant information
typedef struct {
    double forecast;
    char index[50];  // Adjust the size based on your requirements
    double actual;
} ForecastInfo;

// Write callback function to handle received data
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t real_size = size * nmemb;
    Response *response = (Response *)userp;

    char *ptr = realloc(response->data, response->size + real_size + 1);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 0; // Returning 0 to stop the transfer
    }

    response->data = ptr;
    memcpy(&(response->data[response->size]), contents, real_size);
    response->size += real_size;
    response->data[response->size] = 0; // Null-terminate the string

    return real_size;
}

// Parse JSON data and extract relevant information
ForecastInfo parse_json(const char *json_data) {
    ForecastInfo info = {0.0, "", 0.0};  // Initialize index as an empty string
    cJSON *root = cJSON_Parse(json_data);
    if (root == NULL) {
        fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return info;
    }

    cJSON *dataArray = cJSON_GetObjectItemCaseSensitive(root, "data");
    if (cJSON_IsArray(dataArray) && cJSON_GetArraySize(dataArray) > 0) {
        cJSON *firstEntry = cJSON_GetArrayItem(dataArray, 0);

        cJSON *intensity = cJSON_GetObjectItemCaseSensitive(firstEntry, "intensity");
        if (cJSON_IsObject(intensity)) {
            cJSON *forecast = cJSON_GetObjectItemCaseSensitive(intensity, "forecast");
            cJSON *actual = cJSON_GetObjectItemCaseSensitive(intensity, "actual");
            cJSON *index = cJSON_GetObjectItemCaseSensitive(intensity, "index");

            if (cJSON_IsNumber(forecast)) {
                info.forecast = forecast->valuedouble;
            } else {
                fprintf(stderr, "Error getting forecast value\n");
            }

            // Assuming index is a string, you can directly copy it to the info.index field
            if (cJSON_IsString(index) && index->valuestring != NULL) {
                strncpy(info.index, index->valuestring, sizeof(info.index) - 1);
                info.index[sizeof(info.index) - 1] = '\0';  // Null-terminate the string
            } else {
                fprintf(stderr, "Error getting index value\n");
            }

            if (cJSON_IsNumber(actual)) {
                info.actual = actual->valuedouble;
            } else {
                fprintf(stderr, "Error getting actual value\n");
            }
        } else {
            fprintf(stderr, "Error: 'intensity' is not an object\n");
        }
    } else {
        fprintf(stderr, "Error: 'data' is not an array or is empty\n");
    }

    cJSON_Delete(root);

    return info;
}
int main(void) {
    // Initialize libcurl
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize libcurl\n");
        return 1;
    }
      // Get current time
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
    previousDayTime.tm_mday -= 1;
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

    // Concatenate the dates with the link
    char link[200];  // Adjust the size as needed
    sprintf(link, "https://api.carbonintensity.org.uk/intensity/%sT12:00Z/%sT12:00Z", nextDate, currentDate);

    // Print the resulting link
    printf("Resulting Link: %s\n", link);
    // Set the API endpoint
   // const char *url = "https://api.carbonintensity.org.uk/intensity/-12-02T12:00Z/2023-12-20T12:00Z"; //current dateeeee
    curl_easy_setopt(curl, CURLOPT_URL, link);

    // Set the callback function for received data
    Response response = {NULL, 0};
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        // Handle the error (e.g., return 1 or exit the program)
    } else {
        FILE *file = fopen("output.txt", "a");
        FILE *file2 = fopen("extracted_data.txt", "a");
        // Parse JSON and extract relevant information
        ForecastInfo forecastInfo = parse_json(response.data);
        fwrite(response.data, 1, response.size, file);
        fclose(file);
        printf("Data saved to file: output.txt\n");

        // Print the extracted information
        float actual_threshold=271.000;
        if(forecastInfo.actual>=actual_threshold){
        printf("THE INTENSITY HAS CROSSED THE THRESHOLD VALUE!!!\n");
        log_func();
        }
        
        printf("Forecast: %f\n", forecastInfo.forecast);
        printf("Index: %s\n", forecastInfo.index);
        printf("Actual: %f\n", forecastInfo.actual);
        
        //fwrite(response.data, 1, response.size, file2);
        fprintf(file2, "Forecast: %f\n", forecastInfo.forecast);
        fprintf(file2, "Index: %s\n", forecastInfo.index);
        fprintf(file2, "Actual: %f\n\n", forecastInfo.actual);

        fclose(file2);
        
    }

    // Clean up
    curl_easy_cleanup(curl);
    free(response.data);

    return 0;
}
