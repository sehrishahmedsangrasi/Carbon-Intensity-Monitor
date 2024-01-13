#!/bin/bash

# Change to the directory where your daily code is located
cd /home/laiba/Desktop

# Compile and run your daily code
gcc new.c -o daily_executable -lcurl -lcjson
./daily_executable

# Change to the directory where your weekly code is located
cd /home/laiba/Desktop

# Compile and run your weekly code
gcc Data_processing.c -o weekly_executable -lm 
./weekly_executable


