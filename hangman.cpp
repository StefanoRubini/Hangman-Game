#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>

#include "hangmanFunctions.h"

using namespace std;

int main() {
    unordered_map<int, string> words; // used to store all possible words of length 5
    multimap<char, int> charPositions; // used to store position of characters in a word
    ifstream wordsInputFile; // used to open "words.txt" that contains all words of length 5
    string currentWord = ""; // used to parse the words contained in "words.txt"
    int position = 1; // used to associate positions with the words for random selection
    int randomNumber = 0; // used to store a randomly generated number between 1 and 4000
    string randomWord = ""; // used to store a random word selected by using the random number
    char board[7][10] = { // used to represent the hangman and the gallows
        {' ', ' ', '+', '-', '-', '-', '-', ' ', ' ', ' '},
        {' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'_', '_', '|', '_', '_', '_', '_', '_', '_', '_'}
    };

    wordsInputFile.open("words.txt");

    // check if the input file was opened successfully and return 0 if the file fails to open
    if (!wordsInputFile.is_open()) {
        cout << "Error: Unable to open input file" << endl;
        return 0;
    }

    /*
    if the input file was opened successfully, go ahead and parse the entire input file using the
    opened file stream, take the current word and store it into "currentWord" and then insert the
    word into "words[]", using the position of the word in the file as the "key" and the word
    itself as the "value"
    */
    while (wordsInputFile >> currentWord) {
        words[position] = currentWord;
        position++;
    }

    wordsInputFile.close();

    displayHeader();
    displayInfo();

    // generate a random number between 1 and 4000 in order to pick a random word
    srand(time(0));
    randomNumber = (rand() % 4000) + 1;
    
    // pick a random word from the list of words using "randomNumber" as the position
    randomWord = words[randomNumber];

    cout << "The random word: " << randomWord << endl;

    // go through all of the characters contained in the random word and associate the characters
    // with their positions within the string, as this will make it easier to display correct
    // character guesses in their correct spots
    for (unsigned long i = 0; i < randomWord.length(); i++) {
        charPositions.insert({randomWord[i], i});
    }

    int remainingGuesses = 7; // there are 7 guesses as the stickman has 7 body parts to draw
    bool isWordGuessed = true; // used to track if the user correctly guessed the random word
    char characterGuess = ' '; // used to store the character guessed by the user
    string currentGuessedCharacters = "_____"; // used to display the correct character guesses

    displayHangman(board);

    do {
        // if the random word and guessed word are the same, the user has successfully guessed the word
        if (randomWord == currentGuessedCharacters) {
            isWordGuessed = true;
            break;
        }

        cout << "Enter a character to see if the word contains it: ";

        // check if the user is entering valid input, which means only single characters that are
        // letters, and continue to reprompt for valid input until it is given
        characterGuess = getValidCharacterGuess();

        // check if the user provided a character that is contained in the random word
        if (containsGuess(randomWord, characterGuess)) {            
            // retrieve the position for the provided character so we can insert it into the
            // "currentGuessedCharacters" string at the correct position
            auto itr = charPositions.find(characterGuess);
            
            /*
            if the user happens to provide a character that does appear in the random word BUT it
            does NOT exist in "charPositions<>", then this means that they have guessed this character
            before, as we remove correct guesses from the map once they are made
            */
            if (itr == charPositions.end()) {
                cout << "This character has been guessed before, please make another choice." << endl << endl;
                continue;
            }

            /*
            the user provided a character that does appear in the random word, so we go ahead and
            continuously retrieve all possible positions in which we insert the provided character
            into "currentGuessedCharacters", and we use a while loop to accomplish this, as it will
            run for as long as the retrieved iterator containing the character positions is valid.
            once the iterator is no longer valid, this character cannot be guessed in later rounds
            */
            else {
                cout << "Correct guess! The random word contains this character!" << endl;

                while (itr != charPositions.end()) {
                    currentGuessedCharacters[itr->second] = itr->first;
                    charPositions.erase(itr);
                    itr = charPositions.find(characterGuess);
                }
            }
            
            displayHangman(board);
        }
        // the user provided a character that is NOT contained in the random word
        else {
            remainingGuesses--;

            cout << "Incorrect guess! Remaining guesses: " << remainingGuesses << endl;

            // add head (for the first incorrect guess)
            if (remainingGuesses == 6)
                board[1][6] = 'O';
            // add body (for the second and third incorrect guesses)
            if (remainingGuesses == 5)
                board[2][6] = '|';
            if (remainingGuesses == 4)
                board[3][6] = '|';
            // add arms (for the fourth and fifth incorrect guesses)
            if (remainingGuesses == 3)
                board[2][5] = '/';
            if (remainingGuesses == 2)
                board[2][7] = '\\';
            // add legs (for the sixth and seventh incorrect guesses)
            if (remainingGuesses == 1)
                board[4][5] = '/';
            if (remainingGuesses == 0) {
                board[4][7] = '\\';
                isWordGuessed = false;
            }

            displayHangman(board);
        }

        cout << "Correctly Guessed Characters: " << currentGuessedCharacters << endl;
    } while(remainingGuesses > 0 || isWordGuessed);

    if (isWordGuessed) {
        cout << endl << "Congratulations, you have correctly guessed the random word!" << endl;
        cout << "The random word is " << randomWord << " and you had " << 7 - remainingGuesses << " incorrect guesses." << endl;
        cout << "Thank you for playing Hangman, have a wonderful day!" << endl;
    }
    else {
        cout << endl << "Game over. You did not guess the random word correctly." << endl;
        cout << "The random word is: " << randomWord << endl;
        cout << "You guessed the following characters: " << currentGuessedCharacters << endl;
        cout << "Thank you for playing Hangman, have a wonderful day!" << endl;
    }

    return 0;
}