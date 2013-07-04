#include <iostream>

#include "cyg-profile.h"

using namespace std;

class test {
    int function1 (long l);
    int function2 (int i);
  public:
    int function3 (char c);
};

int
test::function1 (long l) {
  return l;
}

int
test::function2 (int i) {
  return test::function1 (i) + 1;
}

int
test::function3 (char c) {
  return test::function2 (c) + 1;
}

int main () {
  class test *ptest;

  cout << "Logfile: " << cygprofile_getfilename () << endl;

  cygprofile_enable();

  ptest = new test();

  return ptest->function3 (1);
}
