#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// defining constants
#define NAME_LEN 30
#define DATE_LEN 10

// struct including all the vars
struct Bank {
    int account_number; 
    char account_type; 
    char name[NAME_LEN + 1];
    char date[DATE_LEN + 1];
    double balance;
    struct Bank *next; // pointer to the next account
};

// function declarations
struct Bank *create_account(struct Bank *account);
struct Bank *deposit_money(struct Bank *account);
struct Bank *withdraw_money(struct Bank *account);
void sort_print_account(struct Bank *account);
void quit_program(struct Bank *account);
// function to read in strings
int read_line(char str[], int n);

#endif
