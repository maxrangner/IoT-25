#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

constexpr int NUM_VALUES_IN_COLOR = 13;

enum cardColor {
    diamonds, // 0.
    spades, // 1.
    hearts, // 2.
    clubs, // 3.
    endOfColors
};

enum fillDeck {
    full,
    empty
};

class Card {
    private:

    public:
        Card (bool empty = false) : noCard(empty), color(0), value(0) {}
        bool noCard;
        int color;
        int value;
};

class Deck {
    private:
        bool shouldFillDeck;
    public:
        Deck(bool fill = true) : shouldFillDeck(fill) {
            if (shouldFillDeck) {
                int numCards = 0;
                for (int i = 0; i < cardColor::endOfColors; i++) {
                    for (int j = 1; j < NUM_VALUES_IN_COLOR + 1; j++) {
                        Card newCard; 
                        newCard.color = i;
                        newCard.value = j;
                        deck.push_back(newCard);
                        numCards++;
                    }
                }
            }
        }

        std::vector<Card> deck;
        void shuffle() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::shuffle(deck.begin(), deck.end(), gen);
        }

        Card deal() {
            Card dealtCard;
            if (deck.empty()) {
                return (dealtCard.noCard = true);
            }
            dealtCard = deck.back();
            deck.pop_back();
            return dealtCard;
        }

        void takeCard (Card newCard) {
            deck.push_back(newCard);
        }

        int getNumCards() {
            return deck.size();
        }

        void printDeck() {
            int cardNum = 1;
            std::cout << "*--- DECK ---*\n";
            for (const Card& c : deck) {
                std::cout << cardNum++
                          << ": Color: "
                          << c.color 
                          << " Value: " 
                          << c.value 
                          << std::endl;
            }
            std::cout << std::endl;
    }
};

int main() {
    Deck myDeck;
    Deck dealersDeck(empty);
    myDeck.shuffle();

    myDeck.printDeck();
    dealersDeck.printDeck();

    
    // int deals = myDeck.getNumCards();
    // for (int i = 0; i < deals; i++) {
    //     Card cardOnTable = myDeck.deal();
    //     std::cout << "DEAL!";
    //     dealersDeck.takeCard(cardOnTable);
    // }

    myDeck.printDeck();
    dealersDeck.printDeck();
}