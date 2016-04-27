#include <vector>
#include <string>

class Puzzle
{
 public:
  //Constructor/destructor are implicitly defined
  
  //Essentials
  void parse(std::string filename);
  void solve();                         // Using minisat as a backend  
  bool satisfiable=true;
  
  //For constructing puzzles without using an input file
  void addNumber(int num, int row, int col); //all parameters must be in [1,n]; row and col index from 1 (the top left corner is (1,1)). If (row, col) already has a number, replaces the number with num
 
  //Getters and setters (encapsulation is necessary to prevent errors like setting a k that doesn't divide n: if the new k or n isn't valid, the function will return an error and exit the program
  inline void setN(int n);
  inline void setK(int k);
  inline void toLatinSquare(){ k = 1; } //For using satdoku as a latin square solver
  inline int getN(){ return n; }
  inline int getK(){ return k; }
  
  //Formatting output/printing
  void printRaw(); //Prints the puzzle in the input format
  void printFancy(); //Prints the puzzle in a more human-readable format

 protected:
 private:
  int n=1; int k=1;
  std::vector<int> puzzle; //0 stands for blank, all nums are in [1,n]

  //Encoding functions that for annoying reasons unfortunately have class members:
  struct ijv{int i; int j; int v;};
  int a(int i, int j, int v){ return i*n*n + j*n + v; }

};

