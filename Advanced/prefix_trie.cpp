/**********************************************************
  Dictionary of words, record of phone numbers using DS
  Prefix Trie : N-Ary Tree for storing word/phone info
***********************************************************/
#include "stdio.h"
#include "stdlib.h"
#include "limits.h"
#include <string>

#define RANGE_MAX 26
#define BOOL(X)   ((X)?"True":"False")
using namespace std;

// Definition of Trie Node
struct Trie{
  bool         isEndofWord;
  struct Trie* children[RANGE_MAX];
};
typedef struct Trie TRIE;

// Create Trie Node
TRIE* create_node() {
  TRIE* temp = (TRIE*)malloc(sizeof(TRIE));
  for(int index = 0; index < RANGE_MAX; index++) {
    temp->children[index] = NULL;
  }
  temp->isEndofWord = false;
  return temp;
}

// Erase entire trie - O(N)
void erase_trie(TRIE* root) {
  if(root != NULL) {
    for(int index = 0; index < RANGE_MAX; index++) {
      if(root->children[index] != NULL) {
        //printf("\nErasing: %c", 'a' + index);
        erase_trie(root->children[index]);
      }
    }
    free(root);
    root = NULL;
  }
}

// Check if tree has no children
bool no_children(TRIE* root) {
  if(root != NULL) {
    for(int index = 0; index < RANGE_MAX; index++) {
      if(root->children[index] != NULL) {
        return false;
      }
    }
  }
  return true;
}

// Insert key into Trie - O(K)
void insert_key(TRIE* root, string key) {
  TRIE* ptr = root;
  for(int index = 0; index < key.size(); index++) {
    int position = key[index] - 'a';
    if(ptr->children[position] == NULL) {
      ptr->children[position] = create_node();
    }
    ptr = ptr->children[position];
  }
  ptr->isEndofWord = true;
  printf("\nInserted key: %s", key.c_str());
}

// Search key from Trie - O(K)
bool search_key(TRIE* root, string key) {
  TRIE* ptr = root;
  for(int index = 0; (ptr != NULL) && index < key.size(); index++) {
    int position = key[index] - 'a';
    ptr = ptr->children[position];
  }
  return(ptr && ptr->isEndofWord);
}

// Delete key from Trie - O(K)
TRIE* delete_key(TRIE* root, string key, int depth = 0) {
  if(root != NULL) {
    // Reached end of word
    if(depth == key.size()) {
      // If end of word mark it as removed
      if(root->isEndofWord) {
        root->isEndofWord = false;
      }
      // Delete only if other children does not exists - REP(LOOP)
      if(no_children(root)) {
        free(root);
        root = NULL;
        return root;
      }
    }

    // Recurse over children
    int position = key[depth] - 'a';
    root->children[position] = delete_key(root->children[position], key, (depth + 1));

    // Delete only if other children does not exists - REP(LOOP)
    // Do not affect other prefixes
    if(no_children(root) && (root->isEndofWord == false)) {
      free(root);
      root = NULL;
    }
  }
  return root;
}

int main() {
  // Insert keys
  string insert[] = {
  "cat", "the", "a", "there", "answer", "any", "by", "bye", "their", "hero", "heroplane" };
  int size1 = sizeof(insert)/sizeof(insert[0]);
  TRIE* root = create_node();
  // Insert keys
  for(int index = 0; index < size1; index++) {
    insert_key(root, insert[index]);
  }

  // Delete keys
  string remove[] = {
    "heroplane", "cat", "their", "a", "bye"
  };
  int size3 = sizeof(remove)/sizeof(remove[0]);
  for(int index = 0; index < size3; index++) {
    // Delete key
    delete_key(root, remove[index]);
    printf("\nKey '%s' exists: %s", remove[index].c_str(),
           BOOL(search_key(root, remove[index])));
  }

  // Search keys
  string search[] = {
    "answer", "a", "b", "bye", "th", "there", "hero", "heroplane"
  };
  int size2 = sizeof(search)/sizeof(search[0]);
  for(int index = 0; index < size2; index++) {
    printf("\nKey '%s' exists: %s", search[index].c_str(),
           BOOL(search_key(root, search[index])));
  }

  // Erase trie
  erase_trie(root);
  return 0;
}
