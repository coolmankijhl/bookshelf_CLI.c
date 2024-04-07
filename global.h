#define SHELVES 5

void addBook(char bookName[], char author[], stackNode** top);
void displayShelf(stackNode *top, int n);
void addShelf(char shelfName[], char username[], int n);
void emptyShelf(int n);

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

char userArgs[SHELVES][100];
struct stackNode* shelves[SHELVES];

