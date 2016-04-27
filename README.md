# satdoku
##Description
sudoku is a puzzle played on an n by n grid divided into sub-grids of size k. The goal is to fill the blank cells of the grid such that each row, column, and subgrid contains a permutation of the numbers [1,n]. satdoku is a super fast n by n Sudoku solver that uses a SAT solver as a backend. It is the only solver I'm aware of that can handle the n by n case, and not just the traditional 9 by 9 case.

##Dependencies
The only dependency is a SAT solver called minisat. I chose minisat because it's in the ubuntu package repos, so on ubuntu just type `sudo apt-get install minisat`. On other OSes, you will need to install minisat such that you can run it from the command line. The name of the command has to be `minisat`. You could also use another SAT solver, as long as you wrapped it with a shell script so that the syntax is `minisat infile outfile`. 

##How to run
To install, just clone the repo, navigate to the directory, and run `make`. Then the syntax to run the program is just `satdoku puzzle`, where `puzzle` is a file containing a sudoku puzzle encoded as described below:

### Input format
The solver can handle `n` by `n` puzzles with sub-grids of size `k`. Of course, `k` must divide `n`. The first line specifies the two variables, and the second line specifies the puzzle. The puzzle is specified by `n^2` numbers or periods delimited by commas (commas are optional between periods and between numbers and periods). The periods represent blank squares, and the numbers represent filled squares; the (i + j*n)th number represents square (i,j), counting from the top left. So it just goes row 1, row 2, ... , row n. Here are some examples:

(solved) puzzle:
```
+-----+-----+-----+
|4 8 3|9 2 1|6 5 7|
|9 6 7|3 4 5|8 2 1|
|2 5 1|8 7 6|4 9 3|
+-----+-----+-----+
|5 4 8|1 3 2|9 7 6|
|7 2 9|5 6 4|1 3 8|
|1 3 6|7 9 8|2 4 5|
+-----+-----+-----+
|3 7 2|6 8 9|5 1 4|
|8 1 4|2 5 3|7 6 9|
|6 9 5|4 1 7|3 8 2|
+-----+-----+-----+
```

input encoding:
```
9 3
4,8,3,9,2,1,6,5,7,9,6,7,3,4,5,8,2,1,2,5,1,8,7,6,4,9,3,5,4,8,1,3,2,9,7,6,7,2,9,5,6,4,1,3,8,1,3,6,7,9,8,2,4,5,3,7,2,6,8,9,5,1,4,8,1,4,2,5,3,7,6,9,6,9,5,4,1,7,3,8,2
```

(unsolved) puzzle:
```
+-----+-----+-----+
|    3|  2  |6    |
|9    |3   5|    1|
|    1|8   6|4    |
+-----+-----+-----+
|    8|1   2|9    |
|7    |     |    8|
|    6|7   8|2    |
+-----+-----+-----+
|    2|6   9|5    |
|8    |2   3|    9|
|    5|  1  |3    |
+-----+-----+-----+
```
input encoding:
```
9 3
..3.2.6..9..3.5..1..1,8.6,4....8,1.2,9..7.......8..6,7.8,2....2,6.9,5..8..2.3..9..5.1.3..
```

Again, commas adjacent to periods are optional (since they don't affect the meaning; commas are only useful for seperating numbers from each other)

Here's a 12 by 12 puzzle:
```
+-----+-----+-----+-----+
|  2  |  5  |7    |4    |
|1    |    6|8    |    3|
|     |2    |    1|    6|
+-----+-----+-----+-----+
|  4  |  2  |5    |     |
|6    |  1  |    2|  9  |
|     |  9  |     |    5|
+-----+-----+-----+-----+
|7   4|     |9    |     |
|     |     |     |     |
|     |     |     |     |
+-----+-----+-----+-----+
|     |     |     |     |
|     |     |     |     |
|     |     |     |     |
+-----+-----+-----+-----+
```

And here's its encoding:
```
12 3
.2..5.7..4..1....6,8....3...2....1..6.4..2.5.....6...1...2.9.....9......5,7.4...9.................................................................
```

satdoku solves it easily, by the way:
```
+--------+--------+--------+--------+
|9  2  3 |1  5  11|7  12 6 |4  10 8 |
|1  7  12|4  10 6 |8  11 9 |5  2  3 |
|4  8  5 |2  7  9 |3  10 1 |11 12 6 |
+--------+--------+--------+--------+
|12 4  9 |6  2  7 |5  8  10|1  3  11|
|6  5  10|3  1  12|11 4  2 |8  9  7 |
|11 1  2 |10 9  8 |12 7  3 |6  4  5 |
+--------+--------+--------+--------+
|7  11 4 |8  3  2 |9  5  12|10 6  1 |
|3  9  8 |7  11 10|6  1  4 |2  5  12|
|10 6  1 |5  12 4 |2  3  11|7  8  9 |
+--------+--------+--------+--------+
|2  12 6 |11 8  5 |4  9  7 |3  1  10|
|5  3  11|12 6  1 |10 2  8 |9  7  4 |
|8  10 7 |9  4  3 |1  6  5 |12 11 2 |
+--------+--------+--------+--------+
```
##System requirements
I've only tested it on ubuntu, but the code is portable and should compile anywhere. Please file a bug report if you find it doesn't work on your OS and I'll try to fix it.

##Group members
Just me :).

##Contributors
Nope

##Open issues/bugs
None that I'm aware of
