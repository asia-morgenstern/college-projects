/* Deck - H8P6
 * 		- creates a deck of cards, uses the Card class
 * 		- saved in CS151\AllHomework
 * 
 * Asia Morgenstern
 * 16 November 2021
 * DUE 18 November 2021
 */

import java.util.Random;

public class Deck {

	private Card[] cards;	// stores 52 Card objects
	private int nextCard;	// represents the array's index, starts at 0, ends at 51
	
	public Deck() {
		// Deck - creates an array of Card objects
		
		cards = new Card[52];
		int i = 0;
		for (int suit = 1; suit <= 4; suit++) {
			int rank = 1;
			while (rank <= 13) {
				cards[i] = new Card(suit, rank);
				rank++;
				i++;
			}
		}
		nextCard = 0;
	}
	
	public void shuffle() {
		/* shuffle - randomizes the cards in the deck
		 * 		   - resets nextCard to 0
		 */
		
		Random rnd = new Random();
		for (int i = 1; i <= 51; i++) {
			int j = rnd.nextInt(i);
			Card tempCard = cards[i];
			cards[i] = cards[j];
			cards[j] = tempCard;
		}
		nextCard = 0;
	}
	
	public Card nextCard() {
		/* nextCard - returns the next Card in the deck
		 * 			- returns null if there is no next card
		 */
		
		if (nextCard < 52) {
			nextCard++;
			return cards[nextCard - 1];
		} else {
			return null;
		}
	}
	
	public int numLeft() {
		// numLeft - returns the number of remaining cards
		
		return (52 - nextCard);
	}
	
	public boolean hasCard() {
		/* hasCard - determines if the deck still has cards to be dealt
		 * 		   - returns true if there are any remaining cards, false if not
		 */
		
		return (nextCard < 52);
	}
	
	public String toString() {
		// toString - returns the remaining cards in the deck
		
		String remaining = "";
		for (int i = nextCard; i <= 50; i++) {
			remaining += cards[i] + ", ";
		}
		return (remaining += cards[51]);
	}
	
}
