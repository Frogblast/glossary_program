#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib> // For system("clear") or system("cls")

using namespace std;

bool accepted = false;
bool running = true;
const int mapSize = 2;

void giveFeedback(string word, string translation);

void countMatchingLetters(int correctLength, const std::pair<const std::__cxx11::string, std::__cxx11::string> &pair, std::__cxx11::string &answer, int &correctLetters);

void gameLoop(std::unordered_map<std::__cxx11::string, std::__cxx11::string> &glossaryMap);

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

    string fileAsOneBigString((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

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

    // Create an unordered_map with int keys and string values
    unordered_map<string, string> glossaryMap;

    for (size_t i = 0; i < words.size(); i += 2)
    {
        glossaryMap[words[i]] = words[i + 1];
    }

    gameLoop(glossaryMap);
    return 0;
}

void gameLoop(std::unordered_map<std::__cxx11::string, std::__cxx11::string> &glossaryMap)
{
    clearConsole();

    cout << "Type the translation of the given word and hit enter.\n\t Answer \"q\" to quit the program." << endl;
    while (running)
    {
        string answer;
        int correctLetters;
        accepted = false;

        // Show next word to be translated
        for (const auto &pair : glossaryMap)
        {
            cout << "The next word is: " << pair.first << endl;
            cout << "Enter the swedish translation \n"
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

            int correctWordLength = pair.second.length();

            countMatchingLetters(correctWordLength, pair, answer, correctLetters);

            float correctnessRatio = static_cast<float>(correctLetters) / correctWordLength;

            accepted = correctnessRatio > 0.6f;

            giveFeedback(pair.first, pair.second);

            // Go back to showing of the next word.
        }
    }
}

void countMatchingLetters(int correctWordLength, const std::pair<const std::__cxx11::string, std::__cxx11::string> &pair, std::__cxx11::string &answer, int &correctLetters)
{
    for (int i = 0; i < correctWordLength; i++)
    {
        bool equalLetters = pair.second[i] == answer[i];
        if (equalLetters)
        {
            correctLetters++;
        }
    }
}

void giveFeedback(string word, string translation)
{
    // If correct (some % of correct letters) then congratulate, if not show the correct translation.
    if (accepted)
    {
        cout << "CORRECT!\n" << endl;
    }
    else
    {
        cout << "WRONG! The translation of: " << word << ", is: " << translation << "\n" << endl;
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