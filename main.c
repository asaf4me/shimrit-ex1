#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include "GenericHashTable.h"

Table *table = NULL; //Global to handle SIGINT
#define TRUE 1

void sig_handler(int signo)
{
    if (signo == SIGINT)
    {
        if (table != NULL)
            freeTable(table);
    }
    printf("\nProccess killed, all the memory freed\n");
    exit(EXIT_SUCCESS);
}

int validation(char c)
{
    if (!isdigit(c))
    {
        printf("Invalid input, please try again\n");
        return ERROR;
    }
    return (int)c;
}

int input()
{
    int c, data;
    if (table == NULL)
    {
        printf("Type 1 to create table\n");
        if (scanf("%d", &c) == 0 || c != 1)
        {
            printf("Wrong input... ");
            while (getchar() != '\n')
                ;
            return ERROR;
        }
        int size, dType, listLength;
        printf("Please type table size (size > 0)\n");
        while (scanf("%d", &size) == 0 || size <= 0)
        {
            printf("Wrong input... Please type table size (size > 0)\n");
            while (getchar() != '\n')
                ;
        }
        printf("Please type table type (type 0 for int, 1 for string)\n");
        while (scanf("%d", &dType) == 0 || (dType != 0 && dType != 1))
        {
            printf("Wrong input... Please type table type (type 0 for int, 1 for string)\n");
            while (getchar() != '\n')
                ;
        }
        printf("Please type linked list length (length > 0)\n");
        while (scanf("%d", &listLength) == 0 || listLength <= 0)
        {
            printf("Wrong input... Please type linked list length (length > 0)\n");
            while (getchar() != '\n')
                ;
        }
        table = createTable(size, dType, listLength);
        assert(table != NULL);
        printf("\nTable created succesfully\ntable size is: %d\ntable type is: %d\nlist length is: %d\n\n", table->size, table->dType, table->listLength);
    }
    else
    {
        printf("Choose:\n2 - Add element\n3 - Remove element\n4 - Search element\n5 - Print table\n6 - Exit\n");
        if (scanf("%d", &c) == 0 || c < 2 || c > 6)
        {
            printf("Wrong input... Choose:\n2 - Add element\n3 - Remove element\n4 - Search element\n5 - Print table\n6 - Exit\n");
            while (getchar() != '\n')
                ;
            return ERROR;
        }
        if (c == 2)
        {
            printf("\nPlease enter your data:\n");
            int res = ERROR;
            if (table->dType == INT_TYPE)
            {
                while (scanf("%d", &data) == 0)
                {
                    printf("Wrong input... Please enter your data (int)\n");
                    while (getchar() != '\n')
                        ;
                }
                res = add(table, (void *)(long)data);
            }
            else
            {
                unsigned int len_max = 1;
                unsigned int current_size = 0;
                char *str = (char *)malloc(len_max * sizeof(char));
                current_size = len_max;
                if (str != NULL)
                {
                    int c = EOF;
                    unsigned int i = 0;
                    c = getchar();
                    while ((c = getchar()) != '\n' && c != EOF)
                    {
                        str[i++] = (char)c;
                        if (i == current_size)
                        {
                            current_size = i + len_max;
                            str = realloc(str, current_size);
                        }
                        str[i] = '\0';
                    }
                }
                res = add(table, (void *)str);
                free(str);
            }

            if (res == ERROR)
                printf("Add failed...\n\n");
            else
                printf("Add success.\n\n");
        }
        else if (c == 3)
        {
            printf("\nPlease enter your data:\n");
            int res;
            if (table->dType == INT_TYPE)
            {
                while (scanf("%d", &data) == 0)
                {
                    printf("Wrong input... Please enter your data (int)\n");
                    while (getchar() != '\n')
                        ;
                }
                res = removeObj(table, (void *)(long)data);
            }
            else
            {
                unsigned int len_max = 1;
                unsigned int current_size = 0;
                char *str = (char *)malloc(len_max * sizeof(char));
                current_size = len_max;
                if (str != NULL)
                {
                    int c = EOF;
                    unsigned int i = 0;
                    c = getchar();
                    while ((c = getchar()) != '\n' && c != EOF)
                    {
                        str[i++] = (char)c;
                        if (i == current_size)
                        {
                            current_size = i + len_max;
                            str = realloc(str, current_size);
                        }
                        str[i] = '\0';
                    }
                }
                res = removeObj(table, (void *)str);
                free(str);
            }
            if (res == ERROR)
                printf("\nRemove failed...\n\n");
            else
                printf("\nRemove success.\n\n");
        }
        else if (c == 4)
        {
            printf("\nPlease enter your data:\n");
            Object *p; 
            if (table->dType == INT_TYPE)
            {
                while (scanf("%d", &data) == 0)
                {
                    printf("Wrong input... Please enter your data (int)\n");
                    while (getchar() != '\n')
                        ;
                }
                printf("\nSearching...\n");
                p = search(table, (void *)(long)data);
            }
            else
            {
                unsigned int len_max = 1;
                unsigned int current_size = 0;
                char *str = (char *)malloc(len_max * sizeof(char));
                current_size = len_max;
                if (str != NULL)
                {
                    int c = EOF;
                    unsigned int i = 0;
                    c = getchar();
                    while ((c = getchar()) != '\n' && c != EOF)
                    {
                        str[i++] = (char)c;
                        if (i == current_size)
                        {
                            current_size = i + len_max;
                            str = realloc(str, current_size);
                        }
                        str[i] = '\0';
                    }
                    printf("\nSearching...\n");
                    p = search(table, (void *)str);
                    free(str);
                }
            }
            if (p == NULL)
                printf("\nData didnt found.\n\n");
            else
                printf("\nData found\n\n");
        }
        else if (c == 5)
        {
            printf("\nPrinting table:\n\n");
            printTable(table);
            printf("\n--------------Done!\n\n");
        }
        else if (c == 6)
        {
            printf("Bye Bye...\n");
            return (EXIT_SUCCESS);
        }
    }

    return ERROR;
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, sig_handler);
    printf("Welcome to hash table tester!\n");
    while (TRUE)
    {
        if (input() == EXIT_SUCCESS)
            break;
    }

    if (table != NULL)
        freeTable(table);

    return 0;
}
