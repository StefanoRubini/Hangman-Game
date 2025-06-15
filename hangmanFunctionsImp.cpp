#include "hangmanFunctions.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Displays the game header.
 * @param none
 * @return none
 */
void displayHeader() {
    cout << endl << "*****************************************" << endl;
    cout << "    Welcome to the game of Hangman!";
    cout <<  endl << "*****************************************" << endl << endl;
}

/**
 * @brief Displays the rules and details of the game.
 * @param none
 * @return none
 */
void displayInfo() {
    cout << "Here are the rules and details for our version of Hangman:" << endl;
    cout << "1. All words used in this game will be 5 characters in length." << endl;
    cout << "2. A word will be randomly selected from a list of 4000 possible words." << endl;
    cout << "3. You will have 5 blank spaces to fill with your guesses for the letters." << endl;
    cout << "4. Since the stickman has 7 parts, you will have 7 guesses to correctly guess the random word." << endl;
    cout << "5. For every incorrect guess, a portion of the stickman's body will be drawn." << endl;
    cout << "6. The game ends when you correctly guess the word or the stickman is fully drawn." << endl;
}
/**
 * @brief Displays the 2D array that represents the hangman and the gallows.
 * @param board The 2D array that contains the hangman and the gallows.
 * @return none
 */
void displayHangman(char board[7][10]) {
    cout << endl;

    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 10; y++) {
            cout << board[x][y];
        }
        cout << endl;
    }
}

/**
 * @brief Determines and returns valid character guesses from user input.
 * @param none
 * @return The valid character guess given by the user.
 */
char getValidCharacterGuess() {
    string playerInput = "";

    while (true) {
        getline(cin, playerInput);

        if (playerInput.size() == 1 && isalpha(playerInput[0])) {
            return tolower(playerInput[0]);
        }
        else {
            cout << "Please enter one character that is a letter: ";
        }
    }
}

/**
 * @brief Determines if the given word contains the given character.
 * @param word A string that represents the randomly selected word.
 * @param guess A char that represents the guess given by the user.
 * @return True if the string contains the character, false otherwise.
 */
bool containsGuess(string word, char guess) {
    for (unsigned long i = 0; i < word.length(); i++) {
        if (word[i] == guess) {
            return true;
        }
    }

    return false;
}