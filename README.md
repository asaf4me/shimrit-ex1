# shimrit-ex1
this exersice implements hash table under certain rules. <br />
@Written by : asaf joseph, for education purpose.

compile with: <br />
gcc -c main.c -o main.o -Wall -Wvla -g <br />
gcc -c GenericHashTable.c -o GenericHashTable.o -Wall -Wvla -g <br />
gcc GenericHashTable.o main.o -o run -Wall -Wvla -g  <br />

valgrind with: <br />
valgrind --tool=memcheck --leak-check=full -v ./run <br />

Note: this is the interactive version, for non-interactive go to non-interactive/
