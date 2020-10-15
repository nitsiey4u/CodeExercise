#include <cstdio>
#include <cstdlib>

struct Node {
  int value;
  struct Node* next;
  struct Node* prev;
};
typedef struct Node NODE;

NODE* create_node(const int value) {
  NODE* temp = (NODE*) malloc(sizeof(NODE));
  temp->value = value;
  temp->next = temp;
  temp->prev = temp;
  return temp;
}

void insert_before(NODE* & head, NODE* & tail, const int value) {
  if((head == NULL) && (tail == NULL)) {
    head = create_node(value);
    tail = head;
  } else {

  }
}

void forward_list(NODE* & head, NODE* & tail) {
  printf("\nList: ");
  for(NODE* ptr = head; ptr && ptr->next != head; ptr = ptr->next) {
    printf("\t%d -->", ptr->value);
  }
  if(tail) {
    printf("\t%d", tail->value);
  }
}

void backward_list(NODE* & head, NODE* & tail) {
  printf("\nList: ");
  for(NODE* ptr = tail; ptr && ptr->prev != tail; ptr = ptr->prev) {
    printf("\t%d -->", ptr->value);
  }
  if(head) {
    printf("\t%d", head->value);
  }
}

void insert_after(NODE* & head, NODE* & tail,
                 const int target, const int value) {
  if((head == NULL) && (tail == NULL)) {
    head = create_node(value);
    tail = head;
  } else {
    NODE* ptr = NULL;
    for(ptr = head; ptr && ptr->next != head; ptr = ptr->next) {
      if(ptr->value == target) {
        break;
      }
    }
    if(ptr->value == target) {
      NODE* temp = create_node(value);
      temp->next = ptr->next;
      temp->prev = ptr;
      ptr->next->prev = temp;
      ptr->next  = temp;
      if(tail == ptr) {
        tail = temp;
        printf("\nNew tail %d", tail->value);
      }
    } else {
      printf("\nTarget %d not found", target);
    }
  }
}

void delete_node(NODE* & head, NODE* & tail, const int target) {
  NODE* ptr = NULL;
  for(ptr = head; ptr && ptr->next != head; ptr = ptr->next) {
    if(ptr->value == target) {
      break;
    }
  }
  if(ptr->value == target) {
    NODE* temp = NULL;
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    if(head == ptr) {
      head = ptr->next;
    } else if (tail == ptr) {
      tail = ptr->prev;
    } else {
      ptr->next = NULL;
      ptr->prev = NULL;
    }
    printf("\nDeleted node %d", ptr->value);
    free(ptr);
    ptr = NULL;
  } else {
    printf("\nTarget %d not found", target);
  }
}

void erase_nodes(NODE* & head, NODE* & tail) {
  NODE* ptr = head;
  while(ptr != tail) {
    NODE* next = ptr->next;
    printf("\nFreed %d", ptr->value);
    free(ptr);
    ptr = next;
  }
  if(tail) {
    printf("\nFreed %d", tail->value);
    free(tail);
  }
  head = NULL;
  tail = NULL;
}

int main() {
  NODE* head = NULL;
  NODE* tail = NULL;
  insert_after(head, tail, 0, 10);
  insert_after(head, tail, 10, 20);
  insert_after(head, tail, 20, 30);
  forward_list(head, tail);
  backward_list(head, tail);
  delete_node(head, tail, 30);
  forward_list(head, tail);
  backward_list(head, tail);
  erase_nodes(head, tail);
  return 0;
}
