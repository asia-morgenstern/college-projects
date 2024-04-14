/* PokerSolitaire - H9P5
 * 				  - runs the game Poker Solitaire
 * 				  - outputs statistics for all games played
 * 
 * Asia Morgenstern
 * 1 December 2021
 * DUE 6 December 2021
 */

import java.util.Scanner;

public class PokerSolitaire {

	public static Card[][] board = new Card[5][5];
	public static PokerHandEvaluator pEval = new PokerHandEvaluator();
	
	public static final int STRAIGHT_FLUSH_SCORE = 100;
	public static final int FOUR_OF_A_KIND_SCORE = 50;
	public static final int FULL_HOUSE_SCORE = 25;
	public static final int FLUSH_SCORE = 20;
	public static final int STRAIGHT_SCORE = 15;
	public static final int THREE_OF_A_KIND_SCORE = 10;
	public static final int TWO_PAIR_SCORE = 5;
	public static final int PAIR_SCORE = 2;
	public static final int BUST_SCORE = 0;
	
	public static Card[][] initBoard() {
		/* initBoard - initializes the board, a 2D array, to null
		 * 			 - returns a 2D array of Card objects
		 */
		
		for (int r = 0; r < 5; r++) {
			for (int c = 0; c < 5; c++) {
				board[r][c] = null;
			}
		}
		return board;
	}
	
	public static void printBoard() {
		/* printBoard - prints the board, a 2D array, with row and column numbers starting at 1
		 * 			  - if a Card is null, prints 2 spaces
		 */
		
		System.out.print("  ");
		for (int c = 0; c < 5; c++) {	
			System.out.print("  " + (c + 1));
		}	
		System.out.println("\n  +--+--+--+--+--+");
		
		for (int r = 0; r < 5; r++) {			
			System.out.print((r + 1) + " ");
			for (int c = 0; c < 5; c++) {
				if (board[r][c] == null) {
					System.out.print("|  ");
				} else {
					System.out.print("|" + board[r][c].toString());
				}
			}
			System.out.println("| " + (r + 1) + "\n  +--+--+--+--+--+");			
		}
		
		System.out.print("  ");
		for (int c = 0; c < 5; c++) {	
			System.out.print("  " + (c + 1));
		}	
	}
	
