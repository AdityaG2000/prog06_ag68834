#include "card.h"
#include "player.h"
#include "deck.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>


using namespace std;

void dealGoFishHand(Deck &d, Player &p) {
    const int CARDS_IN_GOFISH_HAND = 7;

    for (int i = 0; i < CARDS_IN_GOFISH_HAND; i++) {
        p.addCard(d.dealCard()); //deal the 7 cards per each gold-fish hand
    }
}

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    const int NUM_PAIRS_FOR_VICTORY = 14;
    bool isDraw = false;
    bool emptyPrinted = false;
    cout << "Go Fish begins" << endl;
    ofstream out; //open file
    out.open("log.txt");

    //players
    Player p1("Aditya"); //Sample player one
    Player p2("Simba"); //Sample player two

    Deck d;  //create a pristine deck
    d.shuffle(); //shuffle it

    dealGoFishHand(d, p1);
    dealGoFishHand(d, p2);

    Card tempC1; //temp Card so it is pushed out
    Card tempC2; //temp Card so it is pushed out
    int tempInt;

    bool goAgain = true; //booleans to keep track
    bool isWin = false;

    Player pWinner; //Player who wins

    //initial game state
    out << "Initial Conditions " << endl;
    out << p1.getName() <<" hand has: " << p1.showHand() << "." << endl;
    out << p2.getName() <<" hand has: " << p2.showHand() << "." << endl;
    out << p1.getName() <<" book has: " << p1.showBooks() << "." << endl;
    out << p2.getName() <<" book has: " << p2.showBooks() << "." << endl << endl;

    //turn iterator
    int theCurrentTurn = 1;


    while(!isWin){

        while (p1.checkHandForBook(tempC1, tempC2)) {
            p1.bookCards(p1.removeCardFromHand(tempC1), p1.removeCardFromHand(tempC2)); //make books for p1
        }

        while (p2.checkHandForBook(tempC1, tempC2)) {
            p2.bookCards(p2.removeCardFromHand(tempC1), p2.removeCardFromHand(tempC2)); //make books for p2
        }


        //theCurrentTurn turn game state
        out << "Turn " << theCurrentTurn << endl;
        out << p1.getName() <<" hand has: " << p1.showHand() << "." << endl;
        out << p2.getName() <<" hand has: " << p2.showHand() << "." << endl;
        out << p1.getName() <<" book has: " << p1.showBooks() << "." << endl;
        out << p2.getName() <<" book has: " << p2.showBooks() << "." << endl << endl;

        //p1 turn
        while(goAgain && p1.getHandSize() > 0) {
            tempC1 = p1.chooseCardFromHand();
            if(tempC1.getRank() == 0) {
                break;
            }
            out << p1.getName() <<" asks - Do you have a " << tempC1.rankString(tempC1.getRank()) << "?" << endl;
            tempInt = p2.getIndexOfRankInHand(tempC1);
            if(tempInt != -1){
                out << p2.getName() <<" says - Yes. I have a " << tempC1.rankString(tempC1.getRank()) << "." << endl;
                out<< p1.getName() << " books " <<tempC1.toString() << " and " << p1.doGoFish(tempC1, p2.removeCardAtIndex(tempInt)) << "." << endl;
            }
            else {
                out << p2.getName() <<" says - Go Fish! " << endl;
                goAgain = false;
            }
        }
        goAgain = true; //for the turn's loop
        if(d.size() >= 1) {
            out << p1.getName() << " draws " << p1.doGoFish(tempC1, d.dealCard()) << "." << endl << endl;
        }
        else {
            if (emptyPrinted == false) {
                out << "Deck empty" << endl << endl; //letting the user know tha tthe deck is empty so the game is finishing soon
                emptyPrinted = true;
            }
        }

        //p1's lookBook
        if(p1.checkHandForBook(tempC1, tempC2)) {
            p1.bookCards(p1.removeCardFromHand(tempC1), p1.removeCardFromHand(tempC2));
	}

        //p2's turn
        while(goAgain && p2.getHandSize() > 0) {
            tempC2 = p2.chooseCardFromHand();
            out << p2.getName() <<" asks - Do you have a " << tempC2.rankString(tempC2.getRank()) << "?" << endl;
            tempInt = p1.getIndexOfRankInHand(tempC2);
            if(tempInt != -1) {
                out << p1.getName() <<" says - Yes. I have a " << tempC2.rankString(tempC2.getRank()) << "." << endl;
                out<< p2.getName() << " books " <<tempC2.toString() << " and " << p2.doGoFish(tempC2, p1.removeCardAtIndex(tempInt)) << endl;
            } else {
                out << p1.getName() <<" says - Go Fish! " << endl;
                goAgain = false;
            }
        }
        goAgain = true; //for the turn's loop

        if(d.size() >= 1) {
            out << p2.getName() << " draws " << p2.doGoFish(tempC2, d.dealCard()) << endl << endl;
        } else {
            if (emptyPrinted == false) {
                out << "Deck empty" << endl << endl; //letting the user know that the deck is empty so the game is finishing up soon
                emptyPrinted = true;
                }
        }
        //looking in Book
        if(p2.checkHandForBook(tempC1, tempC2)) {
            p2.bookCards(p2.removeCardFromHand(tempC1), p2.removeCardFromHand(tempC2));
        }
        //check to see if there is a winner
        if (p1.getBookSize() >= NUM_PAIRS_FOR_VICTORY) {
            isWin = true;
            pWinner = p1;
        } else if (p2.getBookSize() >= NUM_PAIRS_FOR_VICTORY){
            isWin = true;
            pWinner = p2;
        } else if ((p1.getHandSize() <= 0 || p2.getHandSize() <= 0) && d.size() <= 0) { //game is over; preventing infite loop too
            isWin = true;

            while (p1.checkHandForBook(tempC1, tempC2)) {
                p1.bookCards(p1.removeCardFromHand(tempC1), p1.removeCardFromHand(tempC2)); //make books for p1
            }

            while (p2.checkHandForBook(tempC1, tempC2)) {
                p2.bookCards(p2.removeCardFromHand(tempC1), p2.removeCardFromHand(tempC2)); //make books for p2
            }

            if (p1.getBookSize() > p2.getBookSize()) { //for determining the winner
                pWinner = p1;
            } else if (p1.getBookSize() < p2.getBookSize()) {
                pWinner = p2;
            } else {
                isDraw = true; //case when there is a draw
            }

        }
        theCurrentTurn++;
    }

    //final game state
    out << "Final Turn" << endl;
    if (!isDraw) {
        out << p1.getName() <<" hand has: " << p1.showHand() << "." << endl;
        out << p2.getName() <<" hand has: " << p2.showHand() << "." << endl;
        out << p1.getName() <<" book has: " << p1.showBooks() << "." << endl;
        out << p2.getName() <<" book has: " << p2.showBooks() << "." << endl << endl;

        out << pWinner.getName() << " wins! Congratulations!!!" << endl;
    } else {
        out << "It is a draw! " << endl << endl;
    }


    cout << "Game over" << endl;

    return EXIT_SUCCESS;
}

