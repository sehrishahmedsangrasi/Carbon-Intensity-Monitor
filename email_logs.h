#include <stdio.h>
#include <time.h>
#include "/home/laiba/Desktop/gmail.h"
void writeToLog(const char *message) {
    FILE *logFile = fopen("/home/laiba/Desktop/logfile.log", "a"); // "a" for append mode

    if (logFile != NULL) {
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        fprintf(logFile, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
                timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
                timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, message);

        fclose(logFile);
    } else {
        printf("Error opening log file.\n");
    }
}

int log_func() {
    writeToLog("SENDING EMAIL TO ""slaiba382@gmail.com""....");
    send_mail();
    writeToLog("EMAIL SENT...");

    return 0;
}

