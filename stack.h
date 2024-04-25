#include <stdio.h>
#include <stdlib.h>

#ifndef stack_h
#define stack_h

// Node definition
typedef struct stackNode {
    char *author;
    char *bookName;

    struct stackNode *next;
    int index;
} stackNode;

// Creates a new stack
struct stackNode *stack() {
    struct stackNode *top =
        (struct stackNode *)malloc(sizeof(struct stackNode));
    top->next = NULL;
    top->index = 0;
    return top;
}

// Creates a new node on top of the stack
void push(struct stackNode **top) {
    struct stackNode *ptr =
        (struct stackNode *)malloc(sizeof(struct stackNode));
    ptr->next = *top;
    ptr->index = ((*top)->index) + 1;

    *top = ptr;
}

// Destroys/frees stack from top-down
void destroy(struct stackNode *top) {
    struct stackNode *behindTop = top;
    while (top != NULL) {
        top = top->next;
        free(behindTop->author);
        free(behindTop->bookName);
        free(behindTop);
        behindTop = top;
    }
    free(top);
}

// Destroys/frees the node on top of the stack
void pop(struct stackNode **top) {
    if (*top == NULL) return;

    struct stackNode *temp = *top;
    *top = (*top)->next;
    free(temp);
}

// Returns the index of the top of the stack plus one
int size(struct stackNode *top) {
    if (top == NULL) return 0;

    int max = 0;
    int hold;
    struct stackNode *ptr = top;

    while (ptr != NULL) {
        hold = ptr->index;
        if (hold > max) max = hold;
        ptr = ptr->next;
    }

    return max + 1;
}

// Returns the node on the bottom of the stack
struct stackNode *bottom(struct stackNode *top) {
    if (top == NULL) {
        return NULL;
    }

    struct stackNode *bottom = top;
    while (bottom != NULL && bottom->next != NULL) bottom = bottom->next;

    return bottom;
}

// Reverses a stack's order
void reverse(struct stackNode **top) {
    struct stackNode *prev = NULL;
    struct stackNode *current = *top;
    struct stackNode *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *top = prev;
}

// Resets the indexes of the stack
void reindex(struct stackNode **top, int max_index) {
    struct stackNode *ptr = *top;

    while (ptr != NULL) {
        ptr->index = max_index - 1;
        ptr = ptr->next;
        max_index--;
    }
}

#endif
