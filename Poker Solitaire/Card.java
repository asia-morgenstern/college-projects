/* Card - H8P6
 * 		- creates a card, to be used by the Deck class
 * 		- saved in CS151\AllHomework
 * 
 * Asia Morgenstern
 * 16 November 2021
 * DUE 18 November 2021
 */

public class Card {

	public static final int CLUBS = 1;
	public static final int DIAMONDS = 2;
	public static final int HEARTS = 3;
	public static final int SPADES = 4;
	
	private int suit;	// 1 = clubs, 2 = diamonds, 3 = hearts, 4 = spades
	private int rank;	// 1 = ace, 2 – 10 = face value, 11 = jack, 12 = queen, 13 = king
	
	public Card(int s, int r) {
		/* Card - creates a card given s and r
		 * 
		 * s - card suit
		 * r - card rank
		 */
		
		suit = s;
		rank = r;
		badCard();
	}
	
	public Card(int num) {
		/* Card - creates a card given a number num
		 * 
		 * num - card number
		 */
		
		suit = num/13 + 1;
		rank = num%13 + 1;
		badCard();
	}
	
	public Card(Card c) {
		/* Card - creates a copy of a card given Card c
		 * 
		 * c - another card
		 */
		
		if (c == null) {
			System.out.println("Fatal Error:  Card c does not exist");
			System.exit(0);
		}
		this.suit = c.suit;
		this.rank = c.rank;
	}
	
	public int getSuit() {
		// getSuit - returns the card suit
		
		return suit;
	}
	
	public int getRank() {
		// getRank - returns the card rank
		
		return rank;
	}
	
	public String toString() {
		// toString - returns the rank and suit of the card
		
		String card = "";
		switch (rank) {
		case 1: card = "A";
			break;
		case 10: card = "T";
			break;
		case 11: card = "J";
			break;
		case 12: card = "Q";
			break;
		case 13: card = "K";
			break;
		default: card = rank + "";
			break;
		}
		switch (suit) {
		case 1: card += "C";
			break;
		case 2: card += "D";
			break;
		case 3: card += "H";
			break;
		case 4: card += "S";
			break;
		}
		return card;
	}
	
	public boolean equals(Card c) {
		/* equals - returns true if this card is the same as card c, false if not
		 * 
		 * c - another card
		 */
		
		if (c == null) {
			System.out.println("Fatal Error:  Card c does not exist");
			System.exit(0);
		}
		return (this.suit == c.suit && this.rank == c.rank);
	}
	
	private void badCard() {
		/* badCard - determines if a given card is not valid
		 * 		   - a card is not valid if suit is not between 1 and 4 or if rank is not between 1 and 13
		 */
		
		if (suit < 1 || suit > 4) {
			System.out.println("Fatal Error:  Invalid suit, suit = " + suit);
			System.out.println("  Suit must be between 1 and 4");
			System.exit(0);
		}
		if (rank < 1 || rank > 13) {
			System.out.println("Fatal Error:  Invalid rank, rank = " + rank);
			System.out.println("  Rank must be between 1 and 13");
			System.exit(0);
		}
	}
}
