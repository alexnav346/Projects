Project 1 By Cameron Kozan & Alexander Navarre

Table of Contents
-----------------
1. Functions we've implemented
2. How to run the program
3. Known bugs
4. Sample outputs
-----------------

1. Functions we've implemented
------------------------------
We've implemented a number of functions to help us with making client-server communication slightly easier along with communication with files.
We've made a function that will write a specific message to the buffer and send it as well.
Along with that function, we've made a function that will encapsulate the data within the file along with appending our new message, for message store.
Also, we created two classes called Writer and Reader, which both take in a Socket object so that each Socket will have their own respective Reader and Writer objects.
Within these classes, we do things such as check to make sure the buffer is empty, if its not, read the buffer and do some action on the data that we received, along with a multitude of other things.

2. How to run the program
------------------------------
The only thing you need to do to run the program is A. have java installed on the machine you wish to run it on and B. run "java -jar Server.jar" for the server and "java -jar Client.jar <hostname here>" without the <>. 
Both Jar files should be included within the zip file, or you can compile them yourself with the provided source code.
Along with that, you need a messages.txt file in the same directory as Server.jar

3. Known Bugs
------------------------------
Currently, there are no known bugs.


4. Sample outputs
-----------------------------
Input: MSGGET
Output: 200 OK
One can never be too rich, too thin, or have too much bandwidth.

Input: LOGIN root root1
Output: 410 Wrong UserID or Password

Input: LOGIN root root01
Output: 200 OK

Input: QUIT
Output: 200 OK

Input: SHUTDOWN
Output: 200 OK