#include "Puzzle.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){ //test af
  Puzzle p;
  p.parse(argv[1]);
  cout<<"Puzzle:"<<endl;
  p.printFancy();
  p.solve();
  cout<<"Solution:"<<endl;
  p.printFancy();
  return 0;
}
