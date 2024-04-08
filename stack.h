#include <stdio.h>
#include <stdlib.h>

// Node definition
typedef struct stackNode
{
	char* author;
	char* bookName;

	struct stackNode* next;
	int index;
} stackNode;

// Creates a new stack
struct stackNode* stack()
{
	struct stackNode *top = (struct stackNode*)malloc(sizeof(struct stackNode));
	top->next = NULL;
	top->index = 0;
	return top;
}

// Creates a new node on top of the stack
void push(struct stackNode **top)
{
	struct stackNode *ptr = (struct stackNode*)malloc(sizeof(struct stackNode));
	ptr->next = *top;
	ptr->index = ((*top)->index) + 1;

	*top = ptr;
}

// Destroys/frees stack from top-down
void destroy(struct stackNode *top)
{
	struct stackNode *behindTop = top;
	while(top != NULL)
	{
		top = top->next;
		free(behindTop->author);
		free(behindTop->bookName);
		free(behindTop);
		behindTop = top;
	}
	free(top);
}

// Destroys/frees the node on top of the stack
void pop(struct stackNode **top)
{
	if(*top == NULL)
		return;
	
	struct stackNode *temp = *top;
	if((*top)->next != NULL)
		*top = (*top)->next;
	else
		free((*top));
	free(temp);
}

// Returns the index of the top of the stack plus one
int size(struct stackNode *top)
{
	return (top->index)+1;
}

// Returns the node on the bottom of the stack
struct stackNode* bottom(struct stackNode *top)
{
	struct stackNode *bottom = top;
	while(bottom->next != NULL && bottom != NULL)
		bottom = bottom->next;

	return bottom;
}

// Reverses a stack's order
void reverse(struct stackNode **top)
{
	struct stackNode* prev = NULL;
	struct stackNode* current = *top;
	struct stackNode* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	*top = prev;
}

