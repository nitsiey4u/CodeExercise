#include "stdio.h"
#include "stdlib.h"

#define MAX(X,Y) ((X>Y)?(X):(Y))
#define MIN(X,Y) ((X<Y)?(X):(Y))
#define BOOL(X)  ((X)?"True":"False")

struct BinarySearchTree {
  int value;
  struct BinarySearchTree *left, *right;
};
typedef struct BinarySearchTree BST;

// Helper function for padding
void print_padding(char pad, int level){
  for (int index = 0; index < level; index++ )
    putchar(pad);
}

// Print BST
void print_bst(BST* root, int level){
  if (root == NULL) {
    print_padding( '\t', level);
  } else {
    print_bst(root->right, (level + 1));
    print_padding('\t', level);
    printf("%d\n", root->value);
    print_bst(root->left, (level + 1));
  }
}

// Create BST Tree Node
BST* create_node(const int value) {
  BST* temp = (BST*) malloc(sizeof(BST));
  temp->value = value;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

// Erase BST Tree
void erase_bst(BST* root) {
  if(root != NULL) {
    erase_bst(root->left);
    erase_bst(root->right);
    free(root);
    root = NULL;
  }
}

// Inorder traversal of BST is sorted list
void inorder_traversal(BST* root) {
  if(root != NULL) {
    inorder_traversal(root->left);
    printf("\t%d", root->value);
    inorder_traversal(root->right);
  }
}

// Search BST for specific key - Log(N)
BST* search_key(BST* root, const int key) {
  if(root != NULL) {
    if(root->value == key) {
      return root;
    }
    if(root->value < key) {
      return search_key(root->right, key);
    } else {
      return search_key(root->left, key);
    }
  }
  // Key not found return NULL
  return NULL;
}

// Insert key into BST - O(Log N)
BST* insert_key(BST* root, const int key){
  if(root == NULL) {
    // Insert as tree root
    root = create_node(key);
  } else {
    if(key < root->value) {
      // Insert into left subtree
      root->left  = insert_key(root->left, key);
    } else {
      // Insert into right subtree
      root->right = insert_key(root->right, key);
    }
  }
  return root;
}

// Delete key from BST - Log(N)
BST* delete_key(BST* root, const int key) {
  BST *next = root;
  BST *prev = NULL;
  // Iterate to find key
  while(next && (next->value != key)) {
    prev = next;
    if(key < next->value)
      next = next->left;
    else
      next = next->right;
  }
  // Found key, proceed with delete
  BST* curr = next;
  if(curr && (curr->value == key)) {
    // Has no left subtree & right subtree
    if((curr->left == NULL) && (curr->right == NULL)) {
      // Ensure its not root
      if(prev != NULL) {
        if(prev->left == curr)
          prev->left = NULL;
        else
          prev->right = NULL;
      } else {
        // New root becomes NULL
        root = prev;
      }
    }
    // Has left subtree only
    else if ((curr->left != NULL) && (curr->right == NULL)) {
      // Ensure its not root
      if(prev != NULL) {
        if(prev->left == curr)
          prev->left = curr->left;
        else
          prev->right = curr->left;
      } else {
        // Left subtree becomes new root
        root = curr->left;
      }
    }
    // Has right subtree only
    else if ((curr->left == NULL) && (curr->right != NULL)) {
      // Ensure its not root
      if(prev != NULL) {
        if(prev->left == curr)
          prev->left = curr->right;
        else
          prev->right = curr->right;
      } else {
        // Right subtree becomes new root
        root = curr->right;
      }
    }
    // Has both subtrees
    else {
      BST* left_subtree = curr->left;
      BST* right_subtree = curr->right;
      BST* temp = right_subtree;
      // go to leftmost part of right subtree
      while(temp->left != NULL)
        temp = temp->left;
      temp->left = left_subtree;
      // attach right subtree with parent of curr
      if(prev != NULL) {
        if(prev->left == curr)
          prev->left = right_subtree;
        else
          prev->right = right_subtree;
      } else {
        root = right_subtree;
      }
    }
    // Delete key
    free(curr);
    curr = NULL;
  }
  return root;
}

// Create BST from input array - (N LogN)
BST* create_bst(int arr[], int size) {
  BST* root = NULL;
  for(int index = 0; index < size; index++) {
    root = insert_key(root, arr[index]);
  }
  return root;
}

// Sorted array to balanced BST - O(N)
BST* array_to_bst(int arr[], int low, int high) {
  BST* root = NULL;
  if(low <= high) {
    int mid = low + (high - low)/2;
    root = create_node(arr[mid]);
    root->left  = array_to_bst(arr, low, (mid - 1));
    root->right = array_to_bst(arr, (mid + 1), high);
  }
  return root;
}

// Is valid BST - O(N)
bool is_valid(BST* curr) {
  static BST* prev = NULL;
  if(curr != NULL) {
    // Check left subtree
    if(!is_valid(curr->left)) {
      return false;
    }
    // Ideally previous < current
    if((prev != NULL) && (curr->value <= prev->value)) {
      return false;
    }
    // Current node is Previous for next right child
    prev = curr;
    // Check right subtree
    return is_valid(curr->right);
  }
  return true;
}

// Find least common ancestor of two existing keys - O(Log N)
BST* find_lca(BST* root, const int key1, const int key2) {
  if(root != NULL) {
    // Check range of values
    if(MAX(key1, key2) < root->value) {
      // Max value smaller, means both keys are in left subtree
      return find_lca(root->left, key1, key2);
    } else if(MIN(key1, key2) > root->value) {
      // Min value larger, means both keys are in right subtree
      return find_lca(root->right, key1, key2);
    } else {
      // Both keys are in different subtrees
      return root;
    }
  }
  return NULL;
}

// Find K smallest key in BST
BST* find_ksmallest(BST* root, int& kval) {
  if(root != NULL) {
    // Process left side
    BST* left = find_ksmallest(root->left, kval);
    if(left != NULL) {
      return left;
    }
    // Decrement k value
    kval --;
    if(kval == 0) {
      return root;
    }
    // Process right side
    return find_ksmallest(root->right, kval);
  }
  return NULL;
}

// Find K largest key in BST
BST* find_klargest(BST* root, int& kval) {
  if(root != NULL) {
    // Process right side
    BST* right = find_klargest(root->right, kval);
    if(right != NULL) {
      return right;
    }
    // Decrement k value
    kval --;
    if(kval == 0) {
      return root;
    }
    // Process left side
    return find_klargest(root->left, kval);
  }
  return NULL;
}

// Get distance of path (number of edges) from root to specific key
int path_distance(BST* root, const int key) {
  if(root != NULL) {
    if(root->value == key) {
      return 0;
    }
    if(root->value < key) {
      return 1 + path_distance(root->right, key);
    } else {
      return 1 + path_distance(root->left, key);
    }
  }
  return 0;
}

// Measure distance (number of edges) between two specific nodes
// path_distance(Node1) + path_distance(Node2) - 2 * path_distance(LCA)
int node_distance(BST* root, const int node1, const int node2) {
  if(root != NULL) {
    if((node1 < root->value) && (node2 < root->value)) {
      // Both keys in left subtree
      return node_distance(root->left, node1, node2);
    } else if((root->value < node1) && (root->value < node2)) {
      // Both keys in right subtree
      return node_distance(root->right, node1, node2);
    } else {
      // Current node is LCA, find distance from LCA
      return path_distance(root, node1) + path_distance(root, node2);
    }
  }
  return 0;
}


int main() {
//  int arr[] = {4, 7, 6, 2, 3, 1, 8, 5};

//   int arr[] = {2, 4, 6, 8, 10, 12, 14};
// //  int arr[] = {11, 9, 7, 5, 4, 3, 1};
//   int size  = sizeof(arr)/sizeof(arr[0]);
//   BST* root = create_bst(arr, size);
//   print_bst(root, 0);
//   inorder_traversal(root);

  int srt[] = {2, 4, 6, 8, 10, 12, 14};
  int cnt   = sizeof(srt)/sizeof(srt[0]);
  BST* root = array_to_bst(srt, 0, (cnt - 1));

  int val[] = {1, 5, 11, 3, 15, 13};
  int len   = sizeof(val)/sizeof(val[0]);
  for(int index = 0; index < len; index++) {
    root = insert_key(root, val[index]);
  }

  inorder_traversal(root);
  print_bst(root, 0);

  // int k1 = 6;
  // int k2 = 10;
  // BST* node = find_lca(root, k1, k2);
  // if(node != NULL) {
  //   printf("\nLCA of %d and %d is %d", k1, k2, node->value);
  // } else {
  //   printf("\nLCA of %d and %d not found", k1, k2);
  // }
  //
  // int kval = 2;
  // BST* node = find_klargest(root, kval);
  // if(node != NULL) {
  //   printf("\n%dth largest %d", kval, node->value);
  // } else {
  //   printf("\n%dth largest not found", kval);
  // }
//  printf("\nDistance: %d", path_distance(root, 15));

  printf("\nDistance: %d", node_distance(root, 2, 6));



  // BST* node = NULL;
  // node = search_key(root, 14);
  // node->right = create_node(7);
  // inorder_traversal(root);

  // printf("\nIs Valid: %s", BOOL(is_valid(root)));

  //

  // printf("\nTree: ");
  // print_bst(root, 0);
  // printf("\nInorder traversal: ");
  // inorder_traversal(root);
  //
  // //  int del[] = {2, 6, 10, 14, 1, 3, 5, 11, 13, 15, 8};
  // // int del[] = {8, 4, 6, 10, 12};
  // int del[] = {14, 12, 10, 8, 6, 4, 2};
  // int rem   = sizeof(del)/sizeof(del[0]);
  // for(int index = 0; index < rem; index++) {
  //   printf("\nDelete key: %d", del[index]);
  //   root = delete_key(root, del[index]);
  //   printf("\n New Order: ");
  //   inorder_traversal(root);
  // }

  // const int key = 7;
  // BST* node = search_key(root, key);
  // printf("\nKey %d %sfound", key, ((node)?"":"not "));
  // node->left = create_node(0);
  // printf("\nIs valid BST: %s", BOOL(validate_bst(root)));

  erase_bst(root);
  // int srt[] = {1, 2, 3, 4, 5, 6, 7, 8};
  // int cnt   = sizeof(srt)/sizeof(srt[0]);
  // BST* copy = array_to_bst(srt, 0, (cnt - 1));
  // print_bst(copy, 1);
  // erase_bst(copy);
  return 0;
}
