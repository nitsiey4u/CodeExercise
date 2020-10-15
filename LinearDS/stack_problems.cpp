#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <string>
#include <cctype>
#include <unordered_map>
#include "logging.h"

#define LOG LOG_DISABLE

using namespace std;

enum precedence_t {
  EQUAL = 0,
  LOW   = -2,
  HIGH  = +2,
};
typedef enum precedence_t PRC;

enum association_t {
  LTR = 0,
  RTL = 1,
};
typedef enum association_t ASC;

int get_precedence(const char op) {
  int retval;
  switch(op) {
    case '(':
    case ')': retval = 4; break;
    case '^': retval = 3; break;
    case '*':
    case '/': retval = 2; break;
    case '+':
    case '-': retval = 1; break;
    default:  retval = 0;
  }
  return retval;
}

int get_association(const char op) {
  return (op == '^') ? RTL : LTR;
}

int compare_operators(const char op1, const char op2) {
  int prec1  = get_precedence(op1);
  int prec2  = get_precedence(op2);
  if(prec1 > prec2) {
    return HIGH;
  } else if (prec1 < prec2) {
    return LOW;
  } else {
    return EQUAL;
  }
  return -1;
}

bool is_opening(const char op) {
  return ((op == '(') || (op == '{') || (op == '['));
}

bool is_closing(const char op) {
  return ((op == ')') || (op == '}') || (op == ']'));
}

// Convert infix expression to postfix
string infix_to_postfix(const string infix) {
  stack<char> STACK;
  string postfix;
  for(int index = 0; index < infix.length(); index++) {
    bool flag = true;
    while(flag) {
      const char op  = infix[index];
      if(isalnum(op)) {               // Handle operands
        // Print all operands
        postfix.push_back(op);
        flag = false;
      } else if(STACK.empty() ||      // Handle stack empty
                STACK.top() == '(') {
        // Stack is empty or Top is ( push operator onto stack
        STACK.push(op);
        flag = false;
      } else if(is_opening(op)) {     // Handle opening bracket
        // Put any of the left opening brackets onto stack
        STACK.push(op);
        flag = false;
      } else if(is_closing(op)) {     // Handle closing bracket
        // Do not put the right closing brackets onto stack
        while(!is_opening(STACK.top())) {
          // Pop all operators from stack until left opening is found
          postfix.push_back(STACK.top());
          STACK.pop();
        }
        // Left opening bracket found
        if(is_opening(STACK.top())) {
          STACK.pop();
        }
        flag = false;
      } else {                        // Handle operators
        int precedence = compare_operators(op, STACK.top());
        if(precedence == HIGH) {        // Higher precedence
          // Push higher precedence operator onto stack
          STACK.push(op);
          flag = false;
        } else if(precedence == LOW) {  // Lower precedence
          // Pop lower precedence operator from stack
          postfix.push_back(STACK.top());
          STACK.pop();
        } else {                        // Equal precedence
          // For equal precedence operator compare association
          int association = get_association(op);
          if(op == RTL) {
            // Push operator with Right-Left association
            STACK.push(op);
            flag = false;
          } else {
            // Pop from stack for operator with Left-Right association
            postfix.push_back(STACK.top());
            STACK.pop();
          }
        }
      } // End of operator handling
    } // End of inner while
  } // End of outer for loop

  // Push all operators from stack
  while(!STACK.empty()) {
    postfix.push_back(STACK.top());
    STACK.pop();
  }
  // Display result
  cout << "\nInfix:\t" << infix;
  cout << "\nPostfix:\t" << postfix;
  return postfix;
}

