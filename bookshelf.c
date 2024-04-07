#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "bookshelf.h"
#include "global.h"

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
