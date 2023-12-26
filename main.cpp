#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
    const string filePath = "./glossaryList.txt";
    ifstream inputFile(filePath);

    if(!inputFile.is_open()){
        cerr<<"Error opening file: " << filePath<< endl;
        return 1;
    }

    string fileAsOneBigString((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    cout<< fileAsOneBigString<< endl;

    // Vector to store words
    vector<string> words;

    // Use std::istringstream to split the string
    istringstream iss(fileAsOneBigString);
    string word;
    int vectorSize = 0;

    // Extract words and store them in the vector
    while (iss >> word) {
        words.push_back(word);
        vectorSize++;
    }


    // Create an unordered_map with int keys and string values
    unordered_map<string, string> glossaryMap;

    for (size_t i = 0; i < vectorSize; i+=2)
    {
        glossaryMap[words[i]] = words[i+1];
        cout<< "added word to map"<< endl;
    }

/*     
    // Display the words in the vector
    cout << "Words in the vector:" << endl;
    for (const auto& w : words) {
        cout << w << endl;
    } */

/*     glossaryMap["Czesc"] = "Hej";
    glossaryMap["Slowo"] = "Ord"; */

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