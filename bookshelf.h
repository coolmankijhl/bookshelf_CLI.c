#include "global.h"

// Assigns strings to values
typedef enum userCmd{exitCmd, helpCmd, clearCmd, createCmd, book, shelf, showCmd, shelvesCmd, removeCmd} CMD;
struct commandConversion
{
	CMD value;
	char *str;
} commandConversion [] = {
	{exitCmd, "exit"},
	{helpCmd, "help"},
	{clearCmd, "clear"},
	{createCmd, "create"},
	{book, "book"},
	{shelf, "shelf"},
	{showCmd, "show"},
	{shelvesCmd, "shelves"},
	{removeCmd, "rm"}

};

// Converts string input to an int
CMD cmdToInt(char *str)
{
	for(int i = 0; i < sizeof(commandConversion) / sizeof(commandConversion[0]); i++)
		if(strcmp(str, commandConversion[i].str) == 0)
			return commandConversion[i].value;
}

// Converts int to a command function
void commands()
{
	int userCmd = cmdToInt(userArgs[0]);

	switch(userCmd)
	{
		case(0): //exit
			exitCMD();
			break;
		case(1): //help
			help();
			break;
		case(2): //clear
			system("clear");
			break;
		case(3): //create
			create();
			break;	
		case(6): //show
			show();
			break;	
		case(8): //remove
			rm();
			break;
		default:
			printf("Command not recognized, type \"help\" for a list of commands.\n");
			break;

        }
}

void exitCMD()
{
	printf("Exiting..\n");

	for(int i = 0; i < SHELVES; i++)
			emptyShelf(i);

	exit(1);  
}

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

void create()
{
	int userCmd = cmdToInt(userArgs[1]);

	switch(userCmd)
	{
		case(4): //create book <book name> <author> <shelf slot>
			addBook(userArgs[2], userArgs[3], &shelves[atoi(userArgs[4])-1]);
			break;
		case(5): //create shelf <shelf name> <your name> <shelf slot>
			addShelf(userArgs[2], userArgs[3], atoi(userArgs[4])-1);
			break;
		default:
			printf("ERROR create: invalid arg\n");
	}
}

void show()
{
	int userCmd = cmdToInt(userArgs[1]);

	switch(userCmd)
	{
		case(7): //show shelves
			for(int i = 0; i < SHELVES; i++)
				if(shelves[i] != NULL)
					printf("Shelf %d: %s by %s\n", i+1, shelves[i]->bookName, shelves[i]->author);
				else
					printf("Shelf %d: SHELF SLOT EMPTY\n", i+1);
				break;
		case(5): //show shelf <n>
			int n = atoi(userArgs[2]);
			if(n < SHELVES+1 && n > 0)
				showShelf(shelves[n-1], n);
			else
				printf("ERROR show shelf %d failed: invalid arg\n", n);
			break;
		default:
			printf("ERROR show: invalid arg");
	}
}

void rm()
{
	emptyShelf(atoi(userArgs[1]));	
}
