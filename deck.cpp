#include "deck.h"
#include <stdio.h>
#include <algorithm>

//default constructor. Makes a pristine deck.
Deck::Deck() {
    const int NUM_CARDS_OF_A_SUIT = 13;
    Card newCard;
    myIndex = 0;

    for (int i = 0 ; i < NUM_CARDS_OF_A_SUIT ; i++){ //making spades
        newCard = Card((i + 1), Card::spades);
        myCards[i] = newCard;
    }

    for (int i = NUM_CARDS_OF_A_SUIT ; i < (2 * NUM_CARDS_OF_A_SUIT) ; i++) { //making hearts
        newCard = Card((i - (NUM_CARDS_OF_A_SUIT - 1)), Card::hearts);
        myCards[i] = newCard;
    }

    for (int i = (2 * NUM_CARDS_OF_A_SUIT) ; i < (3 * NUM_CARDS_OF_A_SUIT) ; i++){ //making diamonds
        newCard = Card(i - ((2 * NUM_CARDS_OF_A_SUIT) - 1), Card::diamonds);
        myCards[i] = newCard;
    }

    for (int i = (3 * NUM_CARDS_OF_A_SUIT) ; i < (4 * NUM_CARDS_OF_A_SUIT) ; i++){ //making clubs
        newCard = Card(i - (3 * NUM_CARDS_OF_A_SUIT - 1),Card::clubs);
        myCards[i] = newCard;
    }
}

//shuffles around the deck
void Deck::shuffle(){
    const int NUM_CARDS_IN_DECK = 52;
    vector <Card> tempVector; //temp vector to be used of type card
    Card tempCard;
    if (myIndex == NUM_CARDS_IN_DECK || myIndex == (NUM_CARDS_IN_DECK - 1)) {
        return; //because we can't really shuffle 0 cards or 1 card
    }

    for(int i = 0; size() > i; i++) {
        tempVector.push_back(myCards[i]);
    }

    //flips list ten times the size
    int timesToFlip = 10;

    for(int i = 0; i < (tempVector.size() * timesToFlip); i++){

        int randOne = rand() % tempVector.size() + 0; //Random number one
        int randTwo = rand() % tempVector.size() + 0; //Random number two

        tempCard = tempVector[randOne]; //swapping between elements at randOne and randTwo
        tempVector[randOne] = tempVector[randTwo];
        tempVector[randTwo] = tempCard;
    }

    for(int i = 0; i < size(); i++) { //when done shuffling, get result in myCards which is the shuffled deck.
        myCards[i] = tempVector[i];
    }
    return;
}

//deals a card from the cards in the deck avaliable
//must be atleast one un-dealt card left in the deck
Card Deck::dealCard(){
    const int NUM_CARDS_IN_DECK = 52;
    Card result;
    if(myIndex == NUM_CARDS_IN_DECK) {
        return {0, Card::spades}; //this 0 is special to communicate with my driver. It means that the preconditions for deal card failed
    }
    result = myCards[myIndex];
    myIndex++;
    return result;
}

//gets the size of the deck
int Deck::size() const {
    const int NUM_CARDS_IN_DECK = 52;
    return (NUM_CARDS_IN_DECK - myIndex); //so the size of the deck is 0 when empty as is implied 
}
