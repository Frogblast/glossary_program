#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

bool accepted = false;
bool running = true;
const int mapSize = 2;

void giveFeedback(string correctAnswer);

void countMatchingLetters(int correctLength, const std::pair<const std::__cxx11::string, std::__cxx11::string> &pair, std::__cxx11::string &answer, int &correctLetters);

void gameLoop(std::unordered_map<std::__cxx11::string, std::__cxx11::string> &glossaryMap);

int main()
{

    // Create hashmap with words
    // TODO: Read from a text-file
    fstream txtFile;
    txtFile.open("./glossaryList.txt");
    
    // Create an unordered_map with int keys and string values
    unordered_map<string, string> glossaryMap;

    glossaryMap["Czesc"] = "Hej";
    glossaryMap["Slowo"] = "Ord";

    /*    std::cout << "HashMap contents:" << std::endl;
   for (const auto &pair : glossaryMap)
       {
           cout << "Key: " << pair.first << " Value: " << pair.second << endl;
       } */

    gameLoop(glossaryMap);
    return 0;
}

void gameLoop(std::unordered_map<std::__cxx11::string, std::__cxx11::string> &glossaryMap)
{
    cout<<"Type the translation of the given word and hit enter.\n\t Answer \"q\" to quit the program."<< endl;
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

            giveFeedback(pair.second);

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

void giveFeedback(string correctAnswer)
{
    // If correct (some % of correct letters) then congratulate, if not show the correct translation.
    if (accepted)
    {
        cout << "Good job" << endl;
    }
    else
    {
        cout << "The correct answer is: " << correctAnswer << endl;
    }
}