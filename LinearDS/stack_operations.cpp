#include "stdio.h"
#include "stdlib.h"

#define MAX_SIZE 5

struct stack {
  int top;
  int cache[MAX_SIZE];
};

typedef struct stack STACK;

void initialize(STACK* ptr) {
  ptr->top = -1;
  for(int index = 0; index <= (MAX_SIZE - 1); index++) {
    ptr->cache[index] = 0;
  }
}

bool isFull(STACK* ptr) {
  bool retval = (ptr->top == (MAX_SIZE - 1)) ? true : false;
  return retval;
}

bool isEmpty(STACK* ptr) {
  bool retval = (ptr->top == -1) ? true : false;
  return retval;
}

bool push(STACK* ptr, const int newval) {
  bool retval = true;
  if(isFull(ptr)) {
    printf("\nStack is full.");
    retval = false;
  } else {
    ptr->cache[++ptr->top] = newval;
    printf("\nPushed value: %d", newval);
  }
  return retval;
}

int pop(STACK* ptr) {
  int popval = -1;
  if(isEmpty(ptr)) {
    printf("\nStack is empty.");
  } else {
    popval = ptr->cache[ptr->top--];
    printf("\nPopped value: %d", popval);
  }
  return popval;
}

int top(STACK* ptr) {
  int topval = -1;
  if(isEmpty(ptr)) {
    printf("\nStack is empty.");
  } else {
    topval = ptr->cache[ptr->top];
  }
  return topval;
}

void display(STACK* ptr) {
  printf("\nStack:");
  if(isEmpty(ptr)) {
    printf("\tNil");
  } else {
    printf("\n\tTop --> %d", ptr->cache[ptr->top]);
    for(int index = (ptr->top - 1); index >=0; index--) {
      printf("\n\t\t      %d", ptr->cache[index]);
    }
  }
}

int main () {
  STACK stk;
  initialize(&stk);
  push(&stk, 8);
  push(&stk, 9);
  push(&stk, 10);
  push(&stk, 11);
  push(&stk, 12);
  push(&stk, 13);
  display(&stk);
  pop(&stk);
  display(&stk);
  push(&stk, 22);
  display(&stk);
  pop(&stk);
  display(&stk);
  push(&stk, 33);
  display(&stk);
  pop(&stk);
  pop(&stk);
  pop(&stk);
  push(&stk, 44);
  display(&stk);
  pop(&stk);
  pop(&stk);
  pop(&stk);
  pop(&stk);
  return 0;
}
