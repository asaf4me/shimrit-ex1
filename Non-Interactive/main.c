#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "GenericHashTable.h"

int main()
{
    printf("Int: \n\n");
    Table *tableInt = createTable(4, 0, 2);

    int data_int1 = 1;
    int data_int2 = -6;
    int data_int3 = 16;
    int data_int4 = 36;
    int data_int5 = 1106;
    int data_int6 = 26;

    add(tableInt, &data_int1);
    add(tableInt, &data_int1);
    add(tableInt, &data_int1);
    add(tableInt, &data_int1);
    add(tableInt, &data_int2);
    add(tableInt, &data_int3);
    add(tableInt, &data_int4);
    add(tableInt, &data_int5);
    add(tableInt, &data_int6);
    printf("Before removel: \n");
    printTable(tableInt);
    removeObj(tableInt, &data_int1);
    removeObj(tableInt, &data_int5);
    removeObj(tableInt, &data_int6);
    printf("\nAfter removel: \n");
    printTable(tableInt);
    printf("\n");

    freeTable(tableInt);

    printf("Done\nString: \n\n");
    Table *tableString = createTable(8, 1, 4);

    char *data_string1 = "asaf";
    char *data_string2 = "liraz";
    char *data_string3 = "eli";
    char *data_string4 = "adi";
    char *data_string5 = "efrat";
    char *data_string6 = "zipi";

    add(tableString, data_string1);
    add(tableString, data_string1);
    add(tableString, data_string1);
    add(tableString, data_string1);
    add(tableString, data_string1);
    add(tableString, data_string2);
    add(tableString, data_string3);
    add(tableString, data_string4);
    add(tableString, data_string5);
    add(tableString, data_string6);
    printf("Before removel: \n");
    printTable(tableString);
    printf("\n");
    removeObj(tableString, data_string1);
    removeObj(tableString, data_string1);
    removeObj(tableString, data_string2);
    removeObj(tableString, data_string3);

    printf("\nAfter removel: \n");
    printTable(tableString);
    freeTable(tableString);

    printf("Done \n");

    return EXIT_SUCCESS;
}