# Sudoku Solver

A C++ Sudoku solver for AS Computer Science. It uses a 9-by-9 integer array,
with 0 representing an empty cell, and vectors to store candidate digits.

## How it works

1. Read a puzzle record from the input file.
2. Check each empty cell against its row, column, and 3-by-3 box.
3. Collect the possible digits from 1 to 9.
4. Fill cells that have exactly one candidate.
5. Repeat until the board is full or no more cells can be filled.

This is a singleton-only solver. It does not guess or backtrack, so some
puzzles remain unfinished. It checks input length and digit characters, but
does not yet check whether the original clues form a valid Sudoku.

## Files and input

- `main.cpp`: the program and helper functions.
- `easy.txt`: the supplied 100,000-puzzle input file, included in this repository.
- `.gitignore`: excludes compiled programs and generated files.

Run the program from the project folder so it can find `easy.txt`.
Each input line must have a 12-character identifier, one space, and 81 puzzle
digits. The program reads those 81 digits starting at character index 13;
any trailing difficulty information is ignored. Zero means an empty cell.

The assignment also links to the Sudoku Exchange puzzle bank. To obtain a
separate copy when its folder is absent, run from the project folder:

```sh
git clone https://github.com/grantm/sudoku-exchange-puzzle-bank.git
```

That downloaded repository has its own Git history and is excluded by
`.gitignore`. No additional download is needed to run the included `easy.txt`.

## Compile and run on a Mac

Open this project folder in VS Code, then choose Terminal > New Terminal.
With Apple's Command Line Tools installed, run:

```sh
clang++ -std=c++14 -O2 -Wall -Wextra main.cpp -o sudoku_solver
./sudoku_solver
```

If this Mac reports that `iostream` cannot be found, the following command
uses the Command Line Tools SDK header location used for the tested build:

```sh
clang++ -std=c++14 -O2 -Wall -Wextra -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1 main.cpp -o sudoku_solver
./sudoku_solver
```

The output lists the records read, puzzles attempted, puzzles solved,
puzzles stalled, malformed records, and percentage solved. The main program
currently prints totals rather than each individual solved board.

## Current status

The solver reads the included dataset, calculates candidates, fills singleton
cells, and reports totals. A test of the included `easy.txt` produced:

```text
Lines read: 100000
Attempted: 100000
Solved: 56970
Stalled: 43030
Malformed: 0
Percent solved: 56.97%
```

The remaining 43,030 puzzles stalled under the singleton-only method; this
does not mean they have no solution. Additional solving techniques and
validation of conflicting starting clues remain unfinished. A future
improvement is to display individual boards alongside the summary.
