There are 3 files ->
1. input.c
2. client.c
3. server.c

Command to run code ->
gcc input.c -o input  
./input

gcc -pthread server.c -o server 
./server

gcc client.c -o client
./client

Note->
Everytime we end session we need to change port number. 
