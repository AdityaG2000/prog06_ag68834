#include "card.h"

//Parameters constructor
Card::Card(int rank, Suit s) {
    myRank = rank;
    mySuit = s;
}

//No parameters constructor
Card::Card() { //default card is the ace of spades
    myRank = 1; // 1 = Ace
    mySuit = spades;
}

//String representation of the card
string Card::toString() const {
    string result;
    result = rankString(myRank); //add in the rank first
    result += suitString(mySuit); //then add in the suit
    return (result);
}

//checks if the card passed in has the same suit as the current card
bool Card::sameSuitAs(const Card& c) const {
    bool result = (mySuit == c.mySuit);
    return (result);
}

//returns the card's rank
int Card::getRank() const {
    return myRank;
}

//String representation of the suit
string Card::suitString(Suit s) const {
    switch(s) { //gives a string representation of suit
        case hearts : return "H"; //capital letters because of my personal preference...
        case spades : return "S";
        case diamonds : return "D";
        case clubs : return "C";
    }
    return (""); //should never be reached
}

//String representation of the rank
string Card::rankString(int r) const { //gives a string representation of the rank
    switch(r) {
        case 1 : return "A"; //1 is Ace
        case 2 : return "2";
        case 3 : return "3";
        case 4 : return "4";
        case 5 : return "5";
        case 6 : return "6";
        case 7 : return "7";
        case 8 : return "8";
        case 9 : return "9";
        case 10 : return "10";
        case 11 : return "J"; //11 is jack
        case 12 : return "Q"; //12 is queen
        case 13 : return "K"; //13 is kign
        default : break; //just in case
    }
    return (""); //should never be reached
}

//Overriding == so it works properly with cards
bool Card::operator == (Card const &rhs) {
    bool equalRanks = (myRank == rhs.myRank);
    bool equalSuits = (mySuit == rhs.mySuit);
    return (equalRanks && equalSuits);
}

//Overriding != so it works properly with cards
bool Card::operator != (Card const &rhs) {
    bool equalRanks = (myRank == rhs.myRank);
    bool equalSuits = (mySuit == rhs.mySuit);
    return ((!(equalRanks) || !(equalSuits)));
}

//Overriding << so it works properly with cards' representation
ostream& operator << (ostream& out, const Card& c) {
    string cardOutput = c.toString();
    out << cardOutput;
    return out;
}