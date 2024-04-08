
struct command {
	char *cmd;
	void (*function)();
};

void executeCommand(char* cmdName, struct command* convertLayer);
void book();
void shelf();
void addBook();
void addShelf();
void showShelves();
void showBooks();
void rmShelf();
void rmBook();
void help();
void quit();
void clear();
void save();
void open();
FILE* openFile(char* wor);
void sortShelf();


