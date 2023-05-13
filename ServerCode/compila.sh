#!/bin/bash 
gcc -pthread -o server $(mysql_config --cflags) server.c cJSON.c $(mysql_config --libs) 