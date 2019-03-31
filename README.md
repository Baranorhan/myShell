# myShell

myShell has two different operation type 
Opens shell in interactive mode and runs until "quit" command. 
```sh
$ ./myShell 
```
But if a file is given the shell runs the commands in the file if quit command isn't entered
the shell will continue with interactive mode.
```sh
$ ./myShell Batch.bat
```
```sh
$ ./myShell Batch.sh

```
### Tasks
I created two methods for handling ";" and "|" operations first method checks | and sends
separated inputs to the second method which checks for ";" operations and in 
this method I hold a counter to prevent the program print 
 S H E L L >
 before the outputs from threads were printed. 
 
 I also used pthread_create to handling multithread functionality
