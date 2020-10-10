/**********************************************************
  Least Recently Used (LRU) Cache using DS
  Ordered Map        : Page(Key), Node*(Page) pairs
  Double Linked List : List of Nodes(Pages) present in cache
                       Front = MRU Node, Back = LRU Node
***********************************************************/
#include <memory>
#include <unordered_map>
#include <cstdlib>
#include <cstdio>
#include "logging.h"

#define LOG LOG_DISABLE

using namespace std;

// Structure for page information
struct Node {
  int page;
  struct Node* next;
  struct Node* prev;
};
typedef struct Node NODE;

// Class implementing LRU cache
class LruCache {
private:
  // Mappings of Page Number and Page Info (NODE*)
  unordered_map<int, NODE*> CACHE;

  // Page Info (most recently used) for newly added page
  NODE* front;

  // Page Info (least recently used) for next to be removed page
  NODE* back;

  // Maximum number of pages stored in cache
  int   capacity;

public:
  // Constructor
  LruCache(const int count) {
    front    = NULL;
    back     = NULL;
    capacity = count;
  }

  // Check if cache exceeds capacity
  bool isCacheFull() {
    return (CACHE.size() >= capacity);
  }

  // Check if cache is empty
  bool isCacheEmpty() {
    return (CACHE.size() == 0);
  }

  // Display all active pages in cache
  void displayPages() {
    printf("\nPages: ");
    for(auto itr: CACHE) {
      printf("\t%d", itr.first);
    }
  }

  // Create Page Info
  NODE* createNode(const int page) {
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp->page = page;
    return temp;
  }

  // Delete Page Info (from back)
  bool deleteNode(NODE* & info) {
    bool retval = false;
    if(info == NULL) {
      DINFO(LOG,"Invalid page cannot be deleted");
    } else if (back != info) {
      DINFO(LOG,"Frequent page %d cannot be deleted", info->page);
    } else {
      if(back == front) {
        DINFO(LOG,"Deleted last page %d", info->page);
        front = NULL;
        back = NULL;
      } else {
        DINFO(LOG,"Deleted least frequent page %d", info->page);
        back->prev->next = back->next;
        back = back->prev;
      }
      free(info);
      info = NULL;
      retval = true;
    }
    return retval;
  }

  // Insert Page Info (at front)
  bool insertNode(NODE* & info) {
    bool retval = false;
    if(info == NULL) {
      DINFO(LOG,"Invalid page cannot be inserted");
    } else if(front == NULL) {
      front = info;
      back  = info;
      retval = true;
      DINFO(LOG,"Inserted first page %d at front", info->page);
    } else {
      info->next = front;
      front->prev = info;
      info->prev = NULL;
      front = info;
      retval = true;
      DINFO(LOG,"Inserted new page %d at front", info->page);
    }
    return retval;
  }

  // Move specific Page Info to front
  void moveToFront(NODE* & info) {
    if(front == info) {
      DINFO(LOG,"Most recent page %d is already at front", info->page);
    } else if(back == info) {
      back = back->prev;
      back->next = NULL;
      info->prev = NULL;
      info->next = front;
      front->prev = info;
      front = info;
      DINFO(LOG,"Most recent page %d moved from back to front", info->page);
    } else {
      info->next->prev = info->prev;
      info->prev->next = info->next;
      info->next = front;
      front->prev = info;
      info->prev = NULL;
      front = info;
      DINFO(LOG,"Most recent page %d moved to front", info->page);
    }
  }

  // Display active Page Info from cache
  void displayNodes() {
    printf("\nCache Entries: ");
    for(NODE* ptr = front; ptr != NULL; ptr = ptr->next) {
      printf("\t%d", ptr->page);
    } //  End of for loop
    printf("\nPage Refresh: ");
    for(NODE* ptr = front; ptr != NULL; ptr = ptr->next) {
      if((ptr == front) && (ptr == back)) {
        printf("\tFB");
      } else if((ptr == front) || (ptr == back)) {
        printf("\t%s", (ptr == front) ? "F" : "B");
      } else {
        printf("\t ");
      }
    } //  End of for loop
  }

  // Remove all Page Info from cache
  void eraseNodes() {
    // Remove previous nodes
    for(NODE* ptr = front; (ptr != NULL); ptr = ptr->next) {
      printf("\nVisited: %d", ptr->page);
      NODE* prev = ptr->prev;
      if(prev != NULL) {
        DINFO(LOG,"Deleted prev page %d", prev->page);
        free(prev);
        ptr->prev = NULL;
      }
    } // End of for loop
    //  Remove last node
    if(back != NULL) {
      DINFO(LOG,"Deleted last page %d", back->page);
      free(back);
    }
    back = NULL;
    front = NULL;
  }

  // Put Page Info into cache and create new mapping
  void putPage(const int new_page) {
    if(isCacheFull()) {
      printf("\nCache full, replace to insert new page %d", new_page);
      // Find existing PageInfo from cache
      const int old_page = (back!=NULL) ? back->page : -1;
      auto entry = CACHE.find(old_page);
      if(entry == CACHE.end()) {
        printf("\nLeast frequent page %d does not exist", old_page);
      } else {
        // Remove LRU PageInfo from cache
        if(deleteNode(entry->second)) {
          CACHE.erase(entry);
          printf("\nLeast frequent page %d removed from cache", old_page);
        }
      }
    }
    // Add MRU PageInfo into cache
    NODE* info = createNode(new_page);
    if(insertNode(info)) {
      printf("\nMost frequent page %d added to cache", new_page);
      CACHE[new_page] = info;
    }
  }

  // Get Page Info into cache and update mapping
  void getPage(const int page) {
    // Find existing PageInfo from cache
    auto entry = CACHE.find(page);
    if(entry == CACHE.end()) {
      // For Cache Miss, remove LRU page and insert new page
      printf("\nCache Miss for missing page %d", page);
      putPage(page);
    } else {
      // For Cache Hit, move current page to front (MRU)
      printf("\nCache Hit for existing page %d", page);
      moveToFront(entry->second);
    }
  }

  // Display cache and mappings
  void displayCache() {
    displayPages();
    displayNodes();
  }

  // Destructor
  ~LruCache() {
    // Delete all node entries
    eraseNodes();
    // Delete all cache mappings
    DINFO(LOG,"Deleted all mappings");
    CACHE.clear();
  }

};

int main() {
  LruCache cache(3);
  cache.getPage(1);
  cache.displayCache();
  cache.getPage(2);
  cache.displayCache();
  cache.getPage(3);
  cache.displayCache();
  cache.getPage(4);
  cache.displayCache();
  cache.getPage(1);
  cache.displayCache();
  cache.getPage(3);
  cache.displayCache();
  cache.getPage(2);
  cache.displayCache();
  return 0;
}
