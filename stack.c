#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Stack {
    int pos;
    int size;
    int *store;
};

void Stack_destroy(struct Stack *stack);

void die(char *message, struct Stack *stack){
    if(errno){
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    Stack_destroy(stack);
    exit(1);
}

struct Stack *Stack_new(int size) {
    struct Stack *stack = malloc(sizeof(struct Stack));
    stack->pos = 0;
    stack->size = size;
    stack->store = calloc(size, sizeof(struct Stack));
    return stack;
}

void Stack_destroy(struct Stack *stack){
    if(stack){
        free(stack->store);
        free(stack);
    }
}

void Stack_push(struct Stack *stack, int item) {
    if(!stack) die("Cannot push to null stack", stack);
    if (stack->pos >= stack->size-1){
        stack->size = stack->size*2;
        stack->store = (int*) realloc(stack->store, stack->size * sizeof(int));
        if(!stack->store) die("Cannot allocate more memory for the stack", stack); }
    stack->store[stack->pos] = item;
    stack->pos++;
}

int Stack_pop(struct Stack *stack){
    if(!stack) die("Cannot pop from null stack", stack);
    int ret = stack->store[stack->pos];
    stack->pos--;
    stack->store[stack->pos] = 0;
    return ret;
}


int main(int argc, char *argv[]){
    struct Stack *stack = Stack_new(10);
    int i=0;

    Stack_push(stack, 5);
    Stack_push(stack, 50);
    Stack_push(stack, 1000);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);
    Stack_push(stack, 25);

    for(i=0; i < stack->pos; i++){
        printf("Popped %d from the stack (pos %d)\n", stack->store[i], i);
    }
    Stack_destroy(stack);
    return 0;
}
