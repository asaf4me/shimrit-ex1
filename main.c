#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "GenericHashTable.h"

#define INT_TYPE 0
#define STR_TYPE 1

int main()
{
    int index;
    Table *table = NULL;
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
            int data;
            int res;
            char *str;
            printf("\nPlease enter your data:\n");
            if (table->dType == INT_TYPE)
            {
                scanf("%d", &data);
                res = add(table, (void *)data);
            }
            else
            {
                sscanf("%s", &str);
                res = add(table, (void *)str);
            }
            if (res == ERROR)
                printf("Add failed...\n\n");
            else
                printf("Add success.\n\n");
        }
        else if (index == 3)
        {
            int data;
            int res;
            char *str;
            printf("\nPlease enter your data:\n");
            if (table->dType == INT_TYPE)
            {
                scanf("%d", &data);
                res = removeObj(table, (void *)data);
            }
            else
            {
                sscanf("%s", &str);
                res = removeObj(table, (void *)str);
            }
            if (res == ERROR)
                printf("Remove failed...\n\n");
            else
                printf("Remove success.\n\n");
        }
        else if (index == 4)
        {
            printf("\nSearching...\n");
            int data;
            char *str;
            Object *res;
            printf("Please enter your data:\n");
            if (table->dType == INT_TYPE)
            {
                scanf("%d", &data);
                res = search(table, (void *)data);
            }
            else
            {
                sscanf("%s", &str);
                res = search(table, (void *)str);
            }
            if (res == NULL)
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
