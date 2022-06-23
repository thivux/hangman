#include <iostream>
#include <vector>
// #include <chrono>
#include <thread>
// #include <cstdlib>
#include <conio.h>
#include "../Header/humanUtility.h"

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
}

string getHangPicture(int badGuessCount)
{
    string picture[] = {
        "",
        "   ------------\n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "-------        ",
        "   ------------\n"
        "   |          |\n"
        "   |          O\n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "-------        ",
        "   ------------\n"
        "   |          |\n"
        "   |          O\n"
        "   |          |\n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "-------        ",
        "   ------------\n"
        "   |          |\n"
        "   |          O\n"
        "   |         /|\n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "-------        ",
        "   ------------\n"
        "   |          |\n"
        "   |          O\n"
        "   |         /|\\\n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "-------        ",
        "   ------------\n"
        "   |          |\n"
        "   |          O\n"
        "   |         /|\\\n"
        "   |         / \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "-------        ",
        "   ------------\n"
        "   |          |\n"
        "   |          O\n"
        "   |         /|\\\n"
        "   |         / \\\n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "   |           \n"
        "-------        ",

    };
    return picture[badGuessCount];
}

void renderGame(const string &guessedWord, const int &badGuessCount, const int& hintCount, const string &badGuessString = "")
{
    cout << "Your topic: " << TOPIC << ", your level: " << DIFFICULTY << '\n';
    cout << "Press 1 to  guess full word, 2 to get hint\n";
    cout << "Number of hint left: " << hintLimit[intDifficulty - 1] - hintCount << '\n';
    cout << "\nYour guessed word is: " << guessedWord << "\n";
    cout << "You have made " << badGuessCount << " mistake"
         << (badGuessString.empty() ? "." : "s: ") << badGuessString << '\n'
         << getHangPicture(badGuessCount) << endl;
}

const vector<string> HANGED = {
    "   ------------\n"
    "   |         /\n"
    "   |        O\n"
    "   |       /|\\\n"
    "   |       / \\\n"
    "   |         \n"
    "   |         \n"
    "   |         \n"
    "   |         \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |         /|\\\n"
    "   |         / \\\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        ",
    "   ------------\n"
    "   |           \\\n"
    "   |            O\n"
    "   |           /|\\\n"
    "   |           / \\\n"
    "   |             \n"
    "   |             \n"
    "   |             \n"
    "   |             \n"
    "-------        ",
    "   ------------\n"
    "   |          |\n"
    "   |          O\n"
    "   |         /|\\\n"
    "   |         / \\\n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "   |           \n"
    "-------        "};

void printGameOverInfo(string guessedWord, string word, std::chrono::duration<float> duration, int& highestScore, const int& hintCount)
{
    if (guessedWord != word)
    {
        int n = 0;
        while (!kbhit())
        {
            clearScreen();
            cout << "Game Over!!! You are hanged\n" << "The correct word is " << word << '\n';
            cout << HANGED[n];
            cout << "\nPress any key to exit" << endl;
            n = (n + 1) % HANGED.size();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        char dummy = getch();
    }
    else
    {
        cout << "Congrats!!! You are free\n";
        cout << "It took you " << duration.count() << "s to complete the game\n";
        processScore(duration, highestScore, word, hintCount);
    }
}