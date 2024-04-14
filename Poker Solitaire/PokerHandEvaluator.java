/* PokerHandEvaluator - evaluates a 5 card hand and determines which type of poker hand it is
 * 					  - H8P6
 * 
 * Asia Morgenstern
 * 20 November 2021
 * DUE 29 November 2021
 */

public class PokerHandEvaluator {
	
	private Hand hand;
	
	private boolean straightFlush;
	private boolean fourOfAKind;
	private boolean fullHouse;
	private boolean flush;
	private boolean straight;
	private boolean threeOfAKind;
	private boolean twoPair;
	private boolean onePair;
	private boolean bust;
	
	public void acceptHand(Hand h) {
		/* acceptHand - takes in hand h
		 * 			  - determines the type of poker hand it is
		 * 
		 * h - hand
		 */
		
		straightFlush = false;
		fourOfAKind = false;
		fullHouse = false;
		flush = false;
		straight = false;
		threeOfAKind = false;
		twoPair = false;
		onePair = false;
		bust = false;
		
		hand = h;
		hand.sortHand();
		if (checkIsStraightFlush()) {
			straightFlush = true;
		} else if (checkIsFourOfAKind()) {
			fourOfAKind = true;
		} else if (checkIsFullHouse()) {
			fullHouse = true;
		} else if (checkIsFlush()) {
			flush = true;
		} else if (checkIsStraight()) {
			straight = true;
		} else if (checkIsThreeOfAKind()) {
			threeOfAKind = true;
		} else if (checkIsTwoPair()) {
			twoPair = true;
		} else if (checkIsOnePair()) {
			onePair = true;
		} else {
			bust = true;
		} 
	}
	
	public boolean isStraightFlush() {
		// isStraightFlush - returns if a hand is a straight flush
		
		return straightFlush;
	}
	
	public boolean isFourOfAKind() {
		// isFourOfAKind - returns if a hand is a four of a kind
		
		return fourOfAKind;
	}
	
	public boolean isFullHouse() {
		// isFullHouse - returns if a hand is a full house
		
		return fullHouse;
	}
	
	public boolean isFlush() {
		// isFlush - returns if a hand is a flush
		
		return flush;
	}
	
	public boolean isStraight() {
		// isStraight - returns if a hand is a straight
		
		return straight;
	}
	
	public boolean isThreeOfAKind() {
		// isThreeOfAKind - returns if a hand is a three of a Kind
		
		return threeOfAKind;
	}
	
	public boolean isTwoPair() {
		// isTwoPair - returns if a hand is a two pair
		
		return twoPair;
	}
	
	public boolean isOnePair() {
		// isOnePair - returns if a hand is a one pair
		
		return onePair;
	}
	
	public boolean isBust() {
		// isBust - returns if a hand is 
		
		return bust;
	}
	
	private boolean checkIsStraightFlush() {
		/* checkIsStraightFlush - checks if hand is a straight flush
		 * 						- returns true if it is, false if not
		 */
		
		for (int i = 1; i < hand.getHandSize(); i++) {			
			if (hand.getCard(i).getSuit() != hand.getCard(i + 1).getSuit()) {
				return false;
			}
		}
		
		if (hand.getCard(1).getRank() == 1 && hand.getCard(2).getRank() != 2 && hand.getCard(2).getRank() != 10) {
			return false;
		} else if (hand.getCard(1).getRank() == 1 && hand.getCard(2).getRank() == 10) {			
			for (int i = 2; i < hand.getHandSize(); i++) {
				if (hand.getCard(i).getRank() != hand.getCard(i + 1).getRank() - 1) {
					return false;
				}
			}
			return true;
		}
		
		for (int i = 1; i < hand.getHandSize(); i++) {	
			if (hand.getCard(i).getRank() != hand.getCard(i + 1).getRank() - 1) {
				return false;
			}
		}
		return true;
	}
	
	private boolean checkIsFourOfAKind() {
		/* checkIsFourOfAKind - checks if hand is a four of a kind
		 * 					  - returns true if it is, false if not
		 */
		
		int i = 1;
		int rank1 = hand.getCard(i).getRank();
		int numRank2 = 0;
		for (i = 2; i <= hand.getHandSize(); i++) {
			if (hand.getCard(i).getRank() != rank1) {
				int rank2 = hand.getCard(i).getRank();
				numRank2++;
				for (int j = i + 1; j <= hand.getHandSize(); j++) {
					if (hand.getCard(j).getRank() != rank1 && hand.getCard(j).getRank() != rank2) {
						return false;
					}
				}
			}			
		}
		if (numRank2 > 1 && numRank2 != 4) {
			return false;
		} else {
			return true;
		}
	}
	
	private boolean checkIsFullHouse() {
		/* checkIsFullHouse - checks if hand is a full house
		 * 					- returns true if it is, false if not
		 */
		
		int i = 1;
		int rank1 = hand.getCard(i).getRank();
		for (i = 2; i <= hand.getHandSize(); i++) {
			if (hand.getCard(i).getRank() != rank1) {
				int rank2 = hand.getCard(i).getRank();
				for (int j = i + 1; j <= hand.getHandSize(); j++) {
					if (hand.getCard(j).getRank() != rank1 && hand.getCard(j).getRank() != rank2) {
						return false;
					}
				}
				break;
			}			
		}
		return true;
	}
	
