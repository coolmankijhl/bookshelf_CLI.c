#define SHELVES 5

void addBook(char bookName[], char author[], stackNode** top);
void showShelf(stackNode *top, int n);
void addShelf(char shelfName[], char username[], int n);
void emptyShelf(int n);


void exitCMD();
void create();
void help();
void show();
void rm();

char userArgs[SHELVES][100];
struct stackNode* shelves[SHELVES];

