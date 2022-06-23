#pragma once

#include <iostream> 

using namespace std;

extern string TOPIC, DIFFICULTY;
extern int intDifficulty;
extern int hintLimit[];

string getWord();
char getUserGuesses();
void update(string& guessedWord, const string& word, char guess);
bool guessIsRight(const char& aGuess, const string& word);
bool userPlayAgain();
void getHint(const string& word, string& guessedWord, int& hintCount);
void processScore(const std::chrono::duration<float> &duration, int &highestScore, const string &word, const int& hintCount);