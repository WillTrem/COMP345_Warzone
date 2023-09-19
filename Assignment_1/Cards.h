#pragma once

#include <iostream>
#include <vector>

// PART 4.
// 
// Implement a group of C++ classes that implements a deck and hand of Warzone cards. 
// All the classes / functions that you implement for this component must all reside in a single.cpp / .h file duo named Cards.cpp / Cards.h.

// Written by Roxane Morin, 40191881.


// VS got prickly if I didn't list these beforehand.
class Card;
class Hand;
class Deck;


// CARDS
class Card
{
	private:
	// Pointer to the deck the card belong's to.
	Deck* myDeck = nullptr;
	// Pointer to the card's current owner. 
	Hand* currentOwner = nullptr; // When the card is in the main deck, set to null.

	public:
	Deck* getMyDeck();
	// Get and set the card's current owner, if any.
	Hand* getOwningHand();
	void setOwningHand(Hand* owner);
		
	// Returns whether the card is currently in a player's hand. 
	bool isOwned();

	// Constructors.
	Card(Deck* deck);
	Card(Hand* owner, Deck* deck);

	// Destructor.
	~Card();

	// Base play() method. 
	// Each card has a play() method that enables a player to use it during game play by creating special orders. Once a card has been played, it is removed from the handand put back into the deck.
	virtual void play(); // What level of privacy should it have?
};

// Each card has a type from: bomb, reinforcement, blockade, airlift and diplomacy.
// Making these into different child classes as I imagine they'll have different purposes.
class Card_Bomb : public Card
{
	public:
	Card_Bomb(Deck* deck);
	Card_Bomb(Hand* owner, Deck* deck);
	void play();
};

class Card_Reinforcement : public Card
{
	public:
	Card_Reinforcement(Deck* deck);
	Card_Reinforcement(Hand* owner, Deck* deck);
	void play();
};

class Card_Blockade : public Card
{
	public:
	Card_Blockade(Deck* deck);
	Card_Blockade(Hand* owner, Deck* deck);
	void play();
};

class Card_Airlift : public Card
{
	public:
	Card_Airlift(Deck* deck);
	Card_Airlift(Hand* owner, Deck* deck);
	void play();
};

class Card_Diplomacy : public Card
{
	public:
	Card_Diplomacy(Deck* deck);
	Card_Diplomacy(Hand* owner, Deck* deck);
	void play();
};


// A Hand object is a finite collection of Warzone cards.
class Hand
{
	private:
	//Vector containing pointers to the cards currently in hand.
	std::vector<Card*> myCards;

	public:
	Hand();
	~Hand();

	void addCard(Card* card);
	void removeCard(Card* card);
	void printCards();
	std::vector<Card*> returnMyCards();
};


// DECK
class Deck
{
	// A Deck object contains a finite collection of Warzone cards.

	private:
	// Vector containing the addresses of all existing cards, no matter who is holding them.
	std::vector<Card*> allCards;
	// Vector containing the addresses of the cards currently in the deck.
	std::vector<Card*> deckCards;
		
	public:
	Deck();
	~Deck();

	void addCardUniversal(Card* card); // Insert the given card in both vectors.
	void addCard(Card* card); // Add the given card to the deckCards vector.
	void removeCard(Card* card); // Remove the given card from the deckCards vector.

	// The Deck class must have a draw() method that allows a player to draw a card at random from the cards remaining in the deck and place it in their hand of cards.
	void draw(Hand* drawingHand);

	void printCards();
};














