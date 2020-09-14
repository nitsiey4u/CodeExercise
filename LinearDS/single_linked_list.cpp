#include "stdio.h"
#include "stdlib.h"

struct Node{
	int value;
	struct Node* next;
};
typedef struct Node NODE;

void display_list(NODE* head, const char* title) {
	NODE* ptr = NULL;
	printf("\n%s: ", title);
	for(ptr = head; ptr != NULL; ptr = ptr->next) {
		printf("%d%s", ptr->value, ((ptr->next)? "->" : ""));
	}
}

void delete_list(NODE* head) {
	NODE *ptr, *prev;
	for(prev = head, ptr = ((head)?head->next:NULL); ptr != NULL; prev = ptr, ptr = ptr->next) {
		free(prev);
	}
	free(prev);
	head = NULL;
}

NODE* create_node(int value) {
	NODE* temp = (NODE*) malloc (sizeof(NODE));
	if(temp != NULL) {
		temp->value = value;
		temp->next = NULL;
	}
	return temp;
}

void push_back(NODE** head_ref, int value) {
	NODE *temp = create_node(value);
	if(*head_ref == NULL) {
		*head_ref = temp;
	}
	else {
		NODE* ptr;
		for(ptr = (*head_ref); ptr->next != NULL; ptr = ptr->next);
		ptr->next = temp;
	}
}

// NODE* reverse_list(NODE* head) {
// 	NODE *ptr1, *ptr2, *ptr3;
// 	ptr1 = head;
// 	ptr2 = (ptr1) ? ptr1->next : NULL;
// 	ptr3 = (ptr2) ? ptr2->next : NULL;
//
// 	if(ptr1 != NULL)
// 		ptr1->next = NULL;
// 	else
// 		return ptr1;
//
// 	while(ptr3 != NULL) {
// 		ptr2->next = ptr1;
// 		ptr1 = ptr2;
// 		ptr2 = ptr3;
// 		ptr3 = ptr3->next;
// 	}
//
// 	if(ptr2 != NULL) {
// 		ptr2->next = ptr1;
// 		head = ptr2;
// 	}
// 	return head;
// }
//
// NODE* reverse_sublist(NODE* head, int m, int n) {
// 	NODE *prev, *next, *start, *end, *ptr;
// 	int index;
// 	NODE dummy;
// 	dummy.next = head;
// 	for(ptr = &dummy, index = 0; ptr != NULL; ptr = ptr->next, index++) {
// 		if(index == (m - 1)) {
// 			prev = ptr;
// 			start = prev->next;
// 		}
// 		else if(index == n) {
// 			end = ptr;
// 			next = end->next;
// 			end->next = NULL;
// 			break;
// 		}
// 	}
// 	if(index == n) {
// 		NODE* reverse = reverse_list(start);
// 		prev->next = reverse;
// 		start->next = next;
// 	}
// 	return dummy.next;
// }

NODE* reverse_linked_list(NODE* head) {
	NODE* ptr1 = (head) ? head : NULL;
	NODE* ptr2 = (ptr1) ? ptr1->next : NULL;
	NODE* ptr3 = (ptr2) ? ptr2->next : NULL;
	if(ptr1 && ptr2) {
		ptr1->next = NULL;
		while(ptr2 && ptr2->next) {
			ptr2->next = ptr1;
			ptr1 = ptr2;
			ptr2 = ptr3;
			ptr3 = ptr2->next;
		}
		ptr2->next = ptr1;
		head = ptr2;
	}
	return head;
}

int main(int argc, char* argv[]) {
	NODE* head = NULL;
	push_back(&head, 3);
	push_back(&head, 4);
 	push_back(&head, 5);
	push_back(&head, 6);
	push_back(&head, 7);
	push_back(&head, 8);
	display_list(head, "Linked List");
	head = reverse_linked_list(head);
	display_list(head, "Reversed List");
	// head = reverse_sublist(head, 1, 5);
	// display_list(head, "Reversed Sublist");
	delete_list(head);
}
