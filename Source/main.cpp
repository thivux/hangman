#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "../Header/machinePlay.h"
#include "../Header/humanPlay.h"
#include "../Header/humanDisplay.h"

/* g++ main.cpp guesser.cpp humanDisplay.cpp humanPlay.cpp 
    humanUtility.cpp machinePlay.cpp machineDisplay.cpp machineUtility.cpp
*/
using namespace std;

int main()
{
   string option;
   do
   {
       clearScreen();
       cout << "Choose option: \n"
            << "1. You guess, computer generates words.\n"
            << "2. Computer guesses, you generate words.\n"
            << "3. Exit." << endl;
        cout << "Your choice: ";
        getline(cin, option);
        char optionChar = option[0] - 48;
        try
        {
            if (option.length() != 1)
                throw "Invalid choice";
            if (optionChar < 1 || optionChar > 3)
                throw "Invalid choice";
            if (optionChar == 1)
                humanPlay();
            if (optionChar == 2)
                machinePlay();
            if (optionChar == 3) 
                break;
        }
        catch(const char* message)
        {
            cout << "Error: " << message << endl;   
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        
   }
   while (true);

    return 0;
}