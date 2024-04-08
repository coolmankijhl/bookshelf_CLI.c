
struct command {
	char *cmd;
	void (*function)();
};

void addBook(char bookName[], char author[], stackNode** top);
void displayShelf(stackNode *top, int n);
void addShelf(char shelfName[], char username[], int n);
void executeCommand(char* cmdName, struct command *convertLayer);
FILE*  openFile(char* wor);

void save();
void saveMake();
void saveOpen();
void clear();
void exitCMD();
void create();
void help();
void show();
void rm();
void createBook();
void createShelf();
void showShelf();
void showShelves();
