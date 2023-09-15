// Assignment_1.cpp : Defines the entry point for the application.
//

#include "Temp.h"
#include "Cards.h"

#include "Assignment_1.h"





using namespace std;

int main()
{
	cout << "Hello CMake.\n" << endl;

	// Test the creation of deck, hand, cards.
	Deck testDeck = Deck();

	Hand testHand = Hand();
	Player testPlayer = Player(&testHand);

	Card cardTestUnowned = Card(&testDeck);
	Card cardTestUnowned2 = Card(&testDeck);
	Card cardTestUnowned3 = Card(&testDeck);
	Card cardTestUnowned4 = Card(&testDeck);
	Card cardTestUnowned5 = Card(&testDeck);

	Card cardTestOwned = Card(testPlayer.myHand, &testDeck);

	testDeck.printCards();
	testHand.printCards();

	// Test Play()
	cout << "\n\nNow testing play().\n" << endl;
	cardTestOwned.play();
	testDeck.printCards();
	testHand.printCards();

	// Test Draw()
	cout << "\n\nNow testing draw().\n" << endl;
	testDeck.draw(&testHand);
	testDeck.printCards();
	testHand.printCards();


	return 0;
};
