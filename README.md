# bookshell.c

Bookshell.c is a REPL that manages an array of linked list stack heads called shelves, in the shelf stacks contains book nodes containing the author and book name. 
You can also save the current data to a save file, where it can be accessed later in a current or new session.

## To Compile and Run

This project depends on the readline library. On debian-based systems, this can be installed with:  
```sudo apt-get install libreadline8 libreadline8-dev```

To compile and run:  
```gcc bookshell.c -lreadline && ./a.out```<br><br>

# Todo List:  
  [X]  Create command line with basic commands.  
  [X]  Create help command.  
  [X]  Create commands for creating book/shelf nodes and viewing book/shelf nodes.  
  [X]  Create save/open file system.  
  []  Create sorting command for shelves.  
  [X]  Optimize code.  
  [X]  Organize commands for ease of use. 
  [X]  Create way to view available files.  
  [X]  Arrow key functionality to move the caret left and right, and to access command history up/down.  
  [] Fix memory loss caused by readline library.
