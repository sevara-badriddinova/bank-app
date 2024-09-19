#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bank.h"

// defining constants
#define NAME_LEN 30
#define DATE_LEN 10

// var for sorting choice
char choice;

// creating an account
struct Bank *create_account(struct Bank *account) {
    if (account != NULL) {
        // variable for accounts number
        int count = 0;
        // storing the list in temp variable 
        struct Bank *temp = account;
        while (temp != NULL) {
            // increasing count for accounts num till the end of the list  
            count++;
            // moving node to the next element
            temp = temp->next;
        }
        // max num of accounts is 10
        if (count >= 10) {
            printf("Maximum account limit reached.\n");
            return account;
        }
    }

    // variable declarations
    int account_number; 
    char account_type; 
    char name[NAME_LEN + 1];
    char date[DATE_LEN + 1];
    double balance;

    while (1) {
        printf("Enter account number (4 digits): ");
        scanf("%d", &account_number); 
        // user input validation for account number
        if (account_number < 1000 || account_number > 9999) {
            printf("Enter a number between 1000 and 9999.\n");
            // clearing input buffer and going back to print statement if account num is not in range
            while (getchar() != '\n');
            continue;
        }

        struct Bank *cur = account;
        int duplicate = 0;
        while (cur != NULL) {
            // if new account num is matching with the existing one, we're flagging it and breaking out of the loop 
            if (cur->account_number == account_number) {
                duplicate = 1;
                break;
            }
            cur = cur->next;
        }
        if (duplicate) {
            printf("Account number already used. Enter a different account number.\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Enter account type: c(hecking), s(avings)\n");
        printf("c or s: "); 
        scanf(" %c", &account_type);
        // converting character to lowercase and validating it
        if (tolower(account_type) != 'c' && tolower(account_type) != 's') {
            printf("Wrong account type. Enter c or s.\n");
            // clearing input buffer
            while(getchar() != '\n');
            // asking user to input the character again 
            continue;
        }
        break;
    }

    printf("Enter account holder's name: ");
    // reading in the name without whitespaces 
    read_line(name, NAME_LEN);

    while (1) {
        printf("Enter open date (YYYY-MM-DD): ");
        scanf("%s", date);
        // date validation, should be in a format YYYY-MM-DD
        if (strlen(date) != 10 || date[4] != '-' || date[7] != '-' || strcmp(date, "0000-00-00") == 0) {
            printf("%s Wrong date format.\n", date);
            continue;
        }
        break;
    }

    printf("Enter balance (number only): $ ");
    scanf("%lf", &balance);

    // allocating memory for the new account
    struct Bank *new_account = malloc(sizeof(struct Bank));
    // checking if allocation was successful
    if (new_account == NULL) {
        printf("Memory allocation failed\n");
        return account;
    }
    // assigning values to the new account
    new_account->account_number = account_number;
    new_account->account_type = tolower(account_type);
    strcpy(new_account->date, date);
    strcpy(new_account->name, name); 
    new_account->balance = balance;
    new_account->next = account;

    printf("Account %d is created.\n\n", account_number);
    return new_account;
}

struct Bank *deposit_money(struct Bank *account) {
    int account_number;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &account_number);

    // setting cur pointer to the beginning of the list
    struct Bank *cur = account;
    
    // iterating till the end of linked list
    while (cur != NULL) {
        // comparing acc number to the current acc number
        if (cur->account_number == account_number) {
            break;
        }
        // moving pointer to the next item
        cur = cur->next;
    }

    // account not found  
    if (cur == NULL) {
        printf("Account not found.\n");
        return account;
    }

    for(;;){
        printf("Enter amount (> 0, number only): $ ");
        scanf("%lf", &amount);
        // input validation for the deposit amount
        if (amount <= 0) {
            printf("Amount must be greater than 0.\n");
            continue;
        }
        // adding the deposit to current balance
        cur->balance += amount;
        // printing out the balance
        printf("Remaining balance: $ %-15.2f\n\n", cur->balance);
        break;
    }
    
    return account;
}

struct Bank *withdraw_money(struct Bank *account) {
    // var initialization 
    int account_number;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &account_number);

    struct Bank *cur = account;
    // traversing the list to check if the cur account num matches the acc number in the list 
    while (cur != NULL) {
        if (cur->account_number == account_number) {
            break;
        }
        // moving pointer to the next item
        cur = cur->next;
    }

    for(;;){
        // account not found
        if (cur == NULL) {
            printf("Account not found.\n");
            return account;
        }

        printf("Enter amount (> 0, number only): $ ");
        scanf("%lf", &amount);

        // validating that input is positive for the withdrawal amount
        if (amount <= 0) {
            printf("Amount must be greater than 0.\n");
            continue;
        }

        // if there is less money on the account, break the operation
        if (cur->balance < amount) {
            printf("Insufficient balance.\n\n");
            break;
        }

        // subtracting amount from the balance
        cur->balance -= amount;
        // printing out the balance
        printf("Remaining balance: $%-15.2f\n\n", cur->balance);
        break;
    }
    return account;
}

// comparison function for quick sort
int compare(const void *a, const void *b) {
    struct Bank *accA = *(struct Bank **)a;
    struct Bank *accB = *(struct Bank **)b;
    switch (choice) {
        // compare by account num
        case 'a':
            return accA->account_number - accB->account_number;
        // by name
        case 'h':
            return strcmp(accA->name, accB->name);
        // by date
        case 'o':
            return strcmp(accA->date, accB->date);
        // by balance
        case 'b':
            // comparing balances
            if (accA->balance > accB->balance){ 
                return 1;
            }
            if (accA->balance < accB->balance){
                return -1;
            } 
            return 0;
        default:
            return 0;
    }
}

void sort_print_account(struct Bank *account) {
    // list is empty
    if (account == NULL) {
        printf("No data\n");
        return;
    }

    // pointers to traverse the list
    struct Bank *sorted_accounts[10];
    int count = 0;
    struct Bank *cur = account;

    // storing each value into the list
    while (cur != NULL) {
        sorted_accounts[count++] = cur;
        cur = cur->next;
    }

    printf("Enter the sorting field: a(ccount number), h(older name), o(pen date), b(alance)\n");
    printf("a, h, o or b: ");
    scanf(" %c", &choice);

    // sorting the list of accounts with qsort
    qsort(sorted_accounts, count, sizeof(struct Bank *), compare);

    printf("#### Type Holder name                    Open date          Balance\n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        // printing out formatted table
        printf("%4d  %c   %-30s  %-10s  %15.2f\n",
            sorted_accounts[i]->account_number,
            toupper(sorted_accounts[i]->account_type),
            sorted_accounts[i]->name,
            sorted_accounts[i]->date,
            sorted_accounts[i]->balance);
    }
    printf("--------------------------------------------------------------------\n\n");
}

// quitting program
void quit_program(struct Bank *account) {
    struct Bank *cur;
    // checking if all accounts are not in the list
    while (account != NULL) {
        // storing a value in cur
        cur = account;
        // moving to the next node
        account = account->next;
        // free the current node
        free(cur);
    }
}

int read_line(char str[], int n) {
    int ch, i = 0;

    while (isspace(ch = getchar()));
    str[i++] = ch;
    while ((ch = getchar()) != '\n' && i < n) {
        str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}