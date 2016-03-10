# Sudoku-C

Sudoku Solver

  A simple C Program with an Intuitive Interface that can solve Sudoku puzzles. This program is developed with Turbo C with the classic Console based i/o. Input is accepted by using the arrow keys to select the appropriate cell and entering the value. Entering a value of "0" will clear the current cell. The program will check the input for errors before solving it. There is also an option to save the input puzzle to a text file and load it later.
  The logic behind this code is to identify an empty cell that can legally accept only one number without creating a conflict with any other cells. This is achieved by storing the possibilities in a matrix and iterating through it until a cell with this criteria is found. This matrix will be updated whenever an empty cell is filled, this reduces the number of iterations required to identify the next elligible cell.
  
  Screenshots :
  ![Home Screen](https://github.com/abhilashjoel/Sudoku-C/blob/master/Home%20Screen.png)
  ![Input](https://github.com/abhilashjoel/Sudoku-C/blob/master/Input.png)
  ![Solution](https://github.com/abhilashjoel/Sudoku-C/blob/master/Solution.png)
