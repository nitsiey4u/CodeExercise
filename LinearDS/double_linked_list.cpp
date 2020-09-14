#include <iostream>
#include <cstdlib>

typedef struct DoubleLinkedList{
  struct DoubleLinkedList* next;
  struct DoubleLinkedList* prev;
  int value;
}DLL;

DLL* get_node(int value) {
  DLL* temp = (DLL*) malloc(sizeof(DLL));
  temp->next = NULL;
  temp->prev = NULL;
  temp->value = value;
  return temp;
}

void push_front(DLL** front_ref, int value){
  DLL* front = *front_ref;
  DLL* temp = get_node(value);
  front->prev = temp;
  temp->next = front;
  *front_ref = temp;
}

void push_back(DLL** back_ref, int value){
  DLL* back = *back_ref;
  DLL* temp = get_node(value);
  back->next = temp;
  temp->prev = back;
  *back_ref = temp;
}

DLL* find_node(DLL* head, int value) {
  DLL *ptr;
  for(ptr = head; ptr != NULL; ptr = ptr->next) {
    if(ptr->value == value)
      return ptr;
  }
  return NULL;
}

void display_forward(DLL* head) {
  DLL *ptr;
  for(ptr = head; ptr != NULL; ptr = ptr->next) {
    printf("%d  ", ptr->value);
  }
}

void display_backward(DLL* back) {
  DLL *ptr;
  for(ptr = back; ptr != NULL; ptr = ptr->prev) {
    printf("%d  ", ptr->value);
  }
}

void erase_node(DLL** front_ref, DLL** back_ref, DLL* node_ptr) {
  DLL* front = *front_ref;
  DLL* back = *back_ref;
  if(front == node_ptr) {
    DLL* head = node_ptr->next;
    head->prev = NULL;
    *front_ref = head;
  }
  else if(back == node_ptr) {
    DLL* last = node_ptr->prev;
    last->next =  NULL;
    *back_ref = last;
  }
  else {
    DLL* before = node_ptr->prev;
    DLL* after = node_ptr->next;
    node_ptr->prev->next = after;
    node_ptr->next->prev = before;
  }
  free(node_ptr);
  node_ptr = NULL;
}

void erase_list(DLL* head){
  DLL *ptr, *prev;
  for(prev=head, ptr=(prev)?prev->next : NULL; (ptr != NULL); prev=ptr, ptr=ptr->next) {
    printf("\nDeleting: %d", prev->value);
    free(prev);
  }
  printf("\nDeleting: %d", prev->value);
  free(prev);
  head = NULL;
}

int main() {
  DLL* front = get_node(4);
  front->next = NULL;
  front->prev = NULL;
  DLL* back = front;

  push_front(&front, 2);
  push_back(&back, 5);

  push_front(&front, 1);
  push_back(&back, 6);

  //
  // head = push_back(head, 2);
  // head = push_front(head, 3);
  // head = push_back(head, 4);
  //
  printf("\nForward List: ");
  display_forward(front);

  printf("\nBackward List: ");
  display_backward(back);

  DLL* del_node = find_node(front, 6);
  erase_node(&front, &back, del_node);

  printf("\nForward List: ");
  display_forward(front);

  printf("\nBackward List: ");
  display_backward(back);

  erase_list(front);
  return 0;
}
