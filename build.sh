#!/bin/bash

rm -rf ./Salary.exe
gcc -g -o Salary cal_salary.c `pkg-config --libs --cflags gtk+-3.0`
