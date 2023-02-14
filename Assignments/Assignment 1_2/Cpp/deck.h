#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Suit {
    Hearts,
    Diamonds,
    Spades,
    Clubs
};

class Card
{
public:
    int rank;
    Suit suit;

    Card(int rank, Suit suit);
    
    bool operator == (Card const &other)
    {
        return rank == other.rank;
    }

    bool operator < (Card const &other)
    {
        return rank < other.rank;
    }

    bool operator > (Card const &other)
    {
        return rank > other.rank;
    }

    friend ostream & operator << (ostream &out, const Card &c);
};

class Deck
{
private:
    vector<Card> cards;
public:
    Deck();
    friend ostream & operator << (ostream &out, const Deck &d);
    int size();
    void shuffle();
    void sort();
    Card take();
    void put(Card card);

    static void insert(vector<Card> &cardlist, Card card);
};