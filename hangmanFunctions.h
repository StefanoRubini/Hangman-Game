#ifndef HANGMANFUNCTIONS_H
#define HANGMANFUNCTIONS_H

#include <string>
using namespace std;

void displayHeader();
void displayInfo();
void displayHangman(char board[7][10]);
char getValidCharacterGuess();
bool containsGuess(string word, char guess);

#endif