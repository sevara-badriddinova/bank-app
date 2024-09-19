// this program simulates bank account app behavior using dynamic memory allocation and linked lists
// you can create an account, deposit/withdraw money, and sort/print account
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bank.h"

int main() {
    char code; 
    struct Bank *bank_account = NULL;

    // printing out main menu options
    while (1) {
        printf("******* Main menu *******\n");
        printf("c(reate an account)\n");
        printf("d(eposit money)\n");
        printf("w(ithdraw money)\n");
        printf("s(sort and print accounts)\n");
        printf("q(uit program)\n");
        printf("*************************\n");
        printf("Enter operation code (c, d, w, s, q): ");
        // reading in user input for operation code
        scanf(" %c", &code);
        // clearing input choice
        while(getchar() != '\n');

        // switch statements to determine what operation to perform 
        // each case has a function call 
        switch (code) {
            case 'c':
                bank_account = create_account(bank_account);
                break;
            case 'd':
                bank_account = deposit_money(bank_account);
                break;
            case 'w':
                bank_account = withdraw_money(bank_account);
                break;
            case 's':
                sort_print_account(bank_account);
                break;
            case 'q':
                quit_program(bank_account);
                return 0;
            default:
                // default case
                printf("Illegal code\n");
                break;
        }
    }
}

