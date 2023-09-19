#pragma once

#include "Cards.h"
#include <algorithm>

using namespace std;

// PART 4.
// 
// Implement a group of C++ classes that implements a deck and hand of Warzone cards. 
// All the classes / functions that you implement for this component must all reside in a single.cpp / .h file duo named Cards.cpp / Cards.h.

// Written by Roxane Morin, 40191881.


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

	cout << "Creating a card." << endl;
};
Card::Card(Hand* owner, Deck* deck) // If needed, a card could be created directly into a player's hand.
{
	myDeck = deck;
	myDeck->addCardUniversal(this);

	owner->addCard(this);

	cout << "Creating a card." << endl;
}
// To do: add more for cards of specific types?

// Destructor.
Card::~Card()
{
	// Not sure these are needed, adding just to be safe.
	myDeck = nullptr;
	currentOwner = nullptr;

	delete myDeck;
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

Card_Bomb::Card_Bomb(Deck* deck) : Card::Card(deck)
{
	cout << "It is a Bomb card.\n" << endl;
};
Card_Bomb::Card_Bomb(Hand* owner, Deck* deck) : Card::Card(owner, deck) 
{
	cout << "It is a Bomb card.\n" << endl;
};
void Card_Bomb::play() 
{
	// Actions specific to this type of card.
	cout << "Playing a Bomb card." << endl;

	// Rest of the generic play() method.
	Card::play();
	return;
};

Card_Reinforcement::Card_Reinforcement(Deck* deck) : Card::Card(deck)
{
	cout << "It is a Reinforcement card.\n" << endl;
};
Card_Reinforcement::Card_Reinforcement(Hand* owner, Deck* deck) : Card::Card(owner, deck)
{
	cout << "It is a Reinforcement card.\n" << endl;
};
void Card_Reinforcement::play() 
{
	cout << "Playing a Reinforcement card." << endl;

	Card::play();
	return;
};

Card_Blockade::Card_Blockade(Deck* deck) : Card::Card(deck)
{
	cout << "It is a Blockade card.\n" << endl;
};
Card_Blockade::Card_Blockade(Hand* owner, Deck* deck) : Card::Card(owner, deck)
{
	cout << "It is a Blockade card.\n" << endl;
};
void Card_Blockade::play() 
{
	cout << "Playing a Blockade card." << endl;

	Card::play();
	return;
};

Card_Airlift::Card_Airlift(Deck* deck) : Card::Card(deck)
{
	cout << "It is an Airlift card.\n" << endl;
};
Card_Airlift::Card_Airlift(Hand* owner, Deck* deck) : Card::Card(owner, deck)
{
	cout << "It is an Airlift card.\n" << endl;
};
void Card_Airlift::play() 
{
	cout << "Playing an Airlift card." << endl;

	Card::play();
	return;
};

Card_Diplomacy::Card_Diplomacy(Deck* deck) : Card::Card(deck)
{
	cout << "It is a Diplomacy card.\n" << endl;
};
Card_Diplomacy::Card_Diplomacy(Hand* owner, Deck* deck) : Card::Card(owner, deck)
{
	cout << "It is a Diplomacy card.\n" << endl;
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

	cout << "\nA hand has been created.\n\n" << endl;

	//cout << "\nIs myCards empty? " << myCards.empty() << endl;
	//cout << "Size of myCards: " << myCards.size() << endl;
};
Hand::~Hand()
{
	myCards.clear();
	//delete myCards; Aparently done automatically.
}
vector<Card*> Hand::returnMyCards()
{
	return myCards;
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
	cout << "\n\nHand information." << endl;
	
	cout << "\nIs myCards empty? " << myCards.empty() << endl;
	cout << "Size of myCards: " << myCards.size() << endl;

	cout << "\nCards currently in the hand:" << endl;
	for (Card* card : myCards)
	{
		cout << "\nA new card:" << endl;
		cout << "Card object: " << &card << endl;
		cout << "Card address: " << card << endl;
	}

	cout << "\n" << endl;
};



// DECK
// A Deck object contains a finite collection of Warzone cards.
Deck::Deck()
{
	srand(time(0));
	
	allCards = {};
	deckCards = {};

	cout << "\nA Deck has been created.\n\n" << endl;

	//cout << "\nIs the allCards empty? " << allCards.empty() << endl;
	//cout << "Is the deckCards empty? " << deckCards.empty() << endl;
};
Deck::~Deck()
{
	allCards.clear();
	deckCards.clear();
}
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
	if (deckCards.size() != 0)
	{
		// Get a random card's index.
		int index = rand() % deckCards.size();
		cout << "\nDrew the card at index: " << index << endl;

		drawingHand->addCard(deckCards.at(index));
	}
	else
	{
		cout << "\nNo card could be drawn as the deck is empty." << endl;
	}
	
	return;
};

void Deck::printCards()
{
	cout << "\n\nDeck information." << endl;
	
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

	cout << "\n" << endl;
};
