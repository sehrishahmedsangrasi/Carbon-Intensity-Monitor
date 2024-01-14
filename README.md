## Integration of Email Logs and Weekly Data Processing
## Overview
The project integrates two key components, email_logs.h that facilitates logging and Gmail-based communication, utilizing gmail.h, while weekly_data.c calculates date ranges for querying carbon intensity data. 

## Files
## 1. email_logs.h
## Overview
   The email_logs.h file provides functionality for logging and sending emails. It depends 
   on the gmail.h file for email sending using libcurl.

## File Structure
   email_logs.h: Header file containing functions for logging and sending emails.
   gmail.h: Header file for sending emails using libcurl.
   
## Usage
   1.Include the Header:
     Include the email_logs.h header in your main program.
     
   2.Logging and Sending Email:
     Use the writeToLog function to log messages.
     The log_func function logs the start and end of email sending and sends an email.

## 2. weekly_data.c
## Overview
   The weekly_data.c file is a C program that calculates the current date and the date of 
   the day one week ago. It formats these dates and can be used to construct a link for 
   querying carbon intensity data from a specified API.

## File Structure
   weekly_data.c: C program to calculate and format current and previous dates.

## Usage
   1.Compile and Run:
     Compile the C code using your preferred compiler.
     Execute the compiled binary.
     
   2.Output:
     The program calculates the current date and the date of the day one week ago.
     It formats these dates as strings (YYYY-MM-DD).
