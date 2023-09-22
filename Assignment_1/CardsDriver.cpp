#pragma once

#include "CardsDriver.h"

using namespace std;

// You must deliver a file named CardsDriver.cpp file that contains a free function named testCards() that creates a deck of Warzone cards, then create a hand object that is filled by drawing cards from the deck.
// A free function named testCards() that creates a deck of cards of all different kinds, then creates a hand object that is filled by drawing cards from the deck by repeatedly calling its draw() method, then calls the play() method of all cards in the hand, resulting in the cards being put back in the deck.

// Written by Roxane Morin, 40191881.


void testCards()
{
	cout << "\nTesting in CardsDriver :)\n" << endl;
	
	// Create the deck.
	Deck testDeck = Deck();

	// Populate it.
	Card cardTest = Card(&testDeck);
	cout << "It is a generic card of the base class.\n" << endl;

	Card_Bomb cardBombTest = Card_Bomb(&testDeck);
	Card_Reinforcement cardReinforcementTest = Card_Reinforcement(&testDeck);
	Card_Blockade cardBlockadeTest = Card_Blockade(&testDeck);
	Card_Airlift carAirliftTest = Card_Airlift(&testDeck);
	Card_Diplomacy carDiplomacyTest = Card_Diplomacy(&testDeck);

	// Print the contents of the deck.
	testDeck.printCards();


	// Create the hand & show its information..
	Hand testHand = Hand();
	testHand.printCards();

	// Fill it up by drawing.
	cout << "\nDrawing all cards to fill up the hand:\n" << endl;
	testDeck.draw(&testHand);
	testDeck.draw(&testHand);
	testDeck.draw(&testHand);
	testDeck.draw(&testHand);
	testDeck.draw(&testHand);
	testDeck.draw(&testHand);
	testDeck.draw(&testHand);

	// Show hand and deck information.
	testDeck.printCards();
	testHand.printCards();


	// Play all of the hand's cards to put them back in the deck.
	cout << "\Playing all cards to empty the hand:\n" << endl;
	for (Card* card : testHand.returnMyCards())
	{
		card->play();
	}

	// Show hand and deck information.
	testDeck.printCards();
	testHand.printCards();


	// Test Deck's copy constructor.
	Deck copyDeck = Deck(testDeck);

	cout << "Now printing the copied deck:" << endl;
	copyDeck.printCards();

	// Test Card's copy constructor.
	Card_Bomb copyCardBomb = Card_Bomb(cardBombTest);

	// Test Hand's copy constructor.
	Hand copyHand = Hand(testHand);
	cout << "Now printing the copied hand:" << endl;
	copyHand.printCards();
};


// My old test sequence.
/*
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
	*/