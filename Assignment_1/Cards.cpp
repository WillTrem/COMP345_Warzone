#pragma once

#include "Cards.h"

using namespace std;

// PART 4.
// 
// Implement a group of C++ classes that implements a deck and hand of Warzone cards. 
// All the classes / functions that you implement for this component must all reside in a single.cpp / .h file duo named Cards.cpp / Cards.h.



// CARD.
Deck* Card::getMyDeck()
{
	return myDeck;
}
// Returns whether the card is currently in a player's hand. 
bool Card::isOwned()
{
	return currentOwner != nullptr;
};
// Returns the pointer to the card's current owner, if any.
Hand* Card::getOwningHand()
{
	return currentOwner;
};
// Set the card's current owner.
void Card::setOwningHand(Hand* owner)
{
	currentOwner = owner;
};

// Constructors.
Card::Card(Deck* deck)
{
	myDeck = deck;
	myDeck->addCardUniversal(this);
	myDeck->addCard(this);

	currentOwner = nullptr; // By default, the card is unowned.
};
Card::Card(Hand* owner, Deck* deck) // If needed, a card could be created directly into a player's hand.
{
	myDeck = deck;
	myDeck->addCardUniversal(this);

	owner->addCard(this);
}
// To do: add more for cards of specific types?

// Destructor.
Card::~Card()
{
	currentOwner = nullptr;
	delete currentOwner;
};

// Base play() method. 
// Each card has a play() method that enables a player to use it during game play by creating special orders. Once a card has been played, it is removed from the hand and put back into the deck.
void Card::play() 
{
	cout << "\nA card has been played!" << endl;

	// Remove the card from the current hand.
	currentOwner->removeCard(this);

	return;
};


// Each card has a type from: bomb, reinforcement, blockade, airlift and diplomacy.
// Making these into different child classes as I imagine they'll have different purposes.
void Card_Bomb::play() 
{
	// Actions specific to this type of card.
	cout << "Playing a Bomb card." << endl;

	// Rest of the generic play() method.
	Card::play();
	return;
};

void Card_Reinforcement::play() 
{
	cout << "Playing a Reinforcement card." << endl;

	Card::play();
	return;
};

void Card_Blockade::play() 
{
	cout << "Playing a Blockade card." << endl;

	Card::play();
	return;
};

void Card_Airlift::play() 
{
	cout << "Playing an Airlift card." << endl;

	Card::play();
	return;
};

void Card_Diplomacy::play() 
{
	cout << "Playing a Diplomacy card." << endl;

	Card::play();
	return;
};



// HAND
// A Hand object is a finite collection of Warzone cards.
Hand::Hand()
{
	myCards = {};

	//cout << "\nIs myCards empty? " << myCards.empty() << endl;
	//cout << "Size of myCards: " << myCards.size() << endl;
};
void Hand::addCard(Card* card)
{
	// Update the card's owner.
	card->setOwningHand(this);
	
	// Add the card to the hand's vector.
	myCards.push_back(card);

	// Remove card from the main deck.
	card->getMyDeck()->removeCard(card);

	//printCards();

	return;
};
void Hand::removeCard(Card* card)
{
	// Update the card's owner.
	card->setOwningHand(nullptr);
	
	// Find the card in the vector.
	auto it = find(myCards.begin(), myCards.end(), card);
	// Remove it
	if (it != myCards.end())
		myCards.erase(it);

	// Return card to the main deck.
	card->getMyDeck()->addCard(card);

	//printCards();

	return;
};

void Hand::printCards()
{
	cout << "\nIs myCards empty? " << myCards.empty() << endl;
	cout << "Size of myCards: " << myCards.size() << endl;

	cout << "\nAll cards in the hand:" << endl;
	for (Card* card : myCards)
	{
		cout << "\nA new card:" << endl;
		cout << "Card object: " << &card << endl;
		cout << "Card address: " << card << endl;
	}
};



// DECK
// A Deck object contains a finite collection of Warzone cards.
Deck::Deck()
{
	srand(time(0));
	
	allCards = {};
	deckCards = {};

	//cout << "\nIs the allCards empty? " << allCards.empty() << endl;
	//cout << "Is the deckCards empty? " << deckCards.empty() << endl;
};
void Deck::addCardUniversal(Card* card)
{
	// Insert the given card in the reference vector.
	allCards.push_back(card);
};
void Deck::addCard(Card* card)
{
	// Add the given card to the deckCards vector.
	deckCards.push_back(card);
}; 
void Deck::removeCard(Card* card)
{
	// Remove the given card from the deckCards vector.
	// Find the card in the vector.
	auto it = find(deckCards.begin(), deckCards.end(), card);

	// Remove it
	if (it != deckCards.end())
		deckCards.erase(it);
};

// The Deck class must have a draw() method that allows a player to draw a card at random from the cards remaining in the deck and place it in their hand of cards.
void Deck::draw(Hand* drawingHand)
{
	// Get a random card's index.
	int index = rand() % deckCards.size();
	cout << "\nDrew the card at index: " << index << endl;

	drawingHand->addCard(deckCards.at(index));

	return;
};

void Deck::printCards()
{
	cout << "\nIs deckCards empty? " << deckCards.empty() << endl;
	cout << "Size of deckCards: " << deckCards.size() << endl;
	cout << "Size of allCards: " << allCards.size() << endl;
	
	cout << "\nAll existing cards:" << endl;
	for (Card* card : allCards)
	{
		cout << "\nA card:" << endl;
		cout << "Card object: " << &card << endl;
		cout << "Card address: " << card << endl;
	}

	cout << "\nCards currently in the deck:" << endl;
	for (Card* card : deckCards)
	{
		cout << "\nA card:" << endl;
		cout << "Card object: " << &card << endl;
		cout << "Card address: " << card << endl;
	}
};
