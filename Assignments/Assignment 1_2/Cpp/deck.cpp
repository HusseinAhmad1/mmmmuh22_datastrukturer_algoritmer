#include "deck.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono> 

using namespace std;

/**
 * Help function to convert Suit enum to string
*/
const string SuitToString(Suit s) {
    switch (s) {
        case Suit::Hearts:
            return "H";
        case Suit::Diamonds:
            return "D";
        case Suit::Spades:
            return "S";
        case Suit::Clubs:
            return "C";
    }
    return "";
}

Card::Card(int rank, Suit suit)
{
    this->rank = rank;
    this->suit = suit;
}

/**
 * Overload of << operator for Card class
*/
ostream & operator << (ostream &out, const Card &c)
{
    string r;
    switch(c.rank) {
        case 1:
            r = 'A';
            break;
        case 11:
            r = 'J';
            break;
        case 12:
            r = 'Q';
            break;
        case 13:
            r = 'K';
            break;
        default:
            r = to_string(c.rank);
            break;
    }

    out << r << SuitToString(c.suit);

    return out;
}

/**
 * Create a deck of 52 cards
*/
Deck::Deck() {
    for (Suit s = Suit::Hearts; s <= Suit::Clubs; s = Suit(s + 1)) {
        for (int r=1; r<14; r++) {
            cards.push_back(Card(r, s));
        }
    }
}

/**
 * Overload of << operator for Deck class
*/
ostream & operator << (ostream &out, const Deck &d)
{
    string separator;
    for (auto i: d.cards) {
        out << separator << i;
        separator = ", ";
    }

    return out;
}

/** 
 * Return number of cards in deck
 * 
*/
int Deck::size()
{
    return this->cards.size();
}

/**
 * Shuffle all the cards in deck in ranom order. 
*/
void Deck::shuffle()
{
    auto rng = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(this->cards.begin(),this->cards.end(), rng);
}

/**
 * Sort the deck according to card rank. All aces, the all two's, then all threes, ...
*/
void Deck::sort()
{
    vector<Card> sorted_cards; // Empty temporary deck

    while (this->size() > 0) {
        // Go through the deck from left to right, insert the deck in the appropriate spot
        Deck::insert(sorted_cards, this->take()); //Take a card from the old deck, insert it into the new one
    }

    this->cards = sorted_cards;
}

/**
 * Take the top card from the deck 
*/
Card Deck::take() {
    Card c = this->cards.back();
    this->cards.pop_back();
    return c;
}

/**
 * Put a card on top of the deck 
*/
void Deck::put(Card card) {
    cards.push_back(card);
}


void Deck::insert(vector<Card> &cardlist, Card card) {

    bool control_add = false;
    
    if (cardlist.size() == 0)
    {
        cardlist.push_back(card);
        control_add = true;
    }
    else
    {    
        for (int i = 0; i < cardlist.size(); i++)
        {
            if (card > cardlist[i])
                continue;
            cardlist.insert(cardlist.begin() + i, card);
            control_add = true;
            break;
        }
    }
        
    if (!control_add)
        cardlist.push_back(card);
    return;
}
