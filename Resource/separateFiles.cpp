#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void addEndLineToFile();
void seperateFileBasedOnDifficulty();
void takeFirsStringOfALine();

int main()
{
    // addEndLineToFile();
    seperateFileBasedOnDifficulty();
    // takeFirsStringOfALine();
    return 0;
}

void addEndLineToFile()
{
    string fileName = "job.txt";   // chỉ cần thay đổi tên file ở đây 
    ifstream inFile(fileName);
    string newFileName = "new_job.txt";    // và ở đây 
    ofstream outFile(newFileName);

    if (!inFile.is_open())
        cout << "Error";
    else
    {
        string str;
        while(inFile >> str)
        {
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            outFile << str << endl;
        }
    }

    inFile.close();
    outFile.close();
}

void seperateFileBasedOnDifficulty()
{
    string originalFileName = "job.txt";
    ifstream inFile(originalFileName);

    string easyFileName = "job_easy.txt";
    ofstream myFileEasy(easyFileName);

    string mediumFileName = "job_medium.txt";
    ofstream myFileMedium(mediumFileName);

    string hardFileName = "job_hard.txt";
    ofstream myFileHard(hardFileName);

    if (!inFile.is_open())
        cout << "Error";
    else
    {
        string str;
        while (inFile >> str)
        {
            if (str.length() <= 4)  //những từ có ít hơn 4 kí tự được xếp vào loại dễ
                myFileEasy << str << endl;
            if (str.length() == 5 || str.length() == 6) // 5, 6 kí tự thuộc loại trung bình 
                myFileMedium << str << endl;
            if (str.length() >= 7)                  // nhiều hơn 7 kí tự thuộc loại khó 
                myFileHard << str << endl;
        }
    }
}

void takeFirsStringOfALine()
{
    string oldFile = "1.txt";
    string newFileName = "2.txt";
    ifstream inFile(oldFile);
    ofstream outFile(newFileName);

    if (!inFile.is_open())  
        cout << "Error";
    else 
    {
        while (!inFile.eof())
        {
            string line;
            getline(inFile, line);
            string str;
            int index = 0;
            do 
            {
                char ch = line[index];
                str = str + ch;
                index++;
            }
            while (line[index] != ' ' && line[index] != ':');
            outFile << str << endl;
        }
    }
}