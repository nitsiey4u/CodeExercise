#include <cstdio>
#include <cstdlib>
#include <stack>
#include <list>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define MAX(X,Y) ((X>Y)?(X):(Y))
#define BOOL(X)  ((X)?"True":"False")

typedef unsigned char uchar_t;

// Binary Tree Node
struct BinaryTree{
  char   data;
  struct BinaryTree* left;
  struct BinaryTree* right;
};
typedef struct BinaryTree BTREE;

// Helper for padding
void print_padding(char ch, int n){
  for (int i = 0; i < n; i++) {
    putchar(ch);
  }
}

// Helper to print tree structure
void print_tree(BTREE* root, int level){
  if (root == NULL) {
    print_padding( '\t', level);
  } else {
    print_tree(root->right, (level + 1));
    print_padding('\t', level);
    printf("%c\n", root->data);
    print_tree(root->left, (level + 1));
  }
}

// Create binary tree node
BTREE* create_node(const char data) {
  BTREE* temp = (BTREE*) malloc(sizeof(BTREE));
  temp->data  = data;
  temp->left  = NULL;
  temp->right = NULL;
  return temp;
}

// Erase binary tree
void erase_tree(BTREE* root) {
  // Recurse until node is not null
  if(root != NULL) {
    // Erase left subtree
    erase_tree(root->left);
    // Erase right subtree
    erase_tree(root->right);
    // Erase parent node
    //printf("\nDeleting %c", root->data);
    free(root);
    root = NULL;
  }
}

// Inorder traversal - L, P, R
void inorder_traversal(BTREE* root) {
  // Left, Parent, Right
  if(root != NULL) {
    inorder_traversal(root->left);
    printf("\t%c", root->data);
    inorder_traversal(root->right);
  }
}

// Inorder walkover (Iterative)
void inorder_walkover(BTREE* root) {
  stack<BTREE*> STACK;
  BTREE* ptr = root;
  // Iterate over left child and push to stack (Rep LOOP)
  while(ptr != NULL) {
    STACK.push(ptr);
    ptr = ptr->left;
  }
  // Until stack is empty
  while(!STACK.empty()) {
    // Remove left child and print it
    ptr = STACK.top();
    printf("\t%c", ptr->data);
    STACK.pop();
    // Iterate over right children and push to stack (Rep LOOP)
    ptr = ptr->right;
    while(ptr != NULL) {
      STACK.push(ptr);
      ptr = ptr->left;
    }
  }
}

