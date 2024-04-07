#include "global.h"

struct command {
	char *cmd;
	void (*function)();
}; 

// Argument Conversions
struct command conversions1[] = {
	{"exit", exitCMD},
	{"help", help},
	{"create", create},
	{"clear", clear},
	{"show", show},
	{"rm", rm},
	{NULL, NULL}
};

// Conversions for create argument
struct command createConvert[] = {
	{"shelf", createShelf},
	{"book", createBook},
	{NULL, NULL}
};

// Conversions for show argument
struct command showConvert[] = {
	{"shelf", showShelf},
	{"shelves", showShelves},
	{NULL, NULL}
};

// Calls conversion maps
void executeCommand(char* cmdName, struct command* convertLayer)
{
	for (struct command* entry = convertLayer; entry->cmd != NULL; entry++)
       	{
		if (strcmp(entry->cmd, cmdName) == 0)
	       	{
			entry->function();
			return;
		}
	}
	printf("Command not recognized, type \"help\" for a list of commands.\n");
}

// Clears screen
void clear()
{
	system("clear");
}

// Exits shell
void exitCMD()
{
	printf("Exiting..\n");

	for(int i = 0; i < SHELVES; i++)
			emptyShelf(i);

	exit(1);  
}

// Prints argument help from file
void help()
{
	FILE *file = fopen("commandHelp.txt", "r");
	if(file == NULL)
	{
		printf("ERROR commandHelp.txt file not found.\n");
		return;
	}

	system("clear");

	char c  = fgetc(file);
	while(c != EOF)
	{
		printf("%c", c);
		c = fgetc(file);
	}
	fclose(file);
}

// Calls create conversion map
void create()
{
	executeCommand(userArgs[1], createConvert);
}

// Calls show conversion map
void show()
{
	executeCommand(userArgs[1], showConvert);
}

// Calls addBook in bookshelf.c
void createBook()
{
	addBook(userArgs[2], userArgs[3], &shelves[atoi(userArgs[4])-1]);
}

// Prints header information for all shelves
void showShelves()
{
	for(int i = 0; i < SHELVES; i++)
	{
		if(shelves[i] != NULL)
			printf("Shelf %d: %s by %s\n", i+1, shelves[i]->bookName, shelves[i]->author);
		else
			printf("Shelf %d: SHELF SLOT EMPTY\n", i+1);
	}
}

// Calls addShelf in bookshelf.c
void createShelf()
{
	addShelf(userArgs[2], userArgs[3], atoi(userArgs[4])-1);	
}

// Calls displayShelf in bookshelf.c
void showShelf()
{
	int n = atoi(userArgs[2]);
	if(n < SHELVES+1 && n > 0)
		displayShelf(shelves[n-1], n);
}

// Calls emptyShelf in bookshelf.c for a shelf slot
void rm()
{
	emptyShelf(atoi(userArgs[1]));	
}
