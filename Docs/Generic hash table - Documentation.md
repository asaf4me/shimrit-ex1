**Generic hash table - Documentation** 

*Description* : At this exercise we have been requested to implement generic hash table, that means that the data structure is generic and the same logic can served both int and string. The hashing promise you to handle operation such as: add, remove, search, delete  on the average time of o(1).

**Repos**: `https://github.com/asaf4me/shimrit-ex1`

A the repo you will be able to find interactive main, to check all the function you wants.

*Note :* the way that we have been requested to implement the int handle we actually created aliasing, at the git repository i have updated the  implementation to allocate memory and free it on int as well.

**Instructions:** first make sure that the main folder of the program contain the main.c file ant then compile by type make at the command line, the output will be an executable file named 'run', then simply run it with: **./run**

**Compile/Valgrind:** 

`gcc -c main.c -o main.o -Wall -Wvla -g ` <br />
`gcc -c GenericHashTable.c -o GenericHashTable.o -Wall -Wvla -g ` <br />
`gcc GenericHashTable.o main.o -o run` <br />
``valgrind --tool=memcheck --leak-check=full -v ./run``



 

