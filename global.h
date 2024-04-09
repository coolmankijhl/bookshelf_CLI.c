
struct command {
	char *cmd;
	void (*function)();
};

void executeCommand(char* cmdName, struct command* convertLayer);
int argsCheck(int n);
void showf();
void book();
void shelf();
void addBook();
void addShelf();
void showShelves();
void showBooks();
void rmShelf();
void help();
void quit();
void clean();
void savef();
void openf();
FILE* openFile(char* wor);


