/*
TODO:
Support for swedish and polish letters.
Make everything lower-case by default.
*/

// -*- coding: utf-8 -*-


#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib> // For system("clear") or system("cls")
#include <random>

using namespace std;

bool accepted = false;
bool running = true;

// Function to provide feedback based on correctness
bool giveFeedback(string word, string translation);

// Main game loop
void gameLoop(unordered_map<string, string> &glossaryMap);

void countMatchingLetters(const string &word, const string &answer, int &correctLetters);

// Function to clear the console screen
void clearConsole();

int main()
{
    // Create hashmap with words
    const string filePath = "./glossaryList.txt";
    ifstream inputFile(filePath);

    if (!inputFile.is_open())
    {
        cerr << "Error opening file: " << filePath << endl;
        return 1;
    }

    // Read file content into a single string
    string fileAsOneBigString((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Explictly close the input file since we are done with it
    inputFile.close();

    // Vector to store words
    vector<string> words;

    // Use std::istringstream to split the string
    istringstream iss(fileAsOneBigString);
    string word;

    // Extract words and store them in the vector
    while (iss >> word)
    {
        words.push_back(word);
    }

    // Create an unordered_map with string keys and string values
    unordered_map<string, string> glossaryMap;

    // Populate the map with words and their translations
    for (size_t i = 0; i < words.size(); i += 2)
    {
        glossaryMap[words[i]] = words[i + 1];
    }

    // Start the game loop
    gameLoop(glossaryMap);

    return 0;
}

void gameLoop(unordered_map<string, string> &glossaryMap)
{
    clearConsole();

    cout << "Type the translation of the given word and hit enter.\n\t Answer \"q\" to quit the program." << endl;
    while (running && !glossaryMap.empty())
    {
        string answer;
        int correctLetters;
        accepted = false;
        cout << "next round" << endl;

        // Stores a random value between 0 and current size of the map.
        int randomIndex = rand() % glossaryMap.size();

        auto it = next(begin(glossaryMap), randomIndex);

        cout << "Remaining words: " << glossaryMap.size() << "\n"
             << endl;
        cout << "The next word is: " << it->first << endl;
        cout << "Enter the Swedish translation \n"
             << endl;
        cin >> answer;
        clearConsole();

        if (answer == "q")
        {
            running = false;
            break;
        }

        accepted = false;
        correctLetters = 0;

        int correctWordLength = it->second.length();

        // Count the number of matching letters

        countMatchingLetters(it ->second, answer, correctLetters);

        float correctnessRatio = static_cast<float>(correctLetters) / correctWordLength;

        // Determine if the answer is accepted and provide feedback
        accepted = correctnessRatio > 0.6f;

        // Display feedback
        if (giveFeedback(it->first, it->second))
        {
            glossaryMap.erase(it->first);
        }

        // Go back to showing the next word.
    }
}

void countMatchingLetters(const string &word, const string &answer, int &correctLetters)
{
    for (int i = 0; i < word.length(); i++)
    {
        bool equalLetters = word[i] == answer[i];
        if (equalLetters)
        {
            correctLetters++;
        }
    }
}

bool giveFeedback(string word, string translation)
{
    // If correct (some % of correct letters) then congratulate, if not show the correct translation.
    if (accepted)
    {
        cout << "CORRECT!\n"
             << endl;
        return true;
    }
    else
    {
        cout << "WRONG! The translation of: " << word << ", is: " << translation << "\n"
             << endl;
        return false;
    }
}

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}