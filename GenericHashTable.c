#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "GenericHashTable.h"

/*
@Written by: Asaf Joseph @ID: 203819065.
Description: Implementation of hash table under the right condition.
In the following file you will find the logic of the function mention at the header.
You will be able to easily add/remove/search object at your hash table with this program.
I hope you will find it usefull and easy to read.
P.S further documentation can be found down at the code. 
*/

/**"Private functions"**/
void expand(Table *table);
int addByHash(Table *table, Object *object, int hashKey);

Table *createTable(int size, int dType, int listLength) // Table "constructor"
{
    Table *table = (Table *)malloc(sizeof(Table));
    if (table != NULL)
    {
        table->dType = dType;
        table->listLength = listLength;
        table->size = size;
        table->d = 1;
        table->currentElemets = 0;
        table->arr = (Object **)malloc(size * sizeof(Object *));
        assert(table->arr != NULL);
        for (int i = 0; i < size; i++)
        {
            table->arr[i] = NULL;
        }
        return table;
    }
    return NULL;
}

Object *createObject(void *data) // Object "constructor"
{
    Object *object = (Object *)malloc(sizeof(Object));
    if (object != NULL)
    {
        object->currentListLength = 0;
        object->data = data;
        object->next = NULL;
        return object;
    }
    return NULL;
}

int add(Table *table, void *data)
{
    int hashKey = -1;
    Object *object;
    int addAttemp = ERROR;
    if (table->dType == INT_TYPE) // Hashing with int data
    {
        object = createObject((int *)data);
        hashKey = (table->d * intHashFun(object->data, table->size / table->d));
    }
    else // Hashing with String data
    {
        char *stringObj = (char *)malloc(strlen((char *)data) * sizeof(char) + 1);
        assert(stringObj != NULL);
        strcpy(stringObj, (char *)data);
        object = createObject((char *)stringObj);
        hashKey = (table->d * strHashFun(object->data, table->size / table->d));
    }
    while (addAttemp == ERROR)
    {
        if (table->arr[hashKey] != NULL)
        {
            if (table->currentElemets == table->listLength * table->size)
            {
                expand(table);
                hashKey = (2 * hashKey);
            }
            else if (table->arr[hashKey]->currentListLength == table->listLength)
            {
                for (int i = hashKey + 1; i < hashKey + table->d; i++)
                {
                    addAttemp = addByHash(table, object, i);
                    if (addAttemp != ERROR)
                        return addAttemp;
                }
                expand(table);
                hashKey = (2 * hashKey);
            }
            else
            {
                addAttemp = addByHash(table, object, hashKey);
            }
        }
        else
        {
            addAttemp = addByHash(table, object, hashKey);
        }
    }
    return addAttemp;
}

int addByHash(Table *table, Object *object, int hashKey)
{
    if (table->arr[hashKey] == NULL && hashKey > -1)
    {
        table->arr[hashKey] = object;
        table->arr[hashKey]->currentListLength = 1;
        table->currentElemets++;
        return hashKey;
    }
    else
    {
        // If there is still place in the list, Add to the end
        if (table->arr[hashKey]->currentListLength < table->listLength)
        {
            Object *p = table->arr[hashKey];
            while (p->next)
            {
                p = p->next;
            }
            table->arr[hashKey]->currentListLength++;
            table->currentElemets++;
            p->next = object;
            return hashKey;
        }
    }
    return ERROR;
}

void expand(Table *table)
{
    table->arr = (Object **)realloc(table->arr, 2 * table->size * (sizeof(Object *)));
    assert(table->arr != NULL);
    table->size = table->size * 2;
    table->d = 2 * table->d;
    for (int i = table->size / 2; i < table->size; i++) // Garbage collector
    {
        table->arr[i] = NULL;
    }
    for (int i = (table->size) / 2 - 1; i > 0; i--)
    {
        if (table->arr[i] != NULL)
        {
            table->arr[i * 2] = table->arr[i];
            table->arr[i] = NULL;
        }
    }
}

int removeObj(Table *table, void *data)
{
    int hashKey = -1;
    if (table->dType == INT_TYPE) // Hashing with int data
    {
        hashKey = (table->d * intHashFun(data, table->size / table->d));
    }
    else // Hashing with String data
    {
        hashKey = (table->d * strHashFun(data, table->size / table->d));
    }

    for (int i = hashKey; i < hashKey + table->d; i++)
    {
        Object *myNode = table->arr[i], *previous = NULL;
        while (myNode != NULL)
        {
            if (isEqual(table->dType, myNode->data, data) == EQUAL)
            {
                table->arr[i]->currentListLength--;
                if (previous == NULL)
                    table->arr[i] = myNode->next;
                else
                    previous->next = myNode->next;
                freeObject(myNode, table->dType); //need to free up the memory to prevent memory leak
                table->currentElemets--;
                return i;
            }
            previous = myNode;
            myNode = myNode->next;
        }
    }
    return ERROR;
}

int intHashFun(int *key, int origSize) // Hashing the int
{
    return MOD((long)key, origSize);
}

int strHashFun(char *key, int origSize) // Hashing the string
{
    int hashKey = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        hashKey += (int)key[i];
    }
    return (long)hashKey % origSize;
}

int isEqual(int type, void *data1, void *data2)
{
    if (type == INT_TYPE)
    {
        // Int Compare
        if ((int *)data1 == (int *)data2)
            return EQUAL;
        else
            return NOT_EQUAL;
    }
    else
    {
        //String Compare
        return strcmp((char *)data1, (char *)data2);
    }
}

Object *search(Table *table, void *data)
{
    int hashKey = -1;
    if (table->dType == INT_TYPE) // Hashing with int data
    {
        hashKey = (table->d * intHashFun(data, table->size / table->d));
    }
    else // Hashing with String data
    {
        hashKey = (table->d * strHashFun(data, table->size / table->d));
    }

    Object *object;
    for (int i = hashKey; i < hashKey + table->d; i++)
    {
        object = table->arr[i];
        while (object)
        {
            if (isEqual(table->dType, object->data, data) == 0)
                return object;
            object = object->next;
        }
    }
    return NULL;
}

void printTable(Table *table)
{
    for (int i = 0; i < table->size; i++)
    {
        if (table->arr[i] != NULL)
        {
            printf("[%d]\t", i);
            Object *p = table->arr[i];
            while (p)
            {
                if (table->dType == INT_TYPE)
                {
                    int data = (long)(int *)p->data;
                    if (p->next == NULL)
                        printf("%d", data);
                    else
                        printf("%d \t-->\t ", data);
                }
                else
                {
                    char *data = (char *)p->data;
                    if (p->next == NULL)
                        printf("%s", data);
                    else
                        printf("%s \t-->\t ", data);
                }
                p = p->next;
            }
            printf("\n");
        }
        else
        {
            printf("[%d]\t", i);
            printf("\n");
        }
    }
}

void freeTable(Table *table)
{
    if (table == NULL)
    {
        return;
    }
    for (int i = 0; i < table->size; i++)
    {
        if (table->arr[i] != NULL)
        {
            Object *p = table->arr[i];
            Object *temp;
            while (p)
            {
                temp = p;
                p = p->next;
                freeObject(temp, table->dType);
            }
            table->arr[i] = NULL;
        }
    }
    free(table->arr);
    free(table);
    table->arr = NULL;
    table = NULL;
}

void freeObject(Object *obj, int type)
{
    if (type == STR_TYPE)
    {
        // free String
        free(obj->data);
        free(obj);
    }
    else
    {
        // free Int
        free(obj);
    }
}
