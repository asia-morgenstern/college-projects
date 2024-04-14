/* SudokuPuzzle - project 3
 * 				- creates a sudoku playing app GUI
 * 
 * Asia Morgenstern
 * 5 April 2022
 * DUE 22 April 2022
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import java.util.Random;

public class SudokuPuzzle extends JFrame implements ActionListener {
		
	private SudokuGenerator puzzleGrid = new SudokuGenerator();
	private SudokuSquare[][] squares = new SudokuSquare[9][9];
	private int selectedSquare_R;
	private int selectedSquare_C;
		
	private final Font labelFont = new Font("Times New Roman", Font.PLAIN, 20);
	private final Color highlightColor = new Color(217, 245, 255);
	private final Color hintColor = new Color(0, 153, 0);
	private final Color correctColor = new Color(187, 247, 201);
	private final Color errorColor = new Color(255, 185, 148);
	
	private final Font buttonFont1 = new Font("Times New Roman", Font.PLAIN, 18);
	private final Font buttonFont2 = new Font("Times New Roman", Font.BOLD, 18);
	
	private Random rnd = new Random();

	public SudokuPuzzle() {
		// SudokuPuzzle - creates a sudoku game app
			
		setSize(1000, 500);
		setLocation(175, 100);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Sudoku Puzzle");
		
		// create/design sudoku board
		JPanel leftSide = new JPanel();
		JPanel board = new JPanel();
		
		createNewGame();
		
		JPanel first = new JPanel();
		JPanel second = new JPanel();
		JPanel third = new JPanel();
		JPanel fourth = new JPanel();
		JPanel fifth = new JPanel();
		JPanel sixth = new JPanel();
		JPanel seventh = new JPanel();
		JPanel eighth = new JPanel();
		JPanel ninth = new JPanel();
		
		first.setBackground(Color.BLACK);
		first.setLayout(new GridLayout(3, 3, 3, 3));
		second.setBackground(Color.BLACK);
		second.setLayout(new GridLayout(3, 3, 3, 3));
		third.setBackground(Color.BLACK);
		third.setLayout(new GridLayout(3, 3, 3, 3));
		fourth.setBackground(Color.BLACK);
		fourth.setLayout(new GridLayout(3, 3, 3, 3));
		fifth.setBackground(Color.BLACK);
		fifth.setLayout(new GridLayout(3, 3, 3, 3));
		sixth.setBackground(Color.BLACK);
		sixth.setLayout(new GridLayout(3, 3, 3, 3));
		seventh.setBackground(Color.BLACK);
		seventh.setLayout(new GridLayout(3, 3, 3, 3));
		eighth.setBackground(Color.BLACK);
		eighth.setLayout(new GridLayout(3, 3, 3, 3));
		ninth.setBackground(Color.BLACK);
		ninth.setLayout(new GridLayout(3, 3, 3, 3));
				
		for (int row = 0; row < 9; row++) {
			for (int column = 0; column < 9; column++) {
				int r = row/3;								// determines which 3x3 box
				int c = column/3;
				if (r == 0 && c == 0) {
					first.add(squares[row][column].labelPanel);
				} else if (r == 0 && c == 1) {
					second.add(squares[row][column].labelPanel);
				} else if (r == 0 && c == 2) {
					third.add(squares[row][column].labelPanel);
				} else if (r == 1 && c == 0) {
					fourth.add(squares[row][column].labelPanel);
				} else if (r == 1 && c == 1) {
					fifth.add(squares[row][column].labelPanel);
				} else if (r == 1 && c == 2) {
					sixth.add(squares[row][column].labelPanel);
				} else if (r == 2 && c == 0) {
					seventh.add(squares[row][column].labelPanel);
				} else if (r == 2 && c == 1) {
					eighth.add(squares[row][column].labelPanel);
				} else if (r == 2 && c == 2) {
					ninth.add(squares[row][column].labelPanel);
				}
			}
		}
		
		board.setBackground(Color.BLACK);
		board.setLayout(new GridLayout(3, 3, 5, 6));
		board.add(first);
		board.add(second);
		board.add(third);
		board.add(fourth);
		board.add(fifth);
		board.add(sixth);
		board.add(seventh);
		board.add(eighth);
		board.add(ninth);
		
		leftSide.setLayout(new BorderLayout());
		leftSide.add(new JPanel(), BorderLayout.NORTH);
		leftSide.add(new JPanel(), BorderLayout.SOUTH);
		leftSide.add(new JPanel(), BorderLayout.EAST);
		leftSide.add(new JPanel(), BorderLayout.WEST);
		leftSide.add(board);		
		
		// create/design "game info"
		JPanel gameInfo = new JPanel();
		
		JLabel titleLabel = new JLabel("SUDOKU");
		titleLabel.setFont(new Font("Times New Roman", Font.BOLD, 30));
		titleLabel.setHorizontalAlignment(SwingConstants.CENTER);
		
		JButton newGameButton = new JButton("New Game");
		newGameButton.addActionListener(this);
		newGameButton.setFont(buttonFont2);
		JButton resetGameButton = new JButton("Reset Game");
		resetGameButton.addActionListener(this);
		resetGameButton.setFont(buttonFont2);
		
		gameInfo.setLayout(new GridLayout(3, 1, 0, 7));
		gameInfo.add(titleLabel);
		gameInfo.add(newGameButton);
		gameInfo.add(resetGameButton);
		
		// create/design "keypad"
		JPanel keypad = new JPanel();
		
		JButton oneButton = new JButton("1");
		oneButton.addActionListener(this);
		oneButton.setFont(buttonFont1);
		JButton twoButton = new JButton("2");
		twoButton.addActionListener(this);
		twoButton.setFont(buttonFont1);
		JButton threeButton = new JButton("3");
		threeButton.addActionListener(this);
		threeButton.setFont(buttonFont1);
		JButton fourButton = new JButton("4");
		fourButton.addActionListener(this);
		fourButton.setFont(buttonFont1);
		JButton fiveButton = new JButton("5");
		fiveButton.addActionListener(this);
		fiveButton.setFont(buttonFont1);
		JButton sixButton = new JButton("6");
		sixButton.addActionListener(this);
		sixButton.setFont(buttonFont1);
		JButton sevenButton = new JButton("7");
		sevenButton.addActionListener(this);
		sevenButton.setFont(buttonFont1);
		JButton eightButton = new JButton("8");
		eightButton.addActionListener(this);
		eightButton.setFont(buttonFont1);
		JButton nineButton = new JButton("9");
		nineButton.addActionListener(this);
		nineButton.setFont(buttonFont1);
		
		JButton clearButton = new JButton("Clear Cell");
		clearButton.addActionListener(this);
		clearButton.setFont(buttonFont2);
		JButton hintButton = new JButton("Hint");
		hintButton.addActionListener(this);
		hintButton.setFont(buttonFont2);
		JButton checkButton = new JButton("Check");
		checkButton.addActionListener(this);
		checkButton.setFont(buttonFont2);
		
		keypad.setLayout(new GridLayout(4, 3));
		keypad.add(oneButton);
		keypad.add(twoButton);
		keypad.add(threeButton);
		keypad.add(fourButton);
		keypad.add(fiveButton);
		keypad.add(sixButton);
		keypad.add(sevenButton);
		keypad.add(eightButton);
		keypad.add(nineButton);
		
		keypad.add(clearButton);
		keypad.add(hintButton);
		keypad.add(checkButton);		
		
		// format right side
		JPanel right = new JPanel();
		right.setLayout(new GridLayout(2, 1, 0, 15));
		right.add(gameInfo);
		right.add(keypad);
		
		JPanel rightSide = new JPanel();
		rightSide.setLayout(new BorderLayout());
		rightSide.add(new JPanel(), BorderLayout.NORTH);
		rightSide.add(new JPanel(), BorderLayout.SOUTH);
		rightSide.add(new JPanel(), BorderLayout.EAST);
		rightSide.add(new JPanel(), BorderLayout.WEST);
		rightSide.add(right);
		
		// format GUI
		setLayout(new GridLayout(1, 2, 50, 0));
		add(leftSide);
		add(rightSide);
	}
	
	public void actionPerformed(ActionEvent e) {
		/* actionPerformed - performs an action
		 * 
		 * e - an action event
		 */
		
		if (e.getActionCommand().equals("New Game")) {
			createNewGame();
		} else if (e.getActionCommand().equals("Reset Game")) {
			resetPuzzle();
		} else if (e.getActionCommand().equals("Clear Cell")) {
			clearSquare();
		} else if (e.getActionCommand().equals("Hint")) {
			showHint();
		} else if (e.getActionCommand().equals("Check")) {
			checkPuzzle();
		} else {
			if (selectedSquare_R >= 0 && selectedSquare_C >= 0) {
				placeNumber(e.getActionCommand());
			}
		}
	}
	
	private void createNewGame() {
		// createNewGame - creates a new game
		
		puzzleGrid.setSymmetry(rnd.nextInt(2)%2 == 0);
		puzzleGrid.setValsInPuzzle(rnd.nextInt(63) + 1);
		puzzleGrid.generatePuzzle();
		
		int[][] puzzle = puzzleGrid.getPuzzle();
		int[][] solution = puzzleGrid.getSolution();
		
		for (int r = 0; r < 9; r++) {
			for (int c = 0; c < 9; c++) {
				if (squares[r][c] == null) {
					squares[r][c] = new  SudokuSquare(puzzle[r][c], solution[r][c]);
				} else {
					squares[r][c].resetSquare(puzzle[r][c], solution[r][c]);
				}
			}
		}
		selectedSquare_R = -1;
		selectedSquare_C = -1;
	}
	
	private void resetPuzzle() {
		// resetPuzzle - resets the puzzle to initial state
		
		for (int r = 0; r < 9; r++) {
			for (int c = 0; c < 9; c++) {
				if (squares[r][c].canChange) {
					squares[r][c].label.setText(" ");
				}
				squares[r][c].labelPanel.setBackground(Color.WHITE);
			}
		}
		selectedSquare_R = -1;
		selectedSquare_C = -1;
	}
	
	private void clearSquare() {
		// clearSquare - clears value in changeable squares
		
		if (selectedSquare_R >= 0 && selectedSquare_C >= 0 && squares[selectedSquare_R][selectedSquare_C].canChange) {
			squares[selectedSquare_R][selectedSquare_C].label.setText(" ");
		}
	}
	
	private boolean isComplete() {
		// isComplete - returns true if the puzzle is complete and correct, false otherwise
		
		for (int r = 0; r < 9; r++) {
			for (int c = 0; c < 9; c++) {
				if (squares[r][c].label.getText().equals(" ")) {
					return false;
				}				
				if (!squares[r][c].label.getText().equals(squares[r][c].solVal + "")) {
					return false;
				}
			}
		}
		return true;
	}
	
	private void showHint() {
		// showHint - randomly adds a solution value to the puzzle
		
		if (!isComplete()) {
			int r, c;
			do {
				r = rnd.nextInt(9);
				c = rnd.nextInt(9);
			} while (!squares[r][c].canChange && !squares[r][c].label.getText().equals(" "));
			
			squares[r][c].label.setText(squares[r][c].solVal + "");
			squares[r][c].label.setForeground(hintColor);
		}
	}
	
	private void checkPuzzle() {
		/* checkPuzzle - checks puzzle
		 * 			   - highlights corrects answers in green, incorrect in red/orange
		 */
		
		for (int r = 0; r < 9; r++) {
			for (int c = 0; c < 9; c++) {
				if (squares[r][c].label.getText().equals(" ")) {
					continue;
				}
				if (Integer.parseInt(squares[r][c].label.getText()) != squares[r][c].solVal) {
					squares[r][c].labelPanel.setBackground(errorColor);
				} else {
					squares[r][c].labelPanel.setBackground(correctColor);
				}
			}
		}
		if (isComplete()) {
			JOptionPane.showMessageDialog(this, "Puzzle successfully completed!", "Puzzle Complete", JOptionPane.INFORMATION_MESSAGE);
		}
	}
	
	private void labelClicked() {
		/* labelClicked - saves the indices into the array
		 * 				- used clearSquare() and placeNumber()
		 */
		
		for (int r = 0; r < 9; r++) {
			for (int c = 0; c < 9; c++) {
				if (squares[r][c].labelPanel.getBackground().equals(highlightColor)) {
					selectedSquare_R = r;
					selectedSquare_C = c;
				}
			}
		}
	}
	
	private void placeNumber(String val) {
		/* placeNumber - places a number in the selected square
		 * 			   - relies on a square being clicked FIRST
		 * 
		 * val - a value to be placed in a sudoku square as a String
		 */

		if (squares[selectedSquare_R][selectedSquare_C].canChange) {
			squares[selectedSquare_R][selectedSquare_C].label.setText(val);
			squares[selectedSquare_R][selectedSquare_C].label.setForeground(Color.RED);
		}
	}
	
	private class SudokuSquare {
		// saves information about each square
		
		private int val;
		private int solVal;
		private boolean canChange;
		
		private JLabel label;
		private JPanel labelPanel;
		
		public SudokuSquare(int puzzleVal, int solutionVal) {
			/* SudokuSquare - creates a sudoku square
			 * 
			 * puzzleVal - original puzzle value, 0-9
			 * solutionVal - solution value, 1-9
			 */
			
			val = puzzleVal;
			solVal = solutionVal;
			canChange = (val == 0);
			if (canChange) {
				label = new JLabel(" ");
				label.setForeground(Color.RED);
			} else {
				label = new JLabel(val + "");
			}
			
			labelPanel = new JPanel();
			labelPanel.setBackground(Color.WHITE);
			labelPanel.setLayout(new GridLayout());
			
			label.setBackground(Color.WHITE);
			label.setFont(labelFont);
			label.setHorizontalAlignment(SwingConstants.CENTER);
			
			label.addMouseListener(new MouseAdapter() {
				// lets the label be clickable
				
				public void mouseClicked(MouseEvent e) {
					/* mouseClicked - adds attention to the clicked square
					 * 				- sets labelPanel to highlightColor
					 * 
					 * e - a mouse event
					 */
					
					for (int r = 0; r < 9; r++) {
						for (int c = 0; c < 9; c++) {
							if (squares[r][c].labelPanel.getBackground().equals(errorColor)) {
								continue;
							}
							squares[r][c].labelPanel.setBackground(Color.WHITE);
						}
					}
					labelPanel.setBackground(highlightColor);
					labelClicked();
				}
			});
			
			labelPanel.add(label);
		}
		
		public void resetSquare(int puzzleVal, int solutionVal) {
			/* resetSquare - resets a square
			 * 			   - used when a new puzzle is generated
			 * 
			 * puzzleVal - original puzzle value, 0-9
			 * solutionVal - solution value, 1-9
			 */
			
			val = puzzleVal;
			solVal = solutionVal;
			canChange = (val == 0);
			if (canChange) {
				label.setText(" ");
				label.setForeground(Color.RED);
			} else {
				label.setText(val + "");
				label.setForeground(Color.BLACK);
			}
		}
	}
	
	public static void main(String[] args) {
		SudokuPuzzle window = new SudokuPuzzle();
		window.setVisible(true);
	}
}
