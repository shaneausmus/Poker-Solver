#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void processGame(std::string gameFile);
bool royalFlush(std::vector<int> cards);
int straightFlush(std::vector<int> cards);
int fourOfAKind(std::vector<int> cards);
int fullHouse(std::vector<int> cards);
int flush(std::vector<int> cards);
int straight(std::vector<int> cards);
int threeOfAKind(std::vector<int> cards);
int twoPairs(std::vector<int> cards);
int onePair(std::vector<int> cards);
int highCard(std::vector<int> cards);
std::vector<int> processHand(std::string hand);
int compare(std::vector<int> cards1, std::vector<int> cards2);

const int CARDS_LIMIT = 15;

int main() {
    std::string gameFile = "p054_poker.txt";
    processGame(gameFile);
    return 0;
}

bool royalFlush(std::vector<int> cards) {
    bool checkSameSuit = false;
    for (int i = CARDS_LIMIT; i < (int)cards.size(); ++i) {
        if (cards[i] == 5) {
            checkSameSuit = true;
        }
    }

    if (!checkSameSuit){
        return false;
    } else {
        for (int i = 10; i < CARDS_LIMIT; ++i) {
            if (cards[i] != 1) {
                return false;
            }
        }
        return true;
    }
}

int straightFlush(std::vector<int> cards) {
    int counter = 0;
    bool checkSameSuit = false;
    for (int i = CARDS_LIMIT; i < (int)cards.size(); ++i) {
        if (cards[i] == 5) {
            checkSameSuit = true;
        }
    }

    if (!checkSameSuit){
        return -1;
    } else {
        int i;
        for (i = 0; i < 15; ++i) {
            if (counter == 5) {
                break;
            } else if (cards[i] == 1) {
                ++counter;
            } else {
                counter = 0;
            }
        }
        if (counter != 5) {
            return -1;
        } else {
            return i - 1;
        }
    }
}

int fourOfAKind(std::vector<int> cards) {
    for (int i = 0; i < CARDS_LIMIT; ++i) {
        if (cards[i] == 4) {
            return i;
        }
    }
    return -1;
}

int fullHouse(std::vector<int> cards) {
    int three = 0, two = 0;
    bool check3 = false, check2 = false;
    for (int i = 0; i < CARDS_LIMIT; ++i) {
        if (cards[i] == 3) {
            check3 = true;
            three = i;
        } else if (cards[i] == 2) {
            check2 = true;
            two = i;
        }
    }
    if (check3 && check2) {
        if (three > two) {
            return three;
        } else {
            return two;
        }
    } else {
        return -1;
    }
}

int flush(std::vector<int> cards) {
    for (int i = CARDS_LIMIT; i < 19; ++i) {
        if (cards[i] == 5) {
            return i;
        }
    }
    return -1;
}

int straight(std::vector<int> cards) {
    int i, counter = 0;
    for (i = 0; i < CARDS_LIMIT; ++i) {
        if (counter == 5) {
            break;
        } else if (cards[i] == 1) {
            ++counter;
        } else {
            counter = 0;
        }
    }
    if (counter != 5) {
        return -1;
    } else {
        return i - 1;
    }
}

int threeOfAKind(std::vector<int> cards) {
    for (int i = 0; i < CARDS_LIMIT; ++i) {
        if (cards[i] == 3) {
            return i;
        }
    }
    return -1;
}

int twoPairs(std::vector<int> cards) {
    int pairCount = 0;
    for (int i = 0; i < CARDS_LIMIT; ++i) {
        if (cards[i] == 2) {
            ++pairCount;
        }
        if (pairCount == 2) {
            return i;
        }
    }
    return -1;
}

int onePair(std::vector<int> cards) {
    for (int i = 0; i < 15; ++i) {
        if (cards[i] == 2) {
            return i;
        }
    }
    return -1;
}

int highCard(std::vector<int> cards) {
    int highestCard = -1;
    for (int i = 0; i < CARDS_LIMIT; ++i) {
        if (cards[i] > 0 && i > highestCard) {
            highestCard = i;
        }
    }
    return highestCard;
}

