#pragma once

#include <iostream>
#include <chrono>

using namespace std;

void renderGame(const string &guessedWord, const int &numberOfWrongGuesses, const int& hintCount, const string &stringOfWrongGuesses = "");
void printGameOverInfo(string guessedWord, string word, std::chrono::duration<float> duration, int& highestScore, const int& hintCount);
void clearScreen();
