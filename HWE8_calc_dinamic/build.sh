#!/bin/bash

gcc -shared -o libcalculator.so calculator.c
gcc main.c -ldl -o calculator
