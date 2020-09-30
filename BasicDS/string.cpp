/***********************************************/
/*********** General String Problems	 ***********/
/***********************************************/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <map>            // Red-Black Height Balanced Tree
#include <vector>         // Dynamic Array
#include <unordered_map>  // Hashtable

using namespace std;

// Predefined constants
#define BOOL(val)     ((val) ? "True" : "False")
#define SWAP(x, y)    {x ^= y; y ^= x; x ^= y;}

typedef unsigned long long int  ullint_t;   // 8 bytes unsigned
typedef long long int           llint_t;    // 8 bytes signed
typedef unsigned int            uint_t;     // 4 bytes unsigned

// Helper for qSort Comparator
int comparator(const void* a, const void *b) {
  return (*(char*)a - *(char*)b);
}

// Helper for swapping pointer values
void swap(char* a, char* b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

// Helper for exchanging string characters
void exchange(string & source, int left, int right) {
  char temp = source[left];
  source[left] = source[right];
  source[right] = temp;
}

// Converts String to Integer (MSB to LSB) -->
llint_t string_to_integer(const char* strValue) {
  llint_t intValue = 0;
	// Check for positive/negative sign
  const int signFlag = (strValue[0] == '-') ? -1 : 1;
	// Define limit if sign is passed with number
  const int limitPos = ((strValue[0] == '-') || (strValue[0] == '+')) ? 1 : 0;
	// Parse string left to right for processing each digit
  for (int indexPos = limitPos; indexPos < strlen(strValue); indexPos++) {
    uint_t posval = strValue[indexPos] - '0';
    intValue = (intValue * 10) + posval;
  }
	// Return with exact sign value
  return intValue * signFlag;
}

// Converts String to Integer Reverse (LSB to MSB) <--
llint_t string_to_integer_reverse(const char* strValue) {
  llint_t intValue = 0;
	// Check for positive/negative sign
  const int signFlag = (strValue[0] == '-') ? -1 : 1;
	// Define limit if sign is passed with number
  const int limitPos = ((strValue[0] == '-') || (strValue[0] == '+')) ? 1 : 0;
	uint_t factorPos = 1;
	// Parse string right to left for processing each digit
	for(int indexPos = (strlen(strValue) - 1); indexPos >= limitPos; indexPos--) {
		uint_t posval = (strValue[indexPos] - '0');
		intValue = intValue + factorPos * posval;
		factorPos = factorPos * 10;
	}
	// Return with exact sign value
  return intValue * signFlag;
}

// Converts signed integer to string
void integer_to_string(const int numValue) {
  char* strValue = NULL;
  const uint_t numDigits = log10(abs(numValue)) + 1;
  int beginIndex, endIndex;
  if(numValue > 0) {
    strValue = (char*) malloc (sizeof(char) * (numDigits + 1));
    beginIndex = 0;
    endIndex = numDigits;
    strValue[endIndex] = '\0';
    endIndex --;
  } else {
    strValue = (char*) malloc (sizeof(char) * (numDigits + 2));
    beginIndex = 0;
    strValue[beginIndex] = '-';
    beginIndex++;
    endIndex = numDigits + 1;
    strValue[endIndex] = '\0';
    endIndex --;
  }
  for (int divident = abs(numValue); divident >= 1; (divident = divident / 10)) {
    int remainder = divident % 10;
    strValue[endIndex] = '0' + remainder;
    printf("\nString Position %d = %d", endIndex, remainder);
    endIndex --;
  }
  printf("\nString Value = %s", strValue);
  free(strValue);
}

// String convert case of all characters
void string_convert_case(const char *strVal) {
  int length = strlen(strVal);
  char resVal[length + 1];
  for(int index = 0; index < length; index++) {
    const char chVal = strVal[index];
    if(('a' <= chVal) && (chVal <= 'z')) {
      resVal[index] = 'A' + (chVal - 'a');
    } else {
      resVal[index] = 'a' + (chVal - 'A');
    }
  }
  resVal[length] = '\0';
  printf("\nInput  = %s", strVal);
  printf("\nResult = %s", resVal);
}

// Check whether string is palindrome - O(N)
bool is_palindrome(const char* str, bool ignore_case=true) {
  char* start = (char*)str;
  char* end   = (start)?(start + (strlen(str) - 1)):NULL;
  while (start && end && (start < end)) {
    // Based on ignore case decide comparison logic
    char prev = (ignore_case) ? toupper(*start) : *start;
    char next = (ignore_case) ? toupper(*end) : *end;
    if(prev != next) {
      printf("\nOffending characters are '%c' and '%c'", *start, *end);
      return false;
    }
    start++;
    end--;
  }
  return true;
}

// Check whether strings are anagram - O(N)
bool is_anagram(const char* str1, const char* str2, bool ignore_case=true) {
  // Strings are not of equal length
  if(strlen(str1) != strlen(str2)) {
    return false;
  }
  // Check only for non-null strings
  if(str1 && str2) {
    // Intialize counter
    int counter[UCHAR_MAX] = {0};
    // Traverse over both strings
    for(int index = 0; index < strlen(str1); index++) {
      // For character in string-1 increase counter
      char prev = (ignore_case) ? toupper(str1[index]) : str1[index];
      counter[prev]++;
      // For character in string-2 decrease counter
      char next = (ignore_case) ? toupper(str2[index]) : str2[index];
      counter[next]--;
    }
    // Check if counter is 0 for all characters
    for(int index = 0; index < UCHAR_MAX; index++) {
      if(counter[index] != 0) {
        return false;
      }
    }
  }
  return true;
}

// Sort and compare both strings for anagram - O(NLogN)
bool sort_compare(const char* str1, const char* str2) {
  bool retval = true;
  if(!(str1 && str2 && (strlen(str1) == strlen(str2)))) {
    return false;
  }
  // Intialize and sort string-1
  char val1[strlen(str1) + 1];
  strncpy(val1, str1, strlen(str1));
  qsort(val1, strlen(val1), sizeof(char), comparator);
  // Intialize and sort string-2
  char val2[strlen(str2) + 1];
  strncpy(val2, str2, strlen(str2));
  qsort(val2, strlen(val2), sizeof(char), comparator);
  for(int index = 0; index < strlen(val1); index++) {
    // Compare each character
    if(val1[index] != val2[index]) {
      return false;
    }
  }
  return true;
}

// Map and compare both strings for anagram - O(N)
bool frequency_compare(string source, string target){
  unordered_map<char, int> FMAP;
  // Iterate over source
  for(int index = 0; index < source.length(); index++) {
    const char key = source[index];
    if(FMAP.find(key) != FMAP.end()) {
      FMAP[key]++;
    } else {
      FMAP[key] = 1;
    }
  }
  // Iterate over target
  for(int index = 0; index < target.length(); index++) {
    const char key = target[index];
    if(FMAP.find(key) != FMAP.end()) {
      //  Decrement frequency counter
      FMAP[key]--;
    } else {
      // Key does not exist
      return false;
    }
    // If all combinations are exhausted, remove entry
    if(FMAP[key] == 0) {
      FMAP.erase(key);
    }
  }
  return (FMAP.size() == 0);
}

// Reverse string - O(N)
void string_reverse(char* str) {
  char* start = str;
  char* end   = (start)? (start + (strlen(str) - 1)) : NULL;
  while(start && end && start < end) {
    // Swap start and end characters
    swap(start, end);
    start++;
    end --;
  }
}

// Sliding window algorithm to get substring results - O(N)
void sliding_window_algorithm(const string source, const string target,
                              unordered_map<string, int>& results) {
  // Initialize reference map, with frequency count of each character
  unordered_map<char,int> REFMAP;
  for(int index = 0; index < target.length(); index++) {
    const char key = target[index];
    REFMAP[key]++;
  }
  int counter = REFMAP.size();
  int beginIndex, endIndex;
  // Iterate over source string
  for(endIndex = 0, beginIndex = 0; endIndex < source.length(); endIndex++) {
    const char key = source[endIndex];
    if(REFMAP.find(key) == REFMAP.end()) {
      // Key is not found, so move to next character
      continue;
    } else {
      // Decrement frequency count for visited character
      REFMAP[key]--;
      // Decrement counter, when all occurences of character visited
      if(REFMAP[key] == 0) {
        // Decrement counter, DO NOT REMOVE KEY
        counter --;
      }
    }
    // Counter = 0, all characters of target are visited by endIndex
    while(counter == 0) {
      // Find all substrings from beginIndex to endIndex
      const char key = source[beginIndex];
      if(REFMAP.find(key) != REFMAP.end()) {
        // beginIndex and endIndex, match substring
        const int sublen    = endIndex - beginIndex + 1;
        const string substr = source.substr(beginIndex, sublen);
        // printf("\nLength: %d, String: %s", sublen, substr.c_str());
        results.emplace(substr, sublen);
        // Increment frequency count of visited character
        REFMAP[key]++;
        if(REFMAP[key] > 0) {
          // Increment counter, when all occurences have visited
          counter++;
        }
      }
      beginIndex++;
    } // End of while loop
  } // End of for loop
}

// Minimum source substring matching all characters of target
void minimum_matching_window(const string source, const string target) {
  printf("\nSource:\t%s\nTarget:\t%s", source.c_str(), target.c_str());
  unordered_map<string, int> results;
  sliding_window_algorithm(source, target, results);
  if(results.size() == 0) {
    printf("\nNo matching substring exists");
  }
  int min_window = source.length();
  string min_substr;
  for(auto itr = results.begin(); itr != results.end(); itr++) {
    string substr = itr->first;
    int window = itr->second;
    if(window < min_window) {
      min_window = window;
      min_substr = substr;
    }
  }
  printf("\nMinimum window substring: %s", min_substr.c_str());
}

// Parse source to find anagrams of target
void finding_string_anagrams(const string source, const string target) {
  printf("\nSource:\t%s\nTarget:\t%s", source.c_str(), target.c_str());
  unordered_map<string,int> results;
  sliding_window_algorithm(source, target, results);
  if(results.size() == 0) {
    printf("\nNo anagram exists");
  }
  const int length = target.length();
  for(auto itr = results.begin(); itr != results.end(); itr++) {
    string substr = itr->first;
    int window = itr->second;
    if(length == window) {
      printf("\nAnagram: %s", substr.c_str());
    }
  }
}

// Get maximum substring with distinct characters - O(N)
void maximum_distinct_substring(const string strvalue) {
  string max_substr;
  int max_sublen = 0;
  int counter = 0;
  int beginIndex, endIndex;
  unordered_map<char, int> CHARMAP;
  for(endIndex = 0, beginIndex = 0; endIndex < strvalue.length(); endIndex++) {
    const char key = strvalue[endIndex];
    // Mark character as visited
    CHARMAP[key]++;
    // Character is revisited
    if(CHARMAP[key] > 1) {
      counter++;
    }
    // With fixed endIndex, find beginIndex with distinct character
    while(counter > 0) {
      const char val = strvalue[beginIndex];
      CHARMAP[val]--;
      if(CHARMAP[val] > 0) {
        counter--;
      }
      beginIndex++;
    } // End of while loop
    // All possible substrings with distinct characters
    const int sublen = endIndex - beginIndex + 1;
    const string substr = strvalue.substr(beginIndex, sublen);
    printf("\nDistinct substring: %s", substr.c_str());
    if(sublen > max_sublen) {
      max_sublen = sublen;
      max_substr = substr;
    }
  } // End of for loop
  printf("\nLongest substring: %s", max_substr.c_str());
}

// Get maximum palindrome in string - O(N2)
void get_max_palindrome(const string strvalue) {
  int sublen = 0;
  int subpos = 0;
  const int maxlen = strvalue.length();
  int low, high, index;
  for(index = 0; index < maxlen; index++) {
    // Check for even palindrome
    low  = index - 1;
    high = index;
    while((0 <= low) && (high < maxlen) && (low < high) &&
          (strvalue[low] == strvalue[high])) {
      int length = (high - low) + 1;
      if(length > sublen) {
        sublen = length;
        subpos = low;
      }
      low --;
      high ++;
    }
    // Check for odd palindrome
    low  = index - 1;
    high = index + 1;
    while((0 <= low) && (high < maxlen) && (low < high) &&
          (strvalue[low] == strvalue[high])) {
      int length = (high - low) + 1;
      if(length > sublen) {
        sublen = length;
        subpos = low;
      }
      low --;
      high ++;
    }
  }
  // Longest possible palindrome
  printf("\nSource: %s\nLongest Palindrome: ", strvalue.c_str());
  if((0 <= subpos) && (0 < sublen)) {
    printf("%s", strvalue.substr(subpos, sublen).c_str());
  } else {
    printf("Does not exists.");
  }
}

// Helper to reverse word (C based pointer)
void reverse_word(char* start, char* end) {
  while(start < end) {
    char temp = *start;
    *start = *end;
    *end = temp;
    start ++;
    end --;
  }
}

// Reverse words in sentence (leading whitespaces only)
void reverse_sentence(char* sentence) {
  printf("\nOld Sentence: %s", sentence);
  const int length = strlen(sentence);
  char* prev = sentence;
  char* next = sentence + (length - 1);
  // Iterate over sentence
  for(next = sentence, prev = NULL; *next != '\0'; next++) {
    const char curr_val = *next;
    if(!isspace(curr_val) && (prev == NULL)) {
      prev = next;
    }

    const char next_val = *(next + 1);
    if(prev && (next_val == ' ') || (next_val == '\0')) {
      reverse_word(prev, next);
      prev = NULL;
    }
  }
  reverse_word(sentence, (sentence + (length - 1)));
  printf("\nNew Sentence: %s", sentence);
}

// Reverse substring (C++ style strings)
void reverse_substring(string& sentence, int start, int end){
  int length = sentence.length();
  int beginIndex = ((0 <= start)&&(start < length))? start : -1;
  int endIndex = ((0 <= end)&&(end < length))? end : -1;
  while((beginIndex != -1)&&(endIndex != -1)&&(beginIndex < endIndex)) {
    const char temp = sentence[beginIndex];
    sentence[beginIndex] = sentence[endIndex];
    sentence[endIndex] = temp;
    beginIndex ++;
    endIndex --;
  }
}

// Reverse all words of sentence (leading and trailing whitespaces)
void reverse_string_words(string& sentence) {
  printf("\nOld String: %s", sentence.c_str());
  const int length = sentence.length();
  bool word_flag = false;
  int beginIndex, endIndex;
  for(endIndex = 0, beginIndex = 0; endIndex < sentence.length(); endIndex++) {
    // Found space character or last character of sentence
    if((sentence[endIndex] == ' ') || (endIndex == (length - 1))) {
      endIndex = (sentence[endIndex] == ' ') ? endIndex : endIndex + 1 ;
      if(beginIndex < endIndex) {
        // Word boundary identified only when previous chars not space
        word_flag = true;
      } else {
        beginIndex = (endIndex + 1);  // Begin is moved to next character
      }
    }
    // Start window identified
    while(word_flag && (beginIndex < endIndex)) {
      if(sentence[beginIndex] == ' ') {
        beginIndex++;
      } else {
        // End window identified
        reverse_substring(sentence, beginIndex, (endIndex - 1));
        word_flag = false;
        beginIndex = (endIndex + 1);  // Begin is moved to next window
      }
    }
  }
  // Reverse entire sentence
  reverse_substring(sentence, 0, (length - 1));
  printf("\nNew String: %s", sentence.c_str());
}

// Reverse words list (Array of strings)
void reverse_words_list(string words[], int count) {
  int low  = 0;
  int high = count - 1;
  while(low < high) {
    string temp = words[low];
    words[low] = words[high];
    words[high] = temp;
    low ++;
    high --;
  }
}

// Count frequency of words (ignoring whitespaces)
void frequency_count_words(string sentence) {
  unordered_map<string, int> FMAP;
  const int length = sentence.length();
  bool word_flag = false;
  int beginIndex, endIndex;
  for(endIndex = 0, beginIndex = 0; endIndex < length; endIndex++) {
    // Check for word boundary
    if((sentence[endIndex] == ' ') || (endIndex == (length - 1))) {
      endIndex = (sentence[endIndex] == ' ') ? endIndex : endIndex + 1;
      if(beginIndex < endIndex) {
        word_flag = true;
      } else {
        beginIndex = endIndex + 1;
      }
    }
    while(word_flag && (beginIndex < endIndex)) {
      if(sentence[beginIndex] == ' ') {
        beginIndex++;
      } else {
        //printf("\nWord boundary: %d - %d", beginIndex, (endIndex - 1));
        const int sublen = (endIndex - beginIndex);
        const string substr = sentence.substr(beginIndex, sublen);
        FMAP[substr]++;
        word_flag = false;
        beginIndex = endIndex + 1;
      }
    } //  End of while loop
  } // End of for loop
  // Display frequency count
  for(auto itr = FMAP.begin(); itr != FMAP.end(); itr++) {
    printf("\n%s -> %d", itr->first.c_str(), itr->second);
  }
}


// Helper for display character array
void show_char_array(const string source) {
  const int length = source.length();
  printf("\nIndex:");
  for(int index = 0; index < length; index++) {
    printf("\t%d", index);
  }
  printf("\nChar:");
  for(int index = 0; index < length; index++) {
    printf("\t%c", source[index]);
  }
}

// Helper for displaying LPS array
void show_lps_array(const string pattern, int* LPS, const int length) {
  show_char_array(pattern);
  printf("\nLPS:");
  for(int index = 0; index < length; index++) {
    printf("\t%d", LPS[index]);
  }
}

// Initiliaze longest prefix suffix array for pattern - O(M)
void longest_prefix_suffix(const string pattern, int* LPS, const int length) {
  int lpsIndex = 0;
  int ptrIndex = 1;
  LPS[lpsIndex] = 0;
  while(ptrIndex < length) {
    // If pattern position character matches with LPS position character
    if(pattern[ptrIndex] == pattern[lpsIndex]) {
      lpsIndex++;
      LPS[ptrIndex] = lpsIndex;
      ptrIndex++;
    } else {
      if(lpsIndex > 0) {
        lpsIndex = LPS[lpsIndex - 1];
      } else {
        LPS[ptrIndex] = 0;
        ptrIndex++;
      }
    }
  }
  show_lps_array(pattern, LPS, length);
}

// KMP pattern search algorithm - O(M + N) ~ O(N)
// Here, M := size of pattern and N := size of text
void pattern_search_algorithm(const string text, const string pattern) {
  char* REG = (char*) malloc(sizeof(char) * text.length());
  memset(REG, ' ', text.length());
  // O(M) - Preprocessing pattern to construct LPS [Space = O(M)]
  const int size = pattern.length();
  int* LPS = (int*) malloc(sizeof(int) * pattern.length());
  longest_prefix_suffix(pattern, LPS, size);
  // O(N) - Matching character of text with pattern using LPS
  int txtIndex = 0;   // Index position of text (normal iterator)
  int ptrIndex = 0;   // Index position of pattern (driven by LPS)
  while(txtIndex < text.length()) {
    printf("\nTXT: %d", txtIndex);
    printf("\nPTR: %d", ptrIndex);
    // Compare character of text with pattern
    if(text[txtIndex] == pattern[ptrIndex]) {
      // Found matching character, advance pattern and text
      txtIndex++;
      ptrIndex++;
    } else {
      // Found non-matching character
      if(ptrIndex > 0) {
        // Search for previous matching character in pattern
        ptrIndex = LPS[ptrIndex - 1];
      } else {
        // Pattern match exhausted, advance text
        txtIndex++;
      }
    }
    // Pattern is matched completely with text
    if(ptrIndex == pattern.length()) {
      const int startIndex = (txtIndex - ptrIndex);
      const int endIndex   = startIndex + pattern.length();
      for(int index = startIndex; index < endIndex; index++) {
        REG[index] = '#';
      }
      printf("\nFound pattern '%s' at %d", pattern.c_str(), startIndex);
      if(ptrIndex > 0) {
        ptrIndex = LPS[ptrIndex - 1];
      }
    }
  }
  show_char_array(text);
  string value(REG);
  show_char_array(value);
  free(REG);
  free(LPS);
}

// Print all permutations of string - O(N * N!)
// O(N!) : Number of permutations
// O(N)  : Traverse entire string of length N, to print permutation
void print_string_anagrams(char* source, int low, int high) {
  if(low == high) {
    // Recursion ended display string
    printf("\n%s", source);
  } else {
    for(int index = low; index <= high; index++) {
      // Swap low index character with current index character
      swap((source + low), (source + index));
      // Recurse further to swap next characters
      print_string_anagrams(source, (low + 1), high);
      // Back-tracking swap process
      swap((source + low), (source + index));
    }
  }
}

// Get permutations of string (Non-Repetitive characters) - O(N * N!)
// O(N!) : Number of permutations
// Example: ABC = (Length)3! / (A)1! * (B)1! * (C)1! = 6
// O(N)  : Traverse entire string of length N, to print permutation
void string_possible_permuations(vector<string>& result, string& source,
                         int low, int high) {
  if(low == high) {
    // Recursion ended insert string into results
    result.push_back(source);
  } else {
    for(int index = low; index <= high; index++) {
      // Swap low index character with current index character
      exchange(source, low, index);
      // Recurse further to swap next characters
      string_possible_permuations(result, source, (low + 1), high);
      // Back-tracking swap process
      exchange(source, low, index);
    }
  }
}

// Get distinct permutations of string (Repetitive characters) - O(N * (N!/R!))
// O(N!/R!) : Number of permutations, Number of repetitions for character
// Example: ABCBC = (Length)5! / (A)1! * (B)2! * (C)2! = 30
// O(N)  : Traverse entire string of length N, to print permutations
void string_distinct_permuations(vector<string>& result, string& source,
                              int low, int high) {
  if(low == high) {
    result.push_back(source);
  } else {
    for(int index = low; index <= high; index++) {
      // Ensure that swapping characters are not same (distinct)
      if(source[low] != source[index]) {
        // Swap low index character with current index character
        exchange(source, low, index);
        // Recurse further to swap next characters
        string_possible_permuations(result, source, (low + 1), high);
        // Back-tracking swap process
        exchange(source, low, index);
      }
    }
  }
}

// Find Longest Common Sub-sequence (LCS) of two strings - O(MN)
void longest_common_subsubsequence(string source, string target) {
  int source_length = source.length() + 1; // For 0th column
  int target_length = target.length() + 1; // For 0th row
  int sublen_matrix[target_length][source_length];
  // 0th Column and 0th row is intialized as zero
  memset(sublen_matrix, 0, sizeof(sublen_matrix));
  // Outer loop over target string - ROWS
  for(int row = 1; row < target_length; row++) {
    // Inner loop over source string - COLUMNS
    for(int col = 1; col < source_length; col++) {
      // Compare characters of string at row, col index
      if(target[row - 1] == source[col - 1]) {
        // Character match, increment value from left top diagonal
        sublen_matrix[row][col] = sublen_matrix[row-1][col-1] + 1;
      } else {
        // Character mismatch, take MAX(previous row, previous column)
        sublen_matrix[row][col] =
        max(sublen_matrix[row-1][col], sublen_matrix[row][col-1]);
      }
    }
  }
  // Traverse bottom up for longest common subsequence
  int row = target_length - 1;
  int col = source_length - 1;
  int len = sublen_matrix[row][col];
  int pos = len - 1;
  char LCS[len + 1];
  LCS[len] = '\0';
  while((row > 0) && (col > 0) && (pos >=0)) {
    // If characters are same, go diagonally left upwards
    if(target[row - 1] == source[col - 1]) {
      LCS[pos] = source[col - 1];
      row --;
      col --;
      pos --;
    } else {
      // If characters are same, move left or above
      if(sublen_matrix[row - 1][col] > sublen_matrix[row][col - 1]) {
        // previous row
        row --;
      } else {
        // previous column
        col --;
      }
    }
  }
  printf("\nSource: %s", source.c_str());
  printf("\nTarget: %s", target.c_str());
  printf("\nLongest subsequence: %s (Length: %d)", LCS, len);
  // printf("\nSubsequence Matrix:\n\t");
  // for(int col = 0; col < source_length; col++) {
  //   if(col == 0) {
  //     printf("\t");
  //   } else {
  //     printf("\t%c", source[col - 1]);
  //   }
  // }
  // for(int row = 0; row < target_length; row++) {
  //   printf("\n");
  //   for(int col = 0; col < source_length; col++) {
  //     if(col == 0) {
  //       if(row == 0) {
  //         printf("\t  ");
  //       } else {
  //         printf("\t%c", target[row - 1]);
  //       }
  //     }
  //     printf("\t%d", sublen_matrix[row][col]);
  //   }
  // }
}

int main() {
  // const char* str = "AbCdZDcBa";
  // printf("\nString '%s' is palindrome: %s",
  //           str, BOOL(is_palindrome(str)));
  //
  // const char* str1 = "lisTen";
  // const char* str2 = "siLent";
  // printf("\nStrings '%s' and '%s' are anagrams: %s",
  //           str1, str2, BOOL(is_anagram(str1, str2)));
  //
  // char str[] = {"AAXBB"};
  // string_reverse(str);
  // printf("\nString reverse: %s", str);
  // string str = "ABCDBDCA";
  // char arr[] = {"ABCDBDCA"};
  // qsort(arr, strlen(arr), sizeof(char), comparator);
  // printf("\n%s", arr);


  // minimum_matching_window("ADOBECODEBANC", "ABC");
  // minimum_matching_window("ADAOBECODEABANC", "AABC");
  // minimum_matching_window("BACDACB", "ABC");

  // finding_string_anagrams("cbaebabacd", "abc");
  //  maximum_distinct_substring("abcabcbb");
  // maximum_distinct_substring("aabbccabcxyz");
  // get_max_palindrome("forgeeksskeegfor");
  //get_max_palindrome("abc");
  // string words[] = {"dad", "is", "god"};
  // int length = sizeof(words)/sizeof(string);
  // reverse_words_list(words, length);
  // for(int index = 0; index < length; index++) {
  //   printf("\n%s", words[index].c_str());
  // }
  // char sentence[] = {" time is     money"};
  // reverse_sentence(sentence);
  // string sentence = " time  is  money time is too bad for thinking";
  // frequency_count_words(sentence);
  // string pattern = "ANANAB#BANANA";
  // string text = "AABAACAADAABAABADEFGHIJKAABA";
  // string pattern = "AABA";
  // pattern_search_algorithm(text, pattern);
  // char source[] = {"ABCA"};
  // print_string_anagrams(source, 0, strlen(source) - 1);
  // string source = "ABC";
  // print_string_anagrams(source, 0, (source.length() - 1));
  // vector<string> results;
  // string source = "ABCA";
  // string_distinct_permuations(results, source, 0, (source.length() - 1));
  // printf("\nPermutations: %d", (int)results.size());
  // for(auto itr: results) {
  //   printf("\n%s", itr.c_str());
  // }
  //longest_common_subsubsequence("bqdrcvefgh", "abcvdefgh");
  return 0;
}
