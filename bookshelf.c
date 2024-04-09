#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "stack.h"
#include "global.h"

#define SHELVES 5

char userArgs[SHELVES][100];
struct stackNode* shelves[SHELVES];

// First argument conversions
struct command conversions1[] = {
	{"quit", quit},
	{"q", quit},
	{"exit", quit},
	{"help", help},
	{"book", book},
	{"bk", book},
	{"shelf", shelf},
	{"savef", savef},
	{"openf", openf},
	{"showf", showf},
	{"clean", clean},
	{NULL, NULL}
};

// Conversions for book argument
struct command bookConvert[] = {
	{"add", addBook},
	{"show", showBooks},
	{NULL, NULL}
};

// Conversions for show argument
struct command shelfConvert[] = {
	{"add", addShelf},
	{"show", showShelves},
	{"rm", rmShelf},
	{NULL, NULL}
};

// Parses input for the shell
void main()
{
	char userInput[1000];

	printf("Welcome to \033[0;33mBookshelf_CLI.c!\033[0m Type \"help\" for a list of commands.\nCreated by Michael Cartwright\n\n");
	while(1)
	{
		printf("\033[0;33m(bookshelf)>>>\033[0m ");


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

// Checks if there are a valid number of arguments in statement
int argsCheck(int n)
{
	if(userArgs[n][0] == '\0')
	{
		printf("\033[0;31mERROR\033[0m %s: missing args\n", userArgs[0]);	
		return 0;
	}
	return 1;
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

// Calls book conversion map
void book()
{
	if(!argsCheck(1))
		return;
	executeCommand(userArgs[1], bookConvert);
}

// Calls shelf conversion map
void shelf()
{
	if(!argsCheck(1))
		return;
	executeCommand(userArgs[1], shelfConvert);
}

// Adds book in a shelf
void addBook()
{
	if(!argsCheck(4))
		return;

	struct stackNode** top = &shelves[atoi(userArgs[4])-1];
	if(*top == NULL)
	{
		printf("\033[0;31mERROR\033[0m book add: shelf %d doesn't exist\n", atoi(userArgs[4]));
		return;
	}

	char bookName[50], author[50];
	strcpy(bookName, userArgs[2]);
	strcpy(author, userArgs[3]);

	push(top);

	(*top)->bookName = (char*)malloc(sizeof(char) * (strlen(bookName) + 1));
	(*top)->author = (char*)malloc(sizeof(char) * (strlen(author) + 1));

	strcpy((*top)->bookName, bookName);
	strcpy((*top)->author, author);

	if(*top != NULL && (*top)->bookName != NULL && (*top)->author)
		printf("Successfully created book \033[0;33m%s\033[0m by \033[0;33m%s\033[0m\n", (*top)->bookName, (*top)->author);
	else	
		printf("\033[0;31mERROR\033[0m add book: problem creating shelf\n");
}

// Creates a shelf in a shelf slot
void addShelf()
{
	if(!argsCheck(4))
		return;
	
	char shelfName[50], username[50];
	strcpy(shelfName, userArgs[2]);
	strcpy(username, userArgs[2]);
	int n = atoi(userArgs[4]);

	if(!(n > 0 && n < SHELVES))
	{
		printf("\033[0;31mERROR\033[0m create shelf failed: invalid shelf number\n");
		return;
	}

	if(shelves[n] != NULL)
	{
		printf("A shelf already exists here, are you sure you want to overwrite it? Type 'overwrite' to continue, anything else to abort: ");
		char *arg = (char*)malloc(10 * sizeof(char));
		fgets(arg, sizeof(arg), stdin);
		arg = strtok(arg, " \n");

		if(arg == NULL) {}
		else if(!strcmp(arg, "overwrite\n\0"))
		{
			free(arg);
			return;
		}
		destroy(shelves[n]);
		free(arg);
	}

	struct stackNode *bookshelf = stack();

	bookshelf->next = NULL;

	bookshelf->bookName = (char*)malloc(sizeof(char) * (strlen(shelfName) + 1));
	bookshelf->author = (char*)malloc(sizeof(char) * (strlen(username) + 1));
	bookshelf->index = 0;

	strcpy(bookshelf->bookName, shelfName);
	strcpy(bookshelf->author, username);

	shelves[n-1] = bookshelf;

	if(shelves[n-1] != NULL)
		printf("Successfuly created shelf \033[0;33m%s\033[0m by \033[0;33m%s\033[0m in save slot %d\033[0m\n", bookshelf->bookName, bookshelf->author, n);
	else
		printf("\033[0;31mERROR\033[0m create shelf: failed creating shelf\n");
}


// Prints header information for all shelves
void showShelves()
{
	for(int i = 0; i < SHELVES; i++)
	{
		if(shelves[i] != NULL)
			printf("Shelf %d: \033[0;33m%s\033[0m by \033[0;33m%s\033[0m\n", i+1, bottom(shelves[i])->bookName, bottom(shelves[i])->author);
		else
			printf("Shelf %d: SHELF SLOT EMPTY\n", i+1);
	}
}

// Displays shelf head, its following books, and their respective information
void showBooks()
{
	if(!argsCheck(2))
		return;	

	int n = atoi(userArgs[2]);
	struct stackNode *top = shelves[n-1];

	if(n < SHELVES+1 && n > 0)
	{
		if(top == NULL)
		{
			printf("\033[0;31mERROR\033[0m show shelf %d failed: shelf slot empty\n", n);
			return;
		}

		struct stackNode* ptr = top;

		while(ptr != NULL)
		{	
			printf("(%d) | \033[0;33m%s\033[0m by \033[0;33m%s\033[0m |\n", ptr->index,  ptr->bookName, ptr->author);
			ptr = ptr->next;
		}
		free(ptr);
	}
}

// Removes a shelf from shelf slot n
void rmShelf()
{
	if(!argsCheck(2))
		return;

	int n = atoi(userArgs[2]);
	if(n < SHELVES+1 && n > 0 && shelves[n-1] != NULL)
	{
		printf("Successfully removed \033[0;33mshelf %d\033[0m\n", n);
		destroy(shelves[n-1]);
		shelves[n-1] = NULL;
	}
	else
		printf("\033[0;31mERROR\033[0m shelf rm: shelf %d does not exist.\n", n);

}

// Displays help information from commandHelp.txt
void help()
{
	FILE *file = fopen("commandHelp.txt", "r");
	if(file == NULL)
	{
		printf("\033[0;31mERROR\033[0m commandHelp.txt file not found.\n");
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

// Terminates bookshelf_CLI.c
void quit()
{
	printf("Terminating..\n");

	for(int i = 0; i < SHELVES; i++)
			destroy(shelves[i]);

	exit(1);  
}

// Cleans screen
void clean()
{
	system("clear");
}

// Saves shelf state to a dynamically named .txt file, overwrites if file already exists
void savef()
{	
	if(!argsCheck(1))
		return;

	if(userArgs[1][0] == '.')
	{
		printf("\033[0;31mERROR\033[0m savef: file name cannot start with a '.'\n");
		return;
	}

	FILE *file = openFile("w");
	if(file == NULL)
		return;
	
	for(int i = 0; i < SHELVES; i++)
	{
		if(shelves[i] != NULL)
			fprintf(file, "%d\n", shelves[i]->index+1);
		else
			fprintf(file , "0\n");
		reverse(&shelves[i]);
	}

	for(int i = 0; i < SHELVES; i++)
	{
		fprintf(file, "{\n");

		if(shelves[i] != NULL)
		{	
			struct stackNode* ptr = shelves[i];
			while(ptr != NULL)
			{
				fprintf(file, "%s %s\n", ptr->author, ptr->bookName);
				ptr = ptr->next;
			}
		}
		fprintf(file, "}\n");
	}

	for(int i = 0; i < SHELVES; i++)
			reverse(&shelves[i]);

	fclose(file);
}

// Overwrites current shelves state with data from file
void openf()
{
	if(!argsCheck(1))
		return;

	if(userArgs[1][0] == '.')
	{
		printf("\033[0;31mERROR\033[0m openf: cannot open files that start with a '.'\n");
		return;
	}

	for(int i = 0; i < SHELVES; i++)
			destroy(shelves[i]);

	FILE *file = openFile("r");
	
	if(file == NULL)
		return;

	int indexes[SHELVES];
	for(int i = 0; i < SHELVES; i++)
		fscanf(file, "%d ", &indexes[i]);

	char buffer[3];
	fgets(buffer, sizeof(buffer), file);
	for(int i = 0; i < SHELVES; i++)
	{
		if(indexes[i] != 0)
			shelves[i] = stack();
			
		for(int j = indexes[i]; j > 0; j--)
		{
			shelves[i]->bookName = (char*)malloc(100);
			shelves[i]->author = (char*)malloc(100);
			fscanf(file, "%s %s ", shelves[i]->author, shelves[i]->bookName);
			push(&shelves[i]);
		}
		pop(&shelves[i]);
		fgets(buffer, sizeof(buffer), file);
		fgets(buffer, sizeof(buffer), file);
	}

	fclose(file);
}

// Opens and names file
FILE* openFile(char* wor)
{	
	char path[103] = "./saves/";
	strcat(path, userArgs[1]);
	FILE *file = fopen(path, wor);

	if(file == NULL)
	{
		printf("\033[0;31mERROR\033[0m: could not open file.\n");
		return NULL;
	}
	else
	{
		printf("Successfully found \033[0;33m%s\033[0m\n", userArgs[1]);
		return file;
	}
}

// Displays all avaliable files in saves directory
void showf()
{
	DIR *d = opendir("./saves");
	struct dirent *dir;

	if(d)
	{
		printf("Files: ");
		while((dir = readdir(d)) != NULL)
		{	
			if(dir->d_name[0] != '.')
				printf("%s ", dir->d_name);
		}
		printf("\n");
		closedir(d);
	}
}
