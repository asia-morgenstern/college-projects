/* p2 - project 2
 * 	  - sudoku solver
 * 
 * Asia Morgenstern
 * 12 March 2022
 * DUE 23 March 2022
 */

import java.util.Scanner;
import java.io.*;

public class p2 {

	private static void sudokuSolver(int[][] grid, int[][] sol, int r, int c, int val) {
		/* sudokuSolver - solves a sudoku puzzle
		 * 
		 * grid - a sudoku puzzle
		 * sol - puzzle solution
		 * r - row
		 * c - column
		 * val - number to enter, 1 to 9
		 */
				
		if (c == 9) {								// is c valid			
			++r;
			c = 0;
		}		
		
		if (r >= 9 && c == 0) {						// is r valid
			for (int row = 0; row < 9; row++) {
				for (int column = 0; column < 9; column++) {
					grid[row][column] = sol[row][column];
				}
			}
		} else if (val > 9 && r < 9 && c < 9) {		// is val valid
			int row = r;
			int column = --c;
			if (column == -1) {						// is c valid			
				if (r > 0) {
					--row;
				}
				column = 8;
			}

			do {									// finds the last value entered (last 0 in grid)
				if (grid[row][column] != 0) {
					--column;
					if (column == -1) {				// is c valid			
						if (r > 0) {
							--row;
						}
						column = 8;
					}
				}
			} while (grid[row][column] != 0);

			val = sol[row][column] + 1;				// check next val
			sol[row][column] = 0;			
			sudokuSolver(grid, sol, row, column, val);
		} else if (r < 9 && c < 9) {				// r, c, and val are valid						
			if (grid[r][c] == 0) {
				if (isValidRow(sol, r, val) && isValidColumn(sol, c, val) && isValidBox(sol, r, c, val)) {
					sol[r][c] = val;			
					++c;
					val = 1;
				} else {
					for (; val <= 9; val++) {
						if (isValidRow(sol, r, val) && isValidColumn(sol, c, val) && isValidBox(sol, r, c, val)) {
							sol[r][c] = val;
							++c;
							val = 1;
							break;
						}
					}					
				}				
			} else {
				++c;
				val = 1;
			}
			sudokuSolver(grid, sol, r, c, val);
		}
	}
	
	public static void sudokuSolver(int[][] grid) {		
		/* sudokuSolver - front–end program
		 * 
		 * grid - a sudoku puzzle
		 */
		
		int[][] copy = new int[9][9];
		for (int r = 0; r < 9; r++) {
			for (int c = 0; c < 9; c++) {
				copy[r][c] = grid[r][c];
			}
		}
		sudokuSolver(grid, copy, 0, 0, 1);
	}
	
	private static boolean isValidRow(int[][] grid, int r, int val) {
		/* isValidRow - checks if a row is valid
		 * 			  - returns true if valid, false otherwise
		 * 
		 * grid - a sudoku puzzle
		 * r - row to check
		 * val - a number to check
		 */
		
		for (int c = 0; c < 9; c++) {				// checks every column in r
			if (grid[r][c] == val) {
				return false;
			}
		}
		return true;
	}
	
	private static boolean isValidColumn(int[][] grid, int c, int val) {
		/* isValidColumn - checks if a column is valid
		 * 				 - returns true if valid, false otherwise
		 * 
		 * grid - a sudoku puzzle
		 * c - column to check
		 * val - a number to check
		 */
		
		for (int r = 0; r < 9; r++) {				// checks every row in c
			if (grid[r][c] == val) {
				return false;
			}
		}
		return true;
	}
	
	private static boolean isValidBox(int[][] grid, int row, int column, int val) {
		/* isValidBox - checks if a 3 by 3 box is valid
		 * 			  - returns true if valid, false otherwise
		 * 
		 * grid - a sudoku puzzle
		 * row - row location to check
		 * column - column location to check
		 * val - a number to check
		 */
		
		int rStart;									// determines top left corner of the 3x3
		if ((row + 1)%3 == 1) {
			rStart = row;
		} else if ((row + 1)%3 == 2) {
			rStart = row - 1;
		} else {
			rStart = row - 2;
		}
		
		int cStart;
		if ((column + 1)%3 == 1) {
			cStart = column;
		} else if ((column + 1)%3 == 2) {
			cStart = column - 1;
		} else {
			cStart = column - 2;
		}
		
		for (int r = rStart; r < rStart + 3; r++) {
			for (int c = cStart; c < cStart + 3; c++) {
				if (grid[r][c] == val) {
					return false;
				}
			}			
		}
		return true;
	}
	
	public static void printPuzzle(int[][] grid) {
		/* printPuzzle - prints the sudoku puzzle
		 * 
		 * grid - a sudoku puzzle
		 */
				
		System.out.println("+-----+-----+-----+");				
		for (int r = 0; r < 9; r++) {
			System.out.print("|");
			for (int c = 0; c < 9; c++) {
				System.out.print(grid[r][c]);
				if ((c + 1)%3 == 0) {
					System.out.print("|");
				} else {
					System.out.print(" ");
				}
			}
			if ((r + 1)%3 == 0) {
				System.out.println("\n+-----+-----+-----+");
			} else {
				System.out.println();
			}
		}
	}
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		Scanner fin = null;
		
		System.out.println("Welcome to the sudoku solver.");
		
		System.out.print("\nPlease enter a file name:  ");
		String fileName = in.next() + ".txt";
		
		boolean badFile = true;		
		while (badFile) {
			try {
				fin = new Scanner(new FileInputStream(fileName));
			} catch (FileNotFoundException e) {
				System.out.println(e);
				System.out.print("\nPlease reenter a file name:  ");
				fileName = in.next() + ".txt";
				continue;
			}			
			badFile = false;
		}
		
		int[][] grid = new int[9][9];
		
		for (int r = 0; r < 9; r++) {
			for (int c = 0; c < 9; c++) {
				grid[r][c] = fin.nextInt();
			}
			fin.nextLine();
		}
		fin.close();
				
		System.out.println("\nHere is the solution:");
		sudokuSolver(grid);
		printPuzzle(grid);		
	}
}
