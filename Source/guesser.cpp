#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <set>
#include <bits/stdc++.h>
// #include <string>
// #include "../Header/guesser.h"
#include "../Header/machineUtility.h"

using namespace std;

// tạo wordList từ file dictionary
static vector<string> wordList = readWordListFromFile("../Resource/dictionary.txt");

set<char> getRemainingChars(const set<char> &previousGuesses)
{
    set<char> remainingChars;
    for (char c = 'a'; c <= 'z'; c++)
        remainingChars.insert(c);
    for (char c : previousGuesses)
        remainingChars.erase(c);
    return remainingChars;
}

char selectRandomChar(const set<char> &s)
{
    int r = rand() % s.size();
    set<char>::iterator it = s.begin();
    for (; r != 0; r--)
        it++;
    return *it;
}

char getVowelGuess(const set<char> &remainingChars)
{
    char vowel[] = {'e', 'a', 'o', 'i', 'u', 'y'};
    for (char c : vowel)
    {
        // nếu một kí tự nguyên âm chưa được đoán thì chọn nó luôn 
        if (remainingChars.find(c) != remainingChars.end()) 
            return c;
    }
    return 0;
}

bool isSuitableWord(const string &word, const string &secretWord, const set<char> &remainingChars)
{
    // độ dài không phù hợp -> loại
    if (word.length() != secretWord.length())
        return false;

    // kiểm tra những từ có độ dài phù hợp 
    for (unsigned int i = 0; i < word.length(); i++)
    {
        if (secretWord[i] != '-')   // kiểm tra những kí tự đã được reveal trong secretWord
        {
            if (tolower(word[i]) != tolower(secretWord[i]))     // nếu chúng khác với kí tự ở vị trí tương ứng trong word -> loại
                return false;
        }
        else if (remainingChars.find(word[i]) == remainingChars.end())  // nếu word mang một kí tự đã được đoán sai -> loại 
            return false;
    }
    return true;
}

// Trả về một vector các từ có dài trùng với secretWord được lọc từ wordList
vector<string> getSuitableWords(const vector<string> &wordList, const string &secretWord, const set<char> &remainingChars)
{
    vector<string> result;
    for (const string &word : wordList)
        if (isSuitableWord(word, secretWord, remainingChars))
            result.push_back(word);
    return result;
}

// Đếm số lần xuất hiện các chữ cái chưa đoán và lưu vào một map
map<char, int> getOccurenceCount(const set<char> &remainingChars, const vector<string> &wordList)
{
    map<char, int> count;
    for (char c : remainingChars)
        count[c] = 0;

    for (const string &word : wordList) // với mỗi từ trong wordList
    {
        for (char c : word)     // kiểm tra từng kí tự của nó
        {
            if (count.find(c) != count.end())   // nếu kí tự đó ở trong list remainingChar thì tăng đếm lên 1 
                count[c]++;
        }
    }
    return count;
}

// Trả về chữ cái chưa được đoán có tần số xuất hiện nhiều nhất 
char getMaxOccurenceChar(const set<char> &remainingChars, const map<char, int> &count)
{
    char best = 0;
    int best_count = 0;
    for (auto p : count)
        if (p.second > best_count)
        {
            best = p.first;
            best_count = p.second;
        }
    return best;
}

char getNextGuess(const set<char> &previousGuesses, const string &secretWord)
{
    // tạo một set gồm những kí tự chưa được đoán
    set<char> remainingChars = getRemainingChars(previousGuesses);
    if (remainingChars.size() == 0) // nếu set này không chứa kí tự nào thì khỏi đoán, dừng chương trình
        return 0;

    if (isAllDash(secretWord)) // nếu máy chưa đoán đúng kí tự nào, ưu tiên các nguyên âm
        return getVowelGuess(remainingChars);

    // nếu có ít nhất một kí tự đã được đoán thì không ưu tiên nguyên âm nữa mà ưu tiên 
    // tần suất hiện của các kí tự trong những từ có độ dài phù hợp 
    vector<string> filteredWordList = getSuitableWords(wordList, secretWord, remainingChars);
    // for (auto str : filteredWordList)
    //     cout << str << endl;
    map<char, int> occurenceCount = getOccurenceCount(remainingChars, filteredWordList);
    return getMaxOccurenceChar(remainingChars, occurenceCount);
}

void askUserWord()
{
    string str;
    cout << "What is your word? ";
    cin >> str;
    cout << "Thanks!\n";
    // getline(cin, str);
    // if (count(wordList.begin(), wordList.end(), str) == 0)
    wordList.push_back(str);
}