	private boolean checkIsFlush() {
		/* checkIsFlush - checks if hand is a flush
		 * 				- returns true if it is, false if not
		 */
		
		for (int i = 1; i < hand.getHandSize(); i++) {			
			if (hand.getCard(i).getSuit() != hand.getCard(i + 1).getSuit()) {
				return false;
			}
		}
		return true;
	}
	
	private boolean checkIsStraight() {
		/* checkIsStraight - checks if hand is a straight
		 * 				   - returns true if it is, false if not
		 */
		
		if (hand.getCard(1).getRank() == 1 && hand.getCard(2).getRank() != 2 && hand.getCard(2).getRank() != 10) {
			return false;
		} else if (hand.getCard(1).getRank() == 1 && hand.getCard(2).getRank() == 10) {			
			for (int i = 2; i < hand.getHandSize(); i++) {
				if (hand.getCard(i).getRank() != hand.getCard(i + 1).getRank() - 1) {
					return false;
				}
			}
			return true;
		}
		
		for (int i = 1; i < hand.getHandSize(); i++) {	
			if (hand.getCard(i).getRank() != hand.getCard(i + 1).getRank() - 1) {
				return false;
			}
		}
		return true;
	}
	
	private boolean checkIsThreeOfAKind() {
		/* checkIsThreeOfAKind - checks if hand is a three of a kind
		 * 					   - returns true if it is, false if not
		 */
		
		int numCardsLeft = hand.getHandSize();
		for (int i = 1; i <= numCardsLeft; i++) {
			if (hand.getCard(i).getRank() != hand.getCard(i + 1).getRank()) {
				numCardsLeft--;				
			} else {
				if (hand.getCard(i + 1).getRank() == hand.getCard(i + 2).getRank()) {
					return true;
				} else {
					numCardsLeft--;
				}
			}
		}
		return false;
	}
	
	private boolean checkIsTwoPair() {
		/* checkIsTwoPair - checks if hand is a two pair
		 * 				  - returns true if it is, false if not
		 */
		
		for (int i = 1; i < hand.getHandSize(); i++) {
			if (hand.getCard(i).getRank() == hand.getCard(i + 1).getRank()) {
				for (int j = i + 2; j < hand.getHandSize(); j++) {
					if(hand.getCard(j).getRank() == hand.getCard(j + 1).getRank()) {
						return true;
					}
				}
			}
		}
		return false;
	}
	
	private boolean checkIsOnePair() {
		/* checkIsOnePair - checks if hand is a one pair
		 * 				  - returns true if it is, false if not
		 */
		
		for (int i = 1; i < hand.getHandSize(); i++) {
			if (hand.getCard(i).getRank() == hand.getCard(i + 1).getRank()) {
				return true;
			}
		}
		return false;
	}
	
	public static void main(String[] args) {
		PokerHandEvaluator p = new PokerHandEvaluator();
		Deck d = new Deck();
		Hand h = new Hand();
		
		int numStraightFlush = 0;
		int numFourOfAKind= 0;
		int numFullHouse = 0;
		int numFlush = 0;
		int numStraight = 0;
		int numThreeOfAKind = 0;
		int numTwoPair = 0;
		int numOnePair = 0;
		int numBust = 0;
		
		for (int game = 1; game <= 1000000; game++) {
			h.clearHand();
			d.shuffle();
			for (int i = 0; i < h.getHandSize(); i++) {
				h.receiveCard(d.nextCard());
			}

			p.acceptHand(h);
			
			if (p.isStraightFlush()) {
				numStraightFlush++;
			} else if (p.isFourOfAKind()) {
				numFourOfAKind++;
			} else if (p.isFullHouse()) {
				numFullHouse++;
			} else if (p.isFlush()) {
				numFlush++;
			} else if (p.isStraight()) {
				numStraight++;
			} else if (p.isThreeOfAKind()) {
				numThreeOfAKind++;
			} else if (p.isTwoPair()) {
				numTwoPair++;
			} else if (p.isOnePair()) {
				numOnePair++;
			} else {
				numBust++;
			}			
		}
		
		double percentStraightFlush = (double)numStraightFlush/10000;
		double percentFourOfAKind= (double)numFourOfAKind/10000;
		double percentFullHouse = (double)numFullHouse/10000;
		double percentFlush= (double)numFlush/10000;
		double percentStraight= (double)numStraight/10000;
		double percentThreeOfAKind = (double)numThreeOfAKind/10000;
		double percentTwoPair = (double)numTwoPair/10000;
		double percentOnePair = (double)numOnePair/10000;
		double percentBust = (double)numBust/10000;		
		
		System.out.println("Outcome for Each Type of Poker Hand");
		System.out.println("  Straight Flush:  " + numStraightFlush + "  (" + percentStraightFlush + "%)");
		System.out.println("  Four of a Kind:  " + numFourOfAKind + "  (" + percentFourOfAKind + "%)");
		System.out.println("  Full House:  " + numFullHouse + "  (" + percentFullHouse + "%)");
		System.out.println("  Flush:  " + numFlush + "  (" + percentFlush + "%)");
		System.out.println("  Straight:  " + numStraight + "  (" + percentStraight + "%)");
		System.out.println("  Three of a Kind:  " + numThreeOfAKind + "  (" + percentThreeOfAKind + "%)");
		System.out.println("  Two Pair:  " + numTwoPair + "  (" + percentTwoPair + "%)");
		System.out.println("  One Pair:  " + numOnePair + "  (" + percentOnePair + "%)");
		System.out.println("  Bust:  " + numBust + "  (" + percentBust + "%)");		
	}

}
