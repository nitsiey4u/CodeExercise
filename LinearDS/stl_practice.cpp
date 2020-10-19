#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool is_digit(char c) {
    return isdigit(c);
}

template <typename Q>
void print_queue(Q que) {
  cout << "\nQueue: ";
  while(!que.empty()) {
    cout << "\t" << que.front();
    que.pop();
  }
}

template <typename S>
void print_stack(S stk) {
  cout << "\nStack: ";
  while(!stk.empty()) {
    cout << "\n\t" << stk.top();
    stk.pop();
  }
}

template <typename L>
void print_list(L dll) {
  cout << "\nList: ";
  for(auto itr = dll.rbegin(); itr != dll.rend(); itr++) {
    cout <<"\t" << *itr;
  }
}

template <typename M>
void print_unordered_map(M map) {
  for(auto itr = map.begin(); itr != map.end(); itr++) {
    cout << "\t" << itr->first() << "<-->" << itr->second();
  }
}

struct range {
  int low;
  int high;
};
typedef struct range RANGE;

struct node {
  int value;
  struct node* next;
};
typedef struct node NODE;

int comparator(const void *a, const void *b) {
  //return *(int*)a - *(int*) b;
  return *(int*)b - *(int*) a;
}

void InitRange(string buffer, RANGE* result) {
  const int index = buffer.find("-");
  string lower = buffer.substr(0, index);
  result->low = atoi(lower.substr(1).c_str());
  if(lower[0] == '(') {
    result->low ++;
  }
  //cout << "\nLower: " << result->low;

  string upper = buffer.substr(index + 1);
  result->high = atoi(upper.substr(0, upper.length()-1).c_str());
  if(upper[upper.length()-1] == ')') {
    result->high --;
  }
  //cout << "\nUpper: " << result->high;
}

template <typename R>
bool binary_search(R range_vector, int target) {
  int low = 0;
  int high = range_vector.size() - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if((range_vector[mid].low <= target) &&
       (target <= range_vector[mid].high)) {
      cout << "\nTarget " << target << " within range of "
           << range_vector[mid].low << "-"
           << range_vector[mid].high;
      return true;
    } else if(target < range_vector[mid].low)
      high = mid - 1;
    else {
      low = mid + 1;
    }
  }
  return false;
}


