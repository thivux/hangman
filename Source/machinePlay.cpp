#include <iostream>
#include <set>
#include <cctype>
#include <algorithm>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <conio.h>
#include <string>

#include "../Header/machineUtility.h"
#include "../Header/guesser.h"
#include "../Header/machineDisplay.h"
#include "../Header/humanUtility.h"

using namespace std;

#define MAX_GUESSES 7

// Yêu cầu người chơi nhập độ dài từ mà họ nghĩ ra
int getUserWordLength()
{
    clearScreen();
    int wordLength;
    while (true)
    {
        cout << "\nEnter your word length: ";
        string answer;
        cin >> answer;
        try
        {
            for (int i = 0; i != answer.length(); i++)
                if (answer[i] < 48 || answer[i] > 57)
                    throw "Invalid choice.";
                wordLength = stoi(answer);
                break;
        }

        catch (const char *message)
        {
            cout << message << endl;
        }
    }
    return wordLength;
}

// Khởi tạo giá trị ban đầu cho các biến
void initialize(int &wordLength, string &secretWord, int &incorrectGuess, set<char> &previousGuesses, bool &stop)
{
    wordLength = getUserWordLength();     // độ dài từ
    secretWord = string(wordLength, '-'); // từ mà máy đang đoán được
    incorrectGuess = 0;                   // số từ máy đoán sai
    previousGuesses = set<char>();        // những từ mà máy đã đoán
    stop = false;                         // điều kiện dừng
}

// Yêu cầu người chơi nhập mask sau mỗi lượt máy đoán một chữ cái
string getUserAnswer(char guess)
{
    string answer;
    cout << endl
         << "I guess " << guess << ", please enter your mask: ";
    cin >> answer;
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower); // đề phòng trường hợp người chơi nhập chữ cái in hoa
    return answer;
}

// Kiểm tra mask mà người chơi nhập có hợp lệ hay không
bool isGoodMask(char guess, const string &mask, const string &secretWord)
{
    if (mask.length() != secretWord.length()) // nếu độ dài mask khác độ dài người chơi nhập ban đầu
        return false;
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-') // nếu có một kí tự trong mask không phải dấu -
        {
            if (mask[i] != guess) // kí tự đó phải trùng với guess
                return false;
            if (secretWord[i] != '-' && secretWord[i] != mask[i]) // secretWord[i] phải là dấu ngạch hoặc phải bằng mask[i]
                return false;                                     // thực ra điều kiện hoặc bằng mask[i] này hơi thừa vì máy sẽ không đoán lại những kí tự
                                                                  // đã được đoán trước đó mà
        }
    return true;
    /*
        vậy có các trường hợp mà mask không tốt là: 
        * độ dài không đúng
        * kí tự mà người chơi gợi ý không phải kí tự máy đang đoán 
        * kí tự mà người chơi gợi í ở vị trí i mà secretWord[i] đã được reveal trước đó rồi, giờ chẳng lẽ ghi đè lên à 
    */
}

// Nếu nhận được mask tốt rồi thì update secretWord
void updateSecretWord(const string &mask, string &secretWord)
{
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-')
            secretWord[i] = mask[i];
}

// Xử lý tất cả mọi thứ sau khi người chơi đưa ra mask
void update(char guess, const string &mask, int &incorrectGuess, set<char> &previousGuesses, string &secretWord, bool &stop)
{
    // đầu tiên cần kiểm tra mask: nếu mask không tốt, ném ngoại lệ
    if (!isGoodMask(guess, mask, secretWord))
        throw invalid_argument("Invalid mask, try again"); // sau khi ném ngoại lệ, tất cả code phần sau sẽ không được thực thi

    // insert guess hiện tại vào set những kí tự đã đoán
    previousGuesses.insert(guess); // note: nếu mask người chơi đưa ra không đúng thì guess hiện tại không được đưa vào set kí tự đã đoán

    if (isAllDash(mask)) // nếu mask toàn là - nghĩa là guess hiện tại sai rồi
    {
        incorrectGuess++;                  // tăng biến đếm số lần đoán sai
        if (incorrectGuess == MAX_GUESSES) // kiểm tra số lần đoán sai đã đạt giới hạn chưa
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            stop = true;
        }
    }
    else
    {
        updateSecretWord(mask, secretWord); // nếu mask có kí tự khác - thì update secretWord aka từ máy đang đoán được
        if (isAllNotDash(secretWord))       // update secretWord xong thì kiểm tra xem nó đã thành một từ hoàn chỉnh chưa
            stop = true;
    }

    /*
        điều kiện dừng: 
        * số lần đoán sai đạt giới hạn
        * máy đã đoán được một từ hoàn chỉnh 
    */
}

// In ra số lần đoán sai, kí tự đã đoán, từ máy đang đoán được và vẽ hình hangman
void render(int incorrectGuess, const set<char> &previousGuesses, const string &secretWord)
{
    clearScreen();
    cout << "\nIncorrect guess = " << incorrectGuess
         << "\nPrevious guesses = ";
    for (char c : previousGuesses)
        cout << c;
    cout << "\nSecretWord = " << secretWord << '\n';
    cout << getDrawing(incorrectGuess) << endl;
}

// Khi điều kiện dừng thỏa mãn, hiển thị animation hanged man hoặc dancing man
void playAnimation(bool isLosing, const string &word)
{
    clearScreen();
    if (isLosing)
    {
        while (!kbhit())
        {
            clearScreen();
            cout << "\nI lost :(. My best word is: " << word << endl;
            cout << getNextHangman();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        char dummy = getch();
        askUserWord();
    }
    else
    {
        while (!kbhit())
        {
            clearScreen();
            cout << "\nHaha, I win :D. The word is: " << word << endl;
            cout << getNextStandingman();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        char dummy = getch();
    }
}

void machinePlay()
{
    int wordLength;
    string secretWord;
    int incorrectGuess;
    set<char> previousGuesses;
    bool stop;
    bool gaveUp = false;

    do
    {
        initialize(wordLength, secretWord, incorrectGuess, previousGuesses, stop);
        do
        {
            render(incorrectGuess, previousGuesses, secretWord);
            char guess = getNextGuess(previousGuesses, secretWord);
            if (guess == 0)
            {
                cout << "I give up, hang me\n";
                askUserWord();
                gaveUp = true;
                // std::this_thread::sleep_for(std::chrono::milliseconds(30000));
                break;
            }

            do
            {
                try
                {
                    string mask = getUserAnswer(guess);
                    update(guess, mask, incorrectGuess, previousGuesses, secretWord, stop);
                    break; // nếu mask không hợp lệ, dòng lệnh này sẽ không được kích hoạt và vòng do while
                           // vẫn tiếp tục, yêu cầu người chơi nhập mask
                }
                catch (invalid_argument e)
                {
                    cout << "Invalid mask, try again" << endl;
                }
            } while (true);
        } while (!stop);
        if (!gaveUp)
            playAnimation(incorrectGuess == MAX_GUESSES, secretWord);
    } while (userPlayAgain());
}
