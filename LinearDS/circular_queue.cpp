#include <cstdio>
#include <memory>
#include <iostream>

using namespace std;

class Queue{
private:
  int   size;
  int   front;
  int   rear;
  int*  queue;
public:

  Queue(const int count) {
    size  = count;
    queue = new int[count];
    front = -1;
    rear  = -1;
  }

  bool isEmpty() {
    return (front == -1) && (rear == -1);
  }

  bool isFull() {
    return (((rear + 1) % size) == front);
  }

  bool enQueue(const int value) {
    bool retval = false;
    if(isFull()) {
      cout << "\nQueue is full. Cannot enqueue " << value;
    } else {
      if(rear == -1) {
        rear  = 0;
        front = 0;
      } else {
        rear = (rear + 1) % size;
      }
      queue[rear] = value;
      retval = true;
      cout << "\nInserted " << value;
    }
    return retval;
  }

  bool deQueue() {
    bool retval = false;
    if(isEmpty()) {
      cout << "\nQueue is empty. Cannot deque";
    } else {
      int value = queue[front];
      if(front == rear) {
        front = -1;
        rear = -1;
      } else {
        front = (front + 1) % size;
      }
      cout << "\nDeleted " << value;
      retval = true;
    }
    return retval;
  }

  int getFront() {
    return (front == -1) ? -1 : queue[front];
  }

  void displayQueue() {
    if(isEmpty()) {
      cout << "\nQueue: Empty";
      return;
    }
    cout << "\nQueue:";
    for(int index = front; index != rear; index = ((index + 1) % size)) {
      cout << "x\t" << queue[index];
    }
    cout << "\t" << queue[rear];
    cout << "\nIndex:";
    for(int index = front; index != rear; index = ((index + 1) % size)) {
      cout << "\t" << ((index == front) ? "F" : " ");
    }
    cout << "\tR";
  }

  ~Queue(){
    cout << "\nDeleted all elements";
    delete[] queue;
  }
};

int main() {
  Queue Q(3);
  Q.enQueue(10);
  Q.enQueue(20);
  Q.enQueue(30);
  Q.enQueue(40);
  Q.displayQueue();
  Q.deQueue();
  Q.displayQueue();
  Q.enQueue(40);
  Q.displayQueue();

  Q.enQueue(50);
  Q.displayQueue();

  Q.deQueue();
  Q.displayQueue();
  Q.deQueue();
  Q.displayQueue();
  Q.deQueue();
  Q.displayQueue();
  Q.enQueue(30);
  Q.displayQueue();
  Q.deQueue();
  Q.displayQueue();
  return 0;
}
