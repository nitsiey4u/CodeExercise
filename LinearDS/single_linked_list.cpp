#include <cstdio>
#include <cstdlib>

#define MAX(x,y) ((x>y)?(x):(y))
#define BOOL(x)  ((x)?"True":"False")

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

// Display Node
void display_node(const char* hdr, NODE* ptr) {
  if(ptr != NULL) {
    printf("\n%s: %d", hdr, ptr->value);
  } else {
    printf("\n%s: NULL", hdr);
  }
}

// Display linked list
void display_list(NODE* head) {
  NODE *ptr = NULL;
  printf("\nList:");
  if(head != NULL) {
    for(ptr = head; ptr != NULL; ptr = ptr->next) {
      const char* line = (ptr->next != NULL) ? "--->" : "";
      printf(" %d %s", ptr->value, line);
    }
  } else {
    printf(" NIL ");
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


// Create list of zero nodes of specific count
NODE* zero_nodes_list(const int maxcount) {
  NODE* result = NULL;
  NODE* valptr = NULL;
  for(int index = 0; index < maxcount; index++) {
    NODE* temp = create_node(0);
    if(result == NULL) {
      valptr = temp;
      result = valptr;
    } else {
      valptr->next = temp;
      valptr = valptr->next;
    }
  }
  return result;
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
NODE* merge_sorted_lists(NODE* head1, NODE* head2) {
  NODE* result = NULL;
  NODE* ptr    = NULL;
  NODE* ptr1   = head1;
  NODE* ptr2   = head2;

  while(ptr1 && ptr2) {
    NODE* temp = NULL;
    // Get node with smallest value
    if(ptr1->value < ptr2->value) {
      temp = ptr1;
      ptr1 = ptr1->next;
    } else {
      temp = ptr2;
      ptr2 = ptr2->next;
    }
    // Save smallest node into result
    if(ptr == NULL) {
      // Set new head
      ptr = temp;
      result = ptr;
    } else {
      // Move ptr to last merged node
      ptr->next = temp;
      ptr = ptr->next;
    }
  }
  // Save remainder of ptr1
  if(ptr1) {
    ptr->next = ptr1;
  }
  // Save remainder of ptr2
  if(ptr2) {
    ptr->next = ptr2;
  }
  // Return merged list
  return result;
}

NODE* combine_sort_lists(NODE* & ptr1, NODE* & ptr2) {
  NODE* result = NULL;
  if(ptr1 == NULL) {
    return ptr2;
  } else if (ptr2 == NULL) {
    return ptr1;
  }
  if(ptr1->value < ptr2->value) {
    result = ptr1;
    result->next = combine_sort_lists(ptr1->next, ptr2);
  } else {
    result = ptr2;
    result->next = combine_sort_lists(ptr1, ptr2->next);
  }
  return result;
}

// Merge Sort linked list - O(NLogN)
void merge_sort(NODE* & head) {
  // If only 1 node exists
  if((head == NULL) || (head->next == NULL)) {
    return;
  }
  // Get middle node and split into 2 sub-lists
  NODE* mid = get_middle_node(head);
  NODE* ptr1 = head;
  NODE* ptr2 = mid->next;
  mid->next = NULL;
  // Recursively merge sort sublist-1
  merge_sort(ptr1);
  // Recursively merge sort sublist-2
  merge_sort(ptr2);
  // Merge sublists into sorted sublist
  head = combine_sort_lists(ptr1, ptr2);
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

// Break linked list and alternate merge reversed last-sublist
NODE* middle_alternate_reverse_merge(NODE* head) {
  NODE* middle = get_middle_node(head);
  NODE* head1  = head;
  NODE* head2  = middle->next;
  middle->next = NULL;
  head2 = reverse_linked_list(head2);
  NODE* ptr1 = head1;
  NODE* ptr2 = head2;
  NODE* result = ptr1;
  while(ptr1 && ptr2) {
    NODE* next1 = ptr1->next;
    NODE* next2 = ptr2->next;
    ptr1->next = ptr2;
    ptr2->next = next1;
    ptr1 = next1;
    ptr2 = next2;
  }
  return result;
}

// Check if linked list is palindrome
bool is_palindrome(NODE* head) {
  NODE* middle = get_middle_node(head);
  NODE* head1 = head;
  NODE* head2 = middle->next;
  middle->next = NULL;
  head2 = reverse_linked_list(head2);
  bool flag  = true;
  NODE* ptr1 = head1;
  NODE* ptr2 = head2;
  while((flag) && (ptr1 && ptr2)) {
    flag = (ptr1->value == ptr2->value);
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }
  middle->next = reverse_linked_list(head2);
  return flag;
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

// Reverse linked list in alternate groups of K
NODE* reverse_alternate_sublist_group(NODE* head, const int group) {
  NODE* lower = NULL;
  NODE* upper = NULL;
  NODE *prev, *next, *ptr, *itr;
  int value = 1;
  int index = 0;
  int counter = group;

  NODE dummy;
  dummy.value = 0;
  dummy.next = head;
  for(ptr = head, itr = &dummy; ptr != NULL; itr = ptr, ptr = ptr->next) {
    //printf("\nCounter: %d", counter);
    if(counter == group) {
      prev = itr;
      lower = ptr;
      value = -1;
    } else if(counter == 0) {
      value = +1;
    } else if(counter == 1) {
      if(lower) {
        upper = ptr;
        next = ptr->next;
      }
    }

    if(lower && upper) {
      printf("\nReverse: %d-%d", lower->value, upper->value);
      display_node("Prev", prev);
      display_node("Next", next);

      upper->next = NULL;
      prev->next = reverse_linked_list(lower);
      lower->next = next;
      ptr = lower;
      prev = NULL;
      next = NULL;
      lower = NULL;
      upper = NULL;
    }
    counter = counter + value;
  }
  return dummy.next;
}

// Display circular linked list
void display_circular_list(NODE* head, NODE* tail) {
  printf("\nCircular List: ");
  if(head && tail) {
    for(NODE* ptr = head; ptr != tail; ptr = ptr->next) {
      printf(" %d --> ", ptr->value);
    }
    printf(" %d", tail->value);
  }
}

// Reverse circular linked list
void reverse_circular_list(NODE* & head, NODE* & tail) {
  if((head != NULL) && (head != tail)) {
    NODE* prev = head;
    NODE* curr = prev->next;
    NODE* next = (curr != tail) ? curr->next : NULL;
    prev->next = tail;
    tail = prev;
    while(curr && next && (curr != head) && (next != head)) {
      curr->next = prev;
      prev = curr;
      curr = next;
      next = next->next;
    } // End of while loop
    curr->next = prev;
    head = curr;
  } // End of if block
}

// Delete circular linked list
void delete_circular_list(NODE* & head, NODE* & tail) {
  if(head && tail) {
    NODE *ptr, *prev;
    for(ptr = head, prev = NULL; ptr != tail; prev = ptr, ptr = ptr->next) {
      if(prev != NULL) {
        printf("\nFreeing %d", prev->value);
        free(prev);
        prev = NULL;
      }
    }
    // Delete 2nd last element
    if(prev) {
      printf("\nFreeing %d", prev->value);
      free(prev);
      prev = NULL;
    }
    // Delete last element
    if(tail) {
      printf("\nFreeing %d", tail->value);
      free(tail);
      tail = NULL;
    }
    head = NULL;
  }
}

// Recursively reverse linked list and return number of nodes
int recursive_reverse(NODE* curr, NODE* prev, NODE* &headRef) {
  int retval = 0;
  if(curr == NULL) {
    // Reached end of linked list
    headRef = prev;
  } else {
    // Recursively call over to next node
    retval = 1 + recursive_reverse(curr->next, curr, headRef);
    // Assign current next to previous
    curr->next = prev;
  }
  return retval;
}

// Multiple large numbers represented by linked list - O(N2)
NODE* multiply_lists(NODE* & head1, NODE* & head2) {
  // Reverse list with number 1
  int m = recursive_reverse(head1, NULL, head1);
  // Reverse list with number 2
  int n = recursive_reverse(head2, NULL, head2);
  // Max number of nodes in result
  int maxcount = (m + n + 1);
  // Create result list
  NODE* result = zero_nodes_list(maxcount);
  int count;
  NODE *ptr1, *ptr2;
  for(ptr1 = head2, count = 0; ptr1 != NULL; ptr1 = ptr1->next, count++) {
    int carry = 0;
    NODE* ptr = result;
    int index = 0;
    for(ptr2 = head1; ptr2 != NULL; ptr2 = ptr2->next) {
      while(index < count) {
        // Handle 10th position to skip result values
        ptr = ptr->next;
        index++;
      }
      // Multiply digits and add to previous result
      int value = (ptr1->value * ptr2->value) + ptr->value + carry;
      // Save lowest remainder
      ptr->value = value % 10;
      // Carry overflow value for next iteration
      carry = value / 10;
      // Move to next position of result
      ptr = ptr->next;
    } // Inner loop
    // Handle remaining carry value
    while(carry > 0) {
      int value = carry % 10;
      carry = carry / 10;
      if(ptr != NULL) {
        ptr->value = value;
        ptr = ptr->next;
      } else {
        printf("\nNot available nodes");
      }
    }
  } // Outer loop
  // Reverse final result
  result = reverse_linked_list(result);
  // Remove prefixed buffer zeroes
  NODE* ptr = result;
  while((ptr != NULL) && (ptr->value == 0)) {
    NODE* temp = ptr;
    ptr = ptr->next;
    result = ptr;
    free(temp);
  }
  return result;
}

// Add large numbers represented by linked list - O(N)
NODE* add_lists(NODE* & head1, NODE* & head2) {
  // Reverse list with number 1
  int count1 = recursive_reverse(head1, NULL, head1);
  // Reverse list with number 2
  int count2 = recursive_reverse(head2, NULL, head2);
  // Max number of nodes in result
  int maxcount = MAX(count1, count2) + 1;
  // Max difference which needs to be adjusted
  int difcount = abs(count1 - count2);
  // Create result list
  NODE* result = zero_nodes_list(maxcount);
  // Create list to insert zeros
  NODE* buffer = zero_nodes_list(difcount);
  // Adjust zero to smaller number
  if(count1 != count2) {
    NODE* last = NULL;
    if(count1 > count2) {
      // Get last node for 2nd list
      last = get_last_node(head2);
    } else {
      // Get last node for 1st list
      last = get_last_node(head1);
    }
    // Zeroes appended at last
    last->next = buffer;
  }

  NODE *ptr, *ptr1, *ptr2;
  int carry = 0;
  // Add digits for both numbers
  for(ptr1 = head1, ptr2 = head2, ptr = result;
      ptr1 && ptr2; ptr1 = ptr1->next, ptr2 = ptr2->next) {
    int value = ptr1->value + ptr2->value + carry;
    ptr->value = value % 10;
    carry = value / 10;
    ptr = ptr->next;
  }
  // Handle overflow carry
  while(carry > 0) {
    ptr->value = carry % 10;
    carry = carry / 10;
    ptr = ptr->next;
  }
  // Reverse final result
  result = reverse_linked_list(result);
  ptr = result;
  // Remove prefixed buffer zeroes
  while((ptr != NULL) && (ptr->value == 0)) {
    NODE* temp = ptr;
    ptr = ptr->next;
    result = ptr;
    free(temp);
  }
  return result;
}

// Display union and intersection of lists O(MlogM + NlogN + [M + N])
void union_intersection_lists(NODE* head1, NODE* head2) {
  NODE* union_head = NULL;
  NODE* insct_head = NULL;
  if((head1 != NULL) && (head2 != NULL)) {
    // Merge sort list - O(MlogM)
    merge_sort(head1);
    // Merge sort list - O(NLogN)
    merge_sort(head2);
    // Init values
    NODE* ptr1 = head1;
    NODE* ptr2 = head2;
    NODE* uptr = NULL;
    NODE* iptr = NULL;
    // Get union and intersection result for both lists O(M+N)
    while(ptr1 && ptr2) {
      NODE* temp = NULL;
      // Compare values of both lists
      if(ptr1->value == ptr2->value) {
        // Intersection - Create copy of equal nodes
        NODE* copy = create_node(ptr1->value);
        if(insct_head == NULL) {
          insct_head = copy;
          iptr = insct_head;
        } else {
          iptr->next = copy;
          iptr = iptr->next;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;

        // Initialize temp node for union result
        temp = create_node(copy->value);
      } else {
        // Union - Create copy of smaller nodes
        if(ptr1->value < ptr2->value) {
          temp = create_node(ptr1->value);
          ptr1 = ptr1->next;
        } else {
          temp = create_node(ptr2->value);
          ptr2 = ptr2->next;
        }
      }
      // Every common and uncommon nodes are part of union result
      if(union_head == NULL) {
        union_head = temp;
        uptr = union_head;
      } else {
        uptr->next = temp;
        uptr = uptr->next;
      }
    } // While loop

    // Add remaining nodes to union result
    while(ptr1 != NULL) {
      uptr->next = create_node(ptr1->value);
      uptr = uptr->next;
      ptr1 = ptr1->next;
    }

    // Add remaining nodes to union result
    while(ptr2 != NULL) {
      uptr->next = create_node(ptr2->value);
      uptr = uptr->next;
      ptr2 = ptr2->next;
    }

  } else {
    // If any of the lists is empty
    union_head = (head1 != NULL) ? head1 : head2;
    insct_head = NULL;
  }

  // Display results
  printf("\nUnion: ");
  display_list(union_head);
  printf("\nIntersection: ");
  display_list(insct_head);

  // Delete union and intersection lists
  delete_list(union_head);
  delete_list(insct_head);
}

// Merge lists with alternate nodes (in-place)
void alternate_merge_lists(NODE* & head1, NODE* & head2) {
  NODE* ptr1 = head1;
  NODE* ptr2 = head2;
  // Iterate over both lists
  while(ptr1 && ptr2) {
    NODE* next1 = ptr1->next;
    NODE* next2 = ptr2->next;
    ptr1->next = ptr2;
    ptr2->next = next1;
    ptr1 = next1;
    ptr2 = next2;
  }
  head2 = ptr2;
}

int main() {
  // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  // int size = sizeof(arr)/sizeof(arr[0]);
  // NODE* head = array_to_list(arr, size);
  // display_list(head);
  //head = middle_alternate_reverse_merge(head);
  // printf("\nIs Palindrome: %s", BOOL(is_palindrome(head)));
  // display_list(head);

  // head = reverse_alternate_sublist_group(head, 2);

  // display_list(head);
  // recursive_reverse(head, NULL, head);
  // display_list(head);
  //
  // delete_list(head);

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
  // NODE* head = merge_sorted_lists(head1, head2);
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

  // NODE* tail = get_last_node(head);
  // tail->next = head;
  // display_circular_list(head, tail);
  // reverse_circular_list(head, tail);
  // display_circular_list(head, tail);
  // delete_circular_list(head, tail);

  // delete_list(head);

  //
  // int arr[] = {15, 10, 5, 20, 3, 2};
  // int size = sizeof(arr)/sizeof(arr[0]);
  // NODE* head = array_to_list(arr, size);
  // display_list(head);
  // merge_sort(head);
  // display_list(head);
  // delete_list(head);

//  int arr1[] = {9, 4, 6};
//  int arr2[] = {8, 4, 9};
  // int arr1[] = {9, 9, 9};
  // int size1 = sizeof(arr1)/sizeof(arr1[0]);
  // NODE* head1 = array_to_list(arr1, size1);
  // display_list(head1);
  //
  // int arr2[] = {9, 9, 9};
  // int size2 = sizeof(arr2)/sizeof(arr2[0]);
  // NODE* head2 = array_to_list(arr2, size2);
  // display_list(head2);
  //
  // NODE* result = multiply_lists(head1, head2);
  // NODE* result = add_lists(head1, head2);
  //
  // display_list(result);
  //
  // delete_list(head1);
  // delete_list(head2);
  // delete_list(result);

  // int arr1[] = {10, 15, 4, 20};
  // int size1 = sizeof(arr1)/sizeof(arr1[0]);
  // NODE* head1 = array_to_list(arr1, size1);
  // display_list(head1);
  //
  // int arr2[] = {8, 4, 2, 10};
  // int size2 = sizeof(arr2)/sizeof(arr2[0]);
  // NODE* head2 = array_to_list(arr2, size2);
  // display_list(head2);
  //
  // union_intersection_lists(head1, head2);

  int arr1[] = {1, 2, 3};
  int size1 = sizeof(arr1)/sizeof(arr1[0]);
  NODE* head1 = array_to_list(arr1, size1);
  display_list(head1);

  int arr2[] = {4, 5, 6, 7, 8};
  int size2 = sizeof(arr2)/sizeof(arr2[0]);
  NODE* head2 = array_to_list(arr2, size2);
  display_list(head2);

  alternate_merge_lists(head1, head2);
  display_list(head1);
  display_list(head2);

  delete_list(head1);
  delete_list(head2);

  return 0;
}