int main(int argc, char* argv[]) {
  // Queue Operations
  cout << "\n------- Queue Operations ---------\n";
  queue<int> QUEUE;
  for(int index = 1; index < 4; index++) {
    cout << "\nEnqueued at rear: " << index;
    QUEUE.push(index);
  }
  print_queue(QUEUE);
  cout << "\nQueue Size: " << QUEUE.size();
  for(int counter = 1; counter < 3; counter++) {
    cout << "\nDequeued from front: " << QUEUE.front();
    QUEUE.pop();
  }
  print_queue(QUEUE);
  cout << "\nQueue Size: " << QUEUE.size();

  // Stack Operations
  cout << "\n------- Stack Operations ---------\n";
  stack<int> STACK;
  for(int index = 11; index <= 44; index = index + 11) {
    cout << "\nPushed value at top: " << index;
    STACK.push(index);
  }
  print_stack(STACK);
  cout << "\nStack Size: " << STACK.size();
  for(int counter = 1; counter < 3; counter++) {
    cout << "\nPopped value from top: " << STACK.top();
    STACK.pop();
  }
  print_stack(STACK);
  cout << "\nStack Size: " << STACK.size();

  // Vector Operations
  cout << "\n------- Vector Operations ---------\n";
  vector<int> vec1(5), vec2;
  vector<int> vec3 = {7, 5, 6};
  vector<int>::iterator itr;
  vector<RANGE> range_values;

  for(int index = 0; index < vec1.size(); index++) {
    vec1[index] = (index + 1) * 11;
  }
  cout << "\nVector 1: ";
  for(int index = 0; index < vec1.size(); index++) {
    cout <<"\t" << vec1[index];
  }
  for(int index = 1; index < 4; index++) {
    vec2.push_back(index);
  }
  cout << "\nVector 2: ";
  for(itr = vec2.begin(); itr != vec2.end(); itr++) {
    cout <<"\t" << *itr;
  }
  cout << "\nVector 3: ";
  for(int index = 0; index < vec3.size(); index++) {
    cout <<"\t" << vec3.at(index);
  }

  char input[] = "[4-5],(8-15],[17-20]";
  cout << "\nInput: " << input;
  char* ptr = strtok(input, ",");
  while(ptr != NULL) {
    RANGE range;
    InitRange(string(ptr), &range);
    range_values.push_back(range);
    ptr = strtok(NULL, ",");
  }

  for(int index = 0; index < range_values.size(); index++) {
    cout << "\nRange Index: " << index + 1;
    cout << "\nLow: " << range_values[index].low;
    cout << "\nHigh: " << range_values[index].high;
  }
  binary_search(range_values, 18);

  int arr[] = {3, 7, 2, 1, 9};
  int count = sizeof(arr)/sizeof(arr[0]);
  cout << "\nInput: ";
  for(int index = 0; index < count; index++) {
    cout << "\t" << arr[index];
  }
  qsort(arr, count, sizeof(int), comparator);
  cout << "\nQSORT Output: ";
  for(int index = 0; index < count; index++) {
    cout << "\t" << arr[index];
  }

  // List Operations
  cout << "\n------- List Operations ---------\n";
  list<int> dll;
  for(int index = 1; index < 11; index = index + 2) {
    dll.push_back(index);
  }
  print_list(dll);
  dll.push_front(2);
  print_list(dll);
  dll.remove(3);
  print_list(dll);
  dll.push_front(4);
  print_list(dll);
  dll.remove(5);
  print_list(dll);
  dll.push_front(6);
  print_list(dll);
  dll.sort();
  print_list(dll);

  cout << "\n------- Unordered Map ---------\n";
  unordered_map<string, int> umap;
  umap.emplace("Nitin", 1);
  umap.emplace("Manna", 2);

  for(auto itr : umap) {
    cout << "\n" << itr.first << "<---->" << itr.second;
  }
  cout << "\nKeyval: " << umap["Nitin"];


  cout << "\n------- SET Operations ---------\n";
  set<int> set1;
  set<int> set2;
  for(int index = 1; index <= 10; index++) {
    set1.insert(index);
    if(index % 2 == 0) {
      set2.insert(index);
    }
  }

  printf("\nSet1: ");
  for(auto itr = set1.begin(); itr != set1.end(); ++itr) {
    int item = *itr;
    printf("\t%d", item);
  }
  printf("\nSet2: ");
  for(auto itr = set2.begin(); itr != set2.end(); ++itr) {
    int item = *itr;
    printf("\t%d", item);
  }
  // includes, equals are std specific
  if(includes(set1.begin(), set1.end(), set2.begin(), set2.end())) {
    printf("\nIs Set");
  }

  cout << "\n------- MAX Heap ---------\n";
  priority_queue<int> MAX_HEAP;
  MAX_HEAP.push(3);
  MAX_HEAP.push(10);
  MAX_HEAP.push(2);
  MAX_HEAP.push(12);
  MAX_HEAP.push(1);
  MAX_HEAP.push(4);
  printf("\nMax Element: %d", MAX_HEAP.top());
  MAX_HEAP.pop();
  printf("\nMax Element: %d", MAX_HEAP.top());

  // std::greater gives larger value
  priority_queue <int, vector<int>, greater<int>> MIN_HEAP;
  MIN_HEAP.push(3);
  MIN_HEAP.push(10);
  MIN_HEAP.push(2);
  MIN_HEAP.push(12);
  MIN_HEAP.push(1);
  MIN_HEAP.push(4);
  printf("\nMin Element: %d", MIN_HEAP.top());
  MIN_HEAP.pop();
  printf("\nMin Element: %d", MIN_HEAP.top());

  string str("1234");
  int val = std::count_if(str.begin(), str.end(), is_digit);

  printf("\nVal: %d", val);
  return 0;
}
