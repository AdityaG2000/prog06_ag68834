#include "player.h"

//default constructor
Player::Player() {
    myName = "";
}

//to add a card to the deck
void Player::addCard(Card c) {
    myHand.push_back(c);
}

//will book together two cards.
//precondition is that they match ranks
void Player::bookCards(Card c1, Card c2) {
    myBook.push_back(c1);
    myBook.push_back(c2);
}

//checks if there are any books in the hand
//returns a boolean which is true if there are and false if there arent any books
bool Player::checkHandForBook(Card &c1, Card &c2) {
    bool result;
    result = false;

    for(int i = 0; i < myHand.size(); i++) {

        for(int j = 0; j < myHand.size(); j++) {
            if (myHand[i].getRank() == myHand[j].getRank()) {
                if (i != j) {
                    c1 = myHand[i]; //so we can push out book
                    c2 = myHand[j]; //so we can push out book
                    result = true;
                }
            }
        }

    }
    return (result);
}

//for finding card of the same rank as c
int Player::getIndexOfRankInHand(Card c) const {
    int result = -1;

    for(int i = 0; i < myHand.size(); i++) {
        if(myHand[i].getRank() == c.getRank()) {
            result = i;
        }
    }
    return result;
}

//player's strategy of how to choose which card to ask for.
Card Player::chooseCardFromHand() const {
    int index = 0;
    return myHand[index]; // simple selection strategy
}

//finds if a part is in the hand
bool Player::cardInHand(Card c) const {
    bool result = false;

    for (int i = 0; i < myHand.size(); i++) {
        if((myHand[i].getRank() == c.getRank()) && (myHand[i].sameSuitAs(c))) {
            result = true;
        }
    }
    return result;
}

//removes a specific card from the players hand
Card Player::removeCardFromHand(Card c) {
    bool done = false;

    for(int i = 0; i < myHand.size() && !(done); i++){
        if(myHand[i].getRank() == c.getRank() && myHand[i].sameSuitAs(c)){
            myHand.erase(myHand.begin() + i);
            done = true;
        }
    }
    return c;
}

//creates string output of the player
string Player::showHand() const {
    string out;

    for (int i = 0; i < myHand.size(); i++) { //displays the hand
        out.append(myHand[i].toString() + " ");
    }
    return out;
}

//creates string output of the books
string Player::showBooks() const {
    string myOutput;
    if(myBook.size() > 0){

    for(int i = 0; i < myBook.size() - 1; i = i + 2) {
        myOutput += (myBook[i].toString() + " " + myBook[i + 1].toString() + ", ");
    } 
    }
    return myOutput;
}

//gets the size of the hand
int Player::getHandSize() const {
    return (int)(myHand.size());
}

//gets the size of the book
int Player::getBookSize() const{
    return (((int)myBook.size())/2);
}

//does the operation when one player asks another is they have a rank but the other doesn't
//so they must go fish
string Player::doGoFish(Card cardOne, Card cardTwo) {
    string result;
    addCard(cardTwo);
    addCard(removeCardFromHand(cardOne));
    result = cardTwo.toString() ;
    return (result);
}

//removes card at an index
Card Player::removeCardAtIndex(int index) {
    Card result;
    Card removedCard = myHand[index];
    this -> removeCardFromHand(removedCard);
    result = removedCard;
    return result;
}
