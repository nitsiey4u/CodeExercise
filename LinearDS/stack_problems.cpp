#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
  stack<char> STACK;
  const char* data = "[(])";
  for(int index = 0; index < strlen(data); index++) {
    const char cur_value = data[index];
    if ((cur_value == '[') || (cur_value == '(') || (cur_value == '{')) {
      STACK.push(cur_value);
      continue;
    }
    if (STACK.empty()) {
      printf("\nNot balanced as stack is empty");
      return -1;
    }
    const char pop_value = STACK.top();
    STACK.pop();
    switch(cur_value) {
      case ']' :  if(pop_value != '[') {
                    cout << "\nNot balanced Current: " << cur_value
                         << " Popped: " << pop_value;
                    return -1;
                  }
                  break;
      case ')' : if(pop_value != '(') {
                    cout << "\nNot balanced for " << cur_value
                         << " Popped: " << pop_value;
                    return -1;
                  }
                  break;
      case '}' : if(pop_value != '{') {
                    cout << "\nNot balanced for " << cur_value
                         << " Popped: " << pop_value;
                    return -1;
                  }
                  break;
    }
  }
  cout << "Balanced";
	return 0;
}


// stack<int> stk;
// int index;
// printf("\nSize: %d", (int) stk.size());
// for(index = 1; index < 5; index++) {
//   stk.push(index);
//   printf("\nAdded %d", stk.top());
// }
// printf("\nSize: %d", (int)stk.size());
//
// while(!stk.empty()) {
//   printf("\nRemoving %d", stk.top());
//   stk.pop();
// }
// printf("\nSize: %d", (int) stk.size());