// Convert infix expression to prefix
string infix_to_prefix(const string infix) {
  stack<char> STACK;
  string prefix;
  // Traverse string in reverse way
  for(int index = (infix.length() - 1); index >= 0; index--) {
    bool flag = true;
    const char op = infix[index];
    while(flag) {
      if(isalnum(op)) {             // Handle operands
        // Print operands directly
        prefix.push_back(op);
        flag = false;
      } else if (STACK.empty() ||   // Handle stack empty
                 is_closing(STACK.top())) {
        // If stack empty or top is closing bracket push operator
        STACK.push(op);
        flag = false;
      } else if(is_closing(op)) {   // Handle Closing Bracket
        // Push closing right bracket directly onto stack
        STACK.push(op);
        flag = false;
      } else if(is_opening(op)) {   // Handle Opening Bracket
        // Do not push opening left bracket onto stack
        while(!is_closing(STACK.top())) {
          // Pop all operators of stack until closing right bracket
          prefix.push_back(STACK.top());
          STACK.pop();
        }
        if(is_closing(STACK.top())) {
          // Pop closing right bracket
          STACK.pop();
        }
        flag = false;
      } else {                          // Handle Operators
        // Compare precedence of operator with Stack Top
        int precedence = compare_operators(op, STACK.top());
        if(precedence == HIGH) {        // High precedence operator
          // Push higher precedence operator onto stack
          STACK.push(op);
          flag = false;
        } else if(precedence == LOW) {  // Low precedence operator
          // Pop low precedence operator from stack
          prefix.push_back(STACK.top());
          STACK.pop();
        } else {                        // Equal precedence operator
          // Get association of current operator
          int association = get_association(op);
          if(association == LTR) {
            // Push operator onto stack with Left-Right association
            STACK.push(op);
            flag = false;
          } else {
            // Pop operator from stack with Right-Left association
            prefix.push_back(STACK.top());
            STACK.pop();
          }
        }
      } // Handle operators
    } // End of inner while loop
  } // End of outer for loop

  // While stack is not empty
  while(!STACK.empty()) {
    // Pop all operators of stack
    prefix.push_back(STACK.top());
    STACK.pop();
  }
  // Reverse prefix string
  int length = prefix.length();
  for (int index = 0; index < length / 2; index++) {
    swap(prefix[index], prefix[length - index - 1]);
  }
  // Display result
  cout << "\nInfix:\t" << infix;
  cout << "\nPrefix:\t" << prefix;
  return prefix;
}



template <typename T>
int get_constants(const string values, T & CONST) {
 const char sep = ',';
 int start = 0;
 int length = values.length() - 1;
 int index = values.find(sep);
 while(index != string::npos) {
   string pair = values.substr(start, (index - start));
   // Process pair
   int equal = pair.find('=');
   const string key = pair.substr(0, equal);
   const string val = pair.substr(equal+1);
   DINFO(LOG,"Key: %s, Val: %s", key.c_str(), val.c_str());
   CONST[key.at(0)] = stoi(val);
   start = index + 1;
   index = values.find(sep, start);
   if((start < length) && (index == string::npos)) {
     index = length + 1;
   }
 }
 return CONST.size();
}

int operand_arithmetic(const int op1, const int op2, const char opr) {
  int retval = 0;
  switch(opr) {
    case '-' : retval = op1 - op2; break;
    case '+' : retval = op1 + op2; break;
    case '*' : retval = op1 * op2; break;
    case '/' : retval = op1 / op2; break;
    case '^' : retval = pow(op1, op2); break;
    default  : DINFO(LOG,"Unsupported %c", opr);
  }
  return retval;
}

int evaluate_postfix(const string expr, const string cval, const int size) {
  stack<int> STACK;
  unordered_map<char, int> CONST;
  // Process constant values
  int count = get_constants(cval, CONST);
  if(count != size) {
    DINFO(LOG,"Errror processing constants: %s", cval.c_str());
    return -1;
  }
  // Traverse through postfix expression (Left-Right)
  for(int index = 0; index < expr.length(); index++) {
    const char key = expr[index];
    if(isalnum(key)) {
      // If character is operand, get its constant value
      if(CONST.find(key) != CONST.end()) {
        // Ensure found key value is pushed to stack
        int val = CONST[key];
        DINFO(LOG,"Pushed operand: %d", val);
        STACK.push(val);
      }
    } else {
      // Is character is operator, perform operands arithmetic
      if(STACK.size() >= 2) {
        // Pop operand 2
        int op2 = STACK.top();
        STACK.pop();
        DINFO(LOG,"Popped OP2: %d", op2);
        // Pop operand 1
        int op1 = STACK.top();
        STACK.pop();
        DINFO(LOG,"Popped OP1: %d", op1);
        // Push result of arithmetic operation
        int val = operand_arithmetic(op1, op2, key);
        DINFO(LOG,"Pushed result: %d", val);
        STACK.push(val);
      }
    }
  }
  // Return top of stack
  return STACK.top();
}

