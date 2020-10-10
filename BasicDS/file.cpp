/***********************************************/
/********   Basic File Operations     **********/
/***********************************************/
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

void read_fstream(const char* file_name) {
  fstream file;
  file.open(file_name);
  if(file.is_open()) {
    string word;
    while(file >> word) {
      printf("\nWord: %s", word.c_str());
    }
    file.close();
  }
}

int main() {
  read_stream("/tmp/text.log");
  return 0;
}
