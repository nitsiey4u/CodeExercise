#include "stdio.h"
#include "stdlib.h"

struct Node {
  int value;
  struct Node* next;
};

typedef struct Node NODE;

// Create Node
NODE* create_node(const int value) {
  NODE* ptr = (NODE*)malloc(sizeof(NODE));
  ptr->value = value;
  ptr->next = NULL;
  return ptr;
}

// Display linked list
void display_list(NODE* head) {
  NODE *ptr = NULL;
  printf("\nList:");
  for(ptr = head; ptr != NULL; ptr = ptr->next) {
    const char* line = (ptr->next != NULL) ? "--->" : "";
    printf(" %d %s", ptr->value, line);
  }
}

// Delete entire linked list
void delete_list(NODE* head) {
  NODE *prev, *ptr;
  printf("\nCleanup list");
  for(prev = head, ptr = ((prev)?prev->next:NULL); ptr != NULL; prev = ptr, ptr = ptr->next) {
    printf("\nFreeing: %d", prev->value);
    free(prev);
  }
  if(prev != NULL) {
    printf("\nFreeing: %d", prev->value);
    free(prev);
    prev = NULL;
  }
}

// Insert node to end of linked list
NODE* push_back(NODE* head, const int value) {
  NODE* temp = create_node(value);
  if(head == NULL) {
    head = temp;
  } else {
    NODE* ptr = NULL;
    for(ptr = head; ptr->next != NULL; ptr = ptr->next);
    ptr->next = temp;
  }
  return head;
}

// Insert after node with specific key value
void insert_after(NODE** headptr, const int keyval, const int newval) {
  NODE* head = *headptr;
  NODE* ptr = NULL;
  for(ptr = head; ptr != NULL && ptr->value != keyval; ptr = ptr->next);
  if(ptr != NULL) {
    printf("\nInserting %d after %d", newval, keyval);
    NODE* temp = create_node(newval);
    temp->next = ptr->next;
    ptr->next = temp;
  } else {
    printf("\nKey value %d does not exist", keyval);
  }
}

// Insert before node with specific key value
void insert_before(NODE** headptr, const int keyval, const int newval) {
  NODE *head = *headptr;
  NODE *prev, *ptr;
  for(prev = head, ptr = head; ptr != NULL && ptr->value != keyval; prev = ptr, ptr = ptr->next);
  if(ptr != NULL) {
    printf("\nInserting %d before %d", newval, keyval);
    NODE* temp = create_node(newval);
    if (ptr == head) {
      temp->next = prev;
      head = temp;
    } else {
      temp->next = prev->next;
      prev->next = temp;
    }
  } else {
    printf("\nKey value %d does not exist", keyval);
  }
  *headptr = head;
}

// Delete node with specific key value
void delete_node(NODE** headptr, const int keyval) {
  NODE *head = *headptr;
  NODE *prev, *ptr;
  for(prev = head, ptr = head; ptr != NULL && ptr->value != keyval; prev = ptr, ptr = ptr->next);
  if(ptr != NULL) {
    printf("\nDeleting %d", keyval);
    NODE* temp = NULL;
    if (ptr == head) {
      temp = ptr;
      head = ptr->next;
      printf("\nNew head: %d", head->value);
    } else {
      temp = ptr;
      prev->next = ptr->next;
    }
    free(temp);
    temp = NULL;
  } else {
    printf("\nKey value %d does not exist", keyval);
  }
  *headptr = head;
}

// Delete all matching nodes
void delete_matching_nodes(NODE** headptr, const int keyval) {
  NODE dummy;
  dummy.value = 0;
  dummy.next = *headptr;
  NODE *main = &dummy;
  NODE *prev = main->next;
  NODE *ptr = (prev != NULL)? prev->next : NULL;
  while (ptr != NULL) {
    if(prev->value == keyval) {
      NODE* temp = prev;
      main->next = prev->next;
      free(temp);
      temp = NULL;
    } else {
      main = prev;
    }
    prev = ptr;
    ptr = ptr->next;
  }
  if ((prev != NULL) && (prev->value == keyval)) {
    NODE* temp = prev;
    main->next = prev->next;
    free(temp);
    temp = NULL;
  }
  *headptr = dummy.next;
}

// Get last node of linked list
NODE* get_last_node(NODE* head) {
  NODE* ptr = NULL;
  for(ptr = head; ((ptr != NULL) && (ptr->next != NULL)); ptr = ptr->next);
  return ptr;
}

