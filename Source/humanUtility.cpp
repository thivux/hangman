#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

vector<string> VOCABULARY;
const int MAX_TOPIC = 5;
const int MAX_DIFFICULTY = 3;
string topicArr[MAX_TOPIC] = {"Animal", "Food", "Job", "Sport", "Travel"};
string difficultyArr[MAX_DIFFICULTY] = {"Easy", "Medium", "Hard"};
int timeLimit[MAX_DIFFICULTY] = {60, 90, 120};
int hintLimit[MAX_DIFFICULTY] = {1, 2, 3};
string TOPIC, DIFFICULTY;
int intTopic, intDifficulty;

// GET INPUT
char getUserGuesses()
{
    cout << "Give a guess: ";
    char aGuess;
    cin >> aGuess;
    cout << endl;
    return tolower(aGuess);
}

void getTopicFromUser()
{
    TOPIC = "";
    string answer;
    cout << "Choose topic: " << endl;
    for (int i = 0; i < MAX_TOPIC; i++)
        cout << i + 1 << ". " << topicArr[i] << endl;
    cout << "Your choice: ";
    while (TOPIC == "")
    {
        getline(cin, answer);
        if (answer.length() > 1) // khi user nhập một string từ 2 kí tự trở lên
        {
            cout << "\nInvalid choice!\n";
            cout << "Choose again: ";
        }
        else
        {
            intTopic = answer[0] - 48;
            if (intTopic > 0 && intTopic <= MAX_TOPIC)
                TOPIC = topicArr[intTopic - 1];
            else
            {
                cout << "\nInvalid choice! 2\n";
                cout << "Choose again: ";
            }
        }
    }
}

void getDifficultyFromUser()
{
    DIFFICULTY = "";
    string answer;
    cout << "Choose difficulty: " << endl;
    // for (int i = 0; i < MAX_DIFFICULTY; i++)
    //     cout << i + 1 << ". " << difficultyArr[i] << endl;
    cout << "1. Easy (you have 1 hint and 60s to play)\n";
    cout << "2. Medium (you have 2 hints and 90s to play)\n";
    cout << "3. Hard (you have 3 hints and 120s to play)\n";
    cout << "Your choice: ";

    while (DIFFICULTY == "")
    {
        getline(cin, answer);
        if (answer.length() > 1) // khi user nhập một string từ 2 kí tự trở lên
        {
            cout << "\nInvalid choice!\n";
            cout << "Choose again: ";
        }
        else
        {
            intDifficulty = answer[0] - 48;
            if (intDifficulty > 0 && intDifficulty <= MAX_DIFFICULTY)
                DIFFICULTY = difficultyArr[intDifficulty - 1];
            else
            {
                cout << "\nInvalid choice!\n";
                cout << "Choose again: ";
            }
        }
    }
}

// UPDATE
bool guessIsRight(const char &aGuess, const string &word)
{
    return (word.find(aGuess) != string::npos); // hàm find tìm vị trí của aGuess trong word
}

void update(string &guessedWord, const string &word, char guess)
{
    int n = guessedWord.length();
    for (int i = 0; i < n; i++)
    {
        if (word[i] == guess)
            guessedWord[i] = guess;
    }
}

void processScore(const std::chrono::duration<float> &duration, int &highestScore, const string &word, const int &hintCount)
{
    if (duration.count() >= timeLimit[intDifficulty - 1])
    {
        cout << "Time limit exceeded, no score for you.\n";
    }
    else
    {
        int score = 1000 * (word.length() - hintCount) / (duration.count() * 0.25);
        cout << "Your score is: " << score << '\n';
        if (score > highestScore)
        {
            highestScore = score;
            cout << "This is your highest score!\n";
        }
    }
}

bool userPlayAgain()
{
    cout << "\nWanna play again? (y/n): ";
    char answer;
    cin >> answer;
    cin.ignore(1);
    if (answer == 'y' || answer == 'Y')
        return true;
    else
        return false;
}

// GENERATE WORD
int generateRandomNumber(int limit)
{
    // int maxNumber = VOCABULARY.size();
    srand(time(0));
    int randomNumber = rand() % limit;
    return randomNumber;
}

string normalizeWord(const string &str)
{
    string newStr = str;
    transform(str.begin(), str.end(), newStr.begin(), ::tolower);
    return newStr;
}

string getFileName()
{
    getTopicFromUser();
    cout << endl;
    getDifficultyFromUser();
    return normalizeWord(TOPIC) + '_' + normalizeWord(DIFFICULTY) + ".txt";
}

void getVocabularyList()
{
    string chosenFile = "../Resource/" + getFileName();
    ifstream myFile(chosenFile);

    if (!myFile.is_open())
        cout << "Error opening text file";

    while (!myFile.eof())
    {
        string line;
        myFile >> line;
        VOCABULARY.push_back(line);
    }
    myFile.close();
}

string getWord()
{
    getVocabularyList();
    string str = VOCABULARY[generateRandomNumber(VOCABULARY.size())];
    string newStr = normalizeWord(str);
    return newStr;
}

// GET HINT
void getHint(const string &word, string &guessedWord, int &hintCount)
{
    if (hintCount >= hintLimit[intDifficulty - 1])
    {
        cout << "Hint limit exceeded!";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        return;
    }
    hintCount++;
    int index = 0;
    while (guessedWord[index] != '-')
        index++;
    guessedWord[index] = word[index];
}