	public static int evaluateBoard() {
		/* evaluateBoard - evaluates the rows and columns of the board using PokerHandEvaluater
		 * 				 - returns total score of the board
		 */
		
		Hand h = new Hand();
		int score = 0;
		
		for (int r = 0; r < 5; r++) {
			for (int c = 0; c < 5; c++) {
				h.receiveCard(board[r][c]);
			}
			pEval.acceptHand(h);
			if (pEval.isStraightFlush()) {
				score += STRAIGHT_FLUSH_SCORE;
			} else if (pEval.isFourOfAKind()) {
				score += FOUR_OF_A_KIND_SCORE;
			} else if (pEval.isFullHouse()) {
				score += FULL_HOUSE_SCORE;
			} else if (pEval.isFlush()) {
				score += FLUSH_SCORE;
			} else if (pEval.isStraight()) {
				score += STRAIGHT_SCORE;
			} else if (pEval.isThreeOfAKind()) {
				score += THREE_OF_A_KIND_SCORE;
			} else if (pEval.isTwoPair()) {
				score += TWO_PAIR_SCORE;
			} else if (pEval.isOnePair()) {
				score += PAIR_SCORE;
			} else {
				score += BUST_SCORE;
			}
			h.clearHand();
		}
		
		for (int c = 0; c < 5; c++) {
			for (int r = 0; r < 5; r++) {
				h.receiveCard(board[r][c]);
			}
			pEval.acceptHand(h);
			if (pEval.isStraightFlush()) {
				score += STRAIGHT_FLUSH_SCORE;
			} else if (pEval.isFourOfAKind()) {
				score += FOUR_OF_A_KIND_SCORE;
			} else if (pEval.isFullHouse()) {
				score += FULL_HOUSE_SCORE;
			} else if (pEval.isFlush()) {
				score += FLUSH_SCORE;
			} else if (pEval.isStraight()) {
				score += STRAIGHT_SCORE;
			} else if (pEval.isThreeOfAKind()) {
				score += THREE_OF_A_KIND_SCORE;
			} else if (pEval.isTwoPair()) {
				score += TWO_PAIR_SCORE;
			} else if (pEval.isOnePair()) {
				score += PAIR_SCORE;
			} else {
				score += BUST_SCORE;
			}
			h.clearHand();
		}
		return score;
	}
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in); 
		Deck d = new Deck();
				
		Card card;		
		char confirm;		
		int r;
		int c;		
		char answer = 'N';
		
		int numGamesPlayed = 0;
		int numGamesWon = 0;
		double percentGamesWon = 0.0;
		int totalScore = 0;
		double avgScore = 0;
		int minScore = 1001;
		int maxScore = 0;
		
		System.out.println("Welcome to the game of Poker Solitaire!");		
		
		do {
			System.out.println("\nNew Game!");
			
			numGamesPlayed++;
			
			d.shuffle();
			initBoard();
			
			for (int turn = 1; turn <= 25; turn++) {
				System.out.println("\nYour board:");
				printBoard();
				
				card = d.nextCard();
				
				System.out.println("\n\nYour card is " + card.toString());
				
				do {
					System.out.println("Where would you like to put it?");
					System.out.print("  Row, 1 through 5:  ");
					r = in.nextInt();
					while (r < 1 || r > 5) {
						System.out.println("    Error:  Row must between 1 and 5");
						System.out.print("    Please reenter a row:  ");
						r = in.nextInt();
					}
					
					System.out.print("  Column, 1 through 5:  ");
					c = in.nextInt();
					while (c < 1 || c > 5) {
						System.out.println("    Error:  Column must between 1 and 5");
						System.out.print("    Please reenter a column:  ");
						c = in.nextInt();
					}
					
					if (board[r - 1][c - 1] != null) {
						System.out.println("    Error:  Card already at location");
						System.out.println("    Please choose a new location.");
						confirm = 'N';
						continue;
					}
					
					System.out.print("Please confirm your answer, Y or N:  ");
					confirm = in.next().toUpperCase().charAt(0);
					while (confirm != 'Y' && confirm != 'N') {
						System.out.println("  Error:    Cannot read confirmation");
						System.out.print("  Please reconfirm your answer, Y or N:  ");
						confirm = in.next().toUpperCase().charAt(0);
					}
				} while (confirm == 'N');
				
				board[r - 1][c - 1] = card;				
			}
			
			System.out.println("\nFinal Board");
			printBoard();
			
			int score = evaluateBoard();
			
			System.out.println("\n\nGame Over!");
			System.out.println("Your score is " + score);
			if (score >= 200) {
				System.out.println("  Congratulations!  You won!");
				numGamesWon++;
			} else {
				System.out.println("  Sorry, you didn't win this time.");
			}			
			
			if (score < minScore) {
				minScore = score;
			}
			if (score > maxScore) {
				maxScore = score;
			}
			totalScore += score;
			
			System.out.print("Would you like to play again?  ");
			answer = in.next().toUpperCase().charAt(0);
			while (answer != 'Y' && answer != 'N') {
				System.out.println("\n  Error:  Cannot read answer");
				System.out.print("  Please reenter your answer, Y or N:  ");
				confirm = in.next().toUpperCase().charAt(0);
			}			
		} while (answer == 'Y');
				
		percentGamesWon = ((double)numGamesWon/numGamesPlayed)*100;		
		avgScore = (double)totalScore/numGamesPlayed;
				
		System.out.println("\nGame Statistics:");
		System.out.println("  Games Played:  " + numGamesPlayed);
		System.out.println("  Games Won:  " + numGamesWon);
		System.out.println("  Percent of Games Won:  " + percentGamesWon + "%");
		System.out.println("  Average Score:  " + avgScore);
		System.out.println("  Min Score:  " + minScore);
		System.out.println("  Max Score:  " + maxScore);
		
	}
}
