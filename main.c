#include <stdio.h>
#include <stdlib.h>
#include "GenericHashTable.h"

#define INT_TYPE 0
#define STR_TYPE 1

int main()
{
    // String Table Tester
    void *data5 = (void *)"Asaf";
    void *data7 = (void *)"i";
    void *data8 = (void *)"Liraz";
    Table *table2 = createTable(14, STR_TYPE, 2);
    printf("\n------------------------------------------------------\nStarting String Tester:\nSize of table is: %d\nType of the table is: %d\nList length is: %d\n", table2->size, table2->dType, table2->listLength);
    printf("Add result is: %d\n", add(table2, data5));
    printf("Add result is: %d\n", add(table2, data5));
    printf("Add result is: %d\n", add(table2, data7));

    printf("Printing the table...\n\n");
    printTable(table2);
    printf("\n... Done!\n------------------------------------------------------\n");

    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data8));
    printf("Add result is: %d\n", add(table2, data8));
    printf("Add result is: %d\n", add(table2, data8));
    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data5));
    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data8));
    printf("Add result is: %d\n", add(table2, data8));
    printf("Add result is: %d\n", add(table2, data8));
    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data7));
    printf("Add result is: %d\n", add(table2, data5));

    printf("Delete result is: %d\n", removeObj(table2, data5));
    printf("Delete result is: %d\n", removeObj(table2, data5));
    printf("Delete result is: %d\n", removeObj(table2, data7));
    printf("Add result is: %d\n", add(table2, data5));
    printf("Add result is: %d\n", add(table2, data5));
    printf("Add result is: %d\n", add(table2, data5));

    printf("Printing the table...\n\n");
    printTable(table2);
    freeTable(table2);
    printf("\n... Done!\n------------------------------------------------------\n");

    // // // Int Table Tester
    void *data0 = (void *)0;
    void *data1 = (void *)11;
    void *data2 = (void *)221;
    void *data3 = (void *)11212;
    void *data9 = (void *)11;
    Table *table = createTable(4, INT_TYPE, 4);
    printf("------------------------------------------------------\nStarting Int Tester:\nSize of table is: %d\nType of the table is: %d\nList length is: %d\n", table->size, table->dType, table->listLength);
    printf("Add result is: %d\n", add(table, data0));
    printf("Add result is: %d\n", add(table, data0));
    printf("Add result is: %d\n", add(table, data0));
    printf("Add result is: %d\n", add(table, data0));
    printf("Add result is: %d\n", add(table, data1));
    printf("Add result is: %d\n", add(table, data1));
    printf("Add result is: %d\n", add(table, data1));
    printf("Add result is: %d\n", add(table, data0));
    printf("Add result is: %d\n", add(table, data0));
    printf("Add result is: %d\n", add(table, data2));
    printf("Add result is: %d\n", add(table, data2));
    printf("Add result is: %d\n", add(table, data3));
    printf("Add result is: %d\n", add(table, data3));
    printf("Add result is: %d\n", add(table, data9));
    printf("Add result is: %d\n", add(table, data9));
    printf("Add result is: %d\n", add(table, data9));
    printf("Add result is: %d\n", add(table, data9));
    printf("Add result is: %d\n", add(table, data9));

    printf("Delete result is: %d\n", removeObj(table, data0));
    printf("Delete result is: %d\n", removeObj(table, data0));
    printf("Delete result is: %d\n", removeObj(table, data9));

    printf("Printing the table...\n\n");
    printTable(table);
    freeTable(table);
    printf("\n... Done!\n");

    return 0;
}