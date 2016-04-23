# SATdoku
A super fast Sudoku solver.
### Input format
The solver can handle `nxn` puzzles with sub-grids of size `k`. Of course, `k` must divide `n`. The first line specifies the two variables, and the remainder of the input file specifies the blank and non-blank squares of the puzzle. The numbers and blanks are delimited by commas, so `0,0` would be two adjacent zeros, while `0, ,0` would be zero, blank, zero:
```
n k
a_(0,0),a_(1,0),...a_(n,0)
a_(0,1)            a_(n,1)
           .
	    .
	     . 
a_(0,n-1)	   a_(n-1,n)
a_(0,n),a_(1,n),...a_(n,n)
```
For example, a normal 9x9 puzzle could be encoded like this:
```
9 9 3
 , , , ,3, , , ,8
 , ,6, , , ,3,5,
 , ,3, , ,8, ,4,1
 ,3,1,7, ,6, , ,4
7,5, ,9,8,1, ,3,2
2, , ,3, ,4,1,9,
3,2, ,1, , ,8, ,
 ,1,5, , , ,9, ,
6, , , ,9, , , , 
```
Note: all numbers must be in [1,n]