std::vector<int> processHand(std::string hand) {
    std::vector<int> numsPlayer(19, 0);
    for (int i = 0; i < (int)hand.size(); ++i){
        if (hand[i]==' ') {
        } else if (hand[i]-'0' < 10) {
            ++numsPlayer[hand[i]-'0'];
        } else if (hand[i] == 'T') {
            ++numsPlayer[10];
        } else if (hand[i] == 'J') {
            ++numsPlayer[11];
        } else if (hand[i] == 'Q') {
            ++numsPlayer[12];
        } else if (hand[i] == 'K') {
            ++numsPlayer[13];
        } else if (hand[i] == 'A') {
            ++numsPlayer[14];
        } else if (hand[i] == 'C') {
            ++numsPlayer[15];
        } else if (hand[i] == 'S') {
            ++numsPlayer[16];
        } else if (hand[i] == 'D') {
            ++numsPlayer[17];
        } else if (hand[i] == 'H') {
            ++numsPlayer[18];
        }
    }
    return numsPlayer;
}

int compare(std::vector<int> cards1, std::vector<int> cards2) {
    int highestCard[2] = {0, 0};
    for (int i = 0; i < CARDS_LIMIT; ++i) {
        if (cards1[i] > 0 && i > highestCard[0] && cards2[i] == 0) {
            highestCard[0] = i;
            highestCard[1] = 1;
        }
        if (cards2[i] > 0 && i > highestCard[0] && cards1[i] == 0) {
            highestCard[0] = i;
            highestCard[1] = 2;
        }
    }
    return highestCard[1];
}

