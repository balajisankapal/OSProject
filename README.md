Description ->

Developed a user-friendly banking system with secure login, file-based data storage, and different user roles. Implemented authentication and stored transactional details in files. Incorporated password-protected administrative access. Created multiple login types and enabled account management tasks for administrators. Implemented file locking for data integrity. Utilized socket programming for server-client communication. Demonstrated proficiency in system calls for process management, file management, locking, multithreading, and inter-process communication. Showcased skills in secure authentication, data storage, access control, and multi-user system design.

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