int evaluate_prefix(const string expr, const string cval, const int size) {
  stack<int> STACK;
  unordered_map<char, int> CONST;
  // Process constant values
  int count = get_constants(cval, CONST);
  if(count != size) {
    DINFO(LOG,"Errror processing constants: %s", cval.c_str());
    return -1;
  }
  // Traverse through postfix expression (Right-Left)
  for(int index = (expr.length() - 1); index >= 0; index--) {
    const char key = expr[index];
    if(isalnum(key)) {
      // If character is operand, get its constant value
      if(CONST.find(key) != CONST.end()) {
        // Ensure found key value is pushed to stack
        int val = CONST[key];
        DINFO(LOG,"Pushed operand: %d", val);
        STACK.push(val);
      }
    } else {
      // Is character is operator, perform operands arithmetic
      if(STACK.size() >= 2) {
        // Pop operand 2
        int op1 = STACK.top();
        STACK.pop();
        DINFO(LOG,"Popped OP1: %d", op1);
        // Pop operand 1
        int op2 = STACK.top();
        STACK.pop();
        DINFO(LOG,"Popped OP2: %d", op2);
        // Push result of arithmetic operation
        int val = operand_arithmetic(op1, op2, key);
        DINFO(LOG,"Pushed result: %d", val);
        STACK.push(val);
      }
    }
  }
  // Return top of stack
  return STACK.top();
}

bool balance_parenthesis(const char* data) {
  stack<char> STACK;
  bool retval = false;
  for(int index = 0; index < strlen(data); index++) {
    const char cur_value = data[index];
    // Push opening bracket onto stack
    if(is_opening(cur_value)) {
      STACK.push(cur_value);
      continue;
    }
    // Closing bracket found but stack empty
    if (STACK.empty()) {
      DINFO(LOG,"Not balanced as stack is empty");
      return false;
    }
    // Verify value on stack top
    const char pop_value = STACK.top();
    STACK.pop();
    switch(cur_value) {
      case ']' :  if(pop_value != '[') {
                    cout << "\nNot balanced Current: " << cur_value
                         << " Popped: " << pop_value;
                    return false;
                  }
                  break;
      case ')' : if(pop_value != '(') {
                    cout << "\nNot balanced for " << cur_value
                         << " Popped: " << pop_value;
                    return false;
                  }
                  break;
      case '}' : if(pop_value != '{') {
                    cout << "\nNot balanced for " << cur_value
                         << " Popped: " << pop_value;
                    return false;
                  }
                  break;
    }
  }
  return STACK.empty();
}

int main(int argc, char* argv[]) {
  // const char* data = "[()]{}";
  // bool retval = balance_parenthesis(data);
  // DINFO(LOG,"Expression %s balanced", ((retval)?"is":"not"));

  // infix_to_postfix("A-B/C*D+E");
  // infix_to_postfix("K+L-M*N+(O^P)*W/U/V*T+Q");
  // infix_to_postfix("A-B+(M^N)*(O+P)-Q/R^S*T+Z");
  // infix_to_prefix("K+L-M*N+(O^P)*W/U/V*T+Q");
  //infix_to_prefix("a+b*c-d/e^f");

  // for(auto itr : CONST) {
  //   cout << "\nKey: " << itr.first;
  //   cout << "\tVal: " << itr.second;
  // }

  const string infix = "A+B*C-D/E^F";
  const string postfix = infix_to_postfix(infix);
  const string prefix = infix_to_prefix(infix);
  const string constants = "A=2,B=3,C=4,D=16,E=2,F=3";

  int postval = evaluate_postfix(postfix, constants, 6);
  printf("\nResult: %d", postval);

  int preval = evaluate_prefix(prefix, constants, 6);
  printf("\nResult: %d", preval);

	return 0;
}
