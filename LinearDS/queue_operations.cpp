#include "stdio.h"
#include "stdbool.h"
#define MAX_SIZE 5

struct Queue {
  unsigned int front;
  unsigned int rear;
  unsigned int cache[MAX_SIZE];
};

typedef struct Queue QUEUE;
typedef unsigned int uint_t;

void initialize(QUEUE *ptr) {
  ptr->front = 0;
  ptr->rear = 0;
  for(int index = 0; index <= (MAX_SIZE - 1); index++) {
    ptr->cache[index] = 0;
  }
}

void display(QUEUE *ptr) {
  printf("\nQueue: \n");
  // Above values
  for(int index = 0; index <= (MAX_SIZE - 1); index++) {
    printf("\t%d", ptr->cache[index]);
  }
  printf("\n");
  // Below pointers
  for(int index = 0; index <= (MAX_SIZE - 1); index++) {
    if(index == ptr->front) {
      printf("\t!");
    }
    else if(index == ptr->rear) {
      printf("\tR");
    }
    else {
      printf("\t--");
    }
  }
}

uint_t nextIndex(const uint_t index) {
  return (index + 1) % MAX_SIZE;
}

bool isEmpty(QUEUE *ptr) {
  return (ptr->front == ptr->rear);
}

bool isFull(QUEUE *ptr) {
  return (nextIndex(ptr->rear) == ptr->front);
}

uint_t front(QUEUE *ptr) {
  printf("\nFront Index: %d", ptr->front);
  return ptr->cache[ptr->front];
}

uint_t rear(QUEUE *ptr) {
  printf("\nRear Index: %d", ptr->rear);
  return ptr->cache[ptr->rear];
}

bool enqueue(QUEUE *ptr, const uint_t value) {
  bool retval = true;
  if(isFull(ptr)) {
    printf("\nQueue is full. Cannot enqueue %d", value);
    retval = false;
  } else {
    ptr->rear = nextIndex(ptr->rear);
    ptr->cache[ptr->rear] = value;
    printf("\nEnqueued value: %d", value);
  }
  return retval;
}

uint_t dequeue(QUEUE *ptr) {
  uint_t deqval = 0;
  if(isEmpty(ptr)) {
    printf("\nQueue is empty. Cannot deque.");
  } else {
    ptr->front = nextIndex(ptr->front);
    deqval = ptr->cache[ptr->front];
    printf("\nDequeued value: %d", deqval);
    ptr->cache[ptr->front] = 0;
  }
  return deqval;
}

int main() {
  QUEUE queue;
  initialize(&queue);
  enqueue(&queue, 5);
  enqueue(&queue, 6);
  enqueue(&queue, 7);
  enqueue(&queue, 8);
  enqueue(&queue, 9);
  enqueue(&queue, 10);
  display(&queue);
  dequeue(&queue);
  display(&queue);
  dequeue(&queue);
  display(&queue);
  enqueue(&queue, 9);
  display(&queue);
  enqueue(&queue, 10);
  display(&queue);
  enqueue(&queue, 11);
  display(&queue);
  enqueue(&queue, 12);
  display(&queue);

  dequeue(&queue);
  display(&queue);
  dequeue(&queue);
  display(&queue);
  enqueue(&queue, 22);
  display(&queue);
  enqueue(&queue, 33);
  display(&queue);
  return 0;
}
