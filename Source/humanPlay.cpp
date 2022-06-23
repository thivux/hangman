#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "../Header/humanDisplay.h"
#include "../Header/humanUtility.h"

using namespace std;

const int MAX_BAD_GUESS = 7;

int highestScore = 0;

void humanPlay()
{
    do
    {
        clearScreen();
        string word = getWord();
        string guessedWord(word.length(), '-');
        int badGuessCount = 0;
        string badGuessString;
        int hintCount = 0;

        auto startTime = std::chrono::high_resolution_clock::now();
        do
        {
            clearScreen();
            renderGame(guessedWord, badGuessCount, hintCount, badGuessString);
            char guess = getUserGuesses();
            if (guess == '1' || guess == '2')
            {
                if (guess == '1')
                {
                    cout << "Your full guess: ";
                    cin >> guessedWord;
                    break;
                }
                else
                    getHint(word, guessedWord, hintCount);
            }
            else if (guessIsRight(guess, word))
                update(guessedWord, word, guess);
            else
            {
                badGuessCount++;
                badGuessString += guess;
            }
        } while (guessedWord != word && badGuessCount < MAX_BAD_GUESS);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = endTime - startTime;

        clearScreen();
        renderGame(guessedWord, badGuessCount, hintCount);
        printGameOverInfo(guessedWord, word, duration, highestScore, hintCount);

    } while (userPlayAgain());
}