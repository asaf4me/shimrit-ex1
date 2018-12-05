#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "GenericHashTable.h"

#define INT_TYPE 0
#define STR_TYPE 1
Table *table = NULL; //Global to handle SIGINT

int readFunc(Table *table, int *data);

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

int main()
{
    int index = -1;
    int data = -1;
    signal(SIGINT, sig_handler);
    printf("Welcome to hash table tester!\n");
    while (1)
    {
        if (table == NULL)
        {
            printf("Type 1 to create table\n");
        }
        else
        {
            printf("Choose:\n2 - Add element\n3 - Remove element\n4 - Search element\n5 - Print table\n6 - Exit\n");
        }
        scanf("%d", &index);
        while (index > 6 || index < 0)
        {
            printf("\nWrong choice, please choose:\n1 - create table\n2 - Add element\n3 - Remove element\n4 - Print table\n5 - Exit\n\n");
            scanf("%d", &index);
        }
        int size = -1;
        int dType = -1;
        int listLength = -1;
        if (index == 1 && table == NULL)
        {
            for (int i = 0; i < 3; i++)
            {
                if (i == 0)
                {
                    printf("Please type table size (size > 0)\n");
                    scanf("%d", &size);
                    while (size < 0)
                    {
                        printf("size < 0, Please type table size\n");
                        scanf("%d", &size);
                    }
                }
                else if (i == 1)
                {
                    printf("Please type table type (type 0 for int, 1 for string)\n");
                    scanf("%d", &dType);
                    while (dType != 0 && dType != 1)
                    {
                        printf("type != 0 || type != 1\n");
                        scanf("%d", &dType);
                    }
                }
                else
                {
                    printf("Please type linked list length (length > 0)\n");
                    scanf("%d", &listLength);
                    while (listLength < 0)
                    {
                        printf("length < 0, Please type linked list length\n");
                        scanf("%d", &listLength);
                    }
                }
            }
            table = createTable(size, dType, listLength);
            assert(table != NULL);
            printf("\nTable created succesfully\ntable size is: %d\ntable type is: %d\nlist length is: %d\n\n", table->size, table->dType, table->listLength);
        }
        else if (index == 2)
        {
            printf("\nPlease enter your data:\n");
            int res;
            if (table->dType == INT_TYPE)
            {
                readFunc(table, &data);
                res = add(table, (void *)data);
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
        else if (index == 3)
        {
            printf("\nPlease enter your data:\n");
            int res;
            if (table->dType == INT_TYPE)
            {
                readFunc(table, &data);
                res = removeObj(table, (void *)data);
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
        else if (index == 4)
        {
            printf("\nPlease enter your data:\n");
            Object *p;
            printf("\nSearching...\n");
            if (table->dType == INT_TYPE)
            {
                readFunc(table, &data);
                p = search(table, (void *)data);
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
                    p = search(table, (void *)str);
                    free(str);
                }
            }
            if (p == NULL)
                printf("\nData didnt found.\n\n");
            else
                printf("\nData found\n\n");
        }
        else if (index == 5)
        {
            printf("\nPrinting table:\n\n");
            printTable(table);
            printf("\n--------------Done!\n\n");
        }
        else if (index == 6)
        {
            printf("Bye Bye...\n");
            break;
        }
    }
    if (table != NULL)
    {
        freeTable(table);
    }
    return 0;
}

int readFunc(Table *table, int *data)
{
    if (table->dType == INT_TYPE)
    {
        scanf("%d", data);
        return !ERROR;
    }
    return ERROR;
}
