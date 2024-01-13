# Email Logs

Overview
The email_logs.h file is part of a project that involves sending email notifications using the libcurl library and logging events to a file.

##File Structure
email_logs.h: Header file containing functions to log events and send emails.

##Dependencies
libcurl: A library for transferring data with URLs.

Usage
1.Logging Events:
The writeToLog function logs events to the file specified in the code 
(/home/laiba/Desktop/logfile.log).
Call this function with the event message to log
2.Sending Emails:
The send_mail function sends an email using libcurl. Ensure libcurl is properly installed.
3.Executing the Code:
Compile your code, ensuring that libcurl is linked.
Execute the compiled binary.