// Preorder traversal - P, L, R (DFS)
void preorder_traversal(BTREE* root) {
  // Parent, Left, Right
  if(root != NULL) {
    printf("\t%c", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
  }
}

// Preorder walkover (Iterative)
void preorder_walkover(BTREE* root) {
  stack<BTREE*> STACK;
  BTREE* ptr = root;
  // Iterate print over left child and push right child to stack (Rep LOOP)
  while(ptr != NULL) {
    // Print left child (visited parent)
    printf("\t%c", ptr->data);
    if(ptr->right != NULL) {
      // Push right child to stack
      STACK.push(ptr->right);
    }
    // Iterate over left child
    ptr = ptr->left;
  }
  // Until stack is empty
  while(!STACK.empty()) {
    // Pop element but do not print
    ptr = STACK.top();
    STACK.pop();
    // Rep LOOP
    while(ptr != NULL) {
      // Print left child (visited parent)
      printf("\t%c", ptr->data);
      if(ptr->right != NULL) {
        // Push right child to stack
        STACK.push(ptr->right);
      }
      // Iterate over left child
      ptr = ptr->left;
    }
  }
}

// Postorder traversal - L, R, P
void postorder_traversal(BTREE* root) {
  // Left, Right, Parent
  if(root != NULL) {
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("\t%c", root->data);
  }
}

// Postorder walkover (Iterative)
void postorder_walkover(BTREE* root) {
  stack<BTREE*> STACK;
  BTREE* prev = NULL;
  BTREE* ptr  = root;
  // Iterate over left child and push to stack (Rep LOOP)
  while(ptr != NULL) {
    STACK.push(ptr);
    ptr = ptr->left;
  }
  while(!STACK.empty()) {
    // Pop element but do not print
    ptr = STACK.top();
    STACK.pop();
    if((ptr->right == NULL) || (ptr->right == prev)) {
      // Print only if right child is NULL or visited
      printf("\t%c", ptr->data);
      prev = ptr;
    } else {
      // Again push same element and move to unvisited right child
      STACK.push(ptr);
      ptr = ptr->right;
      // Iterate over left child and push to stack (Rep LOOP)
      while(ptr != NULL) {
        STACK.push(ptr);
        ptr = ptr->left;
      }
    }
  }
}

// Level order traversal (BFS)
void level_order_traversal(BTREE* root) {
  int level, internal, leaves, counter, previous;
  queue<BTREE*> QUEUE;
  if(root != NULL) {
    // Push root node and NULL
    QUEUE.push(root);
    QUEUE.push(NULL);
    level    = 0;
    previous = 0;
    internal = 0;
    leaves   = 0;
    counter  = 0;
  }
  while(!QUEUE.empty()) {
    // Remove front node from queue
    BTREE* node = QUEUE.front();
    QUEUE.pop();
    // Display parent
    if(node != NULL) {
      counter++;
      printf("\t%c", node->data);
      if((node->left == NULL) && (node->right == NULL)) {
        leaves++;
      } else {
        internal++;
        // Add left node to queue
        if(node->left != NULL) {
          QUEUE.push(node->left);
        }
        // Add right node to queue
        if(node->right != NULL) {
          QUEUE.push(node->right);
        }
      }
    } else {
      // Display level
      printf("\nLevel %d - nodes %d", level, (counter - previous));
      previous = counter;
      printf("\n");
      // Push NULL only when queue is not empty
      if(!QUEUE.empty()) {
        QUEUE.push(NULL);
        level++;
      }
    }
  }
  printf("\nTotal Levels: %d, Nodes: %d, Internal: %d, Leaves: %d",
            level, counter, internal, leaves);
}

// Zigzag Level order traversal
void zigzag_level_traversal(BTREE* root) {
  stack<BTREE*> STACK_CURR;
  stack<BTREE*> STACK_NEXT;
  bool is_leftright = true;
  STACK_CURR.push(root);
  printf("\nZigzag order: ");
  while(!STACK_CURR.empty()) {
    // Pop items (current stack)
    BTREE* ptr = STACK_CURR.top();
    STACK_CURR.pop();
    if(ptr != NULL) {
      printf("\t%c", ptr->data);
      if(is_leftright) {
        // Push child left to right (next stack)
        if(ptr->left) {
          STACK_NEXT.push(ptr->left);
        }
        if(ptr->right) {
          STACK_NEXT.push(ptr->right);
        }
      } else {
        // Push child right to left (next stack)
        if(ptr->right) {
          STACK_NEXT.push(ptr->right);
        }
        if(ptr->left) {
          STACK_NEXT.push(ptr->left);
        }
      }
    }
    // Once current stack is empty swap with next stack
    if(STACK_CURR.empty()) {
      // Indicates end of level
      is_leftright = !is_leftright;
      swap(STACK_CURR, STACK_NEXT);
    }
  } // While loop
}

// Create binary tree from input array
BTREE* create_tree(char array[], int index, int size) {
  BTREE* root = NULL;
  if(index < size) {
    root = create_node(array[index]);
    root->left  = create_tree(array, (2 * index + 1), size);
    root->right = create_tree(array, (2 * index + 2), size);
  }
  return root;
}

// Create binary tree from CLI user input
BTREE* input_tree() {
  BTREE* root = NULL;
  char choice;
  do {
    char value;
    printf("\nEnter value[A-Za-z]: ");
    scanf("%c", &value);
    getchar();
    BTREE* temp = create_node(value);
    if(root == NULL) {
      root = temp;
    } else {
      BTREE* ptr = root;
      while(true) {
        char direction;
        printf("\nLeft or Right of %c: ", ptr->data);
        scanf("%c", &direction);
        getchar();
        if((direction == 'l') || (direction == 'L')) {
          // Left child
          if(ptr->left != NULL) {
            ptr = ptr->left;
          } else {
            ptr->left = temp;
            break;
          }
        } else {
          // Right child
          if(ptr->right != NULL) {
            ptr = ptr->right;
          } else {
            ptr->right = temp;
            break;
          }
        }
      }
    }
    printf("\nDo u want to continue[y/n]: ");
    scanf("%c", &choice);
    getchar();
  } while((choice == 'y') || (choice == 'Y'));
  return root;
}

// Search key in binary tree and return
BTREE* search_key(BTREE* root, const char key) {
  if(root != NULL) {
    // Check if parent matches key
    if(root->data == key) {
      return root;
    }
    // Search for key in left subtree
    if(root->left) {
      // Check if key found in left subtree
      BTREE* temp = search_key(root->left, key);
      if(temp && temp->data == key) {
        return temp;
      }
    }
    // Search for key in right subtree
    if(root->right) {
      // Check if key found in left subtree
      BTREE* temp = search_key(root->right, key);
      if(temp && temp->data == key) {
        return temp;
      }
    }
  }
  return NULL;
}

// Get maximum height of tree
int max_height(BTREE* root) {
  if(root == NULL) {
    return 0;
  }
  // Get maximum height of left or right subtree
  return 1 + MAX(max_height(root->left), max_height(root->right));
}

// Get height of any leaf node
int any_height(BTREE* root) {
  if(root == NULL) {
    return 0;
  }
  return 1 + any_height(root->left);
}

// Get total number of nodes of tree
int node_count(BTREE* root) {
  if(root != NULL) {
    // Count node only if not null
    return 1 + node_count(root->left) + node_count(root->right);
  }
  return 0;
}

// Get total number of leaves
int leaves_count(BTREE* root) {
  if(root != NULL) {
    // Count leaf only if left or right child does not exists
    int count = (root->left || root->right)? 0 : 1;
    return count + leaves_count(root->left) + leaves_count(root->right);
  }
  return 0;
}

// Get total number of internal nodes
int internal_count(BTREE* root) {
  if(root != NULL) {
    // Count node only if left or right child exists
    int count = (root->left || root->right)? 1 : 0;
    return count + internal_count(root->left) + internal_count(root->right);
  }
  return 0;
}

// Check for skewed binary tree
bool is_skewed(BTREE* root) {
  if(root != NULL) {
    if((root->left == NULL) && (root->right == NULL)) {
      // Reached leaf node, return true
      return true;
    } else if((root->left != NULL) && (root->right != NULL)) {
      // Reached internal node with 2 children, return false
      return false;
    } else {
      // Reached internal node with 1 child, recurse further
      return is_skewed(root->left) && is_skewed(root->right);
    }
  }
  return true;
}

// Check for balanced binary tree (height difference < 1)
bool is_balanced(BTREE* root) {
  if(root != NULL) {
    // Get height of left subtree
    int left_height  = max_height(root->left);
    // Get height of right subtree
    int right_height = max_height(root->right);
    // Get absolute height difference of subtrees
    int height_diff  = abs(left_height - right_height);
    // Check if height difference <=1 and subtrees are balanced
    return (height_diff <= 1) &&
            is_balanced(root->left) && is_balanced(root->right);
  }
  return true;
}

// Check for full binary tree
bool is_full(BTREE* root) {
  if(root != NULL) {
    // Check whether leaf or internal node with 2 children
    if((root->left == NULL) && (root->right == NULL)) {
      // Reached leaf node, return true
      return true;
    } else if ((root->left != NULL) && (root->right != NULL)) {
      // Reached internal node with 2 children
      return is_full(root->left) && is_full(root->right);
    }
    else {
      // Reached internal node with 1 children, return false
      return false;
    }
  }
  return true;
}

// Check for complete binary tree
bool is_complete(BTREE* root, int index, int nodes) {
  if(root != NULL) {
    // This check always ensures the tree is left filled
    if(index < nodes) {
      return is_complete(root->left,  (2 * index + 1), nodes) &&
             is_complete(root->right, (2 * index + 2), nodes);
    } else {
      // Number of nodes does not match for incomplete tree
      return false;
    }
  }
  return true;
}

// Check fof perfect binary tree
bool is_perfect(BTREE* root, const int level, const int depth) {
  if(root != NULL) {
    // Check whether all internal nodes have 2 children and
    // All leaves are at same depth (maximum height of tree)
    if((root->left == NULL) && (root->right == NULL)) {
      // Reached leaf node with exact depth, return true
      return ((level + 1) == depth);
    } else if ((root->left != NULL) && (root->right != NULL)) {
      // Reached internal node with 2 children, recurse further
      return is_perfect(root->left,  (level + 1), depth) &&
             is_perfect(root->right, (level + 1), depth);
    }
    else {
      // Reached internal node with 1 children, return false
      return false;
    }
  }
  return true;
}

// Create copy of binary tree
BTREE* copy_tree(BTREE* root) {
  BTREE* copy = NULL;
  if(root != NULL) {
    // Create copy of parent
    copy = create_node(root->data);
    // Recursively copy left subtree
    copy->left  = copy_tree(root->left);
    // Recursively copy right subtree
    copy->right = copy_tree(root->right);
  }
  return copy;
}

// Create mirror image of binary tree
void mirror_tree(BTREE* root) {
  if(root != NULL) {
    // Swap both subtrees
    BTREE* temp = root->left;
    root->left  = root->right;
    root->right = temp;
    // Recursively mirror both subtrees
    mirror_tree(root->left);
    mirror_tree(root->right);
  }
}

// Check if binary trees are equal
bool is_equal(BTREE* root1, BTREE* root2) {
  // Check if both subtrees are not null
  if((root1 != NULL) && (root2 != NULL)) {
    // Check if both parents and subtrees are Equal
    return (root1->data == root2->data) &&
            is_equal(root1->left, root2->left) &&
            is_equal(root1->right, root2->right);
  }
  // Check if both subtrees are null
  return ((root1 == NULL) && (root2 == NULL));
}

// Check if binary trees are equal
bool is_mirror(BTREE* root1, BTREE* root2) {
  // Check if both subtrees are not null
  if((root1 != NULL) && (root2 != NULL)) {
    // Check if both parents are Equal and subtrees are Mirror
    return (root1->data == root2->data) &&
            is_mirror(root1->left, root2->right) &&
            is_mirror(root1->right, root2->left);
  }
  // Check if both subtrees are null
  return ((root1 == NULL) && (root2 == NULL));
}

// Print ancestors of key node
bool print_ancestors(BTREE* root, const char key) {
  if(root != NULL) {
    // Key node found
    if(root->data == key) {
      return true;
    }
    // Print parent only if key is found in either of subtrees
    if(print_ancestors(root->left, key) ||
       print_ancestors(root->right, key)) {
      printf("\t%c", root->data);
      return true;
    }
  }
  return false;
}

// Print path from root to key node
bool find_path(BTREE* root, const char key, vector<char>& path) {
  if(root != NULL) {
    // Insert parent irrespective of whether key exists or not
    path.push_back(root->data);
    // Key node found
    if(root->data == key) {
      return true;
    }
    // Check if key is found in either of subtrees
    if(find_path(root->left, key, path) ||
       find_path(root->right, key, path)) {
      return true;
    }
    // Remove parent because no subtrees contain key
    path.pop_back();
  }
  return false;
}

// Find least common ancestor of two keys
char find_lca(BTREE* root, const char key1, const char key2) {
  char lca = '\0';
  // Find path from root to node1 - O(N)
  vector<char> path1;
  if(!find_path(root, key1, path1)) {
    printf("\nNo path found for %c", key1);
    return lca;
  }
  // Find path from root to node2 - O(N)
  vector<char> path2;
  if(!find_path(root, key2, path2)) {
    printf("\nNo path found for %c", key2);
    return lca;
  }
  int i, j;
  for(i = 0, j = 0; i < path1.size() && j < path2.size(); i++, j++) {
    if(path1[i] != path2[j]) {
      printf("\nLCA found: %c", lca);
      return lca;
    }
    lca = path1[i];
  }
  return lca;
}

// Get distance of path (number of edges) from root to specific node
int path_distance(BTREE* root, const char key, const int depth) {
  if(root != NULL) {
    if(root->data == key) {
      return depth;
    }
    return MAX(path_distance(root->left,  key, depth + 1),
               path_distance(root->right, key, depth + 1));
  }
  return 0;
}

// Measure distance (number of edges) between two specific nodes
// path_distance(Node1) + path_distance(Node2) - 2 * path_distance(LCA)
int node_distance(BTREE* root, const char node1, const char node2) {
  int distance = -1;
  // Get path from root to node1
  vector<char>path1;
  if(!find_path(root, node1, path1)) {
    printf("\nNo path found for %c", node1);
    return distance;
  }
  // Get path from root to node2
  vector<char>path2;
  if(!find_path(root, node2, path2)) {
    printf("\nNo path found for %c", node2);
    return distance;
  }
  // Sum of the distances from root to each of the nodes
  distance = path1.size() + path2.size();
  int i, j;
  for(i = 0, j = 0; i < path1.size() && j < path2.size(); i++, j++) {
    if(path1[i] != path2[j]) {
      return distance;
    }
    // Remove twice counted common lca path distance
    distance = distance - 2;
  }
  return distance;
}

// Print leaves in left to right order (like inorder traversal)
void print_leaves(BTREE* root) {
  if(root != NULL) {
    // Goto leftmost subtree
    print_leaves(root->left);
    // Print leaf node
    if((root->left == NULL) && (root->right == NULL)) {
      printf("\t%c", root->data);
      return;
    }
    // Goto rightmost subtree
    print_leaves(root->right);
  }
}

// Print left boundary (top down manner)
void left_subtree(BTREE* root) {
  if(root != NULL) {
    // Print parent before traversing subtrees
    if(root->left != NULL) {
      // If only left subtree exists, print before recurse further
      printf("\t%c", root->data);
      left_subtree(root->left);
    } else if(root->right != NULL) {
      // If only right subtree exists, print before recurse further
      printf("\t%c", root->data);
      left_subtree(root->right);
    } else {
      // Do nothing for leaf nodes
      return;
    }
  }
}

// Print right boundary (bottom up manner)
void right_subtree(BTREE* root) {
  if(root != NULL) {
    // Print parent after traversing subtrees
    if(root->right != NULL) {
      // If only right subtree exists, print after recurse out
      right_subtree(root->right);
      printf("\t%c", root->data);
    } else if(root->left != NULL) {
    // If only left subtree exists, print after recurse out
      right_subtree(root->left);
      printf("\t%c", root->data);
    } else {
      // Do nothing for leaf nodes
      return;
    }
  }
}

// Boundary traversal (recursive)
void boundary_recursive(BTREE* root) {
  // Left boundary traversal (top-down)
  left_subtree(root);
  // Leavers traversal (left-right)
  print_leaves(root);
  // Right boundary traversal (bottom-up)
  right_subtree(root->right);
}

// Boundary traversal (iterative)
void boundary_iterative(BTREE* root) {
  BTREE* ptr = NULL;
  // Left boundary traversal (top-down)
  list<char> mlist;
  ptr = root;
  while(ptr != NULL) {
    if(ptr->left != NULL) {
      // If only left subtree exists, walk down further
      mlist.push_back(ptr->data);
      ptr = ptr->left;
    } else if(ptr->right != NULL) {
      // If only right subtree exists, walk down further
      mlist.push_back(ptr->data);
      ptr = ptr->right;
    } else {
      // Reached left most leaf node
      ptr = NULL;
    }
  }
  // Leaf traversal using BFS
  queue<BTREE*> QUEUE;
  QUEUE.push(root);
  while(!QUEUE.empty()) {
    // Remove node from queue
    BTREE* node = QUEUE.front();
    QUEUE.pop();
    // Check if internal node or leaf node
    if(node->left || node->right) {
      // Left child exists
      if(node->left != NULL) {
        QUEUE.push(node->left);
      }
      // Right child exists
      if(node->right != NULL) {
        QUEUE.push(node->right);
      }
    } else {
      // Leaf node
      mlist.push_back(node->data);
    }
  }
  // Right boundary traversal (bottom-up)
  list<char> rlist;
  ptr = root->right;
  while(ptr != NULL) {
    if(ptr->right != NULL) {
      // If only right subtree exists, walk down further
      rlist.push_back(ptr->data);
      ptr = ptr->right;
    } else if(ptr->left != NULL) {
      // If only left subtree exists, walk down further
      rlist.push_back(ptr->data);
      ptr = ptr->left;
    } else {
      // Reached right most leaf node
      ptr = NULL;
    }
  }
  // Reverse right list and append to main list
  mlist.insert(mlist.end(), rlist.rbegin(), rlist.rend());
  for(auto itr: mlist) {
    printf("\t%c", itr);
  }
}

// Get diameter of tree (longest max distance path between 2 nodes)
int get_diameter(BTREE* root, int& diameter) {
  if(root == NULL) {
    return 0;
  }
  // Get height of left subtree (left most leaf node)
  int left_height  = get_diameter(root->left, diameter);
  // Get height of right subtree (right most leaf node)
  int right_height = get_diameter(root->right, diameter);
  // Compute total distance between subtree leaf nodes
  int total_distance = 1 + left_height + right_height;
  // Check if total distance is maximum
  diameter = MAX(diameter, total_distance);
  // Returns height of binary tree
  return 1 + MAX(left_height, right_height);
}

// Save tree to file (PreOrder Traversal)
void serialize_file(BTREE* root, FILE* fp) {
  if(root != NULL) {
    // Save parent into file
    fprintf(fp, "%c", root->data);
    // Iterate over children
    serialize_file(root->left, fp);
    serialize_file(root->right, fp);
  } else {
    fprintf(fp, "$");
  }
}

// Consruct tree from file (PreOrder Traversal)
BTREE* deserialize_file(FILE* fp) {
  BTREE* root = NULL;
  char ch;
  if(fscanf(fp, "%c", &ch) != EOF) {
    if(ch == '$') {
      return root;
    }
    root = create_node(ch);
    root->left  = deserialize_file(fp);
    root->right = deserialize_file(fp);
  }
  return root;
}

// Get ancestors of specific target and save all nodes into vector
bool get_ancestors(BTREE* root, BTREE*& target, vector<BTREE*>& ancestors) {
  if(root != NULL) {
    // Insert parent irrespective of whether target exists or not
    ancestors.push_back(root);
    // Key node found
    if(root == target) {
      return true;
    }
    // Check if target is found in either of subtrees
    if(get_ancestors(root->left, target, ancestors) ||
       get_ancestors(root->right, target, ancestors)) {
      return true;
    }
    // Remove parent because no subtrees contain target
    ancestors.pop_back();
  }
  return false;
}

// Get downward children at distance K from root node - O(K)
void get_Kdistance_childs(BTREE* root, const int K, set<char> & result) {
  if((root != NULL) && (K >= 0)){
    if(K == 0) {
      // Set used as multiple insertions for same value is idempotent
      result.insert(root->data);
    }
    get_Kdistance_childs(root->left, (K - 1), result);
    get_Kdistance_childs(root->right, (K - 1), result);
  }
}

// Get nodes at distance K from target - O(N)
void get_Kdistance_nodes(BTREE* root, BTREE* target, const int K) {
  // Get all ancestors upto target and save it in vector
  vector<BTREE*> ancestors;
  bool found = get_ancestors(root, target, ancestors);
  if(found == false) {
    printf("\nTarget not found");
    return;
  }

  int count = K;      // Decrement K at every iteration
  set<char> result;   // Nodes at distance K from target
  // Resultant vector (as depicted below)
  // Forefathers -> GrandParent -> Parent -> Current (Target)
  // Traverse vector in reverse way and decrement K value
  for(auto itr = ancestors.rbegin(); (count >= 0) && (itr != ancestors.rend()); itr++) {
    BTREE* node = *itr;
    // Find nodes at distance K from Current (Target)
    // Find nodes at distance K-1 from Parent
    // Find nodes at distance K-2 from GrandParent ...
    // At distance 0 we get ancestor at distance K from Current (Target)
    get_Kdistance_childs(node, count, result);
    count --;
  }
  // Remove target node from the result
  result.erase(target->data);
  // Display all nodes at distance K from target
  printf("\n%d distance nodes from %c: ", K, target->data);
  for(auto itr: result) {
    printf("\t%c", itr);
  }
}

int main() {
  char arr[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
  int size   = sizeof(arr)/sizeof(arr[0]);
  BTREE* root = create_tree(arr, 0, size);
  // print_tree(root, 0);

  // printf("\nTotal number of nodes: %d", node_count(root));
  // printf("\nTotal number of leaves: %d", leaves_count(root));
  // printf("\nTotal number of internal: %d", internal_count(root));
  // printf("\nHeight of binary tree: %d", max_height(root));
  // printf("\nHeight balanced: %s", BOOL(is_balanced(root)));

  BTREE* node1 = search_key(root, 'E');
  node1->left = create_node('X');
  BTREE* node2 = search_key(root, 'F');
  node2->right = create_node('Y');
  BTREE* node3 = search_key(root, 'G');
  node3->left = create_node('Z');
  print_tree(root, 0);

  BTREE* target = search_key(root, 'E');
  get_Kdistance_nodes(root, target, 2);

  // boundary_recursive(root);
  // zigzag_level_traversal(root);

  // printf("\nPreorder Main:\t");
  // preorder_traversal(root);
  // FILE* fp    = NULL;
  // BTREE* copy = NULL;
  // fp = fopen("/tmp/tree.log", "w");
  // if(fp != NULL) {
  //   serialize_file(root, fp);
  // }
  // fclose(fp);
  // fp = fopen("/tmp/tree.log", "r");
  // if(fp != NULL) {
  //   copy = deserialize_file(fp);
  // }
  // fclose(fp);
  // printf("\nPreorder Copy:\t");
  // preorder_traversal(copy);
  // erase_tree(copy);
  // printf("\nPostorder Recursive:\t");
  // postorder_traversal(root);
  // printf("\nPostorder Iterative:\t");
  // postorder_walkover(root);
  // int diameter = 0;
  // get_diameter(root, diameter);
  // printf("\nDiameter of binary tree: %d", diameter);

  // print_tree(root, 0);
  // boundary_iterative(root);
  //
  // k1 = 'B';
  // k2 = 'I';
  // printf("\nDistance %c and %c: %d", k1, k2, node_distance(root, k1, k2));

  // const char key = 'X';
  // printf("\nAncestors of %c :", key);
  // if(!print_ancestors(root, key)) {
  //   printf("\nKey %c not found.", key);
  // }

  // const char key = 'F';
  // vector<char> path;
  // if(find_path(root, key, path)) {
  //   printf("\nPath :");
  //   for(int index = 0; index < path.size(); index++) {
  //     printf("\t%c", path[index]);
  //   }
  // } else {
  //   printf("\nKey %c not found.", key);
  // }

  // printf("\nNode distance: %d", node_distance(root, 'B', 0));
  // printf("\nFull binary tree: %s", BOOL(is_full(root)));
  // int count = node_count(root);
  // printf("\nComplete binary tree: %s", BOOL(is_complete(root, 0, count)));
  // int depth = any_height(root);
  // printf("\nPerfect binary tree: %s", BOOL(is_perfect(root, 0, depth)));
  // printf("\nSkewed binary tree: %s", BOOL(is_skewed(root)));

  // printf("\nCopy:");
  // BTREE* copy = copy_tree(root);
  // level_order_traversal(copy);
  // printf("\nEqual binary trees: %s", BOOL(is_equal(root, copy)));
  // printf("\nMirror binary trees: %s", BOOL(is_mirror(root, copy)));
  // mirror_tree(copy);
  // printf("\nMirror:");
  // level_order_traversal(copy);
  // printf("\nEqual binary trees: %s", BOOL(is_equal(root, copy)));
  // printf("\nMirror binary trees: %s", BOOL(is_mirror(root, copy)));
  // erase_tree(copy);

  // BTREE* head = create_node('W');
  // head->left = create_node('X');
  // head->left->right = create_node('Y');
  // head->left->right->left = create_node('Z');
  // printf("\nSkewed binary tree: %s", BOOL(is_skewed(head)));
  // erase_tree(head);
  // BTREE* node = search_key(root, 'H');
  // node->left = create_node('I');
  // printf("\nHeight balanced: %s", BOOL(is_balanced(root)));

  // level_order_traversal(root);
  // print_tree(root, 0);
  // printf("\nHeight of tree: %d", max_height(root));

  // const char key = 'F';
  // BTREE* node = search_key(root, key);
  // if(node != NULL) {
  //   printf("\nKey %c found in tree", key);
  // } else {
  //   printf("\nKey %c not found in tree", key);
  // }
  // inorder_traversal(root);

  erase_tree(root);
  return 0;
}
