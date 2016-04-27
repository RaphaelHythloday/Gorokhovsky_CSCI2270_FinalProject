#include "Puzzle.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

//Getters and setters
void Puzzle::setN(int new_n){
  if (new_n > k && new_n % k == 0)
    n = new_n;
  else{
    cout << "ERROR: Attempt to set n to " << new_n << " with k = " << k << endl;
    exit(0);
  }
}

void Puzzle::setK(int new_k){
  if (new_k > 0 && n > new_k && n % new_k == 0)
    k = new_k;
  else{
    cout << "ERROR: Attempt to set k to " << new_k << " with n = " << n << endl;
    exit(0);
  }
}

//Solver
void Puzzle::solve(){
  /*
    Let a_{i,j} be row i, column j of the table, indexed from 1. Then we encode the puzzle as follows:
    1. Start with n^3 variables, representing a_{i,j} == v for all i,j,v in [1..n]
    2. Next encode a_{i,j} == v => a_{i,j} != w if w != v (trivial constraint)
    3. Then encode a_{i,j} == v && (i,j) is in unit U => a_{i',j'} != v if (i',j') is in U (the puzzle constraint)
    4. Finally add \exists v such that a_{i,j} == v (because we cannot allow empty squares)
    Here a unit is any row, column, or subgrid of the puzzle.
  */
  ijv vars[n*n*n+1];
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      for (int v=1; v<=n; v++){
	ijv var; var.i=i; var.j=j; var.v=v;
	vars[i*n*n + j*n + v] = var;
      }
    }
  }
  
  if (puzzle.empty()){
    cout << "Please parse or specify a puzzle before solving." << endl;
    return;
  }
  
  ofstream cnf; cnf.open("puzzle.cnf");

#define nut "-"<<
#define er <<" "<<
#define br <<" 0"<<endl
  //Step 1
  //Implemented in the header: syntax for the variable encoding a_{i,j} == v is a(i,j,v)
  cnf << "c Sudoku CNF encoding" << endl;
  //Step 2
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      for(int v=1; v<=n; v++){
	for(int w=1; w<=n; w++){
	  if (w != v) cnf << nut a(i,j,v) er nut a(i,j,w) br;
	}}}}
  
  //Step 3
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      for (int v=1; v<=n; v++){
	for (int x=0; x<n; x++){
	  for(int y=0; y<n; y++){
	    if ((x==i || y==j || ( (x/k)==(i/k) && (y/k)==(j/k) )) && (x!=i || y!=j))
	      cnf << nut a(i,j,v) er nut a(x,y,v) br;
	  }
	}
      }
    }
  }
	  
  //Step 4
   for (int i=0; i<n; i++){
     for (int j=0; j<n; j++){
       for (int v=1; v<=n; v++)
	 cnf << a(i,j,v) << " ";
       cnf br;
     }
   }

   //Also btw you have to set the givens
   for (int i=0; i<n; i++){
     for (int j=0; j<n; j++){
       if(puzzle[i + j*n] > 0)
	 cnf << a(i,j,puzzle[i + j*n]) br;
     }
   }
   
   cnf.close();
  //Solve
   system("minisat puzzle.cnf tempfile.out >/dev/null 2>&1");

  //Update the puzzle with our new solution
   ifstream solfile; solfile.open("tempfile.out");
   string sol;
   
   getline(solfile, sol);
   if(sol == "UNSAT"){
     cout << "No solution!" << endl;
     return;
   }

   getline(solfile, sol);
   stringstream ss(sol); int lit;
   for(int c=0; c<n*n*n; c++){
     ss >> lit;
     ijv var = vars[abs(lit)];
     int i = var.i; int j = var.j; int v = var.v;
     if (lit>0) {
       puzzle[i + j*n] = v;
     }
   }
#undef nut
#undef er
#undef br   
}

void Puzzle::printFancy(){
  int maxDigits = 0;
  for (int i=0; i<puzzle.size(); i++)
    if (to_string(puzzle[i]).length() > maxDigits)
      maxDigits = to_string(puzzle[i]).length();

  string dashes(k*(maxDigits+1)-1, '-'); string horizontal = "+";
  for (int i=0; i<n/k; i++)
    horizontal += dashes + '+';
      
  for (int y=0; y<n; y++){
    if (y%k == 0) cout<<horizontal<<endl;
    for (int x=0; x<n; x++){
      if (x%k == 0) cout<<"|";
      string spaces(maxDigits - to_string(puzzle[y*n+x]).length(), ' ');
      cout<<(puzzle[y*n+x]==0 ? " " : to_string(puzzle[y*n + x])) + spaces;
      if (x%k!= k-1) cout<<" ";
    }
    cout<<"|"<<endl;
  }
  cout<<horizontal<<endl;
}
  
void Puzzle::printRaw(){
  cout<<n<<" "<<k<<endl;
  for(int i=0; i<puzzle.size(); i++){
    if(puzzle[i] == 0)
      cout<<".";
    else{
      cout<<puzzle[i];
      if(i<puzzle.size()-1 && puzzle[i+1] != 0) cout<<",";
    }
  }
  cout<<endl;
}

void Puzzle::parse(string filename){
  string line; ifstream file(filename.c_str());
  
  getline(file, line); stringstream ss(line);
  ss >> n >> k;

  getline(file, line);
  int value; bool in_number = false;
  for(int i=0; i<line.length(); i++){
    if (line[i] == '.'){
      if (in_number){
	puzzle.push_back(value);
	in_number = false;
      }
      puzzle.push_back(0);
    }
    else if (line[i] == ','){
      if (in_number) {
	puzzle.push_back(value);
	in_number = false;
      }
    }
    else if (line[i] > '0' && line[i] <= '9'){
      if (in_number) {
	value *= 10;
	value += line[i] - '0';
      } else {
	in_number = true;
	value = line[i] - '0';
      }
    }
  }
}

void Puzzle::addNumber(int v, int i,int  j){
  puzzle.insert(puzzle.begin()+(i+j*n), v);
}
