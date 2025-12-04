# Terminal Sudoku — C Program

A fully interactive Sudoku game for the terminal, written in simple ANSI C.  
The player enters moves using `ROW COL NUMBER`, and the program validates each step using Sudoku rules (row, column, and 3×3 subgrid).

---

## Features

- 9×9 Sudoku grid with ASCII formatting
- Highlights fixed (given) cells — cannot be modified
- Validates moves:
  - No duplicate number in row
  - No duplicate in column
  - No duplicate in 3×3 subgrid
- Prevents illegal or out-of-bounds input
- Detects when the puzzle is fully solved
- Clean and readable code structure

---

## Files Included

- `sudoku.c` — Complete game source code

---

## How to Build & Run

### Compile:

```bash
gcc sudoku.c -o sudoku