void processGame(std::string gameFile) {
    // for cards; index[0] is clubs, 1 is spades, 2 is diamonds, 3 is hearts
    std::vector<int> numsPlayer1(19, 0), numsPlayer2(19, 0);
    int player1Wins = 0, player2Wins = 0;
    std::ifstream infile;
    std::string filetext, currGame;
    if (!gameFile.empty()) {
        infile.open(gameFile.c_str());
    }
    while (getline(infile, currGame)) {
        numsPlayer1.clear();
        numsPlayer2.clear();
        std::string player1 = currGame.substr(0, 14);
        std::string player2 = currGame.substr(15);
        numsPlayer1 = processHand(player1);
        numsPlayer2 = processHand(player2);
        bool check1 = royalFlush(numsPlayer1), check2 = royalFlush(numsPlayer2);
        if (check1 || check2) {
            if (check1 && check2) {
            }
            if (check1) {
                ++player1Wins;
            } else {
                ++player2Wins;
            }
            continue;
        }

        int checkOne = straightFlush(numsPlayer1), checkTwo = straightFlush(numsPlayer2);
        if (checkOne > -1 || checkTwo > -1) {
            if (checkOne > -1 && checkTwo > -1 && checkOne == checkTwo) {
                int result = compare(numsPlayer1, numsPlayer2);
                if (result == 1) {
                    ++player1Wins;
                } else {
                    ++player2Wins;
                }
            } else if (checkOne > checkTwo) {
                ++player1Wins;
            } else if (checkTwo > checkOne) {
                ++player2Wins;
            }
            continue;
        }

        checkOne = fourOfAKind(numsPlayer1);
        checkTwo = fourOfAKind(numsPlayer2);
        if (checkOne > -1 || checkTwo > -1) {
            if (checkOne > -1 && checkTwo > -1 && checkOne == checkTwo) {
                int result = compare(numsPlayer1, numsPlayer2);
                if (result == 1) {
                    ++player1Wins;
                } else {
                    ++player2Wins;
                }
            } else if (checkOne > checkTwo) {
                ++player1Wins;
            } else if (checkTwo > checkOne) {
                ++player2Wins;
            }
            continue;
        }

        checkOne = fullHouse(numsPlayer1);
        checkTwo = fullHouse(numsPlayer2);
        if (checkOne > -1 || checkTwo > -1) {
            if (checkOne > -1 && checkTwo > -1 && checkOne == checkTwo) {
                int result = compare(numsPlayer1, numsPlayer2);
                if (result == 1) {
                    ++player1Wins;
                } else {
                    ++player2Wins;
                }
            } else if (checkOne > checkTwo) {
                ++player1Wins;
            } else if (checkTwo > checkOne) {
                ++player2Wins;
            }
            continue;
        }


        checkOne = flush(numsPlayer1);
        checkTwo = flush(numsPlayer2);
        if (checkOne > -1 || checkTwo > -1) {
            if (checkOne > -1 && checkTwo > -1 && checkOne == checkTwo) {
                int result = compare(numsPlayer1, numsPlayer2);
                if (result == 1) {
                    ++player1Wins;
                } else {
                    ++player2Wins;
                }
            } else if (checkOne > checkTwo) {
                ++player1Wins;
            } else if (checkTwo > checkOne) {
                ++player2Wins;
            }
            continue;
        }

        checkOne = straight(numsPlayer1);
        checkTwo = straight(numsPlayer2);
        if (checkOne > -1 || checkTwo > -1) {
            if (checkOne > -1 && checkTwo > -1 && checkOne == checkTwo) {
                int result = compare(numsPlayer1, numsPlayer2);
                if (result == 1) {
                    ++player1Wins;
                } else {
                    ++player2Wins;
                }
            } else if (checkOne > checkTwo) {
                ++player1Wins;
            } else if (checkTwo > checkOne) {
                ++player2Wins;
            }
            continue;
        }

        checkOne = threeOfAKind(numsPlayer1);
        checkTwo = threeOfAKind(numsPlayer2);
        if (checkOne > -1 || checkTwo > -1) {
            if (checkOne > -1 && checkTwo > -1 && checkOne == checkTwo) {
                int result = compare(numsPlayer1, numsPlayer2);
                if (result == 1) {
                    ++player1Wins;
                } else {
                    ++player2Wins;
                }
            } else if (checkOne > checkTwo) {
                ++player1Wins;
            } else if (checkTwo > checkOne) {
                ++player2Wins;
            }
            continue;
        }

        checkOne = twoPairs(numsPlayer1);
        checkTwo = twoPairs(numsPlayer2);
        if (checkOne > -1 || checkTwo > -1) {
            if (checkOne > -1 && checkTwo > -1 && checkOne == checkTwo) {
                int result = compare(numsPlayer1, numsPlayer2);
                if (result == 1) {
                    ++player1Wins;
                } else {
                    ++player2Wins;
                }
            } else if (checkOne > checkTwo) {
                ++player1Wins;
            } else if (checkTwo > checkOne) {
                ++player2Wins;
            }
            continue;
        }

        checkOne = onePair(numsPlayer1);
        checkTwo = onePair(numsPlayer2);
        if (checkOne > -1 || checkTwo > -1) {
            if (checkOne > -1 && checkTwo > -1 && checkOne == checkTwo) {
                int result = compare(numsPlayer1, numsPlayer2);
                if (result == 1) {
                    ++player1Wins;
                } else {
                    ++player2Wins;
                }
            } else if (checkOne > checkTwo) {
                ++player1Wins;
            } else if (checkTwo > checkOne) {
                ++player2Wins;
            }
            continue;
        }

        checkOne = highCard(numsPlayer1);
        checkTwo = highCard(numsPlayer2);
        if (checkOne > -1 || checkTwo > -1) {
            if (checkOne > -1 && checkTwo > -1 && checkOne == checkTwo) {
                int result = compare(numsPlayer1, numsPlayer2);
                if (result == 1) {
                    ++player1Wins;
                } else {
                    ++player2Wins;
                }
            } else if (checkOne > checkTwo) {
                ++player1Wins;
            } else if (checkTwo > checkOne) {
                ++player2Wins;
            }
            continue;
        }
    }

    infile.close();
    std::cout << "Player 1 wins: " << player1Wins << "\n";
    std::cout << "Player 2 wins: " << player2Wins;
}