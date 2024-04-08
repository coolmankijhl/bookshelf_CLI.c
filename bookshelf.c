#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "global.h"

#define SHELVES 5

char userArgs[SHELVES][100];
struct stackNode* shelves[SHELVES];

struct command {
	char *cmd;
	void (*function)();
}; 

// First argument conversions
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

// Parses input for the shell
int main()
{
	char userInput[100];

	printf("Welcome to Bookshell.c! Type \"help\" for a list of commands.\n");
	while(1)
	{
		printf("(bookshell)>>> ");


		fgets(userInput, sizeof(userInput), stdin);
			
		char *token = strtok(userInput, " \n");

		for(int i = 0; i < SHELVES && token != NULL; i++)
		{	
			strcpy(userArgs[i], token);
			token = strtok(NULL, " \n");
		}

		executeCommand(userArgs[0], conversions1);

		strcpy(userInput, "");
		for(int i = 0; i < sizeof(userArgs) / sizeof(userArgs[0]); i++)
			strcpy(userArgs[i], "");

			
	}
		
}

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

// Calls create conversion map
void create()
{
	executeCommand(userArgs[1], createConvert);
}

// Calls addBook
void createBook()
{
	addBook(userArgs[2], userArgs[3], &shelves[atoi(userArgs[4])-1]);
}

// Adds book in a shelf
void addBook(char bookName[], char author[], stackNode** top)
{
	if(bookName[0] == '\0' || bookName[0] == '\0')
	{
		printf("ERROR create book: no author or name arg\n");
		return;
	}	
	if(*top == NULL)
	{
		printf("ERROR create book: no shelf arg or shelf is doesn't exist\n");
		return;
	}
	push(top);

	(*top)->bookName = (char*)malloc(sizeof(char) * (strlen(bookName) + 1));
	(*top)->author = (char*)malloc(sizeof(char) * (strlen(author) + 1));

	strcpy((*top)->bookName, bookName);
	strcpy((*top)->author, author);

	if(*top != NULL)
		printf("Successfully created book %s by %s\n", (*top)->bookName, (*top)->author);
}

// Calls addShelf
void createShelf()
{
	addShelf(userArgs[2], userArgs[3], atoi(userArgs[4])-1);	
}

// Creates a shelf in a shelf slot
void addShelf(char shelfName[], char username[], int n)
{
	if(shelfName[0] == '\0' || username[0] == '\0', !(n > -1 && n < SHELVES))
	{
		printf("ERROR create shelf failed: not enough arguments or invalid shelf number\n");
		return;
	}

	if(shelves[n] != NULL)
	{
		printf("A shelf already exists here, are you sure you want to overwrite it? Type 'overwrite' to continue, anything else to abort: ");
		char *arg = (char*)malloc(50 * sizeof(char));
		fgets(arg, sizeof(arg), stdin);
		arg = strtok(arg, " \n");

		if(!strcmp(arg, "overwrite\n"))
		{
			free(arg);
			return;
		}
		free(shelves[n]);
		free(arg);
	}

	struct stackNode *bookshelf = stack();

	bookshelf->next = NULL;

	bookshelf->bookName = (char*)malloc(sizeof(char) * (strlen(shelfName) + 1));
	bookshelf->author = (char*)malloc(sizeof(char) * (strlen(username) + 1));

	strcpy(bookshelf->bookName, shelfName);
	strcpy(bookshelf->author, username);

	shelves[n] = bookshelf;

	if(shelves[n] != NULL)
		printf("Successfuly created shelf %s by %s in save slot %d\n", bookshelf->bookName, bookshelf->author, n+1);
	else
		printf("ERROR create shelf: failed creating shelf\n");
}

// Calls show conversion map
void show()
{
	executeCommand(userArgs[1], showConvert);
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

// Calls displayShelf if arg is [1, SHELVES] inclusive
void showShelf()
{
	int n = atoi(userArgs[2]);
	if(n < SHELVES+1 && n > 0)
		displayShelf(shelves[n-1], n);
}

// Displays shelf head, its following books, and their respective information
void displayShelf(stackNode *top, int n)
{
	if(top == NULL)
	{
		printf("ERROR show shelf %d failed: shelf slot empty\n", n);
		return;
	}

	struct stackNode* ptr = top;

	while(ptr != NULL)
	{	
		printf("(%d) | %s by %s |\n", ptr->index+1,  ptr->bookName, ptr->author);
		ptr = ptr->next;
	}
	free(ptr);
}

// Calls emptyShelf for a shelf slot
void rm()
{
	emptyShelf(atoi(userArgs[1]));	
}

// Destroys shelf and frees memory from it and its books
void emptyShelf(int n)
{
	struct stackNode *ptr = shelves[n-1];
	while (ptr != NULL)
       	{
		struct stackNode *nextPtr = ptr->next;
		free(ptr->author);
		free(ptr->bookName);
		ptr = nextPtr;
	}
	destroy(shelves[n-1]);
	shelves[n-1] = NULL;
}

// Displays help information from commandHelp.txt
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

// exits bookshell.c
void exitCMD()
{
	printf("Exiting..\n");

	for(int i = 0; i < SHELVES; i++)
			emptyShelf(i);

	exit(1);  
}

// Clears screen
void clear()
{
	system("clear");
}