// Get middle node of linked list
NODE* get_middle_node(NODE* head) {
  NODE* slow = head;
  NODE* fast = (slow)?slow->next:NULL;
  while(slow && fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

// Get node with specific key value
NODE* get_value_node(NODE* head, const int value) {
  NODE* ptr = NULL;
  for(ptr = head; (ptr != NULL) && (ptr->value != value); ptr = ptr->next);
  return ptr;
}

// Get node with specific index
NODE* get_index_node(NODE* head, const int index) {
  NODE* ptr = NULL;
  int counter = 0;
  for(counter = 1, ptr = head; (ptr != NULL) && (counter != index); counter++, ptr = ptr->next);
  return ptr;
}

// Convery array to linked list
NODE* array_to_list(int arr[], int size) {
  NODE* head = NULL;
  for(int index = 0; index < size; index++) {
    head = push_back(head, arr[index]);
  }
  return head;
}

// Break linked list and alternate merge both sublists
NODE* middle_alternate_merge(NODE* head) {
  NODE* middle = get_middle_node(head);
  NODE* head1 = head;
  NODE* head2 = middle->next;
  middle->next = NULL;
  NODE* ptr1 = head1;
  NODE* ptr2 = head2;
  NODE* result = ptr1;
  while(ptr1 && ptr2) {
    NODE* temp1 = ptr1->next;
    NODE* temp2 = ptr2->next;
    ptr1->next = ptr2;
    ptr2->next = temp1;
    ptr1 = temp1;
    ptr2 = temp2;
  }
  if(ptr1) {
    ptr1->next = NULL;
  }
  if(ptr2) {
    ptr2->next = NULL;
  }
  return result;
}

// Merge two sorted linked lists into one
NODE* merge_sort_lists(NODE* head1, NODE* head2) {
  NODE* ptr1 = head1;
  NODE* ptr2 = head2;
  NODE* main = NULL;
  if(ptr1 && ptr2) {
    main = (ptr1->value <= ptr2->value) ? ptr1 : ptr2;
  } else {
    main = (ptr1) ? ptr1 : ptr2;
  }
  while(ptr1 && ptr2) {
    NODE* temp1 = ptr1->next;
    NODE* temp2 = ptr2->next;
    if(ptr1->value < ptr2->value) {
      // since ptr1 is smaller (consume it)
      // ptr1->next = smaller value between ptr2 and temp1
      if(temp1 && temp1->value <= ptr2->value) {
        ptr1->next = temp1;
      } else {
        ptr1->next = ptr2;
      }
      // cosumed ptr1 so increment to next
      ptr1 = temp1;
    }
    else if(ptr1->value > ptr2->value) {
      // since ptr2 is smaller (consume it)
      // ptr2->next = smaller value between ptr1 and temp2
      if(temp2 && temp2->value < ptr1->value) {
        ptr2->next = temp2;
      } else {
        ptr2->next = ptr1;
      }
      // cosumed ptr2 so increment to next
      ptr2 = temp2;
    } else {
      printf("\nPTR matching %d %d", ptr1->value, ptr2->value);
      // consume ptr1 and ptr2
      ptr1->next = ptr2;
      if(temp1 && temp2 && (temp1->value <= temp2->value)) {
        ptr2->next = temp1;
      } else {
        ptr2->next = temp2;
      }
      // cosumed ptr1 and ptr2 so increment to next
      ptr1 = temp1;
      ptr2 = temp2;
    }
  }
  return main;
}

// Reverse linked list
NODE* reverse_linked_list(NODE* head) {
  NODE* ptr1 = (head) ? head : NULL;
  NODE* ptr2 = (ptr1) ? ptr1->next : NULL;
  NODE* ptr3 = (ptr2) ? ptr2->next : NULL;
  NODE* main = ptr1;
  if(ptr1 && ptr2) {
		ptr1->next = NULL;
		while(ptr2 && ptr2->next) {
      ptr2->next = ptr1;
      ptr1 = ptr2;
      ptr2 = ptr3;
      ptr3 = ptr3->next;
    }
    ptr2->next = ptr1;
    main = ptr2;
  }
  return main;
}

// Break linked list and merge reversed sublists
NODE* reverse_merge_list(NODE* head) {
  NODE* middle = get_middle_node(head);
  middle->next = reverse_linked_list(middle->next);
  return head;
}

// Find loop node in linked list
NODE* find_loop_node(NODE* head) {
  NODE* slow = head;
  NODE* fast = (slow) ? slow->next : NULL;
  while(slow && fast && fast->next) {
    if(slow == fast) {
      return slow;
    }
    slow = slow->next;
    fast = fast->next->next;
  }
  return NULL;
}

// Detect and break loop in linked list
void detect_break_loop(NODE* head) {
  NODE* loop = find_loop_node(head);
  if(loop == NULL) {
    printf("\nNo loop exists");
    return;
  }
  printf("\nNode %d is one of the loop nodes", loop->value);
  NODE* ptr1 = head;
  NODE* ptr2 = loop;
  while(ptr2->next != ptr1) {
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }
  printf("\nLoop Start: %d", ptr1->value);
  printf("\nLoop End: %d", ptr2->value);
  ptr2->next = NULL;
}

// Reverse linked list from M to N
NODE* reverse_sublist_range(NODE* head, const int m, const int n) {
  if((m < 0)||(n < 0)||(m >= n)) {
    printf("\nInvalid range %d-%d", m, n);
    return head;
  }
  NODE dummy;
  dummy.value = 0;
  dummy.next = head;
  NODE *prev, *next, *start, *end, *ptr;
  int index;
  // Iterate over linked list
  for(index = 0, ptr = &dummy; ptr != NULL; index++, ptr = ptr->next) {
    if(index == (m-1)) {
      prev = ptr;
      start = ptr->next;
    }
    if(index == n) {
      next = ptr->next;
      end = ptr;
      end->next = NULL;
      break;
    }
  }
  if(index == n) {
    prev->next = reverse_linked_list(start);
    start->next = next;
  }
  return dummy.next;
}

// Reverse linked list in groups of K
NODE* reverse_sublist_group(NODE* head, const int group) {
  NODE* main = NULL;
  NODE* chain = NULL;
  NODE* ptr = head;
  NODE *start, *prev;
  while (ptr != NULL) {
    prev  = NULL;
    start = ptr;
    int count = group;
    // Reverse group
    while (ptr && (count > 0)) {
      NODE* temp = ptr->next;
      ptr->next = prev;
      prev = ptr;
      ptr = temp;
      count --;
    }
    // Set new head
    if(main == NULL) {
      main = prev;
    }
    // Chain previous start to current previous (last)
    if(chain != NULL) {
      chain->next = prev;
    }
    // Reset chain to current start
    chain = start;
  }
  return main;
}

// Recursively reverse linked list
void recursive_reverse(NODE* curr, NODE* prev, NODE* &headRef) {
  if(curr == NULL) {
    // Reached end of linked list
    headRef = prev;
  } else {
    // Recursively call over to next node
    recursive_reverse(curr->next, curr, headRef);
    // Assign current next to previous
    curr->next = prev;
  }
}

int main() {
  int arr[] = {1, 2};
  int size = sizeof(arr)/sizeof(arr[0]);
  NODE* head = array_to_list(arr, size);
  display_list(head);

  recursive_reverse(head, NULL, head);
  display_list(head);

  delete_list(head);

  // head = reverse_sublist_group(head, 1);
  // display_list(head);
  // delete_list(head);

  // head = reverse_merge_list(head);
  // display_list(head);

  // NODE* temp = get_index_node(head, 3);
  // NODE* last = get_last_node(head);
  // printf("\nLoop induced %d --> %d", last->value, temp->value);
  // last->next = temp;
  // detect_break_loop(head);
  // //last->next = NULL;
  // delete_list(head);
  // int arr1[] = {1, 5, 9, 12};
  // int size1 = sizeof(arr1)/sizeof(arr1[0]);
  // NODE* head1 = array_to_list(arr1, size1);
  // display_list(head1);
  //
  // int arr2[] = {2, 4, 7, 10};
  // int size2 = sizeof(arr2)/sizeof(arr2[0]);
  // NODE* head2 = array_to_list(arr2, size2);
  // display_list(head2);
  //
  // NODE* head = merge_sort_lists(head1, head2);
  // display_list(head);
  // delete_list(head);

  //merge_sort_lists(head1, head2);
  // NODE* last = get_last_node(head);
  // printf("\nLast Node: %d", (last)?last->value:-1);
  // NODE* middle = get_middle_node(head);
  // printf("\nMiddle Node: %d", (middle)?middle->value:-1);
  // head = middle_alternate_merge(head);
  // display_list(head);
  // delete_list(head);
  return 0;
}
